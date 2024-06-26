#include "Skydome.h"

void Skydome::Initialize(Model* model) {
	model_ = model;

	object = std::make_unique<Object3d>();
	object->Initialize();
	object->SetModel(model_);
	object->SetScale(scale);
}

void Skydome::Update(const DirectX::XMFLOAT3& playerpos) {
	rot -= 0.1f;
	object->SetRotation({ 0,rot,0 });
	object->SetPosition({ 
		playerpos.x,
		0,
		playerpos.z,
		});
	object->Update();
}

void Skydome::Draw() {
	object->Draw();
}