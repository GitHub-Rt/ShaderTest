#include "PlayScene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//�K�v�I�u�W�F�N�g�̌Ăяo��
	Instantiate<Player>(this);
	//Instantiate<Enemy>(this);

}

//�X�V
void PlayScene::Update()
{
	
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}