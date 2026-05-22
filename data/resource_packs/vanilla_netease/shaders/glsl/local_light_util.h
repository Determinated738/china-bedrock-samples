#ifndef __LOCAL_LIGHT_UTIL_H__
#define __LOCAL_LIGHT_UTIL_H__
#ifndef _UNIFORM_PER_FRAME_CONSTANTS_H
#define _UNIFORM_PER_FRAME_CONSTANTS_H

#ifndef _UNIFORM_MACRO_H
#define _UNIFORM_MACRO_H

#ifdef MCPE_PLATFORM_NX
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) uniform x {
#define END_UNIFORM_BLOCK };
#define UNIFORM 
#else
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) 
#define END_UNIFORM_BLOCK
#define UNIFORM uniform 
#endif

#if __VERSION__ >= 420
#define LAYOUT_BINDING(x) layout(binding = x)
#else
#define LAYOUT_BINDING(x) 
#endif

#endif


#ifdef MCPE_PLATFORM_NX
layout(binding = 2) uniform PerFrameConstants {
#endif
// BEGIN_UNIFORM_BLOCK(PerFrameConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM vec3 VIEW_POS;
#ifdef MCPE_NETEASE
// TIME will loop from [0, 210]
// make sure your shader handles the case when it transitions from 210 to 0
#endif
UNIFORM float TIME;
#ifdef MCPE_NETEASE
UNIFORM vec4 BLEND_COLOR;
UNIFORM vec4 USER_FOR_COLOR_NEAR;
UNIFORM vec4 USER_FOR_COLOR_FAR;

UNIFORM vec4 LIGHT_NUM_STRENGTH;
UNIFORM vec4 LIGHT_POS_RANGE_0;
UNIFORM vec4 LIGHT_COLOR_ATTEN_0;
UNIFORM vec4 LIGHT_DIR_TYPE_0;
UNIFORM vec4 LIGHT_FALLOFF_COS_0;

UNIFORM vec4 LIGHT_POS_RANGE_1;
UNIFORM vec4 LIGHT_COLOR_ATTEN_1;
UNIFORM vec4 LIGHT_DIR_TYPE_1;
UNIFORM vec4 LIGHT_FALLOFF_COS_1;

UNIFORM vec4 LIGHT_POS_RANGE_2;
UNIFORM vec4 LIGHT_COLOR_ATTEN_2;
UNIFORM vec4 LIGHT_DIR_TYPE_2;
UNIFORM vec4 LIGHT_FALLOFF_COS_2;

UNIFORM vec4 PLANAR_SHADOW_PARAMS1;
UNIFORM vec4 PLANAR_SHADOW_PARAMS2;
UNIFORM vec4 PLANAR_SHADOW_PARAMS3;
UNIFORM vec4 PLANAR_SHADOW_PARAMS4;
#endif
UNIFORM vec4 FOG_COLOR;
UNIFORM vec2 FOG_CONTROL;
UNIFORM float RENDER_DISTANCE;
UNIFORM float FAR_CHUNKS_DISTANCE;
UNIFORM float OCCLUSION_HEIGHT_OFFSET;
END_UNIFORM_BLOCK

#endif


vec3 CalcPointLighting(in vec3 P, in vec3 N, in vec4 lightPosRange, in vec4 lightColorAtten)
{
	vec3 L = lightPosRange.rgb - P;
	float D2 = dot(L, L) + 0.001;
	L *= inversesqrt(D2);
	float NoL = clamp( dot(N, L), 0.0, 1.0);
	float Atten = clamp(D2 / (lightPosRange.w * lightPosRange.w), 0.0, 1.0);
	Atten = 1.0 - Atten * Atten;
	Atten *= Atten;
	Atten *= 1.0 / (D2 * lightColorAtten.w + 1.0);
	vec3 color = lightColorAtten.rgb * (NoL * Atten);
	return color;
}

vec3 CalcSpotLighting(in vec3 P, in vec3 N, in vec4 lightPosRange, in vec4 lightColorAtten, 
	in vec3 lightDir, in vec3 fallOffCosHalfThetaPHi)
{
	vec3 L = lightPosRange.rgb - P;
	float D2 = dot(L, L) + 0.001;
	L *= inversesqrt(D2);
	float NoL = clamp( dot(N, L), 0.0, 1.0);
	float Atten = clamp(D2 / (lightPosRange.w * lightPosRange.w), 0.0, 1.0);
	Atten = 1.0 - Atten * Atten;
	Atten *= Atten;
	Atten *= 1.0 / (D2 * lightColorAtten.w + 1.0);
	float DoL = dot( lightDir, -L );
	float Spot = clamp(DoL * fallOffCosHalfThetaPHi.y + fallOffCosHalfThetaPHi.z, 0.0, 1.0);
	Spot *= Spot;
	vec3 color = lightColorAtten.rgb * (NoL * Atten * Spot);
	return color;
	// DiffLit += color * shadowMapCoefficient;
	// SpecLit += color * GetPbrBRDF(L, N, V, rough2, NoV, NoL, SpecularColor) ;
}

vec3 _LocalLightRadiance(vec4 position, vec4 normal) {
//#if defined(RNGL_UNLIT) || !defined(FANCY)
//	return vec3(0.0);
//#else
	// vec3 pLightColor1 = pointLightColor1.xyz;
	// vec3 pLightPos = pointLightPosRadius1.xyz;
	// float radius = pointLightPosRadius1.w;
	// float dLight = max(0.0, dot(N, normalize(pLightPos - position)));
	// float attenuation = attenuate_cusp(length(position.xyz - pLightPos), radius, 1.0);
	// return (pLightColor1 * dLight + vec3(1.0)) * attenuation;
	//float lightNum = LIGHT_NUM.x;
	vec3 ret = vec3(0);
	//if (lightNum >= 1.0)
#if	defined(NETEASE_LOCAL_LIGHT_NUM_1) || defined(NETEASE_LOCAL_LIGHT_NUM_2) || defined(NETEASE_LOCAL_LIGHT_NUM_3)
	{
		float type = LIGHT_DIR_TYPE_0.w;
		if (type < 1.0)
		{
			ret.xyz += CalcPointLighting(position.xyz, normal.xyz, LIGHT_POS_RANGE_0.xyzw, LIGHT_COLOR_ATTEN_0.xyzw);
		}
		else
		{
			ret.xyz += CalcSpotLighting(position.xyz, normal.xyz, LIGHT_POS_RANGE_0.xyzw, LIGHT_COLOR_ATTEN_0.xyzw,
				LIGHT_DIR_TYPE_0.xyz, LIGHT_FALLOFF_COS_0.xyz);
		}
	}
#endif
	//else if (lightNum >= 2.0)
#if	defined(NETEASE_LOCAL_LIGHT_NUM_2) || defined(NETEASE_LOCAL_LIGHT_NUM_3)
	{
		float type = LIGHT_DIR_TYPE_1.w;
		if (type < 1.0)
		{
			ret.xyz += CalcPointLighting(position.xyz, normal.xyz, LIGHT_POS_RANGE_1.xyzw, LIGHT_COLOR_ATTEN_1.xyzw);
		}
		else
		{
			ret.xyz += CalcSpotLighting(position.xyz, normal.xyz, LIGHT_POS_RANGE_1.xyzw, LIGHT_COLOR_ATTEN_1.xyzw,
				LIGHT_DIR_TYPE_1.xyz, LIGHT_FALLOFF_COS_1.xyz);
		}
	}
#endif
	//else if (lightNum >= 3.0)
#if	defined(NETEASE_LOCAL_LIGHT_NUM_3)
	{
		float type = LIGHT_DIR_TYPE_2.w;
		if (type < 1.0)
		{
			ret.xyz += CalcPointLighting(position.xyz, normal.xyz, LIGHT_POS_RANGE_2.xyzw, LIGHT_COLOR_ATTEN_2.xyzw);
		}
		else
		{
			ret.xyz += CalcSpotLighting(position.xyz, normal.xyz, LIGHT_POS_RANGE_2.xyzw, LIGHT_COLOR_ATTEN_2.xyzw,
				LIGHT_DIR_TYPE_2.xyz, LIGHT_FALLOFF_COS_2.xyz);
		}
	}
#endif
	return ret;

//#endif
}

vec4 getLightColor(vec4 worldSpacePosition, vec4 worldSpaceNormal) {
	vec3 finalColor = vec3(0, 0, 0);
	vec3 localLightRad = _LocalLightRadiance(worldSpacePosition, worldSpaceNormal);
	finalColor += localLightRad.xyz;
	return vec4(finalColor.xyz, 0);
}
#endif