#include "Obstacle.h"

void Obstacle::Initialize(Model* model, const DirectX::XMFLOAT3 pos) {
	model_ = model;

	object = std::make_unique<Object3d>();
	object->Initialize();
	object->SetModel(model_);

	position = pos;
	object->SetPosition(position);

	scale = MyMath::RandomFloat(2.0f, 3.0f);
	object->SetScale({ scale,scale,scale });
}

void Obstacle::Update() {
	lifeTimer--;

	if (lifeTimer < 0) {
		isDead = true;
	}

	if (isCounter) {
		object->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	}
	else {
		object->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	}

	object->SetPosition({
		object->GetPosition().x,
		object->GetPosition().y,
		object->GetPosition().z,
		});
	object->Update();
}

void Obstacle::Draw() {
	object->Draw();
}

void Obstacle::Dead() {

	isDead = true;
}

void Obstacle::Counter() {
	isCounter = true;
}