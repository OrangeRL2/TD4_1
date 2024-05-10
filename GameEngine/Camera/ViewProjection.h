/*
* ViewProjection.h
* カメラ関連の処理
*/


#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

class ViewProjection
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int window_width, int window_height);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	void CameraMoveVector(XMFLOAT3 move);

	/// <summary>
	///ベクトルによる視点移動
	///</summary>
	void CameraMoveEyeVector(XMFLOAT3 move);

	//ゲッター
	XMMATRIX GetMatrix() { return matView; }
	XMFLOAT3 GetEye() { return eye_; }
	XMFLOAT3 GetTarget() { return target_; }

	//セッター
	void SetEye(XMFLOAT3 eye) { eye_ = eye; }
	void SetTarget(XMFLOAT3 target) { target_ = target; }
	void SetUp(XMFLOAT3 up) { up_ = up; }

private:
	// 射影行列
	static XMMATRIX matProjection;
	static XMMATRIX matView;
	XMFLOAT3 eye_;
	XMFLOAT3 target_;
	XMFLOAT3 up_;
};
