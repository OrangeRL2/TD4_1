#include "PressSpace.h"

void PressSpace::Initialize(SpriteCommon* spriteCommon) {

	SP = std::make_unique<Sprite>();
	SP->Initialize(spriteCommon, SpriteManager::space);
	SP->SetPosition({ WinApp::window_width / 2, 650 });
	SP->SetSize({ SP->GetSize().x * 0.75f,SP->GetSize().y * 0.75f });
}

void PressSpace::Update() {

	if (isActive) {

		UITimer--;
		if (UITimer <= 0) {
			if (isUIDraw) {
				isUIDraw = false;
			}
			else {
				isUIDraw = true;
			}

			UITimer = MaxUITimer;
		}
	}
}

void PressSpace::Draw() {

	if (isUIDraw && isActive) {
		SP->Draw();
	}
}