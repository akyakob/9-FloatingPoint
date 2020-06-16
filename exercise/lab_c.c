/*-----------------------------------------------------------------------
  Simple program to illustrate passing parameters
  student copy
  Compiling wiht -O0 and -O1 give different results 
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h> 

// Our complex data structure
typedef struct{
   double re, im; //real and imaginary parts
} dcomplex;

/*-------------------------------------------------------------------------
  Complex math function that takes structs as input returns the result 
  as a pass by value struct 
  
  Where: dcomplex a - complex data to add
         dcomplex b - complex data to add
         
  Returns dcomplex - complex sum
  Error handling: none
-------------------------------------------------------------------------*/
dcomplex addSSS( dcomplex a, dcomplex b) { 
   dcomplex sum;           // Temporary variable for result 
   // Perform complex arithmetic 
   sum.re = a.re + b.re;
   sum.im = a.im + b.im;
   return sum;
} 

/*-------------------------------------------------------------------------
  Complex math function that takes structs as input returns an a pointer 
  to a remote struct to store the result.  This is typical for C code  
    
  Where: dcomplex - pointer to the location to contain the sum
         dcomplex a - complex data to add
         dcomplex b - complex data to add
         
  Returns int  - always 0
  Error handling: none
-------------------------------------------------------------------------*/
int addSPI(dcomplex* sum, dcomplex a, dcomplex b) {
   // Perform complex arithmetic using the pointer
   (*sum).re = a.re + b.re;
   (*sum).im = a.im + b.im;
    
   return 0; 
} 

/*-------------------------------------------------------------------------
  Complex math function that takes structs as input returns the a pointer 
  to a local struct (generates errors)
 
  Where: dcomplex a - complex data to add
         dcomplex b - complex data to add
         
  Returns dcomplex* - pointer to the sum
  Error handling: none 
-------------------------------------------------------------------------*/
dcomplex* addSSP(dcomplex a, dcomplex b) {
   dcomplex sum;     // Temporary local automatic variable, warning "ok" 
   // Perform complex arithmetic 
   sum.re = a.re + b.re;
   sum.im = a.im + b.im;

   return &sum;
  } 
  
/*-------------------------------------------------------------------------
  Complex math function that takes pointers as input returns an a pointer 
  to a remote struct to store the result.  This is typical for C code  
    
  Where: dcomplex*   - pointer to the location to contain the sum
         dcomplex *a - pointer to complex data to add
         dcomplex *b - pointer to complex data to add
         
  Returns int  - always 0
  Error handling: none
-------------------------------------------------------------------------*/
int addPPP(dcomplex* sum, dcomplex *a, dcomplex *b) {
   // Perform complex arithmetic using the pointer
   (*sum).re = (*a).re + (*b).re;
   (*sum).im = (*a).im + (*b).im;
 
   return 0; 
}
  
  
/*-------------------------------------------------------------------------
  This function consumes a little stack space  
-------------------------------------------------------------------------*/
void stackSucker(void) {
   char space [10];
   for (int i= 0; i <sizeof(space); i++) { space [i] = 0x00;}
   return;
}


int main (int argc, char **argv) {
   char tmp[] = "Are these results right?"; 
   
   // Values to test with 
   dcomplex dc1 = {1,2};
   dcomplex dc2={3,4};
   dcomplex dc3;
   dcomplex *dc4;
   dcomplex *dc6;
   dcomplex *dc5 = &dc3;
   
   /* Adds a struct to a struct and returns a struct */
   dc3 = addSSS(dc1,dc2);
   printf("Adding %f+%fi and %f+%fi\n",dc1.re, dc1.im,dc2.re, dc2.im);
   printf("   Result(addSSS) is:%f+%fi\n\n",dc3.re, dc3.im);
 
   /* Adds a struct to a struct and uses a passed pointer */
   addSPI(dc5, dc1,dc2);
   printf("Adding %f+%fi and %f+%fi\n",dc1.re, dc1.im,dc2.re, dc2.im);
   printf("   Result(addSPI) is:%f+%fi\n\n",dc5->re, dc5->im);  
 
   /* Adds a struct pointer to a struct pointer and uses a passed pointer */
   addPPP(dc5, &dc1, &dc2);
   printf("Adding %f+%fi and %f+%fi\n",dc1.re, dc1.im,dc2.re, dc2.im);
   printf("   Result(addPPP) is:%f+%fi\n\n",dc5->re, dc5->im);  
  
   /* Adds a struct to a struct and returns a local pointer */
   printf("Adding %f+%fi and %f+%fi\n",dc1.re, dc1.im,dc2.re, dc2.im);
   printf("%s length is %d bytes\n", tmp, (int)strlen(tmp)+1);  
   dc4 = addSSP(dc1,dc2);
   printf("   Result(addSSP) is:%f+%fi\n\n",dc4->re, dc4->im);
   
   /* Adds a struct to a struct and returns a local pointer */
   /* but has a stack using function call in between */
   printf("Adding %f+%fi and %f+%fi\n",dc1.re, dc1.im,dc2.re, dc2.im);
   dc6 = addSSP(dc1,dc2);
   stackSucker();
   printf("%s length is %d bytes\n", tmp, (int)strlen(tmp)+1);  
   printf("   Result(addSSP) is:%f+%fi\n",dc6->re, dc6->im);
   
   return (0);
}
