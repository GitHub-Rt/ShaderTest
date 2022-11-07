#include "ClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//�R���X�g���N�^
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

//������
void ClearScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Assets/ClearLogo.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void ClearScene::Update()
{
	//Enter����������v���C�V�[����
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	//Space����������^�C�g���V�[����
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//�`��
void ClearScene::Draw()
{
	//�摜�̕`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void ClearScene::Release()
{
}