#pragma once
#include "GameObject.h"
class RootJob :
    public GameObject
{
public:
    RootJob(GameObject* parent);
    ~RootJob();
    void Initialize();
    void Update();
    void Draw();
    void Release();
};

