/*
* WinApp.cpp
* Windows関連の処理
*/

#include "WinApp.h"
#include <imgui_impl_win32.h>
#pragma comment(lib, "winmm.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WinApp* WinApp::GetInstance() {
	static WinApp instance;

	return &instance;
}

//ウィンドウプロシージャ
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ImGui用ウィンドウプロージャ呼び出し
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		/*OS・・・コンピューターを動かすためのソフトウェアのこと
		Operating System オペレーティング システムの略
		コンピューター全体を管理、制御し、人が使えるようにする役割がある*/
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::Initialize()
{
	//システムタイマーの分解度を上げる
	timeBeginPeriod(1);

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;	//ウィンドウプロシージャを設定
	w.lpszClassName = L"DirectXGame";		//ウィンドウクラス名
	/*ウィンドウクラス・・・「どのようなウィンドウを作るかの定義」のこと
	アイコン、メニュー、カーソルなどと、ウィンドウプロシージャが定義されている*/
	w.hInstance = GetModuleHandle(nullptr);	//ウィンドウハンドル
	/*ウィンドウハンドル・・・コンピュータが各ウィンドウに割り振る管理番号
	これを指定することで、コンピュータに該当のウィンドウを認識させる*/
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指名

	//ウィンドウクラスをOSに登録する
	RegisterClassEx(&w);
	//ウィンドウサイズ{X座標 Y座標 横幅 縦幅}
	RECT wrc = { 0, 0, window_width, window_height };
	//自動でサイズを補修する

	HWND hDWnd = GetDesktopWindow();//デスクトップのハンドルを取得
	RECT r;
	GetWindowRect(hDWnd, &r);
	SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(
		w.lpszClassName,//クラス名
		L"Jet Swim",			//タイトルバーの文字
		WS_POPUP,	//標準的なウィンドウスタイル
		CW_USEDEFAULT,			//表示X座標(OSに任せる)
		CW_USEDEFAULT,			//表示Y座標(OSに任せる)
		width,	//ウィンドウ横幅
		height,	//ウィンドウ縦幅
		nullptr,				//親ウィンドウハンドル
		nullptr,				//メニューハンドル	
		w.hInstance,			//呼び出しアプリケーションハンドル
		nullptr);				//オプション

	
	//マウスカーソル非表示
	//ShowCursor(FALSE);

	GetWindowRect(hwnd, &window_rect);
	GetClientRect(hwnd, &client_rect);

	width = 1280;
	height = 720;

	int resize_width = width + ((window_rect.right - window_rect.left) - (client_rect.right - client_rect.left));
	int resize_hight = height + ((window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top));
	SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	SetWindowPos(hwnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, resize_width, resize_hight, SWP_NOMOVE);

	//ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);

}

void WinApp::Update() {
	RECT wrc = { 0, 0, window_width, window_height };
	//マウスカーソルの移動範囲
	ClipCursor(&wrc);
}

void WinApp::ScreenMode(bool full) {
	HWND hDWnd = GetDesktopWindow();//デスクトップのハンドルを取得
	RECT r;
	GetWindowRect(hDWnd, &r);
	
	//int width = EnumDisplayMonitors(NULL, NULL, MyMonitorEnumProc, 0);
	//int height = EnumDisplayMonitors(NULL, NULL, MyMonitorEnumProc, 0);
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
	if (full) {
		width = 1280;
		height = 720;
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
		//ウィンドウを表示状態にする
		ShowWindow(hwnd, SW_SHOW);
	}
	else {
		SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(hwnd, HWND_TOP, r.left, r.top, width, height, SWP_NOZORDER);
		//ウィンドウを表示状態にする
		ShowWindow(hwnd, SW_SHOW);
	}
}

bool WinApp::ProcessMesseage()
{
	MSG msg{};

	//メッセージがある？
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);//キー入力メッセージの処理
		DispatchMessage(&msg);//プロシージャにメッセージを送る
	}

	//×ボタンで終了メッセージが来たらゲームループを抜ける
	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}

void WinApp::Finalize()
{
	//マウスカーソルの制限を解除
	ClipCursor(NULL);
	//ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}