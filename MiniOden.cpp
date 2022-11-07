#include "MiniOden.h"

//�R���X�g���N�^
MiniOden::MiniOden(GameObject* parent)
    :GameObject(parent, "MiniOden"),pFbx(nullptr),hModel_(-1)
{
}

//�f�X�g���N�^
MiniOden::~MiniOden()
{
}

//������
void MiniOden::Initialize()
{
    pFbx = new Fbx;
    pFbx->Load("Assets/oden.fbx");


    transform_.scale_.x = 0.5f;
    transform_.scale_.y = 0.5f;
    transform_.scale_.z = 0.5f;

    transform_.position_.x += 3;
}

//�X�V
void MiniOden::Update()
{
}

//�`��
void MiniOden::Draw()
{
    pFbx->Draw(transform_);
}

//�J��
void MiniOden::Release()
{
}