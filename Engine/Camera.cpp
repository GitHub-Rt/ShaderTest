#include "Camera.h"

//変数
XMVECTOR position_;		//カメラの位置（視点）
XMVECTOR target_;		//見る位置（焦点）
XMMATRIX viewMatrix_;	//ビュー行列
XMMATRIX projMatrix_;	//プロジェクション行列

//初期化
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -20, 0);	//カメラの位置
	target_ = XMVectorSet(0, 0, 0, 0);		//カメラの焦点

	//プロジェクション行列                  v----視野角　この場合45°をラジアンで表記 --> XMConvertToRadians(x°)で表記しても問題ない
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.5f, 100.0f);
	//                                          アスペクト比 ------↑           ↑----　これより近いものは表示しないよって値が第三引数(近クリッピング)、最後の引数はこれより遠いものは描画しないよの値(遠クリッピング)
}

//更新
void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	position = position_;
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target)
{
	target = target_;
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	return (viewMatrix_);
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	return (projMatrix_);
}