#include "Input.h"


namespace Input
{

	LPDIRECTINPUT8 pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//キーボード
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];				//前フレームでの各キーの状態

	//マウス
	float mousePosition;

	//コントローラー
	XINPUT_STATE controllerState_;


	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr;
		hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"DirectInput8Createの作成に失敗しました", L"エラー", MB_OK);
			return hr;
		}

		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"Deviceの作成に失敗しました", L"エラー", MB_OK);
			return hr;
		}
		hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);


		return S_OK;
	}


	void Update() 
	{
		memcpy(prevKeyState, &keyState, sizeof(prevKeyState));

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);//LPDIRECTINPUT8 pDInput = nullptr;をRELEASEする
	}

	
	///////////// キーボード /////////////

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)//128ビット目
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if ((keyState[keyCode] & 0x0080) == 0 && (prevKeyState[keyCode] & 0x0080) != (keyState[keyCode] & 0x0080))
		{
			return true;
		}
		return false;

	}


	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if ((keyState[keyCode] & 0x0080) && (prevKeyState[keyCode] & 0x0080) != (keyState[keyCode] & 0x0080))
		{
			return true;
		}
		return false;
	}


	////////////// マウス /////////////

	float GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = ((float)x, (float)y, 0, 0);
	}



	////////////// コントローラー /////////////

	bool IsPad(int Pad)
	{
		XInputGetState(0, &controllerState_);//(0, &controllerState_);一個しかつないでいないから０
		if (controllerState_.Gamepad.wButtons & Pad)//ボタンの設定
		{
			return TRUE; //押してる
		}
		return FALSE; //押してない
	}

	float IsGetStick_Left_X()
	{
		float value = controllerState_.Gamepad.sThumbLX;// 左スティックの横方向の傾き具合
		value = value / 32767;
		if (value <= 0.2f && value >= -0.2f)
		{
			value = 0.0f;
		}
		return value;
	}


	float IsGetStick_Right_Y()
	{
		float value = controllerState_.Gamepad.sThumbLY;// 左スティックの縦方向の傾き具合
		value = value / 32767;
		if (value <= 0.2f && value >= -0.2f)
		{
			value = 0.0f;
		}
		return value;
	}

	void Vibration(float LeftVibration, float RightVibration)
	{
		LeftVibration = LeftVibration * 65535;
		RightVibration = RightVibration * 65635;

		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = LeftVibration; // 左モーターの強さ
		vibration.wRightMotorSpeed = RightVibration;// 右モーターの強さ
		XInputSetState(0, &vibration);
	}



}