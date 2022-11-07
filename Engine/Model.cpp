#include <vector>
#include "Model.h"
#include "Fbx.h"
#include "Direct3D.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx;
		Transform transform;
		std::string fileName;
	};
	std::vector<ModelData*>	_datas;
}

int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->fileName = fileName;
	pData->pFbx = nullptr;
	for (int i = 0; i < _datas.size(); i++)
	{
		if (_datas[i]->fileName == fileName)
		{
			pData->pFbx = _datas[i]->pFbx;
			break;
		}
	}

	if (pData->pFbx == nullptr)
	{
		pData->pFbx = new Fbx;
		pData->pFbx->Load(fileName);
	}


	_datas.push_back(pData);
	return _datas.size() - 1;
}

void Model::SetTransform(int hModel, Transform transform)
{
	_datas[hModel]->transform = transform;
}

void Model::Draw(int hModel)
{
	_datas[hModel]->pFbx->Draw(_datas[hModel]->transform);
}

//解放処理
void Model::Release()
{
	for (int i = 0;i < _datas.size();i++)
	{
		bool isExist = false;	//今消そうとするFbxデータを参照しているのがいるのかどうか
		for (int j = i + 1; j < _datas.size(); j++)
		{
			if (_datas[i]->pFbx == _datas[j]->pFbx)
			{
				isExist = true;
				break;
			}
		}
		//もうそのデータが参照されていなければ
		if (!isExist)
		{
			FBX_SAFE_DELETE(_datas[i]->pFbx);
		}
		FBX_SAFE_DELETE(_datas[i]);
	}

	_datas.clear();
}