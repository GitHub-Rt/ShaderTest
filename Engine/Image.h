#pragma once

#include <vector>
#include <string>
#include "Sprite.h"
#include "Transform.h"


namespace Image
{
	//�摜���
	struct ImageData
	{
		//�t�@�C����
		std::string fileName;

		//���[�h�����摜�f�[�^�̃A�h���X
		Sprite* pSprite;

		//�s��
		Transform transform;

		//�R���X�g���N�^
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