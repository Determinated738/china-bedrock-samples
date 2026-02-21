
// Copyright (c) Mojang AB.  All rights reserved.

#ifndef _UNIFORM_PATTERN_CONSTANTS_H
#define _UNIFORM_PATTERN_CONSTANTS_H

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
uniform PatternConstants {
#endif
	// BEGIN_UNIFORM_BLOCK(PatternConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
	UNIFORM vec4 PATTERN_COLORS[7];
	UNIFORM vec4 PATTERN_UV_OFFSETS_AND_SCALES[7];
	UNIFORM float PATTERN_COUNT;
	END_UNIFORM_BLOCK

#endif
