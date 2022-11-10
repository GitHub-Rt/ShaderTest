
cbuffer global
{
	float4x4 matWVP;		//行列を扱う型 --> float4x4
};


//頂点シェーダー
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	pos = mul(pos,matWVP);	//ベクトルを行列で変形させる関数 --> mul(ベクトル,行列)
	return pos;
}

//ピクセルシェーダー
//（） : セマンティクス----------------v
float4 PS(float4 pos:SV_POSITION) : SV_TARGET
{
	//posにはスクリーン上のピクセル数が入る
	
	return float4(1 -(pos.x / 800 ), 1, 1, 1);
}