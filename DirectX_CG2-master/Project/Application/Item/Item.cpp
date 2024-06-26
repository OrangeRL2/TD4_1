#include "Item.h"

#include"Input.h"
#include<Time.h>

void Item::Initialize()
{
	ItemObj_ = Object3d::Create();
	ItemModel_ = Model::LoadFromOBJ("Box");
	ItemObj_->SetModel(ItemModel_);
	ItemObj_->SetPosition(position_);
	ItemObj_->SetScale(scale_);
	ItemObj_->SetRotation(rotation_);
	srand((unsigned int)time(NULL));
	isDamageBoost = true;
}

void Item::Update(const int playerHp, const DirectX::XMFLOAT3& distance)
{
	//アイテム挙動
	Move(playerHp,distance);
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

void Item::Move(const int playerHp,const DirectX::XMFLOAT3& distance)
{
	//上下に移動する
	/*position_.y += speed;
	if (position_.y >=moveLim ) {
		speed = -1.5f;
	}
	if(position_.y<=-moveLim){
		speed = +1.5f;
	}*/

	//プレイヤーを通り過ぎると前方に移動する
	if (position_.x <= distance.x-20 ) {
		position_ = { distance.x+50,distance.y,distance.z };
		ChangMode(playerHp);
	}
	ItemObj_->SetPosition(position_);
}


void Item::ChangMode(const int playerHp)
{
	////プレイ状況で必要な効果に準ずるモードチェンジ
	////現状は仮で順番に変更される
	//if (isDamageBoost == true) {
	//	isDamageBoost = false;
	//	isHeel = true;
	//}
	//else if (isHeel == true) {
	//	isHeel = false;
	//	isSlow = true;
	//}
	//else if (isSlow == true) {
	//	isSlow = false;
	//	isDamageBoost = true;
	//}
	

	//プレイヤーがの体力が少ないとき
	if(playerHp == 5){
	    heelPercent = 0;
	}
	else {
		heelPercent = 100 / playerHp;// 体力の数値
	}

	//スピードが速いとき
	slowPercent = 10 * playerHp;

	
	//回復処理優先で確率でのモードチェンジ
	while (true) {
		int r = rand() % 100 + 1;
		int r2 = rand() % 100 + 1;
		if (heelPercent >= r) {
			isSlow = false;
			isDamageBoost = false;
			isHeel = true;
		}
		else {
			if (slowPercent >= r2) {
				isHeel = false;
				isDamageBoost = false;
				isSlow = true;
			}
			else {
				isSlow = false;
				isHeel = false;
				isDamageBoost = true;
			}
		}
		break;
	}
}

void Item::Ability(int playerHp,int bossHp, const DirectX::XMFLOAT3& distance)
{
	if (isDamageBoost == true) {
		bossHp -= 1;
	}
	else if (isHeel == true) {
		int maxHp = 3;
		if (maxHp > playerHp) {
			playerHp += 1;
		}
	}
	else if (isSlow == true) {

	}
	position_ = { distance.x + 50,distance.y,distance.z };
	ChangMode(playerHp);
	ItemObj_->SetPosition(position_);
}
