
//    register ----v�@�����o���݂����Ȃ���
Texture2D tex : register(t0);		//�e�N�X�`���[���󂯎��
SamplerState smp : register(s0);	//�T���v�����󂯎��



cbuffer global
{
	float4x4 matWVP;		//�s��
	float4	 color;			//�}�e���A���̐F
	bool	 isTexture;		//�e�N�X�`���̗L��
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};


//���_�V�F�[�_�[
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD )
{
	//�s�N�Z���V�F�[�_�[�ɓn���ϐ�
	VS_OUT outData;

	
	outData.pos = mul(pos,matWVP);		//�x�N�g�����s��ŕό`������֐� --> mul(�x�N�g��,�s��)
	outData.uv = uv;


	//�܂Ƃ߂ēn��
	return outData;
}

//�s�N�Z���V�F�[�_�[
//�i�j : �Z�}���e�B�N�X----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{

	//�O���f�[�V����
	//return float4(1 -(pos.x / 800 ), 1, 1, 1);

	if (isTexture)
	{
		return tex.Sample(smp, inData.uv);
	}
	else
	{
		return color;
 }
	
}