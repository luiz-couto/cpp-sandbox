
cbuffer staticMeshBuffer {
    float4x4 W;
    float4x4 VP;
};

struct VS_INPUT {
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float2 TexCoord : TEXCOORD;
};

struct PS_INPUT {
    float4 Pos      : SV_POSITION;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float2 TexCoord : TEXCOORD;
};

PS_INPUT VS(VS_INPUT input) {
    PS_INPUT output;
    float4 worldPos = mul(float4(input.Pos, 1.0f), W);
    output.Pos = mul(worldPos, VP);
    output.Normal = mul(input.Normal, (float3x3)W);
    output.Tangent = mul(input.Tangent, (float3x3)W);
    output.TexCoord = input.TexCoord;
    return output;
}