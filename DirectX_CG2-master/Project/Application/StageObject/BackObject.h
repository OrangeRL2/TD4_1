#pragma once
#include"WinApp.h"
#include"Object3d.h"
#include"Model.h"
#include"MyMath.h"

class BackObject
{
public:

	void Initialize(Model* model, const float scl, const float frq, const float gdis);

	void Update(const DirectX::XMFLOAT3& playerpos, const float rot);

	void Draw();

	bool GetIsDead() { return isDead; }

	void SetColor(DirectX::XMFLOAT4 col) { color = col; }

private:

	const float pDistance = 200.0f;
	const float rotRandom = 10.0f;
	const float sclRandom = 2.0f;
	const float MaxBackDistance = 100.0f;
	float groundDistance = -15.0f;
	float backDistance = 0.0f;
	float oneScale = 0.0f;

	std::list<std::unique_ptr<Object3d>> object_;
	Model* model_ = nullptr;

	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { oneScale,oneScale,oneScale };
	DirectX::XMFLOAT4 color = { 1,1,1,1 };

	float frequency = 0.0f;
	float timer = frequency;

	bool isDead = false;

	const float MaxPlayerMoveVal = 60.0f;
	float playerMoveVal = MaxPlayerMoveVal;
};
