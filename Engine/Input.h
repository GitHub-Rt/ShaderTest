#pragma once



#include <dInput.h>
#include "XInput.h"



#pragma comment(lib,"Xinput.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")



#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}



namespace Input
{
	HRESULT Initialize(HWND hWnd);
	void Update();					
	void Release();

	//�L�[�{�[�h
	bool IsKey(int keyCode);		//�L�[��������Ă�����ture ������ĂȂ����false
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	
	//�}�E�X
	void SetMousePosition(int x, int y);
	float GetMousePosition();

	//�R���g���[���[
	bool IsPad(int Pad);			//�R���g���[���[�֐�
	float IsGetStick_Left_X();		//���X�e�B�b�N���֐�
	float IsGetStick_Right_Y();		//���X�e�B�b�N�c�֐�
	void Vibration(float LeftVibration, float RightVibration);	//�U���֐�
};