#pragma once
#include <DirectXMath.h>
#include <DirectXTex.h>
/*
* FbxModel3d.h
* FBX専用3Dモデル一つごとの処理
*/

#include <string>
#include <vector>
#include <Windows.h>
#include <Wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <fbxsdk.h>

//ノード
struct Node {
	//ローカルスケール
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	//ローカル回転角
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	//ローカル移動
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	//親ノード
	Node* parent = nullptr;
	//名前
	std::string name;
	//ローカル変形行列
	DirectX::XMMATRIX transform;
	//グローバル変形行列
	DirectX::XMMATRIX globalTransform;
};

//ボーン構造体
struct Bone {
	//名前
	std::string name;
	//初期姿勢の逆行列
	DirectX::XMMATRIX invInitialPose;
	//クラスター(FBX側のボーン情報)
	FbxCluster* fbxCluster;
	//コンストラクタ
	Bone(const std::string& name) {
		this->name = name;
	}
};

class FbxModel
{
public://内部クラス
	//ボーン構造体
	struct Bone {
		//名前
		std::string name;
		//初期姿勢の逆行列
		DirectX::XMMATRIX invInitialPose;
		//クラスター(FBX側のボーン情報)
		FbxCluster* fbxCluster;
		//コンストラクタ
		Bone(const std::string& name) {
			this->name = name;
		}
	};


private:
	//Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;
	//std::を省略
	using string = std::string;
	template <class T> using vector = std::vector<T>;


public:
	//フレンドクラス
	friend class FbxLoader;


public://定数
	//ボーンインデックスの最大数
	static const int MAX_BONE_INDICES = 4;

public://サブクラス
	// 頂点データ構造体
	struct VertexPosNormalUvSkin
	{
		DirectX::XMFLOAT3 pos; // xyz座標
		DirectX::XMFLOAT3 normal; // 法線ベクトル
		DirectX::XMFLOAT2 uv;  // uv座標
		UINT boneIndex[MAX_BONE_INDICES];	//ボーン番号
		float boneWeight[MAX_BONE_INDICES];	//ボーン重み
	};

	//メッシュを持つノード
	Node* meshNode = nullptr;
	//頂点データ配列
	std::vector<VertexPosNormalUvSkin> vertices;
	//頂点インデックス配列
	std::vector<unsigned short>indices;

	//アンビエント係数
	DirectX::XMFLOAT3 ambient = { 1,1,1 };
	//ディフューズ係数
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	//テクスチャメタデータ
	DirectX::TexMetadata metadata = {};
	//スクラッチイメージ
	DirectX::ScratchImage scratchImg = {};


	/// <summary>
	/// デストラクタ
	/// </summary>
	~FbxModel();

	/// <summary>
	/// バッファ生成
	/// </summary>
	void CreateBuffers(ID3D12Device* device);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// モデルの変形行列取得
	/// </summary>
	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }

	//ゲッター
	std::vector<Bone>& GetBones() { return bones; }
	FbxScene* GetFbxScene() { return fbxScene; }

private:
	//モデル名
	std::string name;
	//ノード配列
	std::vector<Node> nodes;
	//ボーン配列
	std::vector<Bone> bones;

	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	//FBXシーン
	FbxScene* fbxScene = nullptr;

};

