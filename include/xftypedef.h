#ifndef __XF_TYPEDEF_H__
#define __XF_TYPEDEF_H__

typedef signed char int8;  
typedef unsigned char   uint8;  
typedef short  int16;  
typedef unsigned short  uint16;  
typedef int  int32;  
typedef unsigned   uint32;  
typedef long long  int64;  
typedef unsigned long long   uint64;  
  
/* 7.18.1.2  Minimum-width integer types */  
typedef signed char int_least8;  
typedef unsigned char   uint_least8;  
typedef short  int_least16;  
typedef unsigned short  uint_least16;  
typedef int  int_least32;  
typedef unsigned   uint_least32;  
typedef long long  int_least64;  
typedef unsigned long long   uint_least64;  
  
/*  7.18.1.3  Fastest minimum-width integer types  
 *  Not actually guaranteed to be fastest for all purposes  
 *  Here we use the exact-width types for 8 and 16-bit ints.  
 */  
typedef signed char int_fast8;  
typedef unsigned char uint_fast8;  
typedef short  int_fast16;  
typedef unsigned short  uint_fast16;  
typedef int  int_fast32;  
typedef unsigned  int  uint_fast32;  
typedef long long  int_fast64;  
typedef unsigned long long   uint_fast64;  
  
/* 7.18.1.5  Greatest-width integer types */  
typedef long long  intmax;  
typedef unsigned long long   uintmax;

//typedef enum {
//    false = (char)0,
//    true,
//} bool;

typedef uint8 *XF_Memory;

#endif