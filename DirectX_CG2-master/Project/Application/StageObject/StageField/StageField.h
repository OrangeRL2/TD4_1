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
  static const int cBlockCount_ = 1;

public:
  void Initialize();
  void Update();
  void Draw();
  void Finalize();

public:

private:
  Model* modelWoodBox_;
  std::vector<Object3d*> blockWoodBoxList_;

  std::map<std::string, Model*>  models_;

  LevelData* levelData_;
};
