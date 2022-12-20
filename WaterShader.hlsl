
//    register ----v�@�����o���݂����Ȃ���
Texture2D tex : register(t0);		//�e�N�X�`���[���󂯎��
SamplerState smp : register(s0);	//�T���v�����󂯎��
Texture2D texNormal:register(t1);	//Normal�e�N�X�`���[���󂯎��


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
	float scroll;			//uv�X�N���[��
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float4 color : TEXCOORD1;
	float4 specular : TEXCOORD2;
	float4 V : TEXCOORD3;
	float4 R : TEXCOORD4;
	float4 light : TEXCOORD5;
	float4 normal : TEXCOORD6;
};


//���_�V�F�[�_�[
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//�s�N�Z���V�F�[�_�[�ɓn���ϐ�
	VS_OUT outData;


	outData.pos = mul(pos, matWVP);		//�x�N�g�����s��ŕό`������֐� --> mul(�x�N�g��,�s��)
	outData.uv = uv;


	//�@��
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	normal.w = 0;


	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);
	tangent.w = 0;

	//�]�@��
	float3 binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);


	//�����x�N�g��(���_����J�����Ɍ������x�N�g��)
	float4 eye = normalize(camPos - mul(outData.pos, matW));
	outData.V.x = dot(eye, tangent);
	outData.V.y = dot(eye, binormal);
	outData.V.z = dot(eye, normal);
	outData.V.w = 0;


	//���C�g����
	float4 light = float4(1, 3, -1, 0);
	light = normalize(light);

	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//�܂Ƃ߂ēn��
	return outData;
}

//�s�N�Z���V�F�[�_�[
//�i�j : �Z�}���e�B�N�X----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient_;

	float2 uv1 = inData.uv;
	uv1.x += scroll;
	float4 normal1 = texNormal.Sample(smp, uv1) * 2 - 1;


	float2 uv2 = inData.uv;
	uv2.x -= scroll * 0.3;
	uv2.y *= 1.2f;
	float4 normal2 = texNormal.Sample(smp, uv2) * 2 - 1;

	float4 normal = normal1 + normal2;
	normal.w = 0;
	normal = normalize(normal1);


	inData.color = dot(normal, inData.light);
	inData.color = clamp(inData.color, 0, 1);



	//���˂������̃x�N�g��   : reflect�֐�(�x�N�g���A�@��)
	inData.R = reflect(inData.light, normal);

	//���ςׂ̂���Ńn�C���C�g�ɂȂ�
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
	float4 result = diffuse + ambient_ + inData.specular;

	result.a = 0;

	return result;
}