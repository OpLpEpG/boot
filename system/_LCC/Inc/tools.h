#pragma once

#define _GETARG_1(a1, ...) a1
#define _GETARG_2(a1, a2, ...) a2
#define _GETARG_3(a1, a2, a3, ...) a3
#define _GETARG_4(a1, a2, a3, a4, ...) a4
#define _GETARG_5(a1, a2, a3, a4, a5, ...) a5
#define _GETARG_6(a1, a2, a3, a4, a5, a6, ...) a6
#define _GETARG_7(a1, a2, a3, a4, a5, a6, a7, ...) a7
#define _GETARG_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a8
#define _GETARG_9(a1, a2, a3, a4, a5, a6, a7, a8, a9,  ...) a9
#define _GETARG_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10,  ...) a10
#define _GETARG_11(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define _GETARG_12(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) a12

#define _EXTARG_2(a1, a2, ...) a1, a2
#define _EXTARG_3(a1, a2, a3, ...) a1, a2, a3
#define _EXTARG_4(a1, a2, a3, a4, ...) a1, a2, a3, a4
#define _EXTARG_5(a1, a2, a3, a4, a5, ...) a1, a2, a3, a4, a5
#define _EXTARG_6(a1, a2, a3, a4, a5, a6, ...) a1, a2, a3, a4, a5, a6
#define _EXTARG_7(a1, a2, a3, a4, a5, a6, a7,  ...) a1, a2, a3, a4, a5, a6, a7
#define _EXTARG_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a1, a2, a3, a4, a5, a6, a7, a8
#define _EXTARG_9(a1, a2, a3, a4, a5, a6, a7, a8, a9,  ...) a1, a2, a3, a4, a5, a6, a7, a8, a9
#define _EXTARG_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a1, a2, a3, a4, a5, a6, a7, a8, a9, a10
#define _EXTARG_11(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11
#define _EXTARG_12(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12

#define GETARG_1(...) _GETARG_1(__VA_ARGS__)
#define GETARG_2(...) _GETARG_2(__VA_ARGS__)
#define GETARG_3(...) _GETARG_3(__VA_ARGS__)
#define GETARG_4(...) _GETARG_4(__VA_ARGS__)
#define GETARG_5(...) _GETARG_5(__VA_ARGS__)
#define GETARG_6(...) _GETARG_6(__VA_ARGS__)
#define GETARG_7(...) _GETARG_7(__VA_ARGS__)
#define GETARG_8(...) _GETARG_8(__VA_ARGS__)
#define GETARG_9(...) _GETARG_9(__VA_ARGS__)
#define GETARG_10(...) _GETARG_10(__VA_ARGS__)
#define GETARG_11(...) _GETARG_11(__VA_ARGS__)
#define GETARG_12(...) _GETARG_12(__VA_ARGS__)

#define EXTARG_2(...) _EXTARG_2(__VA_ARGS__)
#define EXTARG_3(...) _EXTARG_3(__VA_ARGS__)
#define EXTARG_4(...) _EXTARG_4(__VA_ARGS__)
#define EXTARG_5(...) _EXTARG_5(__VA_ARGS__)
#define EXTARG_6(...) _EXTARG_6(__VA_ARGS__)
#define EXTARG_7(...) _EXTARG_7(__VA_ARGS__)
#define EXTARG_8(...) _EXTARG_8(__VA_ARGS__)
#define EXTARG_9(...) _EXTARG_9(__VA_ARGS__)
#define EXTARG_10(...) _EXTARG_10(__VA_ARGS__)
#define EXTARG_11(...) _EXTARG_11(__VA_ARGS__)
#define EXTARG_12(...) _EXTARG_12(__VA_ARGS__)

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0


//#define NUMARGS(...)  (sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)
//Example: #pragma message(VAR_NAME_VALUE(DELAY2CHAR))

#define NO_INIT __attribute__ ((section(".noinit")))
#define INLINE_FORCE __attribute__ ((__always_inline__)) inline
