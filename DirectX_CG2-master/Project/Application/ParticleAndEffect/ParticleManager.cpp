/*
* ParticleManager.cpp
* パーティクル複数の処理
*/

#include "ParticleManager.h"
#include "MyMath.h"

ParticleManager::~ParticleManager() {

}

void ParticleManager::Initialize(Model* model) {
	model_ = model;
}

void ParticleManager::UpdateAlways(int interval, bool isActive, bool isBubble) {
	//寿命が尽きたパーティクルを全削除
	particle.remove_if([](std::unique_ptr<Particle>& p) {
		return p->GetIsDead();
		});

	if (isActive) {
		interval_--;

		if (interval_ <= 0) {

			std::unique_ptr<Particle>p = std::make_unique<Particle>();

			p->Initialize(model_);
			p->oneGrain.num_frame = oneGrain.num_frame;
			p->oneGrain.position = oneGrain.position;
			p->oneGrain.velocity = oneGrain.velocity;
			p->oneGrain.accel = oneGrain.accel;
			p->oneGrain.s_scale = oneGrain.s_scale;
			p->oneGrain.e_scale = oneGrain.e_scale;
			p->SetColor(oneGrain.color);

			//パーティクルを登録する
			particle.push_back(std::move(p));

			//発生間隔をリセット
			interval_ = interval;
		}

	}

	for (std::unique_ptr<Particle>& p : particle) {
		DirectX::XMFLOAT3 moveVal = { 0,0,0 };

		if (isBubble) {
			moveVal = {
				MyMath::RandomFloat(-bubbleMoveVal, bubbleMoveVal),
				MyMath::RandomFloat(bubbleBuoyancy, bubbleBuoyancy * 1.25f),
				MyMath::RandomFloat(-bubbleMoveVal, bubbleMoveVal),
			};
		}
		p->Update(moveVal, 1.0f);
	}
}

void ParticleManager::AddAlways(XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float life, XMFLOAT4 color) {
	oneGrain.num_frame = life;
	oneGrain.position = position;

	//速度をランダム化
	XMFLOAT3 vel{};
	vel.x = MyMath::RandomFloat(-velocity.x, velocity.x);
	vel.y = MyMath::RandomFloat(-velocity.y, velocity.y);
	vel.z = MyMath::RandomFloat(-velocity.z, velocity.z);

	oneGrain.velocity = vel;
	oneGrain.accel = accel;
	oneGrain.s_scale = start_scale;
	oneGrain.e_scale = 0;
	oneGrain.color = color;
}

void ParticleManager::UpdateHit(float gamespeed, bool isBubble) {
	//寿命が尽きたパーティクルを全削除
	particle.remove_if([](std::unique_ptr<Particle>& p) {
		return p->GetIsDead();
		});

	for (std::unique_ptr<Particle>& p : particle) {
		DirectX::XMFLOAT3 moveVal = { 0,0,0 };

		if (isBubble) {
			moveVal = {
				MyMath::RandomFloat(-bubbleMoveVal,bubbleMoveVal),
				MyMath::RandomFloat(bubbleBuoyancy,bubbleBuoyancy * 1.25f),
				MyMath::RandomFloat(-bubbleMoveVal,bubbleMoveVal),
			};
		}
	
		p->Update(moveVal, gamespeed);
	}

}

void ParticleManager::AddHit(XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float life, int amount, XMFLOAT4 color) {

	particleAmount = amount;
	for (int i = 0; i <= amount; i++) {

		std::unique_ptr<Particle>p = std::make_unique<Particle>();

		//速度をランダム化
		XMFLOAT3 vel = {
			MyMath::RandomFloat(-velocity.x, velocity.x),
			MyMath::RandomFloat(-velocity.y, velocity.y),
			MyMath::RandomFloat(-velocity.z, velocity.z),
		};

		//数値を登録
		p->Initialize(model_);
		p->oneGrain.num_frame = MyMath::RandomFloat(life, life * 2.0f);
		p->oneGrain.position = position;
		p->oneGrain.velocity = vel;
		p->oneGrain.accel = accel;
		p->oneGrain.s_scale = start_scale;
		p->oneGrain.e_scale = 0;
		p->SetColor(color);

		//パーティクルを登録する
		particle.push_back(std::move(p));
	}
}

void ParticleManager::UpdateSpin(float gamespeed) {

	//寿命が尽きたパーティクルを全削除
	particle.remove_if([](std::unique_ptr<Particle>& p) {
		return p->GetIsDead();
		});

	//パーティクルを回転させる
	if (rot < 2.0f) {
		rot += rotVal;
	}
	else {
		rot = 0.0f;
	}

	for (std::unique_ptr<Particle>& p : particle) {
		DirectX::XMFLOAT3 moveVal = { 0,0,0 };

		p->oneGrain.velocity = {
				(float)cos((2.0f / (float)particleAmount * p->oneGrain.num + rot) * MyMath::PI) * circleRange,
				(float)-sin((2.0f / (float)particleAmount * p->oneGrain.num + rot) * MyMath::PI) * circleRange,
				0,
		};

		p->Update(moveVal, gamespeed);
	}
}

void ParticleManager::AddSpin(XMFLOAT3 position, float start_scale, float life, float cRange, int amount, bool colorful) {

	particleAmount = amount;
	circleRange = cRange;

	for (int i = 0; i <= amount; i++) {

		//色をカラフルにする
		if (colorful) {
			randomColor = {
				MyMath::RandomFloat(0.25f,0.75f),
				MyMath::RandomFloat(0.25f,0.75f),
				MyMath::RandomFloat(0.25f,0.75f),
				1.0f
			};
		}
		else {
			randomColor = { 1,1,1,1 };
		}

		std::unique_ptr<Particle>p = std::make_unique<Particle>();

		//数値を登録
		p->Initialize(model_);
		p->oneGrain.num = i;
		p->oneGrain.num_frame = life;
		p->oneGrain.position = position;
		p->oneGrain.s_scale = start_scale;
		p->oneGrain.e_scale = 0;
		p->SetColor(randomColor);
		p->oneGrain.velocity = {
			(float)sin((2.0f / amount * i) * MyMath::PI),
			(float)cos((2.0f / amount * i) * MyMath::PI),
			0,
		};
		
		//パーティクルを登録する
		particle.push_back(std::move(p));
	}
}

void ParticleManager::Draw() {
	for (std::unique_ptr<Particle>& p : particle) {
		p->Draw();
	}
}
