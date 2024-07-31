#pragma once
#include "Object3d.h"
#include "Model.h"
#include"ParticleManager.h"

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
	void Update(const int playerHp, const DirectX::XMFLOAT3& distance);

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
	void Move(const int playerHp, const DirectX::XMFLOAT3& distance);

	/// <summary>
	/// 効果切り替え
	/// </summary>

	void ChangMode(const int playerHp);

	
	void Ability(int playerHp,int bossHp, const DirectX::XMFLOAT3& distance);


	DirectX::XMFLOAT3 GetPosition() { return position_; }
	bool GetIsHeel() { return isHeel; }
	bool GetIsSlow() { return isSlow; }
	bool GetIsDamage() { return isDamageBoost; }

private:
	Object3d* ItemObj_ = nullptr;
	Model* ItemModel_ = nullptr;

	//アイテムの座標
	DirectX::XMFLOAT3 position_ = { -30,0,0 };
	DirectX::XMFLOAT3 scale_ = { 0.5f,0.5f,0.5f };
	DirectX::XMFLOAT3 rotation_ = { 0,0,0 };
	//アイテム移動量
	//DirectX::XMFLOAT3 move_ = { 0.2f,0,0 };
	DirectX::XMFLOAT3 move = { 10.0f,0.0f,0.0f };

	//フラグ
	bool isHeel = false;
	bool isSlow = false;
	bool isDamageBoost = false;

	
	//移動処理関連
	float moveLim = 15.0f;//上昇の上限値
	float moveLim2 = 10.0f;//下降の上限値
	float moveUp = 0.0f; //
	float moveDown = 0.0f;//
	float speedLim = 1.0f;
	float speed = 0.0f;
	float speed2 = 0.1f;
	float speedBoost = 0.0f;
	int timer = 0;
	
	//モードチェンジ関連(各効果の変化率)
	int heelPercent = 80;
	int slowPercent = 50;
	int damagePercent = 50;

	//定数
	const int popCoolTime = 50;

};

