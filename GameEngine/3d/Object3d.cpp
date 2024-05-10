/*
* Object3d.cpp
* 3Dオブジェクト一つごとの処理
*/

#include "Object3d.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
const float Object3d::radius = 5.0f;				// 底面の半径
const float Object3d::prizmHeight = 8.0f;			// 柱の高さ
ID3D12Device* Object3d::device_ = nullptr;
UINT Object3d::descriptorHandleIncrementSize = 0;
ID3D12GraphicsCommandList* Object3d::cmdList_ = nullptr;
ComPtr<ID3D12RootSignature> Object3d::rootsignature;
ComPtr<ID3D12PipelineState> Object3d::pipelinestate;
ComPtr<ID3D12DescriptorHeap> Object3d::descHeap;
ComPtr<ID3D12Resource> Object3d::vertBuff;
ComPtr<ID3D12Resource> Object3d::indexBuff;
ComPtr<ID3D12Resource> Object3d::texbuff;
CD3DX12_CPU_DESCRIPTOR_HANDLE Object3d::cpuDescHandleSRV;
CD3DX12_GPU_DESCRIPTOR_HANDLE Object3d::gpuDescHandleSRV;
XMMATRIX Object3d::matView{};
//ViewProjection Object3d::viewProjection;
XMMATRIX Object3d::matProjection{};
XMFLOAT3 Object3d::eye = { 0, 0, -50.0f };
XMFLOAT3 Object3d::target = { 0, 0, 0 };
XMFLOAT3 Object3d::up = { 0, 1, 0 };
D3D12_VERTEX_BUFFER_VIEW Object3d::vbView{};
D3D12_INDEX_BUFFER_VIEW Object3d::ibView{};
std::vector<Model::VertexPosNormalUv> Object3d::vertices;
std::vector<unsigned short> Object3d::indices;
//Object3d::Material Object3d::material;

void Object3d::StaticInitialize(ID3D12Device* device)
{
	// nullptrチェック
	assert(device);

	Object3d::device_ = device;

	//モデルにデバイスをセット
	Model::SetDevice(device);

	// パイプライン初期化
	InitializeGraphicsPipeline();

	// モデル生成
	CreateModel();

}

void Object3d::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	// PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Object3d::cmdList_ == nullptr);

	// コマンドリストをセット
	Object3d::cmdList_ = cmdList;

	// パイプラインステートの設定
	cmdList->SetPipelineState(pipelinestate.Get());
	// ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(rootsignature.Get());
	// プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3d::PostDraw()
{
	// コマンドリストを解除
	Object3d::cmdList_ = nullptr;
}

Object3d* Object3d::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Object3d* object3d = new Object3d();
	if (object3d == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!object3d->Initialize()) {
		delete object3d;
		assert(0);
		return nullptr;
	}

	//スケールをセット
	float scale_val = 1.0f;
	object3d->scaleMax_ = { scale_val, scale_val, scale_val };

	return object3d;
}

void Object3d::InitializeGraphicsPipeline()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/OBJVS.hlsl",	// シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0",	// エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/OBJPS.hlsl",	// シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0",	// エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ // xy座標
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // 法線ベクトル
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // uv座標
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	// グラフィックスパイプラインの流れを設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// サンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	// ラスタライザステート
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	//gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	// デプスステンシルステート
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGA全てのチャンネルを描画
	blenddesc.BlendEnable = true;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	//blenddesc.DestBlend = D3D12_BLEND_ONE;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// ブレンドステートの設定
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// 深度バッファのフォーマット
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	//gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	// 頂点レイアウトの設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状設定（三角形）
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;	// 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[4];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[3].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ルートシグネチャの生成
	result = device_->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
	assert(SUCCEEDED(result));

	gpipeline.pRootSignature = rootsignature.Get();

	gpipeline.BlendState.AlphaToCoverageEnable = true;

	// グラフィックスパイプラインの生成
	result = device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate));
	assert(SUCCEEDED(result));

}

void Object3d::CreateModel()
{

}

void Object3d::UpdateViewMatrix()
{
	// ビュー行列の更新
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

bool Object3d::Initialize()
{
	HRESULT result;
	
	// nullptrチェック
	assert(device_);

	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc2 =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferColor) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));
	assert(SUCCEEDED(result));

	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc2,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB2));
	assert(SUCCEEDED(result));

	//ビュープロジェクション初期化
	//viewProjection_ = viewProjection;

	return true;
}

void Object3d::Update()
{
	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation_.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation_.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation_.y));
	matTrans = XMMatrixTranslation(position_.x, position_.y, position_.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	// 親オブジェクトがあれば
	if (parent != nullptr) {
		// 親オブジェクトのワールド行列を掛ける
		matWorld *= parent->matWorld;
	}

	// 定数バッファへデータ転送
	result = constBuffB0->Map(0, nullptr, (void**)&constMap0);
	constMap0->mat = matWorld * viewProjection_->GetMatrix();	// 行列の合成
	constBuffB0->Unmap(0, nullptr);

	// 定数バッファへデータ転送
	result = constBuffB2->Map(0, nullptr, (void**)&constMapColor);
	constMapColor->color = color_;	// 行列の合成
	constBuffB2->Unmap(0, nullptr);

}

void Object3d::UpdateScale() {
	//スケールにイージングを掛ける
	if (scaleFrame < 1.0f) {
		scaleFrame += 0.025f;
	}
}

void Object3d::Draw()
{
	// nullptrチェック
	assert(device_);
	assert(Object3d::cmdList_);

	//モデルがセットされていなければ描画をスキップ
	if (model_ == nullptr) return;

	// 定数バッファビューをセット
	cmdList_->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	// 定数バッファビューをセット
	cmdList_->SetGraphicsRootConstantBufferView(1, constBuffB2->GetGPUVirtualAddress());

	//モデルを描画
	model_->Draw(cmdList_, 2);
}
