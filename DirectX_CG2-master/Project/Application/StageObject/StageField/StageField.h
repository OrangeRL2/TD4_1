/*
* StageField.h
* ステージ用のフィールド
*/

#pragma once

#include "Model.h"
#include "Object3d.h"

#include "ObjectLoader.h"

#include <map>
//#include <memory>
//include <List>

struct LevelData;

class StageField {
public:
  static const int cBlockCount_ = 100;

public:
  void Initialize();
  void Update();
  void Draw();
  void Finalize();

public:
  void SetViewProjection(ViewProjection& vp) {
    viewProjection_ = &vp;
  }

  std::vector<Object3d*> GetList() {
    return blockWoodBoxList_;
  }

private:
  Model* modelWoodBox_;
  Object3d* sampleBlock_;

  Object3d* blocks_[100];

  std::vector<Object3d*> blockWoodBoxList_;

  std::map<std::string, Model*>  models_;

  LevelData* levelData_;

  //ビュープロジェクション
  ViewProjection* viewProjection_ = nullptr;
};
