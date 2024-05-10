/*
* DirectXCommoon.cpp
* DirectX関連の処理
*/

#include "DirectXCommon.h"
#include <cassert>
#include <thread>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

void DirectXCommon::Initialize(WinApp* winApp)
{
	//FPS固定初期化
	InitializeFixFPS();

	//NULL検出
	assert(winApp);

	//メンバ変数に記録
	winApp_ = winApp;

	//デバイスの生成
	InitializeDevice();
	//コマンド関連の初期化
	InitializeCommand();
	//スワップチェーンの初期化
	InitializeSwapchain();
	//レンダーターゲットビューの初期化
	InitializeRenderTargetView();
	//深度バッファの初期化
	InitializeDepthBuffer();
	//フェンスの初期化
	InitializeFence();
}

void DirectXCommon::InitializeDevice()
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	/*デバッグレイヤー・・・デバッグするための層*/
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif

	//DXGIファクトリーの生成
	/*DXGIファクトリー・・・DXGIの各種オブジェクトを生成するクラス*/
	/*DXGI・・・DirectX グラフィックス インフラストラクチャー(基盤となる設備や要素のこと)の略
	アダプターの列挙やスワップチェインの作成等をしてくれる*/
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	//アダプターの列挙用
	/*アダプター・・・直訳すれば「適合させるもの」
	「交流から直流への電流の変換」と「電圧の変換」が主な役割
	ここではグラフィックボードのアダプタのことを指す*/
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter4> tmpAdapter;

	//パフォーマンスが高いものから順に、すべてのアダプターを列挙する
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++) {
		//動的配列に追加する
		adapters.push_back(tmpAdapter);
	}

	//妥当なアダプタを選別する
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		//アダプターの情報を取得する
		adapters[i]->GetDesc3(&adapterDesc);

		//ソフトウェアデバイスを回避
		/*ソフトウェアデバイス・・・ソフトウェアでエミュレーションしているものやオンボードグラフィック*/
		/*エミュレーション・・・ある装置やソフトウェア、システムの挙動を別のソフトウェアなどによって模倣し、代替として動作させること*/
		/*オンボードグラフィック・・・パーソナルコンピュータのマザーボード上に搭載されているグラフィックスコントローラ (GPU) のこと*/
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//デバイスを採用してループを抜ける
			/*デバイス・・・パソコン・タブレット・スマートフォンや、それらと接続して使う装置の総称*/
			tmpAdapter = adapters[i];
			break;
		}
	}

	//対応レベルの配列
	/*対応レベル(機能レベル)・・・明確に定義されたGPU機能のセット*/
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		//採用したアダプターでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(&device));
		if (result == S_OK) {
			//デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}

#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

		//抑制するエラー
		D3D12_MESSAGE_ID denyIds[] = {
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		//抑制する表示レベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		//表示したエラーの表示を抑制する
		infoQueue->PushStorageFilter(&filter);
	}
#endif // _DEBUG

}

void DirectXCommon::InitializeCommand()
{
	//コマンドアロケータを生成
/*コマンドアロケータ・・・コマンドリストに積み込むバッファを確保するオブジェクト*/
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)
	);
	assert(SUCCEEDED(result));

	//コマンドリストを生成
	/*コマンドリスト・・・一連の流れの描画命令をコマンドとして積み込まれたバッファリスト*/
	result = device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(&commandList)
	);
	assert(SUCCEEDED(result));

	//コマンドキューの設定
	/*コマンドキュー・・・コマンドの待ち行列*/
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//コマンドキューを生成
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeSwapchain()
{
	//スワップチェーンの設定
	/*スワップチェーン・・・ダブルバッファリングを簡単に実装する為にDirecctXが用意した仕組み*/
	/*ダブルバッファリング・・・画面や画像を連続的に書き換える際に、描画領域と同じサイズのバッファ領域をメモリ上に2つ用意して、交互に描画処理を行なう手法*/
	swapChainDesc.Width = WinApp::window_width;
	swapChainDesc.Height = WinApp::window_height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//色情報の書式
	swapChainDesc.SampleDesc.Count = 1;//マルチサンプルしない
	/*マルチサンプル・・・空間アンチエイリアシングの一種であり、コンピュータグラフィックスでジャギーを除去するために使用される手法*/
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//バックバッファ用
	/*バックバッファ・・・画面に描画していない方の描画キャンバス*/
	swapChainDesc.BufferCount = 2;//バッファ数を２つに設定
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//IDXGISwapChain1のComPtrを用意
	ComPtr<IDXGISwapChain1> swapChain1;

	//スワップチューンの生成
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(),
		winApp_->GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1);
	assert(SUCCEEDED(result));

	//生成したIDXGISwapChain1のオブジェクトをIDXGISwapChain4に変換する
	swapChain1.As(&swapChain);
}

