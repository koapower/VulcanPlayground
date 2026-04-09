struct VSInput {
    float3 Pos;
    float3 Color;
};

struct PushConstants {
    float4x4 mvp;
};
[[vk::push_constant]] PushConstants pc;

struct VSOutput {
    float4 Pos : SV_POSITION;
    float3 Color;
};

[shader("vertex")]
VSOutput main(VSInput input) {
    VSOutput output;
    output.Pos   = mul(pc.mvp, float4(input.Pos, 1.0));
    output.Color = input.Color;
    return output;
}

[shader("fragment")]
float4 main(VSOutput input) {
    return float4(input.Color, 1.0);
}
