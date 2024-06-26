#include "DodgeEffect.h"
#include <cmath>
#include <random>
void DodgeEffect::Initialize(SpriteCommon* spCommon, ViewProjection* viewPro, XMFLOAT3 position) {

	const float rnd_vel = 0.5f;
	XMFLOAT3 vel{};
	vel.x = MyMath::RandomFloat(-rnd_vel * 5, -1);
	vel.y = MyMath::RandomFloat(-rnd_vel, rnd_vel);
	vel.z = MyMath::RandomFloat(0, 0);

	position_.x = position.x;
	position_.y = position.y;
	position_.z = position.z;

	input_ = Input::GetInstance();
	viewProjection = viewPro;
	spriteCommon_ = spCommon;
	scale = { 1.0f,1.0f,1.0f };
	model_ = Model::LoadFromOBJ("Box");
	playerObject = std::make_unique<Object3d>();
	playerObject->Initialize();
	playerObject->SetModel(model_);
	playerObject->SetPosition(position_);
	playerObject->SetScale(scale);
	playerObject->SetRotation(rot);
	playerObject->SetColor({ 1,1,1,0.8f });
}

void DodgeEffect::Update() {

	time++;

	if (time >= 2) {
		//Delete();
	}

	playerObject->SetPosition(position_);
	playerObject->Update();
}

void DodgeEffect::Draw() {
	//オブジェクト描画
	if (isInactive == false) {
		playerObject->Draw();
	}

	//playerObject->Draw();
}

void DodgeEffect::Delete() {
	isInactive = true;
}