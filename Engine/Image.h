#pragma once

#include <vector>
#include <string>
#include "Sprite.h"
#include "Transform.h"


namespace Image
{
	//画像情報
	struct ImageData
	{
		//ファイル名
		std::string fileName;

		//ロードした画像データのアドレス
		Sprite* pSprite;

		//行列
		Transform transform;

		//コンストラクタ
		ImageData() : pSprite(nullptr)
		{
			fileName = "";
			pSprite = nullptr;
		}
	};

	int Load(std::string fileName);
	void Draw(int handle);
	void Release(int handle);
	void SetTransform(int handle, Transform& transform);
	XMMATRIX GetMatrix(int handle);
}