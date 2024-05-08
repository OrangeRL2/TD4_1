/*
* FbxObject3d.h
* FBX専用3Dオブジェクト一つごとの処理
*/

#pragma once

#include "FbxModel.h"
#include "FbxLoader.h"
#include "ViewProjection.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <String>

class FbxObject3d
{
protected://エイリアス
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//静的メンバ関数
	//setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device_ = device; }
	static void SetViewProjection(ViewProjection* viewProjection) { FbxObject3d::viewProjection_ = viewProjection; }

	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

private://静的メンバ変数
	//デバイス
	static ID3D12Device* device_;
	//カメラ
	static ViewProjection* viewProjection_;

	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

public://定数
	//ボーンの最大数
	static const int MAX_BONES = 32;

public://サブクラス
	//定数バッファ用データ構造(座標変換行列用)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//ビュープロジェクション行列
		XMMATRIX world;		//ワールド行列
		XMFLOAT3 cameraPos;	//カメラ座標
	};

	//定数バッファ用データ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};


public://メンバ関数
	///<sumarry>
	///初期化
	///</summary>
	void Initialize();

	///<sumarry>
	///毎フレーム処理
	///</summary>
	void Update();

	///<sumarry>
	///描画
	///</summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	///<sumarry>
	///アニメーション開始
	///</summary>
	void PlayAnimation();

	///<sumarry>
	///アニメーション停止
	///</summary>
	void StopAnimation();

	///<sumarry>
	///モデルのセット
	///</summary>
	///<param name="model">モデル</param>
	void SetModel(FbxModel* model) { model_ = model; }

	void SetRotation(XMFLOAT3 rot) { rotation = rot; }
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetScale(XMFLOAT3 scl) { scale = scl; }

protected://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;

	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0, 0, 0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FbxModel* model_ = nullptr;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;
};

