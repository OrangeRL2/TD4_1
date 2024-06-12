#pragma once
#include "Object3d.h"
#include "Model.h"

class Item
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const DirectX::XMFLOAT3& distance);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 敵に与えるダメージが大きくなる
	/// </summary>
	void DamageBoost();

	/// <summary>
	/// 回復
	/// </summary>
	void Heel();

	/// <summary>
	/// 動きが遅くなる
	/// </summary>
	void Slow();

	/// <summary>
	/// 右から左に流れる動き
	/// </summary>
	void Move(const DirectX::XMFLOAT3& distance);

	/// <summary>
	/// 効果切り替え
	/// </summary>
	void ChangMode();

	
	void Ability(int playerHp,int bossHp, const DirectX::XMFLOAT3& distance);
private:
	Object3d* ItemObj_ = nullptr;
	Model* ItemModel_ = nullptr;

	//アイテムの座標
	DirectX::XMFLOAT3 position_ = { -30,0,0 };
	DirectX::XMFLOAT3 scale_ = { 0.5f,0.5f,0.5f };
	DirectX::XMFLOAT3 rotation_ = { 0,0,0 };
	//アイテム移動量
	DirectX::XMFLOAT3 move_ = { 0.2f,0,0 };

	//フラグ
	bool isHeel = false;
	bool isSlow = false;
	bool isDamageBoost = false;
};

