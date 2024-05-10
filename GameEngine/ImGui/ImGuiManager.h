/*
* ImGuiManager.h
* ImGui関連の処理
*/

#pragma once
#include "DirectXCommon.h"

class ImGuiManager
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// ImGui受付開始
	/// </summary>
	void Begin();

	/// <summary>
	/// ImGui受付終了
	/// </summary>
	void End();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	HRESULT result;
	DirectXCommon* dxCommon_ = nullptr;

	//SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;
};

