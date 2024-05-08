/*
* NumberUI.h
* 数字UIの処理
*/

#pragma once
#include"Sprite.h"

class NumberUI
{
public:
	static const int maxDigit = 16;	// 最大桁数
	static const int fontWidthA = 80;			// フォント画像内1文字分の横幅(A)
	static const int fontHeightA = 128;		// フォント画像内1文字分の縦幅(A)

	static const int fontWidthB = 160;			// フォント画像内1文字分の横幅(B)
	static const int fontHeightB = 256;		// フォント画像内1文字分の縦幅(B)

	///<summary>初期化</summary>
	void Initialize(SpriteCommon* spriteCommon, UINT texnumber, int digit);

	///<summary>終了処理</summary>
	void Finalize();

	///<summary>更新</summary>
	void Update(int number, DirectX::XMFLOAT2 pos, float scale, bool drawzero);

	///<summary>描画</summary>
	void Draw();

	//セッター
	void SetColor(DirectX::XMFLOAT4 col) { color = col; }

private:
	int fontWidth;			// フォント画像内1文字分の横幅
	int fontHeight;		// フォント画像内1文字分の縦幅

	// スプライトデータの配列
	Sprite* spriteDatas[maxDigit] = {};
	//色
	DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
	//表示桁数
	int drawDigit = 0;

	//数字の間隔
	float spriteInterval = 10.0f;
};

