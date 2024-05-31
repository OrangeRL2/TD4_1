/*
* StageField.cpp
* ステージ用のフィールド
*/

#include "StageField.h"
#include "DirectXCommon.h"
#include "Framewark.h"

#include "LevelLoader.h"
#include <cassert>
#include <sstream>
#include <iomanip>

void StageField::Initialize() {
  levelData_ = LevelLoader::LoadFile("StageField");

   modelWoodBox_ = Model::LoadFromOBJ("WoodenBox");
   models_. insert(std::make_pair("WoodenBox", modelWoodBox_));

  for(auto& objectData : levelData_->objects) {
    // ファイル名から登録済みモデルを検索
   Model* model =
     nullptr;
    decltype(models_)::iterator it =
      models_.find(objectData.fileName);
    if (it != models_.end()) {
      model = it->second;
    }

    Object3d* newBlock = Object3d::Create();

    newBlock->SetModel(modelWoodBox_);

    // 座標
    DirectX::XMFLOAT3 pos;
    DirectX::XMStoreFloat3(&pos, objectData.translation);
    newBlock->SetPosition(pos);

    // 回転角
    DirectX::XMFLOAT3 rot;
    DirectX::XMStoreFloat3(&rot, objectData.rotation);
    newBlock->SetRotation(rot);

    // 座標
    DirectX::XMFLOAT3 scale;
    DirectX::XMStoreFloat3(&scale, objectData.scaling);
    newBlock->SetScale(scale);

    //色
    DirectX::XMFLOAT4 color = {0,0,0,0};
    newBlock->SetColor(color);

    blockWoodBoxList_.push_back(newBlock);
  }
}

void StageField::Update() {
  for(auto& block : blockWoodBoxList_) {
    block->Update();
  }
}

void StageField::Draw() {
  for(auto& block : blockWoodBoxList_) {
    block->Draw();
  }
}

void StageField::Finalize() {
  delete modelWoodBox_;

  for (Object3d*& block : blockWoodBoxList_) {
    delete block;
  }
  delete levelData_;
}
