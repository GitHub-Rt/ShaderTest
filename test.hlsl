
//    register ----v　引き出しみたいなもの
Texture2D tex : register(t0);		//テクスチャーを受け取る
SamplerState smp : register(s0);	//サンプルを受け取る



cbuffer global
{
	float4x4 matWVP;		//行列
	float4	 color;			//マテリアルの色
	bool	 isTexture;		//テクスチャの有無
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};


//頂点シェーダー
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD )
{
	//ピクセルシェーダーに渡す変数
	VS_OUT outData;

	
	outData.pos = mul(pos,matWVP);		//ベクトルを行列で変形させる関数 --> mul(ベクトル,行列)
	outData.uv = uv;


	//まとめて渡す
	return outData;
}

//ピクセルシェーダー
//（） : セマンティクス----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{

	//グラデーション
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