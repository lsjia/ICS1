/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 罗思佳 2021201679
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int a1 = x & y;
  int a2 = ~x & ~y;
  int res = ~a1 & ~a2;
  return res;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  int res = 0x49;
  res |= (res << 9);
  res |= (res << 18);
  
  return res;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {

  int y = x << 16; 
  y = y >> 16;
  return !(x ^ y);
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  //6个运算符
  /*int a = x + 1;
  int b = ~x;
  int c = a^b;
  
  return !(c + !a);*/

  //5个运算符，转换为Tmin
  int min = x + 1;
  int b = min + min;
  return !(b + !min);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //法一
  /*n = ~n+33; //32-n
   int y = x << n; 
  y = y >> n;
  return !(x ^ y);*/
  //法二
  /*x = x >> (n+31); //右移n-1
  return !x + !(~x);*/
  //法三
  x = x >> (n+31);
  int sign = x >> 31;
  return !(x ^ sign);
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
  int x = !!n;//排除0的干扰
  x = x << 31;
  n = n + 31;
  x = x >> n;

  return x;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    x = x | (x >> 16);
    x = x | (x >> 8);
    int mask = 0xaa;
    int res = x & mask;
    return !!res;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
 /* int n1 = n << 3;
  int m1 = m << 3;
  int y1 = (x >> n1) & 0xff;
  int y2 = (x >> m1) & 0xff;
  y1 = y1 << m1;
  y2 = y2 << n1;
  int y = y1 | y2;

  int z1 = 0xff << n1;
  int z2 = 0xff << m1;
  int z = ~(z1 | z2);
  z = z & x; 
  return y | z;
  */
  int n1 = n << 3;
  int m1 = m << 3;
  int y = ((x >> n1)^(x >> m1)) & 0xff;
  int res = (y << n1) ^ (y << m1);
  res = res ^ x;
  return res;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  //法一，4个运算符，取反加一
  /*int z = x >> 31;
  int y = x ^ z;
  y = y + (z & 1);
  return y;*/
  //法二，3个运算符，减一取反（和取反加一等价）
  int z = x >> 31;
  x = x + z;
  x = x ^ z;
  return x;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

    int z = x >> 31;
    int m = (1 << n) + z;//如果是负数的话，需要先加2^n - 1
    int y = x + (z & m);
    y = y >> n; 
    return y;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {

  int res = uf ^ 0x80000000;//取反
  int t = uf & 0x7fffffff;//取绝对值
  if(t > 0x7f800000) return uf;//NaN和无穷
 return res;
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //0或上0的相反数的符号位是0，其他的都是1
  int y = (~x) + 1;
  x = x | y;
  x = x >> 31;
  return(x+1);
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
   int b = ~0;
   int x = b << highbit;
   x = x << 1;
   x = ~x;
   int y = b << lowbit;
   return x & y;
   


   //错误做法1，没有考虑到lowbit > highbit的情况
   /*
   int b = ~0;
   int x = b << (highbit+1);
   int y = b << lowbit;
   return x ^ y;*/
  //错误做法2,当highbit为31时，b不会移位，要分开写
  /*int b = ~0;
   int x = b << (highbit+1);
   x = ~x;
   int y = b << lowbit;
   return x & y;*/
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {

 //int y1 = (y >> 31) & 1;  没有必要 &1
 //12个运算符
/* int y1 = y >> 31;
 int z1 = x^y;
 z1 = z1 >> 31;
 z1 = z1 & 1;
 int z = ~x + y + 1;//y-x
 z = z >> 31;
 return (!z1 & z) | (z1 & y1);*/
 //10个运算符
 /*int m = x^y;
 int z = ~x + y + 1;
 int res = (m & y) | ((~m) & z);
 return (res >> 31) & 1;*/
 //9
 int m = x^y;
int z = ~y + x ;
int res = (m & y) | (~(m|z));
return (res >> 31) & 1;

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  //9个运算符
  /*x = x >> n;
  int y = (x >> 31) & !!n;
  int c = (y << 31) >> (n+31);
  
  return x ^ c;*/
  //7个运算符
 /* x = x >> n;
  int sign = x >> 31;
  sign = x << (~n+32);
  sign = sign << 1;
  return x ^ sign;*/

  //优化后，6个运算符
  x = x >> n;
  int sign = x & (1 << 31);
  sign = sign >> n;
  return x ^ (sign << 1);
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x7FFFFFFF (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  //方案一 19
  /*int w1 = (x >> 31) ;
  int w2 = (x >> 30) ;
  int min = 1 << 31;
  int max = ~min;
  int y = x << 1;
  int w = (w1 ^ w2) + (~0);
  w1 = (w1 << 31) >> 31;
  w2 = (w2 << 31) >> 31;
  return (w & y) | (~w & ((w2 & max) | (w1 & min))) ;*/
  //方案二 12
  /*int min = 1 << 31;
  int z1;
  int y = x << 1;
  z1 = y >> 31;
  int z2 = (x ^ y) >> 31;
  x = ((min ^ z1) & z2) | (x & ~z2);
  x = x << (z2 + 1);
  return x;*/
  
  //方案三 10
  int min = 1 << 31;
  int z1;
  int y = x << 1;
  z1 = y >> 31;
  int z2 = (x ^ y) >> 31;
  int res = ((min ^ z1) & z2) | (y & ~z2);
  
  return res;

}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  //10个运算符
  /*int z = ~y + x + 1;
  int z1 = (x^y) >> 31;
  //z1 = z1 & 1;
  int c = (y^z) >> 31;
  return (z1+1) | (c & 1);*/

  //8个运算符
  int z = ~y + x + 1;//x-y
  int m = x ^ y;
  int n = x ^ z;
  return ((m & n) >> 31) + 1;
  
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
  //14个运算符
  /*int low2 = x & 0x3;
  int sign = (x >> 31) & 1;
  sign = (sign | !x) | !low2; 
  sign = sign + ~0;
  int y = x >> 2;
  int z = y << 1;
  z = z + y;
  int res = z + (low2 + sign);
  return res;*/
 //法二
 /* int low2 = x & 0x3;
  int sign = (x >> 31) & 1;
  int sn = (~0) + (((!x) | (!low2)) | sign);
  int y = x >> 2;
  int z = y << 1;
  z = z + y;
  int res = z + (low2 + sn);
  return res;*/
 //11个运算符
   int low2 = x & 0x3;
  int y = x >> 2;
  y = (y << 1) + y;
  low2 = low2 + low2 + low2;
  int sign = x >> 31;
  int z = low2 + ( sign & 3);
  z = z >> 2;
  return y + z;

}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
    /*int y = ~x + 1;//取反加一，即相反数
    int z = x & y;
    int res = x ^ z;
    int high = (x >> 31) & 1;
 
    return !(res + high) & (!!x);*/
   //优化后
    int y = x + ~0;//x-1
    int z = x & y;//如果是2的幂次，x 和 x-1 的并是0
    int sign = x >> 31;
    return !(z + sign + !x);//排除负数和0的情况

}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int index = 32;
  unsigned sign = x & 0x80000000;
  if(sign) //如果是负数 (之前没有考虑负数要取反加一)
   x = -x;
  
  unsigned tmp = x;

  while(index)
  {
    int s = (tmp >> (index-1)) & 1;
    if(s)
    {
      break;
    }
    
    index = index - 1;;
  }
  
  if(!index) return 0;

  int exp = index + 126;//index - 1 + 127

  tmp = tmp << (33 - index);
  tmp = tmp >> 1;
  int low8 = tmp & 0xff;
  int tail = (tmp >> 8) & 1;
  int halfMax = 128;
  int t = 0x100;
  if(low8 > halfMax)
  {
    tmp = tmp + t;//进位 
  } 
  if(low8 == halfMax)
  {
    tmp = tmp + t*tail;
  }

  tmp = tmp >> 8;
  int high9 = sign + (exp << 23);
  unsigned res = tmp + high9;
  
  return res;
  //当尾数位最高位有进位时，阶码要加一
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
 /* int sum = 1;
  int sign = x >> 31;
  int x1 = x >> 16;
  int step1 = !!(sign ^ x1);
  step1 = step1 << 4;//step等于0或16
  x = x >> step1;
  //sum = sum + step1;

  int x2 = x >> 8;
  int step2 = !!(sign ^ x2);
  step2 = step2 << 3;
  x = x >> step2;
  //sum = sum + step2;

  int x3 = x >> 4;
  int step3 = !!(sign ^ x3);
  step3 = step3 << 2;
  x = x >> step3;
  //sum = sum + step3;

  int x4 = x >> 2;
  int step4 = !!(sign ^ x4);
  step4 = step4 << 1;
  x = x >> step4;
  //sum = sum + step4;
  
  int x5 = x >> 1;
  int step5 = !!(sign ^ x5);
  x = x >> step5;
  //sum = sum + step5;

  sum = sum + step1 + step2 + step3 + step4 + step5 + (x^sign) ;
  return sum;*/
  int y = (x << 1)^x;
  int step1 = !!(y >> 16);
  step1 <<= 4;
  y >>= step1; 

 int step2 = !!(y >> 8);
 step2 <<= 3;
 y >>= step2;

 int step3 = !!(y >> 4);
 step3 <<= 2;
 y >>= step3;

 int step4 = !!(y >> 2);
 step4 <<= 1;
 y >>= step4;

 int step5 = !!(y >> 1);
 return step1 + step2 + step3 + step4 + step5 + 1;
}

