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
    pFbx->Load("Assets\\torus.fbx");

    
}

//�X�V
void Player::Update()
{
    transform_.rotate_.y++;
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