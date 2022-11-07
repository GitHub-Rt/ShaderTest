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
    pFbx->Load("Assets\\oden.fbx");

    transform_.scale_.x = 0.25f;
    transform_.scale_.y = 0.25f;
    transform_.scale_.z = 0.25f;
    transform_.position_.z -= 10.0f;

    Instantiate<MiniOden>(this);
}

//更新
void Player::Update()
{
    transform_.rotate_.y++;

    //左右移動
    if (Input::IsKey(DIK_D))
    {   
        //右移動
        transform_.position_.x += 0.05f;
    }
    if (Input::IsKey(DIK_A))
    {
        //左移動
        transform_.position_.x -= 0.05f;
    }


    //弾の出力
    if (Input::IsKeyDown(DIK_SPACE))
    {
        GameObject* pBullet = Instantiate<Bullet>(pParent_);
        pBullet->SetPosition(transform_.position_);
    }
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