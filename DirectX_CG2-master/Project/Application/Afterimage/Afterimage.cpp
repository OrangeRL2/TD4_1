#include "Afterimage.h"
void Afterimage::Initialize(SpriteCommon* spCommon, ViewProjection* viewPro, XMFLOAT3 position) {

	this->position_ = position;

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

void Afterimage::Update() {
	playerObject->SetRotation(rot);
	playerObject->SetPosition(position_);
	playerObject->Update();
}

void Afterimage::Draw() {
	//オブジェクト描画
		playerObject->Draw();
}

void Afterimage::Delete() {
	isInactive = true;
}