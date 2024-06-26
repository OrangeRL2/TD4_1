#include "BackObject.h"

void BackObject::Initialize(Model* model, const float scl, const float frq, const float gdis) {
	model_ = model;
	oneScale = scl + MyMath::RandomFloat(-sclRandom, sclRandom);
	scale = { oneScale,oneScale,oneScale };
	frequency = frq;
	groundDistance = gdis;
	playerMoveVal = frequency;
}

void BackObject::Update(const DirectX::XMFLOAT3& playerpos) {

	if (playerMoveVal - playerpos.x < 0) {
		backDistance = MyMath::RandomFloat(MaxBackDistance / 2, MaxBackDistance);

		//背景オブジェクトを登録
		std::unique_ptr<Object3d>object = std::make_unique<Object3d>();

		object->Initialize();
		object->SetModel(model_);
		object->SetScale(scale);
		object->SetRotation({
			MyMath::RandomFloat(-rotRandom,rotRandom),
			MyMath::RandomFloat(-rotRandom,rotRandom),
			MyMath::RandomFloat(-rotRandom,rotRandom),
			});

		object->SetPosition({
			playerpos.x + pDistance,
			groundDistance,
			backDistance,
			});
		object_.push_back(std::move(object));

		playerMoveVal = playerpos.x + frequency + MyMath::RandomFloat(-frequency / 2,frequency / 2);
	}

	for (std::unique_ptr<Object3d>& object : object_) {
		object->Update();
		if (object->GetPosition().x <= playerpos.x - pDistance) {
			isDead = true;
		}
	}

}

void BackObject::Draw() {

	for (std::unique_ptr<Object3d>& object : object_) {
		object->Draw();
	}
}