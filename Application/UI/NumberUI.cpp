/*
* NumberUI.cpp
* 数字UIの処理
*/

#include "NumberUI.h"

void NumberUI::Initialize(SpriteCommon* spriteCommon, UINT texnumber, int digit) {

	drawDigit = digit;

	if (texnumber == 0) {
		fontWidth = fontWidthA;
		fontHeight = fontHeightA;
	}
	else {
		fontWidth = fontWidthB;
		fontHeight = fontHeightB;
	}

	// 全てのスプライトデータについて
	for (int i = 0; i < _countof(spriteDatas); i++)
	{
		// スプライトを生成する
		spriteDatas[i] = new Sprite();
		spriteDatas[i]->Initialize(spriteCommon);
		spriteDatas[i]->SetIndex(texnumber);
	}
}

void NumberUI::Finalize() {
	for (int i = 0; i < _countof(spriteDatas); i++) {
		delete spriteDatas[i];
	}
}

void NumberUI::Update(int number, DirectX::XMFLOAT2 pos, float scale, bool drawzero) {

	//0未満にはならない
	if (number < 0) {
		number = 0;
	}
	
	if (pow(10, drawDigit) <= number) {
		drawDigit++;
	}

	//numの桁数を求める
	int dig = 0;
	int num = number;

	// 0になるまで10で割る
	if (num == 0) {
		++dig;
	}
	while (num != 0)
	{
		num /= 10;
		// 割った回数をカウント
		++dig;
	}

	if (!drawzero) {
		drawDigit = dig;
	}

	// 全ての数字について
	for (int i = 0; i < drawDigit; i++) {
		
		int fontIndex = number / (int)pow(10,i);

		// 座標計算
		spriteDatas[spriteIndex]->SetPosition({ pos.x - ((fontWidth + spriteInterval) * scale * i) + (drawDigit - 1) * scale * fontWidth / 2, pos.y});
		spriteDatas[spriteIndex]->SetLeftTop({ (float)fontIndex * (float)fontWidth + 1, 0 });
		spriteDatas[spriteIndex]->SetTextureSize({ (float)fontWidth - 1, (float)fontHeight - 1 });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		spriteDatas[spriteIndex]->SetColor(color);

		// 文字を１つ進める
		spriteIndex++;
	}

	spriteIndex = 0;
}

void NumberUI::Draw() {
	// 全てのスプライトについて
	for (int i = 0; i < drawDigit; i++)
	{
		// スプライト描画
		spriteDatas[i]->Draw();
	}
	
}

