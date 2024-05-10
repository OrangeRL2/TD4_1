#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    float3 light = float3(1, 1, 0);
    float3 lightdir = normalize(light);
    float3 lightcolor = float3(1,1,1);
	
	VSOutput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(mat, pos);
	output.normal = normal;
	//Lambert反射
    output.color.rbg = 1 - dot(-lightdir, output.normal) * m_diffuse * lightcolor;
    output.color.a = m_alpha;
	output.uv = uv;
	return output;
}