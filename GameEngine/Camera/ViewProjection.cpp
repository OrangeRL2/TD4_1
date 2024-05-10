/*
* ViewProjection.cpp
* カメラ関連の処理
*/

#include "ViewProjection.h"
using namespace DirectX;

XMMATRIX ViewProjection::matProjection{};
XMMATRIX ViewProjection::matView{};

void ViewProjection::Initialize(int window_width, int window_height) {

	eye_ = { 0 , 0 , -50 };	//視点座標
	target_ = { 0 , 0 , 0 };	//注視点座標
	up_ = { 0 , 1 , 0 };		//上方向ベクトル

	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 10000.0f
	);

	Update();
}

void ViewProjection::Update() {

	XMFLOAT3 xmEye;
	xmEye.x = eye_.x;
	xmEye.y = eye_.y;
	xmEye.z = eye_.z;

	XMFLOAT3 xmTarget;
	xmTarget.x = target_.x;
	xmTarget.y = target_.y;
	xmTarget.z = target_.z;

	XMFLOAT3 xmUp;
	xmUp.x = up_.x;
	xmUp.y = up_.y;
	xmUp.z = up_.z;

	matView = XMMatrixLookAtLH(XMLoadFloat3(&xmEye), XMLoadFloat3(&xmTarget), XMLoadFloat3(&xmUp));
	matView *= matProjection;

}

void ViewProjection::CameraMoveVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void ViewProjection::CameraMoveEyeVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}
