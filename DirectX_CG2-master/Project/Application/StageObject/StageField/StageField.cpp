/*
* StageField.cpp
* ステージ用のフィールド
*/

#include "StageField.h"
#include "DirectXCommon.h"
#include "Framewark.h"

ObjectLoader* StageField::objectLoader_ = ObjectLoader::GetInstance();

void StageField::Initialize() {
  std::unique_ptr<Object3d> newBlock =
    std::make_unique<Object3d>();

  //newBlock->Initialize();
  //newBlock->SetModel(
  //    objectLoader_->GetModel(
  //      ObjectLoder::modelName::modelWoodBox_
  //    )
  //);
  //newBlock->SetPosition({0,0,0});
  //newBlock->SetScale({10.0,10.0,10.0});
  //newBlock->SetScaleMax({10.0,10.0,10.0});
  //newBlock->SetRotation({0,0,0});
  //newBlock->SetColor({1.0,1.0,1.0,1.0});
  //
  //newBlock->Update();

  newBlock.reset(objectLoader_->GetObject3d(ObjectLoader::objName::objWoodBox_));

  blockWoodBoxList_.push_back(std::move(newBlock));
}

void StageField::Update() {
  for (std::unique_ptr<Object3d>& block : blockWoodBoxList_) {
    block->Update();
  }
}

void StageField::Draw() {
  for (std::unique_ptr<Object3d>& block : blockWoodBoxList_) {
    block->Draw();
  }
}

void StageField::Finalize() {
  //blockWoodBoxList_.clear();
}
