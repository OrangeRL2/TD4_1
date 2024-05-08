/*
* Input.cpp
* 入力デバイス関連の処理
*/

#include "Input.h"
#include <cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
using namespace OogamiEngine;

Input* Input::GetInstance() {
	static Input instance;

	return &instance;
}

void Input::Initialize(WinApp* winApp)
{
	//借りてきたWinAppのインスタンスを記録
	winApp_ = winApp;

	//DirectInputの初期化
	/*DirectInput・・・マイクロソフトによって開発されたソフトウェアコンポーネント「Microsoft DirectX」のうちのひとつ
	マウス、キーボード、ジョイスティック、ゲームコントローラ等を介してユーザーからの入力情報を収集するためのAPI*/

	HRESULT result;

	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//マウスデバイスの生成
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	result = mouse->SetDataFormat(&c_dfDIMouse);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	/*排他制御・・・複数の主体が同じ資源を同時に利用すると競合状態が生じる場合に、ある主体が資源を利用している間、別の主体による資源の利用を制限もしくは禁止する仕組み*/
	result = keyboard->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	result = mouse->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::Update()
{
	HRESULT result;

	//前回のキー入力を保存
	memcpy(keyPre, key, sizeof(key));
	//更新前に最新マウス情報を保存
	g_PrevMouseState = g_CurrentMouseState;

	//キーボード情報の取得開始
	result = keyboard->Acquire();
	//マウス情報の取得開始
	result = mouse->Acquire();

	//全キーの入力情報を取得する
	result = keyboard->GetDeviceState(sizeof(key), key);
	//マウスの状態を取得
	result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);

	//マウスカーソルの場所を取得
	GetCursorPos(&p);
	ScreenToClient(winApp_->GetHwnd(), &p);

}

bool Input::PushKey(BYTE keyNumber)
{
	//指定キーを押していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber] && keyPre[keyNumber] == FALSE) {
		return true;
	}
	return false;
}

bool Input::PushMouse(MouseButton type) {
	// 左クリックされているか判定
	if (g_CurrentMouseState.rgbButtons[type] & (0x80))
	{
		return true;
	}
	return false;
}

// クリックした瞬間の判定
bool Input::OnMouseDown(MouseButton type)
{
	if (!(g_PrevMouseState.rgbButtons[type] & (0x80)) &&
		g_CurrentMouseState.rgbButtons[type] & (0x80))
	{
		return true;
	}

	return false;
}