#include "Input.h"


namespace Input
{

	LPDIRECTINPUT8 pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//�L�[�{�[�h
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];				//�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	float mousePosition;

	//�R���g���[���[
	XINPUT_STATE controllerState_;


	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr;
		hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"DirectInput8Create�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
			return hr;
		}

		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"Device�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
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
		SAFE_RELEASE(pDInput);//LPDIRECTINPUT8 pDInput = nullptr;��RELEASE����
	}

	
	///////////// �L�[�{�[�h /////////////

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)//128�r�b�g��
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
		//���͉����ĂāA�O��͉����ĂȂ�
		if ((keyState[keyCode] & 0x0080) && (prevKeyState[keyCode] & 0x0080) != (keyState[keyCode] & 0x0080))
		{
			return true;
		}
		return false;
	}


	////////////// �}�E�X /////////////

	float GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = ((float)x, (float)y, 0, 0);
	}



	////////////// �R���g���[���[ /////////////

	bool IsPad(int Pad)
	{
		XInputGetState(0, &controllerState_);//(0, &controllerState_);������Ȃ��ł��Ȃ�����O
		if (controllerState_.Gamepad.wButtons & Pad)//�{�^���̐ݒ�
		{
			return TRUE; //�����Ă�
		}
		return FALSE; //�����ĂȂ�
	}

	float IsGetStick_Left_X()
	{
		float value = controllerState_.Gamepad.sThumbLX;// ���X�e�B�b�N�̉������̌X���
		value = value / 32767;
		if (value <= 0.2f && value >= -0.2f)
		{
			value = 0.0f;
		}
		return value;
	}


	float IsGetStick_Right_Y()
	{
		float value = controllerState_.Gamepad.sThumbLY;// ���X�e�B�b�N�̏c�����̌X���
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
		vibration.wLeftMotorSpeed = LeftVibration; // �����[�^�[�̋���
		vibration.wRightMotorSpeed = RightVibration;// �E���[�^�[�̋���
		XInputSetState(0, &vibration);
	}



}