void DirectXCommon::InitializeRenderTargetView()
{
	//RTV用デスクリプタヒープの設定
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;//裏表の２つ

	backBuffers.resize(swapChainDesc.BufferCount);

	//RTV用デスクリプタヒープの生成
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers.size(); i++) {
		//スワップチェーンからバッファを取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//デスクリプタヒープのハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//裏か表かでアドレスがずれる
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//レンダーターゲットビューの設定
		/*レンダーターゲットビュー・・・バックバッファを描画キャンバスとして扱う為のオブジェクト*/
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//レンダーターゲットビューの生成
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXCommon::InitializeDepthBuffer()
{
	//深度バッファ
	//リソース設定
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = WinApp::window_width;		//レンダーターゲットに合わせる
	depthResourceDesc.Height = WinApp::window_height;	//レンダーターゲットに合わせる
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//デプスステンシル

	//深度値用ヒーププロパティ
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;//深度値1.0f(最大値)でクリア
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット

	//深度バッファ生成
	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,//深度値書き込みに使用
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff)
	);

	//深度バッファビュー用デスクリプタヒープ生成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;//深度ビューは1つ

	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//デプスステンシルビュー
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	//深度バッファビュー生成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);
}

void DirectXCommon::InitializeFence()
{
	//フェンスの生成
	/*フェンス・・・CPUとGPUで同期をとるためのDirecctXの仕組み*/
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

void DirectXCommon::PreDraw()
{
	//バックバッファの番号を取得(2つなので0番か1番)
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	// 1 リソースバリアで書き込み可能に変更
	/*リソースバリア・・・バックバッファを描画できる状態に切り替えたり、描画後にバッファを表示用の状態に戻すコマンド*/

	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get();//バックバッファを指定
	//barrierDesc.Transition.Subresource = bbIndex;
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//表示状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//描画状態へ
	commandList->ResourceBarrier(1, &barrierDesc);

	// 2 描画先の変更
	//レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =
		rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3 画面クリア           R      G     B     A
	FLOAT clearColor[] = { 0.0f, 0.25f, 0.5f, 0.0f };

	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//ビューポート設定コマンド
	/*ビューポート・・・描画領域
	頂点シェーダからの出力座標はビューポートの領域にマッピングされる*/
	D3D12_VIEWPORT viewport{};
	viewport.Width = WinApp::window_width;	//横幅
	viewport.Height = WinApp::window_height;//縦幅
	viewport.TopLeftX = 0;			//左上X
	viewport.TopLeftY = 0;			//左上Y
	viewport.MinDepth = 0.0f;		//最小深度
	viewport.MaxDepth = 1.0f;		//最大深度
	//ビューポート設定コマンドを、コマンドリストに積む
	commandList->RSSetViewports(1, &viewport);

	//シザー矩形
	/*描画領域の絞り込み設定の一種
	その範囲からずれた部分の描画をカットする*/
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;									//切り抜き座標左
	scissorRect.right = scissorRect.left + WinApp::window_width;	//切り抜き座標右
	scissorRect.top = 0;									//切り抜き座標上
	scissorRect.bottom = scissorRect.top + WinApp::window_height;	//切り抜き座標下
	//シザー矩形設定コマンドを、コマンドリストに積む
	commandList->RSSetScissorRects(1, &scissorRect);

}

void DirectXCommon::PostDraw()
{
	//バックバッファの番号を取得
	swapChain->GetCurrentBackBufferIndex();

	// 5 リソースバリアを戻す
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//描画状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;		//表示状態へ
	commandList->ResourceBarrier(1, &barrierDesc);

	//命令のクローズ
	result = commandList->Close();
	assert(SUCCEEDED(result));

	//コマンドリストの実行
	ID3D12CommandList* commandLists[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(1, commandLists);

	//画面に表示するバッファをフリップ(裏表の入替え)
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	//コマンドの実行完了を待つ
	commandQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		if (event != 0) {
			fence->SetEventOnCompletion(fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}

	//FPS固定
	UpdateFixFPS();

	//キューをクリア
	result = commandAllocator->Reset();
	assert(SUCCEEDED(result));
	//再びコマンドリストを貯める準備
	result = commandList->Reset(commandAllocator.Get(), nullptr);
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeFixFPS()
{
	//現在時間を記録する
	reference_ = std::chrono::steady_clock::now();
}

void DirectXCommon::UpdateFixFPS()
{
	// 1/60秒ぴったりの時間
	const std::chrono::microseconds kMinTime(uint64_t(1000000.0f / 60.0f));
	// 1/60秒よりわずかに短い時間
	const std::chrono::microseconds kMinCheckTime(uint64_t(1000000.0f / 65.0f));

	//現在時間を取得する
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	//前回記録からの経過時間を取得する
	std::chrono::microseconds elapsed =
		std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	// 1/60秒(よりわずかに短い時間)経ってない場合
	if (elapsed < kMinCheckTime) {
		// 1/60秒経過するまで微小なスリープを繰り返す
		while (std::chrono::steady_clock::now() - reference_ < kMinTime) {
			//1マイクロ秒スリープ
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	//現在の時間を記録する
	reference_ = std::chrono::steady_clock::now();
}