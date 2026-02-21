#include "ShaderConstants.fxh"

// Fake implementation of netease's sfx so that material validator passes
struct PS_Input
{
    float2 uv : TEXCOORD0;
    float4 position : SV_Position;
};

struct PS_Output
{
    float4 color : SV_Target;
};

float2 SFX_UV_OFFSET;
float2 SFX_UV_SCALE;
float2 SFX_UV_REPEAT;
float4 SFX_MIX_COLOR;

ROOT_SIGNATURE
void main(in PS_Input PSInput, out PS_Output PSOutput)
{
    // Real one would sample texture here and repeat
    PSOutput.color = float4(PSInput.uv, 0, 0);
}