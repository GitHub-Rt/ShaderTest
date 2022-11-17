
//    register ----v　引き出しみたいなもの
Texture2D tex : register(t0);		//テクスチャーを受け取る
SamplerState smp : register(s0);	//サンプルを受け取る



cbuffer global
{
	float4x4 matW;			//ワールド行列
	float4x4 matWVP;		//ワールド・ビュー・プロダクションの合成行列
	float4x4 matNormal;		//法線変形させるための行列
	float4	 color;			//マテリアルの色
	float4  camPos;			//カメラの位置
	bool	 isTexture;		//テクスチャの有無
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float4 color : COLOR0;
	float4 specular : COLOR1;
};


//頂点シェーダー
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL )
{
	//ピクセルシェーダーに渡す変数
	VS_OUT outData;

	
	outData.pos = mul(pos,matWVP);		//ベクトルを行列で変形させる関数 --> mul(ベクトル,行列)
	outData.uv = uv;
	
	float4 light = float4(1, 1, -1, 0);
	light = normalize(light);

	//法線
	normal = mul(normal, matNormal);

	outData.color = dot(normal, light);
	outData.color = clamp(outData.color, 0, 1);

	//視線ベクトル(頂点からカメラに向かうベクトル)
	float V = normalize( camPos - mul( pos, matW ) );
	
	//反射した光のベクトル   : reflect関数(ベクトル、法線)
	float4 R = reflect(light, normal);

	//内積のべき乗でハイライトになる
	outData.specular = pow( clamp( dot(R, V), 0, 1), 5) * 5;


	//まとめて渡す
	return outData;
}

//ピクセルシェーダー
//（） : セマンティクス----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient;


	if (isTexture == true)
	{
		diffuse = tex.Sample(smp, inData.uv) * inData.color;
		ambient = tex.Sample(smp, inData.uv) * 0.8f;
	}
	else
	{
		diffuse = color * inData.color;
		ambient = color * 0.3f;
	}
	return diffuse + ambient + inData.specular;
}
