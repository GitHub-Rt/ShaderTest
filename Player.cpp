#include "Player.h"
#include "Bullet.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "MiniOden.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
    Release();
}

//������
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

//�X�V
void Player::Update()
{
    transform_.rotate_.y++;

    //���E�ړ�
    if (Input::IsKey(DIK_D))
    {   
        //�E�ړ�
        transform_.position_.x += 0.05f;
    }
    if (Input::IsKey(DIK_A))
    {
        //���ړ�
        transform_.position_.x -= 0.05f;
    }


    //�e�̏o��
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

//�`��
void Player::Draw()
{
    pFbx->Draw(transform_);
}

void Player::DrawSub()
{
    Draw();
}

//�J��
void Player::Release()
{
    FBX_SAFE_DELETE(pFbx);
}

void Player::ReleaseSub()
{
    Release();
}