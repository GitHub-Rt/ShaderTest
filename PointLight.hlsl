
//    register ----v　引き出しみたいなもの
Texture2D tex : register(t0);		//テクスチャーを受け取る
SamplerState smp : register(s0);	//サンプルを受け取る



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
	float4 lightPos : COLOR6;
};


//頂点シェーダー
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーに渡す変数
	VS_OUT outData;


	outData.pos = mul(pos, matWVP);		//ベクトルを行列で変形させる関数 --> mul(ベクトル,行列)
	outData.uv = uv;

	//ライトの位置
	outData.lightPos = float4(0, 5, 0, 0);

	////ライトの向き
	//outData.light = float4(0, 0, -1, 0);
	//outData.light = normalize(outData.light);

	//法線
	outData.normal = mul(normal, matNormal);
	outData.normal.w = 0;

	//outData.color = dot(normal, light);
	//outData.color = clamp(outData.color, 0, 1);

	////視線ベクトル(頂点からカメラに向かうベクトル)
	//outData.V = normalize(camPos - mul(pos, matW));

	////反射した光のベクトル   : reflect関数(ベクトル、法線)
	//outData.R = reflect(light, normal);

	////内積のべき乗でハイライトになる
	//outData.specular = pow(clamp(dot(R, V), 0, 1), 5) * 5;

	//まとめて渡す
	return outData;
}

//ピクセルシェーダー
//（） : セマンティクス----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient_;

	//頂点の位置から見た光の方向
	inData.light = inData.pos - inData.lightPos;
	inData.light = normalize(inData.light);

	
	inData.color = dot(inData.normal, inData.light);
	inData.color = clamp(inData.color, 0, 1);

	//視線ベクトル(頂点からカメラに向かうベクトル)
	inData.V = normalize(camPos - mul(inData.pos, matW));

	//反射した光のベクトル   : reflect関数(ベクトル、法線)
	inData.R = reflect(inData.light, inData.normal);

	//内積のべき乗でハイライトになる
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