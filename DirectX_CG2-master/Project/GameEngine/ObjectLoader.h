#pragma once
#include <Model.h>

#include <memory>
#include <List>
#include <Object3d.h>

class ObjectLoader {
public:
  //モデル名
  enum modelName {
    modelWoodBox_
  };

  //オブジェクト名
  enum objName {
    objWoodBox_
  };

public:
  void CreateModelList();

  void CreateObjectList();

  void ResetObjectList();

  void Finalize();

  //モデル取得
  Model* GetModel(int32_t modelName) const {
    return models_[modelName].get();
  }

  Object3d* GetObject3d(int32_t object3dName) const {
    return objs_[object3dName].get();
  }

private:
  //モデルリスト
  std::vector<std::unique_ptr<Model>> models_;

  //オブジェリスト
  std::vector<std::unique_ptr<Object3d>> objs_;

private:
  ObjectLoader() = default;
  ~ObjectLoader();
  //コピーコンストラクタを無効
  ObjectLoader(const ObjectLoader&) = delete;
  //代入演算子を無効
  const ObjectLoader& operator=(const ObjectLoader&) = delete;

public://static
  static ObjectLoader* GetInstance();
};
