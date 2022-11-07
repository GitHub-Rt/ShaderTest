#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//���������Ǘ�����N���X
class MiniOden : public GameObject
{
    Fbx* pFbx;
    int hModel_;    //���f���ԍ�

public:
    //�R���X�g���N�^
    MiniOden(GameObject* parent);

    //�f�X�g���N�^
    ~MiniOden();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};