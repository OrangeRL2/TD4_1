/*
* Button.cpp
* ボタンUIの処理
*/

#include "Button.h"
using namespace OogamiEngine;

void Button::Initialize(Input* input, SpriteCommon* spriteCommon, int index) {
	se_ = SEManager::GetInstance();
	spriteCommon_ = spriteCommon;
	input_ = input;

	sprite_ = new Sprite();
	sprite_->Initialize(spriteCommon_,index);

	size_ = sprite_->GetSize();

}
void Button::UpdateMouse(DirectX::XMFLOAT2 mouse) {
	MouseCollision(mouse);
}

void Button::Update(DirectX::XMFLOAT2 pos,float size) {

	sprite_->SetPosition(pos);
	sprite_->SetSize({ size_.x * size,size_.y * size});
	sprite_->Update();

}

void Button::MouseCollision(DirectX::XMFLOAT2 mouse) {

	isPush = false;
	DirectX::XMFLOAT2 pos = sprite_->GetPosition();
	DirectX::XMFLOAT2 size = sprite_->GetSize();

	//ボタンとカーソルが重なったら
	if (mouse.x >= pos.x - size.x / 2 &&
		mouse.y >= pos.y - size.y / 2 &&
		mouse.x <= pos.x + size.x / 2 &&
		mouse.y <= pos.y + size.y / 2) {

	
		isSoundPlay = true;

		//ボタンサイズ変更
		const float s = 5.0f;
		size.x += size.x / s;
		size.y += size.y / s;

		//左クリックでフラグをオン
		if (input_->OnMouseDown(Input::MouseButton::Left)) {
			isPush = true;
		}
	}
	else {
		isSoundPlay = false;
	}

	sprite_->SetSize(size);
	sprite_->Update();
}

void Button::Draw() {
	sprite_->Draw();
}