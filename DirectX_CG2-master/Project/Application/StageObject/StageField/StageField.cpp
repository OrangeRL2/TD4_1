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

  //modelWoodBox_ =
  //  ObjectLoader::GetInstance()->GetModel(
  //  ObjectLoader::modelName::modelWoodBox_);

 //  models_.insert(std::make_pair("WoodenBox", modelWoodBox_));

   //sampleBlock_ = Object3d::Create();
   //sampleBlock_->Initialize();
   //sampleBlock_->SetModel(Model::LoadFromOBJ("WoodenBox"));

   //sampleBlock_->SetPosition({0,0,0});
   //sampleBlock_->SetRotation({0,0,0});
   //sampleBlock_->SetScale({1,1,1});
   //sampleBlock_->Update();

   for(int i = 0; i<cBlockCount_; i++) {
     blocks_[i] = Object3d::Create();
     blocks_[i]->Initialize();
     blocks_[i]->SetModel(Model::LoadFromOBJ("WoodenBox"));

     blocks_[i]->SetPosition({
       -cBlockCount_  + (float)i,
       0,0});
     blocks_[i]->SetRotation({0,0,0});
     blocks_[i]->SetScale({1,1,1});
     blocks_[i]->Update();
   }

   //for (auto& objectData :
   //  LevelLoader::LoadFile("StageField")->objects) {
   //  // ファイル名から登録済みモデルを検索
   //  Model* model =
   //    nullptr;
   //  decltype(models_)::iterator it =
   //    models_.find(objectData.fileName);
   //  if (it != models_.end()) {
   //    model = it->second;
   //  }

   //  Object3d* newBlock = Object3d::Create();

   //  newBlock->Initialize();

   //  newBlock->SetModel(Model::LoadFromOBJ("WoodenBox"));

   //  // 座標
   //  DirectX::XMFLOAT3 pos;
   //  DirectX::XMStoreFloat3(&pos, objectData.translation);
   //  newBlock->SetPosition(pos);

   //  // 回転角
   //  DirectX::XMFLOAT3 rot;
   //  DirectX::XMStoreFloat3(&rot, objectData.rotation);
   //  newBlock->SetRotation(rot);

   //  // 座標
   //  DirectX::XMFLOAT3 scale;
   //  DirectX::XMStoreFloat3(&scale, objectData.scaling);
   //  newBlock->SetScale(scale);

   //  //色
   //  DirectX::XMFLOAT4 color = { 0,0,0,0 };
   //  newBlock->SetColor(color);

   //  newBlock->Update();

   //  blockWoodBoxList_.push_back(newBlock);

   //  sampleBlock_->SetModel(model);
   //  sampleBlock_->SetPosition(pos);
   //  sampleBlock_->SetRotation(rot);
   //  sampleBlock_->SetScale(scale);
   //  sampleBlock_->Update();
   //}
}

void StageField::Update() {
  //for(auto& block : blockWoodBoxList_) {
  //  DirectX::XMFLOAT3 pos = block->GetPosition();

  //  pos.z += 0.5f;
  //  block->SetPosition(pos);
  //  block->Update();
  //}

  DirectX::XMFLOAT3 pos =
    blocks_[cBlockCount_/2]->GetPosition();

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
  //sampleBlock_->SetPosition(pos);

 // sampleBlock_->Update();

  for(int i = 0; i<cBlockCount_; i++) {
    blocks_[i]->Update();
  }
}

void StageField::Draw() {
  //for(auto& block : blockWoodBoxList_) {
  //  block->Draw();
  //}
  //sampleBlock_->Draw();

  for(int i = 0; i<cBlockCount_; i++) {
    blocks_[i]->Draw();
  }

}

void StageField::Finalize() {
  //delete modelWoodBox_;

  //for (Object3d*& block : blockWoodBoxList_) {
  //  delete block;
  //}

  for(int i = 0; i<cBlockCount_; i++) {
    delete blocks_[i];
  }


 // delete sampleBlock_;
}
