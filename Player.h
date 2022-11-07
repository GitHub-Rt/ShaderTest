#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    Fbx* pFbx;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;
    void UpdateSub();

    //描画
    void Draw() override;
    void DrawSub();

    //開放
    void Release() override;
    void ReleaseSub();
};