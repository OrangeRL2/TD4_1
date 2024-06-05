#include "Item.h"

#include"Input.h"

void Item::Initialize()
{
	ItemObj_ = Object3d::Create();
	ItemModel_ = Model::LoadFromOBJ("Box");
	ItemObj_->SetModel(ItemModel_);
	ItemObj_->SetPosition(position_);
	ItemObj_->SetScale(scale_);
	ItemObj_->SetRotation(rotation_);
	isDamageBoost = true;
}

void Item::Update(const DirectX::XMFLOAT3& distance)
{
	//アイテム挙動
	Move(distance);
	//各アイテムの効果
	if (isDamageBoost == true) {
		DamageBoost();
	}
	if (isHeel == true) {
		Heel();
	}
	if (isSlow == true) {
		Slow();
	}
	//更新
	ItemObj_->Update();
}

void Item::Draw()
{
	//描画
	ItemObj_->Draw();
}

void Item::DamageBoost()
{
	//色変更(赤)
	ItemObj_->SetColor({ 1,0,0,1 });
	//プレイヤー攻撃力アップの処理
	//playerのボスに与えるダメージ量の値を足す
}

void Item::Heel()
{
	//色変更(緑)
	ItemObj_->SetColor({ 0,1,0,1 });
	//プレイヤー回復の処理
	//playerのhpの値を足す
}

void Item::Slow()
{
	//色変更(青)
	ItemObj_->SetColor({ 0,0,1,1 });
	//全体の動きを遅くさせる処理
	//playerのspeedBoostを初期値にする
}

void Item::Move(const DirectX::XMFLOAT3& distance)
{
	if (position_.x <= distance.x-20 ) {
		position_ = { distance.x+50,distance.y,distance.z };
		ChangMode();
	}
	ItemObj_->SetPosition(position_);
}

void Item::ChangMode()
{
	//プレイ状況で必要な効果に準ずるモードチェンジ
	if (isDamageBoost == true) {
		isDamageBoost = false;
		isHeel = true;
	}
	else if (isHeel == true) {
		isHeel = false;
		isSlow = true;
	}
	else if (isSlow == true) {
		isSlow = false;
		isDamageBoost = true;
	}
	
	

	//プレイヤーがの体力が少ないとき
	// 
	//Heel();
}
