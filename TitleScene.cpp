#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Assets/TitleLogo.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void TitleScene::Update()
{
	//Enter����������v���C�V�[����
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	//Esc����������v���O�������I��������
	if (Input::IsKeyDown(DIK_ESCAPE))
	{
		quick_exit;
	}
}

//�`��
void TitleScene::Draw()
{
	//�摜�̕`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleScene::Release()
{
}