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

	//キーボード
	bool IsKey(int keyCode);		//キーが押されていたらture 押されてなければfalse
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	
	//マウス
	void SetMousePosition(int x, int y);
	float GetMousePosition();

	//コントローラー
	bool IsPad(int Pad);			//コントローラー関数
	float IsGetStick_Left_X();		//左スティック横関数
	float IsGetStick_Right_Y();		//左スティック縦関数
	void Vibration(float LeftVibration, float RightVibration);	//振動関数
};