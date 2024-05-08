/*
* WinApp.h
* Windows関連の処理
*/

#pragma once
#include <Windows.h>
#include <DirectXMath.h>

class WinApp final
{
private:
	//コンストラクタ
	WinApp() {};
	//デストラクタ
	~WinApp() {};

public:
	//コピーコンストラクタ無効
	WinApp(const WinApp& winApp) = delete;
	//代入演算子無効
	WinApp& operator=(const WinApp& winApp) = delete;

public://定数
	//ウィンドウサイズ
	static const int window_width = 1520;//横幅
	static const int window_height = 855;//縦幅

public://静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://メンバ関数

	static WinApp* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// スクリーンモードの変更
	/// </summary>
	void ScreenMode(bool full);

	/// <summary>
	/// メッセージの処理
	/// </summary>
	bool ProcessMesseage();

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	//ゲッター
	HWND GetHwnd() const { return hwnd; }
	DirectX::XMFLOAT2 GetMousePos() { return { (float)MousePos.x,(float)MousePos.y }; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

private://メンバ変数
	//ウィンドウハンドル
	HWND hwnd = nullptr;
	//ウィンドウクラスの設定
	WNDCLASSEX w{};

	POINT MousePos;

	int width;
	int height;
};

