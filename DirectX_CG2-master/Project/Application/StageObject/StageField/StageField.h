/*
* StageField.h
* ステージ用のフィールド
*/

#pragma once

#include "Model.h"
#include "Object3d.h"

#include "ObjectLoader.h"

#include <memory>
#include <List>

class StageField {
public:
  void Initialize();
  void Update();
  void Draw();
  void Finalize();

public:
  static ObjectLoader* objectLoader_;

private:
  std::unique_ptr<Model> modelWoodBox_;

  std::list< std::unique_ptr<Object3d> > blockWoodBoxList_;
};
