#include "Afterimage.h"
#include <cmath>
#include <random>
void Afterimage::Initialize(SpriteCommon* spCommon, ViewProjection* viewPro, XMFLOAT3 position, XMFLOAT3 pRot) {

	const float rnd_vel = 0.5f;
	XMFLOAT3 vel{};
	vel.x = MyMath::RandomFloat(0, 0);
	vel.y = MyMath::RandomFloat(-rnd_vel, rnd_vel);
	vel.z = MyMath::RandomFloat(0, 0);

	position_.x = position.x + vel.x;
	position_.y = position.y + vel.y;
	position_.z = position.z + vel.z;
	float randScale;
	randScale = MyMath::RandomFloat(0.5f, 3.0f);
	rot.x += pRot.x;
	rot.y += pRot.y;
	rot.z += pRot.z;

	input_ = Input::GetInstance();
	viewProjection = viewPro;
	spriteCommon_ = spCommon;
	scale = { 0.0f,0.04f,0.04f };
	scale.x += randScale;
	model_ = Model::LoadFromOBJ("Box");
	playerObject = std::make_unique<Object3d>();
	playerObject->Initialize();
	playerObject->SetModel(model_);
	playerObject->SetPosition(position_);
	playerObject->SetScale(scale);
	playerObject->SetRotation(rot);
	playerObject->SetColor({ 1,1,1,0.8f });
}

void Afterimage::Update(XMFLOAT3 position) {

	time++;
	if (time >= 10) {
		Delete();
	}

	const float rnd_vel = 0.8f;
	XMFLOAT3 vel{};
	vel.x = MyMath::RandomFloat(0, 0);
	vel.y = MyMath::RandomFloat(-rnd_vel+0.2f, rnd_vel);
	vel.z = MyMath::RandomFloat(0, 0);

	position_.x = position.x + vel.x;
	position_.y = position.y + vel.y;
	position_.z = position.z + vel.z;

	playerObject->SetScale(scale);
	playerObject->SetPosition(position_);
	playerObject->Update();
}

void Afterimage::Draw() {
	//オブジェクト描画
	//if (isInactive == false) {
		playerObject->Draw();
	//}
}

void Afterimage::Delete() {
	isInactive = true;
}