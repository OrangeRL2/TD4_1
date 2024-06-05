/*
* Particle.cpp
* パーティクル一粒分の処理
*/

#include "Particle.h"
#include "MyMath.h"

Particle::~Particle() {
	//delete object;
}

void Particle::Initialize(Model* model) {

	object = std::make_unique<Object3d>();
	object->Initialize();
	object->SetModel(model);
}

void Particle::Update(DirectX::XMFLOAT3 moveVal, float gamespeed) {

	if (oneGrain.frame >= oneGrain.num_frame) {
		isDead = true;
	}

	oneGrain.frame += gamespeed;

	//速度による移動
	oneGrain.position.x += oneGrain.velocity.x * speed.x * gamespeed + moveVal.x;
	oneGrain.position.y += oneGrain.velocity.y * speed.y * gamespeed + moveVal.y;
	oneGrain.position.z += oneGrain.velocity.z * speed.z * gamespeed + moveVal.z;
	
	//進行度を0～1の範囲に換算
	float f = oneGrain.frame / oneGrain.num_frame;
	//スケールの線形補間
	oneGrain.scale = (oneGrain.e_scale - oneGrain.s_scale) * f;
	oneGrain.scale += oneGrain.s_scale;

	object->SetPosition(oneGrain.position);
	object->SetScale({ oneGrain.scale, oneGrain.scale, oneGrain.scale });
	object->Update();

	if (speed.x > 0) {
		speed.x += oneGrain.accel.x * gamespeed;
	}
	else {
		speed.x = 0;
	}
	if (speed.y > 0) {
		speed.y += oneGrain.accel.y * gamespeed;
	}
	else {
		speed.y = 0;
	}
	if (speed.z > 0) {
		speed.z += oneGrain.accel.z * gamespeed;
	}
	else {
		speed.z = 0;
	}
}

void Particle::Draw() {
	object->Draw();
}
