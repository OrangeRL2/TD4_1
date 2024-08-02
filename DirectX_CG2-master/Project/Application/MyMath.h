/*
* Easing.h
* イージングの処理
*/

#pragma once
#include <DirectXMath.h>
#include <random>
using namespace DirectX;

class MyMath {

public:
	static const float PI;	//円周率

	//速 >>> 遅 Type1
	static float easeOutCubic(float x);

	//速 >>> 遅 Type2
	static float easeOutQuint(float x);

	//遅 >>> 速 >>> 遅
	static float easeInOutSine(float x);

	//速 >>> 遅(戻り)
	static float easeOutBack(float x);

	//遅 >>> 速
	static float easeInCubic(float x);

	/// <summary>
	/// 乱数(float)
	/// </summary>
	static float RandomFloat(float min, float max);

	/// <summary>
	/// 乱数(int)
	/// </summary>
	static int RandomInt(int min, int max);

	//度数法⇔弧度法の関数
	static float Deg2Rad(float Deg);	//度数法を弧度法に変換する関数
	static float Rad2Deg(float rad);	//弧度法を度数法に変換する関数

	XMFLOAT3 NormalizeXMFLOAT3(const XMFLOAT3& v);

};