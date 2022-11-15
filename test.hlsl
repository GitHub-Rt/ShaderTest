
//    register ----v�@�����o���݂����Ȃ���
Texture2D tex : register(t0);		//�e�N�X�`���[���󂯎��
SamplerState smp : register(s0);	//�T���v�����󂯎��



cbuffer global
{
	float4x4 matWVP;		//�s��
	float4x4 matNormal;		//�@���ό`�����邽�߂̍s��
	float4	 color;			//�}�e���A���̐F
	bool	 isTexture;		//�e�N�X�`���̗L��
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float4 color : COLOR;
};


//���_�V�F�[�_�[
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL )
{
	//�s�N�Z���V�F�[�_�[�ɓn���ϐ�
	VS_OUT outData;

	
	outData.pos = mul(pos,matWVP);		//�x�N�g�����s��ŕό`������֐� --> mul(�x�N�g��,�s��)
	outData.uv = uv;
	
	float4 light = float4(1, 1, -1, 0);
	light = normalize(light);

	normal = mul(normal, matNormal);

	outData.color = dot(normal, light);
	outData.color = clamp(outData.color, 0, 1);

	//�܂Ƃ߂ēn��
	return outData;
}

//�s�N�Z���V�F�[�_�[
//�i�j : �Z�}���e�B�N�X----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient;


	if (isTexture == true)
	{
		diffuse = tex.Sample(smp, inData.uv) * inData.color;
		ambient = tex.Sample(smp, inData.uv) * 0.3f;
	}
	else
	{
		diffuse = color * inData.color;
		ambient = color * 0.3f;
	}
	return diffuse + ambient;
}
