#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    Fbx* pFbx;

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;
    void UpdateSub();

    //�`��
    void Draw() override;
    void DrawSub();

    //�J��
    void Release() override;
    void ReleaseSub();
};