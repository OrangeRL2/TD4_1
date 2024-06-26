#pragma once
#include"WinApp.h"
#include"Object3d.h"
#include"Model.h"
#include"MyMath.h"

class Skydome
{
public:

	void Initialize(Model* model);

	void Update(const DirectX::XMFLOAT3& playerpos);

	void Draw();

private:

	const float scl = 1000.0f;
	float rot = 0.0f;

	std::unique_ptr<Object3d> object;
	Model* model_ = nullptr;

	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { scl,scl,scl };
};
