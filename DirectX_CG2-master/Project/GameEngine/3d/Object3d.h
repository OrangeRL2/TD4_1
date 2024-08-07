/*
* Object3d.h
* 3Dオブジェクト一つごとの処理
*/

#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>

/// <summary>
/// 3Dオブジェクト
/// </summary>

class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX mat;	// ３Ｄ変換行列
	};

	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferColor {
		XMFLOAT4 color; //色(RGBA)
	};

private: // 定数
	static const int division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = 4;		// 頂点数
	static const int indexCount = 3 * 2;		// インデックス数

public: // 静的メンバ関数
	/// <summary>静的初期化</summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>描画前処理</summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>描画後処理</summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device_;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList_;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	static ComPtr<ID3D12Resource> indexBuff;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ビュー行列
	static XMMATRIX matView;
	//static ViewProjection viewProjection;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;
	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	//static VertexPosNormalUv vertices[vertexCount];
	static std::vector<Model::VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	static std::vector<unsigned short> indices;

	//マテリアル
	//static Material material;

private:// 静的メンバ関数
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	//static void InitializeDescriptorHeap();

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	//static void LoadTexture(const std::string& directoryPath,const std::string& filename);

	/// <summary>
	/// モデル作成
	/// </summary>
	static void CreateModel();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

	/// <summary>
	/// マテリアルの読み込み
	/// </summary>
	//static void LoadMaterial(const std::string& directoryPath, const std::string& filename);

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 更新(スケールのみ)
	/// </summary>
	void UpdateScale();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	const XMFLOAT3& GetPosition() const { return position_; }
	const XMFLOAT3& GetRotation() const { return rotation_; }
	const XMFLOAT3& GetScaleMax() const { return scaleMax_; }
	Model* GetModel() const { return model_; }
	float GetScaleFrame() const { return scaleFrame; }

	//セッター
	void SetPosition(const XMFLOAT3& position) { position_ = position; }
	void SetRotation(const XMFLOAT3& rotation) { rotation_ = rotation; }
	void SetScale(const XMFLOAT3& scale) { scale_ = scale; }
	void SetScaleMax(const XMFLOAT3& scaleMax) { scaleMax_ = scaleMax; }
	void SetColor(const XMFLOAT4& color) { color_ = color; }

	//setter
	void SetModel(Model* model) { model_ = model; }

private: // メンバ変数
	//モデル
	Model* model_ = nullptr;

	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
	ComPtr<ID3D12Resource> constBuffB2; // 定数バッファ

	// ローカルスケール
	XMFLOAT3 scale_ = { 1,1,1 };
	//スケール最大値
	XMFLOAT3 scaleMax_ = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation_ = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position_ = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	//
	ViewProjection* viewProjection_;

	float scaleFrame = 0.0f;

	XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	ConstBufferDataB0* constMap0 = nullptr;
	bool depth = false;

	//定数バッファのマッピング
	ConstBufferColor* constMapColor = nullptr;
};

