/*
* Easing.cpp
* イージングの処理
*/

#include "MyMath.h"

const float MyMath::PI = 3.14159f;

float MyMath::easeOutCubic(float x) {
	return 1 - (float)pow(1 - x, 3);
}

float MyMath::easeOutQuint(float x) {
	return 1 - (float)pow(1 - x, 5);
}

float MyMath::easeInOutSine(float x) {
	return -((float)cos(PI * x) - 1) / 2;
}

float MyMath::easeOutBack(float x) {
	const float c1 = 1.00158f;
	const float c3 = c1 + 1.0f;

	return 1 + c3 * (float)pow(x - 1, 3) + c1 * (float)pow(x - 1, 2);
}

float MyMath::easeInCubic(float x) {
	return x * x * x;
}

float MyMath::RandomFloat(float min, float max) {
	//乱数
	std::random_device rnd;

	std::mt19937 mt(rnd());
	std::uniform_real_distribution<> rate(min, max);

	return (float)rate(rnd);
}

int MyMath::RandomInt(int min, int max) {
	//乱数
	std::random_device rnd;

	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rate(min, max);

	return rate(rnd);
}

//度数法を弧度法に変換する関数
float MyMath::Deg2Rad(float Deg) {

	return Deg * 3.14f / 180.0f;

}

//弧度法を度数法に変換する関数
float MyMath::Rad2Deg(float rad) {

	return rad / 3.14f * 180.0f;

}

XMFLOAT3 MyMath::NormalizeXMFLOAT3(const XMFLOAT3& v)
{
	// Convert XMFLOAT3 to XMVECTOR
	XMVECTOR vec = XMLoadFloat3(&v);

	// Normalize the XMVECTOR
	vec = XMVector3Normalize(vec);

	// Store the result back in an XMFLOAT3
	XMFLOAT3 normalizedVec;
	XMStoreFloat3(&normalizedVec, vec);

	return normalizedVec;
}