#include "Player.h"
#include "Bullet.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "MiniOden.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr)
{
}

//デストラクタ
Player::~Player()
{
    Release();
}

//初期化
void Player::Initialize()
{
    pFbx = new Fbx;
    pFbx->Load("Assets\\Ground.fbx");

    transform_.scale_.x = 2.0f;
    transform_.scale_.y = 2.0f;
    transform_.scale_.z = 2.0f;

    transform_.position_.y = 1.2f;
    transform_.position_.z = -10.0f;
}

//更新
void Player::Update()
{
    //transform_.rotate_.y++;
}

void Player::UpdateSub()
{
    Update();
}

//描画
void Player::Draw()
{
    pFbx->Draw(transform_);
}

void Player::DrawSub()
{
    Draw();
}

//開放
void Player::Release()
{
    FBX_SAFE_DELETE(pFbx);
}

void Player::ReleaseSub()
{
    Release();
}