/*
* Player.cpp
* 自機の処理
*/
#include "Player.h"
#include "MyMath.h"
#include <cmath>
#include <random>
float ez(float x) {
	return x * x * x;
}
void Player::Initialize(SpriteCommon* spCommon, ViewProjection* viewPro, SEManager* SE) {
	se = SE;
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
	HP = std::make_unique<PlayerHP>();
	HP->Initialize(spriteCommon_);
	stamina = std::make_unique<PlayerStamina>();
	stamina->Initialize(spriteCommon_);

}

void Player::Update() {

	if (hp > 0) {
		Move();
		Dodge2();
	}
	HP->Update();
	stamina->Update(staminaTimer);
	//DodgeActive();
	//Dodge();

	invincibleTimer--;
	if (invincibleTimer <= 0) {
		invincibleTimer = invincibleTimerMax;
		isInvincible = false;
	}

	if (input_->TriggerKey(DIK_D)) {
		//OnCollision(1);
	}


	if (moveSpeed <= 0) {
		/*	if (dodgeRot.z != 0.0f) {
				dodgeRot.z -= 1.0f;
			}*/

		rot.z = turnSpeed;
	}
	moveFlag = false;
	//動き
	if (input_->PushKey(DIK_W)) {
		moveFlag = true;
		if (turnSpeed < 70.0f)
		{
			turnSpeed += 0.6f;
		}
		if (MoveSpeedUp < MaxSpeedUp) {
			MoveSpeedUp += acceleration;
		}
		position.y += MoveSpeedUp;
		MoveSpeedDown = 0.0f;
	}

	if (input_->PushKey(DIK_S)) {
		moveFlag = true;
		if (turnSpeed > -70.0f)
		{
			turnSpeed -= 0.6f;
		}
		if (MoveSpeedDown < MaxSpeedDown) {
			MoveSpeedDown += acceleration;
		}
		position.y -= MoveSpeedDown;
		MoveSpeedUp = 0.0f;
	}
	else if(moveFlag==false)
	{	
		// 押してないときにスピードが落ちる
		if (MoveSpeedUp > 0.0f) {
			MoveSpeedUp -= acceleration;
		}
		// 0以下にならないように
		if (MoveSpeedUp < 0.0f) {
			MoveSpeedUp = 0.0f;
		}

		// 押してないときにスピードが落ちる
		if (MoveSpeedDown > 0.0f) {
			MoveSpeedDown -= acceleration;
		}
		// 0以下にならないように
		if (MoveSpeedDown < 0.0f) {
			MoveSpeedDown = 0.0f;
		}

		//ローテーションを元に戻す
		if (turnSpeed <= 0.00f) {
			turnSpeed += 1.5f;
		}
		if (turnSpeed >= 0.0f) {
			turnSpeed -= 1.5f;
		}
	}
	


	finalRot = { rot.x + dodgeRot.x,rot.y + dodgeRot.y,rot.z + dodgeRot.z };

	particle->UpdateHit(1.0f, true);
	dodgeParticle->UpdateSpin(position, 1.0f);
	damageEffect->Update();

	playerObject->SetRotation(rot);
	playerObject->SetPosition(position);
	playerObject->SetScale(scale);
	playerObject->Update();

	for (std::unique_ptr<Afterimage>& object0 : afterimage_)
	{
		object0->Update(position);
	}

	for (std::unique_ptr<DodgeEffect>& object1 : dodgeEffect_)
	{
		object1->Update();
	}
	afterimage_.remove_if([](std::unique_ptr<Afterimage>& object0) {
		return object0->GetActive();
		});
}

void Player::Draw() {
	//オブジェクト描画
	if ((int)invincibleTimer % 2 == 0 && hp > 0) {
		playerObject->Draw();
	}

	particle->Draw();
	dodgeParticle->Draw();
	for (std::unique_ptr<Afterimage>& object0 : afterimage_)
	{
		object0->Draw();
	}

	for (std::unique_ptr<DodgeEffect>& object1 : dodgeEffect_)
	{
		object1->Draw();
	}
}

void Player::Draw2D() {
	damageEffect->Draw();
	HP->Draw();
	stamina->Draw();
}

