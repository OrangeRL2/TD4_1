/*
* Input.h
* 入力デバイス関連の処理
*/

#pragma once
#include "winApp.h"
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800 //directInputのバージョン指定
#include <dinput.h>
#include <DirectXMath.h>

namespace OogamiEngine {

	//入力
	class Input final
	{
	private:
		//コンストラクタ
		Input() {};
		//デストラクタ
		~Input() {};

	public:
		//コピーコンストラクタ無効
		Input(const Input& input) = delete;
		//代入演算子無効
		Input& operator=(const Input& input) = delete;

		//namespace省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	public://メンバ関数

		//マウスボタンの種類
		enum MouseButton {
			Left,
			Right,
			Wheel,
		};

		static Input* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize(WinApp* winApp);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// キーの押下をチェック
		/// </summary>
		bool PushKey(BYTE keyNumber);

		/// <summary>
		/// キーのトリガーをチェック
		/// </summary>
		bool TriggerKey(BYTE keyNumber);

		/// <summary>
		/// マウスの押下をチェック
		/// </summary>
		bool PushMouse(MouseButton type);

		/// <summary>
		/// クリックした瞬間
		/// </summary>
		bool OnMouseDown(MouseButton type);

		//ゲッター
		DirectX::XMFLOAT2 GetMousePoint() { return { (float)p.x,(float)p.y }; }

	private://メンバ変数

		//WindowsAPI
		WinApp* winApp_ = nullptr;

		//DirectInputのインスタンス
		ComPtr<IDirectInput8> directInput = nullptr;

		ComPtr<IDirectInputDevice8> keyboard;
		ComPtr<IDirectInputDevice8> mouse;

		//全キーの入力状態を取得する
		BYTE key[256] = {};
		//前回の全キーの状態
		BYTE keyPre[256] = {};

		POINT p;

	private://静的メンバ変数
		DIMOUSESTATE g_CurrentMouseState;	//マウスの現在の入力情報
		DIMOUSESTATE g_PrevMouseState;		//マウスの一フレーム前の入力情報
	};
}

