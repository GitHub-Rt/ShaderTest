#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//◆◆◆を管理するクラス
class MiniOden : public GameObject
{
    Fbx* pFbx;
    int hModel_;    //モデル番号

public:
    //コンストラクタ
    MiniOden(GameObject* parent);

    //デストラクタ
    ~MiniOden();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};