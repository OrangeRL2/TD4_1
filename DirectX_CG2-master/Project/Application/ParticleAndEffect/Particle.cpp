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

void Particle::Update(float gamespeed) {

	if (oneGrain.frame >= oneGrain.num_frame) {
		isDead = true;
	}

	oneGrain.frame += gamespeed;

	//速度による移動
	oneGrain.position.x += oneGrain.velocity.x * speed.x * gamespeed;
	oneGrain.position.y += oneGrain.velocity.y * speed.y * gamespeed;
	oneGrain.position.z += oneGrain.velocity.z * speed.z * gamespeed;
	//回転
	oneGrain.rotation.x += oneGrain.velocity.x * 30.0f * gamespeed;
	oneGrain.rotation.y += oneGrain.velocity.y * 30.0f * gamespeed;
	oneGrain.rotation.z += oneGrain.velocity.z * 30.0f * gamespeed;
	//進行度を0～1の範囲に換算
	float f = oneGrain.frame / oneGrain.num_frame;
	//スケールの線形補間
	oneGrain.scale = (oneGrain.e_scale - oneGrain.s_scale) * f;
	oneGrain.scale += oneGrain.s_scale;

	object->SetPosition(oneGrain.position);
	object->SetRotation(oneGrain.rotation);
	object->SetScale({ oneGrain.scale, oneGrain.scale, oneGrain.scale });
	object->Update();

	if (speed.x > 0) {
		speed.x += oneGrain.accel.x * gamespeed;
	}
	if (speed.y > 0) {
		speed.y += oneGrain.accel.y * gamespeed;
	}
	if (speed.z > 0) {
		speed.z += oneGrain.accel.z * gamespeed;
	}
}

void Particle::Draw() {
	object->Draw();
}
