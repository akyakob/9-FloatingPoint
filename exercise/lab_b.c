/*-----------------------------------------------------------------------
  Simple program to dump IEEE single precision floating point numbers
  student copy
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>


int main( int argc, char *argv[] ) {
 float epsilon     = 1.0;
 float lastEpsilon;
 
 // Loop until the addition does not change the result
 while ((float)(1.0 + epsilon/2) != (float)1.0) {
   printf("%10.8g\t%.20f\n",epsilon,(1.0 + epsilon/2));

   epsilon = epsilon/2.0; //divide epsilon by 2
   
 }  

 // Print out the calculated and actual Epsilon
 printf("Calculated Machine Epsilon: %2.6g\n", epsilon);
 printf("Actual Machine Epsilon:     %2.6g\n", FLT_EPSILON);
 
 
 epsilon = 1.0;
 /*------------------------------------------------------------------------
   Insert your double precision code here when instructed
 ------------------------------------------------------------------------*/
 while ((1.0 + epsilon/2) != 1.0) {
   printf("%10.8g\t%.20f\n",epsilon,(1.0 + epsilon/2));

   epsilon = epsilon/2.0; //divide epsilon by 2
   
 }  

 // Print out the calculated and actual Epsilon
 printf("Calculated Machine Epsilon (double precision): %2.6g\n", epsilon);
 printf("Actual Machine Epsilon (double precison):      %2.6g\n", DBL_EPSILON);

 return 0;
} 

