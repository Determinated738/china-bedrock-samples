#ifndef _UNIFORM_RENDER_CHUNK_CONSTANTS_H
#define _UNIFORM_RENDER_CHUNK_CONSTANTS_H

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
#extension GL_ARB_enhanced_layouts : enable
layout(binding = 0) uniform RenderChunkConstants {
#endif
// BEGIN_UNIFORM_BLOCK(RenderChunkConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM POS4 CHUNK_ORIGIN_AND_SCALE;
#ifdef MCPE_NETEASE
UNIFORM float BLOCK_LIGHT_TYPE;
#endif
UNIFORM float RENDER_CHUNK_FOG_ALPHA;
END_UNIFORM_BLOCK

#endif
