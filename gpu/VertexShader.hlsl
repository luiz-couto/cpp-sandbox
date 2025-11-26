struct VS_INPUT {
    float4 Pos : POSITION; // change to float3?
    float4 Colour : COLOUR;
};

struct PS_INPUT {
    float4 Pos : SV_POSITION; // change to float3?
    float4 Colour : COLOUR;
};

PS_INPUT VS(VS_INPUT input) {
    PS_INPUT output;
    output.Pos = input.Pos;
    output.Colour = input.Colour;
    return output;
}