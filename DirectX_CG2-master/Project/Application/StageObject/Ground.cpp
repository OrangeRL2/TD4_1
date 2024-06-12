#include "Ground.h"

void Ground::Initialize(Model* model) {

	model_ = model;

	for (int i = 0; i < groundNum; i++) {

		object[i] = std::make_unique<Object3d>();
		object[i]->Initialize();
		object[i]->SetModel(model_);
		object[i]->SetPosition({ i * scl - scl * groundNum / 2, distance, -distance });
		object[i]->SetScale(scale);
	}
}

void Ground::Update(const DirectX::XMFLOAT3& playerpos) {

	for (int i = 0; i < groundNum; i++) {
		if (object[i]->GetPosition().x - playerpos.x <= -scl * groundNum / 2) {
			object[i]->SetPosition({
				object[i]->GetPosition().x + scl * (groundNum - 1),
				object[i]->GetPosition().y,
				object[i]->GetPosition().z
				});
		}

		object[i]->Update();
	}
}

void Ground::Draw() {

	for (int i = 0; i < groundNum; i++) {
		object[i]->Draw();
	}
}