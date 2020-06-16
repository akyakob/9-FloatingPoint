/*-----------------------------------------------------------------------
  Simple program to dump IEEE single precision floating point numbers
  student copy
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIGN_MASK 0x80000000 
#define SIGN_SHIFT 31       
#define EXPONENT_MASK 0x7F800000     
#define EXPONENT_SHIFT 23 

#define EXPONENT_BIAS 0x7F  
#define SIGNIFICAND_MASK 0x007FFFFF 

void ieeePrint(float fnum);

   typedef union fpoint {
	float floatVal;
	int intVal;
   }fpoint;

int main(int argc, char * argv[]) {
   
      // Must have a number
   if (2 == argc) {
      ieeePrint(atof(argv[1]));
   }
   else {
      printf("This decodes IEEE single precision numbers\n");
      printf("Error: Syntax is: %s number\n", argv[0]);
   }

   return(0);
}

void ieeePrint(float fnum) {
   int sign, exponent, significand;
   // We require a union because C won't let us mask floating point
   fpoint ieee;
   ieee.floatVal = fnum;

   // Break the floating point item into the proper parts

   sign = (ieee.intVal & SIGN_MASK) >> SIGN_SHIFT;              // to get the sign of the number
   exponent = ((ieee.intVal & EXPONENT_MASK) >> EXPONENT_SHIFT) - EXPONENT_BIAS;  //extracts exponent
   significand = (ieee.intVal & SIGNIFICAND_MASK) << 1;      //extracts significand 
   
   printf("Number %f => Bin sign:%d Dec exponent:%d  Hex significand .%x\n", ieee.floatVal, sign, exponent, significand);
   return;
}

