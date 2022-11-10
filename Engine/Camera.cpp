#include "Camera.h"

//�ϐ�
XMVECTOR position_;		//�J�����̈ʒu�i���_�j
XMVECTOR target_;		//����ʒu�i�œ_�j
XMMATRIX viewMatrix_;	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -20, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);		//�J�����̏œ_

	//�v���W�F�N�V�����s��                  v----����p�@���̏ꍇ45�������W�A���ŕ\�L --> XMConvertToRadians(x��)�ŕ\�L���Ă����Ȃ�
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.5f, 100.0f);
	//                                          �A�X�y�N�g�� ------��           ��----�@������߂����͕̂\�����Ȃ�����Ēl����O����(�߃N���b�s���O)�A�Ō�̈����͂����艓�����͕̂`�悵�Ȃ���̒l(���N���b�s���O)
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position = position_;
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target = target_;
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return (viewMatrix_);
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return (projMatrix_);
}