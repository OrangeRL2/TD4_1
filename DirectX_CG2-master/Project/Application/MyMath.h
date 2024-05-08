/*
* Easing.h
* イージングの処理
*/

#pragma once
#include <DirectXMath.h>
#include <random>

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

	

};