/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  //优化前法1
  /*unsigned tmp = uf & 0x7fffffff;
  //如果是NaN
  if(tmp >= 0x7f800000) return uf;
  int exp = uf & 0x7f800000;
  int M = uf & 0x7fffff;//尾数
  int low2 = uf & 0x3;//末尾2位
  int sign = uf & 0x80000000;//符号位

  if(exp > 0x800000)//如果前后都是规格化数
  {
    return uf - 0x800000;
  }

  int M1 = M >> 1;//右移1位后的尾数
  if(low2 == 3) M1 += 1;//是否需要进位
  //另法 M1 += !(low2^3);

  /*if(!exp)//如果前后都是非规格化数
  {        
    return M1 + sign;

  } 
  //如果阶码为1
  M1 = M1 + 0x400000;

  return sign + M1;*/
  
  //优化前法2
  /*unsigned tmp = uf & 0x7fffffff;
  //如果是NaN
  if(tmp >= 0x7f800000) return uf;
  int exp = uf & 0x7f800000;
  int M = uf & 0x7fffff;//尾数
  int low2 = uf & 0x3;//末尾2位
  int sign = uf & 0x80000000;//符号位

  if(exp > 0x800000)//如果前后都是规格化数
  {
    return uf - 0x800000;
  }

  int M1 = M >> 1;//右移1位后的尾数
  if(low2 == 3) M1 += 1;//是否需要进位
  //另法 M1 += !(low2^3);

  M1 = M1 + (exp >> 1);
  return sign + M1;*/


  //优化后，13个运算符
  unsigned tmp = uf & 0x7fffffff;
  //如果是NaN
  if(tmp >= 0x7f800000) return uf;
  int exp = uf & 0x7f800000;
  int low2 = uf & 0x3;//末尾2位
  
  if(exp > 0x800000)//如果前后都是规格化数
  {
    return uf - 0x800000;
  }

  int temp = uf;
  temp = temp >> 1;//右移1位后的尾数
  if(low2 == 3) temp += 1;//是否需要进位
  //另法 M1 += !(low2^3);
  //优化
  temp = temp & 0xbfffffff;
  return temp;
}
