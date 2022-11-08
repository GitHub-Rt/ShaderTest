
//頂点シェーダー
float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

//ピクセルシェーダー
//（） : セマンティクス　
float4 PS(float4 pos:SV_POSITION) : SV_TARGET
{
	//posにはスクリーン上のピクセル数が入る
	
	return float4(1 -(pos.x / 800 ), 1, 1, 1);
}