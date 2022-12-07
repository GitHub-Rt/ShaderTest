
//    register ----v　引き出しみたいなもの
Texture2D tex : register(t0);		//テクスチャーを受け取る
SamplerState smp : register(s0);	//サンプルを受け取る
Texture2D texNormal:register(t1);	//Normalテクスチャーを受け取る


cbuffer global
{
	float4x4 matW;			//ワールド行列
	float4x4 matWVP;		//ワールド・ビュー・プロダクションの合成行列
	float4x4 matNormal;		//法線変形させるための行列
	float4  camPos;			//カメラの位置
	float4	 color;			//マテリアルの色
	float4 ambient;			//環境光
	float4 specular;		//ハイライトの色
	float	shiness;		//ハイライトの強さ
	bool	 isTexture;		//テクスチャの有無
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
};


//頂点シェーダー
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL )
{
	//ピクセルシェーダーに渡す変数
	VS_OUT outData;

	
	outData.pos = mul(pos,matWVP);		//ベクトルを行列で変形させる関数 --> mul(ベクトル,行列)
	outData.uv = uv;
	
	outData.light = float4(0, 0, -1, 0);
	outData.light = normalize(outData.light);

	//法線
	outData.normal = mul(normal, matNormal);
	outData.normal.w = 0;

	

	//まとめて渡す
	return outData;
}

//ピクセルシェーダー
//（） : セマンティクス----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient_;


	inData.color = dot(inData.normal, inData.light);
	inData.color = clamp(inData.color, 0, 1);

	//視線ベクトル(頂点からカメラに向かうベクトル)
	inData.V = normalize(camPos - mul(inData.pos, matW));

	//反射した光のベクトル   : reflect関数(ベクトル、法線)
	inData.R = reflect(inData.light, inData.normal);

	//内積のべき乗でハイライトになる
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