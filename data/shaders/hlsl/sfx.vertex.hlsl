#include "ShaderConstants.fxh"

// Fake implementation of netease's sfx so that material validator passes
struct VS_Input
{
    float4 position : POSITION;
    float2 uv : TEXCOORD0;
};

struct PS_Input
{
    float2 uv : TEXCOORD0;
    float4 position : SV_Position;
};

ROOT_SIGNATURE
void main(in VS_Input VSInput, out PS_Input PSInput)
{
  PSInput.position = mul(WORLDVIEWPROJ, VSInput.position);
  PSInput.uv = VSInput.uv;
}