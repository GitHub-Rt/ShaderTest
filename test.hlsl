
//���_�V�F�[�_�[
float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

//�s�N�Z���V�F�[�_�[
//�i�j : �Z�}���e�B�N�X�@
float4 PS(float4 pos:SV_POSITION) : SV_TARGET
{
	//pos�ɂ̓X�N���[����̃s�N�Z����������
	
	return float4(1 -(pos.x / 800 ), 1, 1, 1);
}