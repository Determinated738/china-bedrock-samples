#ifndef _UNIFORM_TEXT_CONSTANTS_H
#define _UNIFORM_TEXT_CONSTANTS_H

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
uniform TextConstants {
#endif
// BEGIN_UNIFORM_BLOCK(TextConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM float GLYPH_SMOOTH_RADIUS;
UNIFORM float OUTLINE_CUTOFF;
UNIFORM float SHADOW_SMOOTH_RADIUS;
UNIFORM vec4 SHADOW_COLOR;
UNIFORM vec2 SHADOW_OFFSET;
END_UNIFORM_BLOCK

#endif