void Player::Move() {

	//速度を決まる
	move.x = speed + speedBoost + easingPos * 0.2f;
	//speedがspeedLimにならないように
	if (speed > speedLim) {
		speed = speedLim;
	}
	if (speed < speedLim)
	{
		speed += 0.001f;
	}
	if (speed >= speedLim / 2) {
		/*std::unique_ptr<Afterimage>newAfterimage = std::make_unique<Afterimage>();
		newAfterimage->Initialize(spriteCommon_, viewProjection, position);
		afterimage_.push_back(std::move(newAfterimage));*/
	}
	else {
		for (std::unique_ptr<Afterimage>& object0 : afterimage_)
		{
			object0->Delete();
		}
	}

	//std::unique_ptr<Afterimage>newAfterimage = std::make_unique<Afterimage>();
	//newAfterimage->Initialize(spriteCommon_, viewProjection, position,rot);
	//afterimage_.push_back(std::move(newAfterimage));

	position.x += move.x;
	position.y += move.y;
	position.z += move.z;

	playerObject->SetRotation(rot);
	playerObject->SetPosition(position);
	playerObject->Update();

}

void Player::OnCollision(const int dmg) {
	//speed -= 0.05f;
	isHit = true;
	
	//無敵時間以外ならダメージ
	if (!isInvincible) {
		hp -= dmg;
		HP->OnHit();
		damageEffect->SetTimer();
		particle->AddHit(position, 0.5f, 60.0f, 10, { 1,1,1,0.51f }, { 0.5f ,0.5f,0.5f });
		isInvincible = true;
		for (std::unique_ptr<Afterimage>& object0 : afterimage_)
		{
			object0->Delete();
		}
	}

	se->Play(se->Damage(), 1.0f, 0.0f);
}

void Player::Dodge2() {
	if (staminaTimer >= 100 && spaceTimer == 0.0f) {
		if (input_->TriggerKey(DIK_SPACE)) {
			staminaTimer -= 110;
			spaceTimer = 10;
			stamina->OnUse();
			easingFlag = 1;
			frame = 0;
			for (int i = 0; i < 200; i++) {
				for (std::unique_ptr<Afterimage>& object0 : afterimage_)
				{
					object0->Delete();
				}

				for (std::unique_ptr<DodgeEffect>& object1 : dodgeEffect_)
				{
					object1->Delete();
				}
			}

			se->Play(se->Avoidance(), 1.0f, 1.0f);
		}
	}
	if (staminaTimer < 600.0f) {
		staminaTimer+=0.5f;
	}
	
	if (staminaTimer >= 600.0f) {
		staminaTimer = 600.0f;
	}

	if (spaceTimer > 0.0f) {
		spaceTimer -= 2.0f;
	}

	if (spaceTimer < 0.0f) {
		spaceTimer = 0.0f;
	}

	if (easingFlag == 1) {
		for (int i = 0; i < 200; i++) {
			if (afterFlag[i] == 0) {

				std::unique_ptr<Afterimage>newAfterimage = std::make_unique<Afterimage>();
				newAfterimage->Initialize(spriteCommon_, viewProjection, position,rot);
				afterimage_.push_back(std::move(newAfterimage));


				afterFlag[i] = 1;
				break;
			}
		}
		frame++;
		if (frame <= endFrame / 4) {
			easingPos += 0.3f;
			scale.x += 0.03f;
			scale.y -= 0.10f;
		}
		if (frame >= endFrame / 4) {
			easingPos += 0.02f;
			scale.x += 0.01f;
			//scale.y -= 0.1f;
		}
		if (frame >= endFrame / 2) {
			easingPos += 0.01f;
			scale.x += 0.02f;
			//scale.y -= 0.02f;
		}

		/*std::unique_ptr<DodgeEffect>newDodgeEffect = std::make_unique<DodgeEffect>();
		newDodgeEffect->Initialize(spriteCommon_, viewProjection, position);
		dodgeEffect_.push_back(std::move(newDodgeEffect));*/
	}
	if (frame == endFrame) {
		easingFlag = 0;
		//easingPos = 0.0f;

		//scale = { 1.0f,1.0f,1.0f };
	}
	if (easingFlag == false) {
		if (scale.x > 1.0f) {
			scale.x -= 0.05f;
		}
		// 0以下にならないように
		if (scale.x < 1.0f) {
			scale.x = 1.0f;
		}

		if (scale.y < 1.0f) {
			scale.y += 0.05f;
		}
		// 0以下にならないように
		if (scale.y > 1.0f) {
			scale.y = 1.0f;
		}

		if (easingPos > 0.0f) {
			easingPos -= 0.1f;
		}
		if (easingPos < 0.0f) {
			easingPos = 0.0f;
		}
	}
}

void Player::DodgeOnHit() {
	if (staminaTimer == 0) {
		staminaTimer = 50;
		//easingPos = 50.0f;
		easingFlag = 1;
		frame = 0;
		for (int i = 0; i < 200; i++) {
			for (std::unique_ptr<Afterimage>& object0 : afterimage_)
			{
				object0->Delete();
			}
		}
	}
}