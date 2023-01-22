
//    register ----v�@�����o���݂����Ȃ���
Texture2D tex : register(t0);		//�e�N�X�`���[���󂯎��
SamplerState smp : register(s0);	//�T���v�����󂯎��



cbuffer global
{
	float4x4 matW;			//���[���h�s��
	float4x4 matWVP;		//���[���h�E�r���[�E�v���_�N�V�����̍����s��
	float4x4 matNormal;		//�@���ό`�����邽�߂̍s��
	float4  camPos;			//�J�����̈ʒu
	float4	 color;			//�}�e���A���̐F
	float4 ambient;			//����
	float4 specular;		//�n�C���C�g�̐F
	float	shiness;		//�n�C���C�g�̋���
	bool	 isTexture;		//�e�N�X�`���̗L��
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float4 color : COLOR0;
	float4 specular : COLOR1;
	float4 V : COLOR2;
	float4 R : COLOR3;
	float4 light : COLOR4;
	float4 normal : COLOR5;
	float4 lightPos : COLOR6;
};


//���_�V�F�[�_�[
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�ɓn���ϐ�
	VS_OUT outData;


	outData.pos = mul(pos, matWVP);		//�x�N�g�����s��ŕό`������֐� --> mul(�x�N�g��,�s��)
	outData.uv = uv;

	//���C�g�̈ʒu
	outData.lightPos = float4(0, 5, 0, 0);

	////���C�g�̌���
	//outData.light = float4(0, 0, -1, 0);
	//outData.light = normalize(outData.light);

	//�@��
	outData.normal = mul(normal, matNormal);
	outData.normal.w = 0;

	//outData.color = dot(normal, light);
	//outData.color = clamp(outData.color, 0, 1);

	////�����x�N�g��(���_����J�����Ɍ������x�N�g��)
	//outData.V = normalize(camPos - mul(pos, matW));

	////���˂������̃x�N�g��   : reflect�֐�(�x�N�g���A�@��)
	//outData.R = reflect(light, normal);

	////���ςׂ̂���Ńn�C���C�g�ɂȂ�
	//outData.specular = pow(clamp(dot(R, V), 0, 1), 5) * 5;

	//�܂Ƃ߂ēn��
	return outData;
}

//�s�N�Z���V�F�[�_�[
//�i�j : �Z�}���e�B�N�X----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient_;

	//���_�̈ʒu���猩�����̕���
	inData.light = inData.pos - inData.lightPos;
	inData.light = normalize(inData.light);

	
	inData.color = dot(inData.normal, inData.light);
	inData.color = clamp(inData.color, 0, 1);

	//�����x�N�g��(���_����J�����Ɍ������x�N�g��)
	inData.V = normalize(camPos - mul(inData.pos, matW));

	//���˂������̃x�N�g��   : reflect�֐�(�x�N�g���A�@��)
	inData.R = reflect(inData.light, inData.normal);

	//���ςׂ̂���Ńn�C���C�g�ɂȂ�
	//inData.specular = pow(clamp(dot(inData.R, inData.V), 0, 1), 5) * 5;
	inData.specular = pow(clamp(dot(inData.R, inData.V), 0, 1), shiness) * specular;



	if (isTexture == true)
	{
		diffuse = tex.Sample(smp, inData.uv) * inData.color;
		ambient_ = tex.Sample(smp, inData.uv) * ambient;
	}
	else
	{
		diffuse = color * inData.color;
		ambient_ = color * ambient;
	}
	return diffuse + ambient_ + inData.specular;
}