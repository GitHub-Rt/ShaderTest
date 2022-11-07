#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Assets/TitleLogo.jpg");
	assert(hPict_ >= 0);
}

//更新
void TitleScene::Update()
{
	//Enterを押したらプレイシーンへ
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	//Escを押したらプログラムを終了させる
	if (Input::IsKeyDown(DIK_ESCAPE))
	{
		quick_exit;
	}
}

//描画
void TitleScene::Draw()
{
	//画像の描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}