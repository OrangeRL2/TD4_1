/*
* PostEffect.h
* ポストエフェクトの処理
*/

#pragma once
#include "Sprite.h"

class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 描画コマンドの発行
    /// </summary>
    void Draw(SpriteCommon* spriteCommon);

private:

};

