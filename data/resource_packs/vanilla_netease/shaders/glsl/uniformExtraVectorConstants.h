#ifndef _UNIFORM_EXTRA_VECTOR_CONSTANTS_H
#define _UNIFORM_EXTRA_VECTOR_CONSTANTS_H

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
layout(binding = 1) uniform SfxConstants {
#endif
// BEGIN_UNIFORM_BLOCK(SfxConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM vec4 EXTRA_VECTOR1;
UNIFORM vec4 EXTRA_VECTOR2;
UNIFORM vec4 EXTRA_VECTOR3;
UNIFORM vec4 EXTRA_VECTOR4;
UNIFORM vec4 SUN_DIR;
UNIFORM vec4 WATER_TEXTURE_UV_RANGE;
UNIFORM vec4 SKY_NEAR_COLOR;
UNIFORM vec4 SKY_FAR_COLOR;
UNIFORM vec4 RAIN_NEAR_COLOR;
UNIFORM vec4 RAIN_FAR_COLOR;
UNIFORM vec4 COLOR_MAPPING_PARAM;
END_UNIFORM_BLOCK

#endif
