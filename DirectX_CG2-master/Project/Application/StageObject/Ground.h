#pragma once
#include"WinApp.h"
#include"Object3d.h"
#include"Model.h"
#include"MyMath.h"

class Ground
{
public:

	void Initialize(Model* model);

	void Update(const DirectX::XMFLOAT3& playerpos);

	void Draw();

private:

	static const int groundNum = 5;
	const float scl = 200.0f;
	const float distance = -20.0f;

	std::unique_ptr<Object3d> object[groundNum];
	Model* model_ = nullptr;

	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { scl / 2,scl / 2,scl / 2 };
};
