#include "PlayScene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//必要オブジェクトの呼び出し
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);

}

//更新
void PlayScene::Update()
{
	
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}