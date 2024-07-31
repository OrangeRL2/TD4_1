#pragma once
#include"WinApp.h"
#include"Object3d.h"
#include"Model.h"
#include"MyMath.h"

class Obstacle
{
public:

	void Initialize(Model* model, const DirectX::XMFLOAT3 pos);

	void Update();

	void Draw();

	void Dead();
	void Counter();

	DirectX::XMFLOAT3 GetPosition() { return position; }
	float GetScale() { return scale; }

	bool GetIsDead() { return isDead; }
	bool GetIsCounter() { return isCounter; }

private:

	std::unique_ptr<Object3d> object;
	Model* model_ = nullptr;

	DirectX::XMFLOAT3 position = { 0,0,0 };
	float scale = 0;

	int lifeTimer = 300;
	bool isCounter = false;
	bool isDead = false;
};
