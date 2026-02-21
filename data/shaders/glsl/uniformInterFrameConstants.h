#ifndef _UNIFORM_INTER_FRAME_CONSTANTS_H
#define _UNIFORM_INTER_FRAME_CONSTANTS_H

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
uniform InterFrameConstants {
#endif
// BEGIN_UNIFORM_BLOCK(InterFrameConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
// in secs. This is reset every 1 hour. so the range is [0, 3600]
// make sure your shader handles the case when it transitions from 3600 to 0
UNIFORM float TOTAL_REAL_WORLD_TIME;
UNIFORM MAT4 CUBE_MAP_ROTATION;
END_UNIFORM_BLOCK

#endif
