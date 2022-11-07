#include "MiniOden.h"

//コンストラクタ
MiniOden::MiniOden(GameObject* parent)
    :GameObject(parent, "MiniOden"),pFbx(nullptr),hModel_(-1)
{
}

//デストラクタ
MiniOden::~MiniOden()
{
}

//初期化
void MiniOden::Initialize()
{
    pFbx = new Fbx;
    pFbx->Load("Assets/oden.fbx");


    transform_.scale_.x = 0.5f;
    transform_.scale_.y = 0.5f;
    transform_.scale_.z = 0.5f;

    transform_.position_.x += 3;
}

//更新
void MiniOden::Update()
{
}

//描画
void MiniOden::Draw()
{
    pFbx->Draw(transform_);
}

//開放
void MiniOden::Release()
{
}