#include "ObjectLoader.h"
#include "DirectXCommon.h"
////モデルリスト
//std::vector<std::unique_ptr<Model>> ObjectLoader::models_;
//
////オブジェリスト
//std::vector<std::unique_ptr<Object3d>> ObjectLoader::objs_;

void ObjectLoader::CreateModelList() {
  std::unique_ptr<Model> newModel =
    std::make_unique<Model>();

#pragma region ModelLoad
   newModel.reset( Model::LoadFromOBJ("WoodenBox"));
#pragma endregion

  models_.push_back(std::move(newModel));

  newModel.release();
}

void ObjectLoader::CreateObjectList() {
  std::unique_ptr<Object3d> newObject3d =
    std::make_unique<Object3d>();
#pragma region Obecte3dLoad
  newObject3d->Initialize();
  newObject3d->SetModel(
    models_[ObjectLoader::objName::objWoodBox_].get()
  );
  newObject3d->SetPosition({0,0,0});
  newObject3d->SetScale({10.0,10.0,10.0});
  newObject3d->SetScaleMax({10.0,10.0,10.0});
  newObject3d->SetRotation({0,0,0});
  newObject3d->SetColor({1.0,1.0,1.0,1.0});

  objs_.push_back(std::move(newObject3d));
#pragma endregion

  newObject3d.release();
}

void ObjectLoader::Finalize() {
  objs_.clear();
  models_.clear();
}

ObjectLoader::~ObjectLoader() {
}

ObjectLoader* ObjectLoader::GetInstance() {
  static ObjectLoader instance;
  return &instance;
}
