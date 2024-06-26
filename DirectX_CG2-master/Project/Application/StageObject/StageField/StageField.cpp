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
   for (auto& objectData :
     LevelLoader::LoadFile("StageField")->objects) {
     //// ファイル名から登録済みモデルを検索
     Model* model = Model::LoadFromOBJ("WoodenBox");

     Object3d* newBlock = Object3d::Create();

     newBlock->Initialize();

     newBlock->SetModel(model);

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
     DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };
     newBlock->SetColor(color);

     newBlock->Update();

     blockWoodBoxList_.push_back(newBlock);
   }
}

void StageField::Update() {
  for(auto& block : blockWoodBoxList_) {
    DirectX::XMFLOAT3 pos = block->GetPosition();

    pos.z += 0.5f;
    block->SetPosition(pos);
    block->Update();
  }

  DirectX::XMFLOAT3 pos =
      blockWoodBoxList_.front()->GetPosition();

  viewProjection_->SetEye({
    pos.x,
    pos.y,
    pos.z - 30.0f
    });
  viewProjection_->SetTarget({
    pos.x,
    pos.y,
    pos.z
    });
  viewProjection_->SetUp({ 0,1,0 });
}

void StageField::Draw() {
  for(auto& block : blockWoodBoxList_) {
    block->Draw();
  }
}

void StageField::Finalize() {
  for (Object3d*& block : blockWoodBoxList_) {
    delete block;
  }
}
