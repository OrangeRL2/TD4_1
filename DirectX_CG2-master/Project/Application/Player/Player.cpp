/*
* Player.cpp
* 自機の処理
*/

#include "Player.h"
#include "MyMath.h"
#include <cmath>
#include <random>

void Player::Initialize(SpriteCommon* spCommon, ViewProjection* viewPro) {
	input_ = Input::GetInstance();
	viewProjection = viewPro;
	spriteCommon_ = spCommon;
	scale = { 1.0f,1.0f,1.0f };
	model_ = Model::LoadFromOBJ("Fish");
	playerObject = std::make_unique<Object3d>();
	playerObject->Initialize();
	playerObject->SetModel(model_);
	playerObject->SetPosition(position);
	playerObject->SetScale(scale);
	playerObject->SetRotation(rot);
	speed = 0.0f;

	particle = std::make_unique<ParticleManager>();
	particle->Initialize(Model::LoadFromOBJ("Particle"));
	dodgeParticle = std::make_unique<ParticleManager>();
	dodgeParticle->Initialize(Model::LoadFromOBJ("Particle"));
	damageEffect = std::make_unique<DamageEffect>();
	damageEffect->Initialize(spriteCommon_);
}

void Player::Update() {
	Move();
	//Dodge();

	invincibleTimer--;
	if (invincibleTimer <= 0) {
		invincibleTimer = invincibleTimerMax;
		isInvincible = false;
	}

	if (input_->TriggerKey(DIK_D)) {
		OnCollision(1);
	}
	if (input_->TriggerKey(DIK_A)) {
		if (moveSpeed <= 0) {
			Dodge();
		}
	}
//#pragma endregion

//#pragma region dodge
	if (isDodgeInvincible == true) {
		dodgeTimer -= 5.0f;
		invincibleTimer -= 0.0f;

//#pragma region rotate

		const float rotationSpeed = 50.0f;

		DirectX::XMFLOAT3 rotation = { 0 , 0 , 0 };

		rotation.z = rotationSpeed;

		dodgeRot.x += rotation.x;
		dodgeRot.y += rotation.y;
		dodgeRot.z += rotation.z;
//#pragma endregion

		isHitMap = false;

		angle = dodgeRot;

		if (moveSpeed < maxSpeed) {
			moveSpeed += accelaration;

			if (maxSpeed <= moveSpeed) {
				moveSpeed = maxSpeed;
			}
		}
	}

	if (dodgeTimer <= 0) {
		dodgeTimer = dodgeTimerMax;
		invincibleTimer = invincibleTimerMax;
		isDodgeInvincible = false;
	}

	else {
		if (0 < moveSpeed) {
			moveSpeed -= accelaration / 2;

			if (moveSpeed <= 0) {
				moveSpeed = 0;
			}
		}

	}
	if (isHitMap == false) {
		velocity = {
			moveSpeed * -cosf(angle.z) ,
			moveSpeed * sinf(angle.z) ,
			0
		};
	}
	else {
		velocity = {
			moveSpeed * -cosf(-angle.z) ,
			moveSpeed * -sinf(-angle.z) ,
			0
		};
	}

	position.x += velocity.x;
	//position.y += velocity.y;
	//position.z += velocity.z;

//#pragma endregion

	if (moveSpeed <= 0) {
	/*	if (dodgeRot.z != 0.0f) {
			dodgeRot.z -= 1.0f;
		}*/
		
		rot.z = turnSpeed;
	}

	//動き
	if (input_->PushKey(DIK_W)) {
		if (turnSpeed < 10.0f)
		{
			turnSpeed += 1.0f;
		}
		position.y += gravity;
	}

	if (input_->PushKey(DIK_S)) {
		if (turnSpeed > -10.0f)
		{
			turnSpeed -= 1.0f;
		}
		position.y -= gravity;
	}
	//上に泳いでない時に下に動く
	else if (position.y >= -moveLim) {
		if (turnSpeed > -10.0f)
		{
			turnSpeed -= 1.0f;
		}

	}

	//ローテーションを元に戻す
	if (turnSpeed <= 0.00f) {
		turnSpeed += 0.5f;
	}
	if (turnSpeed >= 0.0f) {
		turnSpeed -= 0.5f;
	}

	finalRot = { rot.x + dodgeRot.x,rot.y + dodgeRot.y,rot.z + dodgeRot.z };

	particle->UpdateHit(1.0f, true);
	dodgeParticle->UpdateSpin(1.0f);
	damageEffect->Update();

	playerObject->SetRotation(rot);
	playerObject->SetPosition(position);
	playerObject->Update();
}

void Player::Draw() {
	//オブジェクト描画
	if ((int)invincibleTimer % 2 == 0) {
		playerObject->Draw();
	}

	particle->Draw();
	dodgeParticle->Draw();
}

void Player::Draw2D() {
	damageEffect->Draw();
}

void Player::Move() {

	//速度を決まる
	move.x = speed + speedBoost;
	//speedがspeedLimにならないように
	if (speed > speedLim) {
		speed = speedLim;
	}
	if (speed < speedLim)
	{
		speed += 0.001f;
	}

	position.x += move.x;
	position.y += move.y;
	position.z += move.z;

	playerObject->SetRotation(rot);
	playerObject->SetPosition(position);
	playerObject->Update();

}

void Player::OnCollision(const int dmg) {
	speed -= 0.02f;
	isHit = true;
	//無敵時間以外ならダメージ
	if (!isInvincible) {
		hp -= dmg;
		damageEffect->SetTimer();
		particle->AddHit(position, 0.5f, 60.0f, 10, { 1,1,1,0.51f }, { 0.5f,0.5f,0.5f });
		isInvincible = true;

	}
}

void Player::Dodge() {
	if (!isDodgeInvincible) {
		dodgeParticle->AddSpin(position, 0.25f, 60.0f, 0.5f, 10, false);
		dodgeRot = { 0.0f,0.0f,0.0f };
		isDodgeInvincible = true;
	}

}


