/**************************************************************************
  quadTest.c - for the student
  This program demonstrates C99's complex support.
 
 12/22/2018 - R. Repka  Initial version
 03/27/2019 - R. Repka  b**2 typo
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include </usr/include/complex.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"
#define RNUM (500000)
/************************************************************************
   Simple code to test complex support  
************************************************************************/
int main(int argc, char* argv[]){ 

   double anum = NAN; /*set to NAN (not a number) so if it's used without being
                        set to a value then it'll throw an error */
   double bnum = NAN;
   double cnum = NAN;

   int rc;
   /* getopt_long stores the option index here. */
   int option_index = 0;
  
   /* This contains the short command line parameters list */
   char *getoptOptions = "a:b:c:"; //required arg has letter and colon, not required just has letter
  
   struct option long_options[] = {
      {"numa",      required_argument,       0, 'a'}, 
      {"numb",      required_argument,       0, 'b'}, 
      {"numc",      required_argument,       0, 'c'}, 
      {0, 0, 0, 0}
    };
 
	opterr = 1;           /* Enable automatic error reporting */
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options,  &option_index)) != -1) { 

      switch (rc)
        {
        case 'a':    
          anum = atof(optarg);
          break;

        case 'b':    
          bnum = atof(optarg);
          break;

        case 'c':    
          cnum = atof(optarg);
          break;

	case '?':  /* Handled by the default error handler */
          break;

       default:
          printf ("Internal error: undefined option %0xX\n", rc);
          exit(PGM_INTERNAL_ERROR);
       } // End switch 
   } /* end while */

   if ((optind < argc) /* add lots of stuff here */  ){  //handles the case where the args are not the right letters
      fprintf(stderr, "Tests quadratic root finding methods\n");
      fprintf(stderr, "usage: ./quadTest -a[num] Anum -b[num] Bnum -c[num] Cnum\n"); 
      return(PGM_INTERNAL_ERROR);
       }

   //rest of error checking

   else if (isnan(anum) || isnan(bnum) || isnan(cnum)) { //isnan() is func to check if a var is NAN
      fprintf(stderr, "Not enough arguments\n");
      fprintf(stderr, "quadTest is a quadratic solver that solves for the roots of a polynomial\n");
      fprintf(stderr, "Format should be ./quadTest -a Avalue -b Bvalue -c Cvalue\n");
      }

   else if (fabs(anum) < HW_EPSILON) {
      fprintf(stderr, "'a' should be nonzero.\n"); 
      }

   else{
   polynomial p; //init a poly, already has pointer to it in this format
   //init root list
   double complex rootList[2]; //solution list
   initPoly(&p, 3); 
   //put a b c into polyCoefs
   p.polyCoef[0] = anum;
   p.polyCoef[1] = bnum;
   p.polyCoef[2] = cnum;
DECLARE_TIMER(CalcTimer)
DECLARE_REPEAT_VAR(RVar)
START_TIMER(CalcTimer)
BEGIN_REPEAT_TIMING(RNUM,RVar)
   quadraticRoots(&p, rootList);
END_REPEAT_TIMING
PRINT_TIMER(CalcTimer)
PRINT_RTIMER(CalcTimer,RNUM)
   printf("The roots of: %.2lfx**2 + %.2lfx + %.2lf\n",anum,bnum,cnum);
   printf("Root1: %.2f + %.2fi\n", creal(rootList[0]), cimag(rootList[0]));
   printf("Root2: %.2f + %.2fi\n", creal(rootList[1]), cimag(rootList[1]));
   freePoly(&p);
       }

/* a polynomial (from rootfinding.h) has nterms and polyCoefs. polyCoefs are of type double complex
   (which you can have other types like int complex) but there are 3 nterms and each is in complex
   form and you can write something in int or float form and still have it be complex like 1 will
   technically be 1 + 0i
  */
/*
   polynomial p; //init a poly, already has pointer to it in this format
   //init root list
   double complex rootList[2]; //solution list
   initPoly(&p, 3); 
   //put a b c into polyCoefs
   p.polyCoef[0] = anum;
   p.polyCoef[1] = bnum;
   p.polyCoef[2] = cnum;
DECLARE_TIMER(CalcTimer)
DECLARE_REPEAT_VAR(RVar)
START_TIMER(CalcTimer)
BEGIN_REPEAT_TIMING(RNUM,RVar)
   quadraticRoots(&p, rootList);
END_REPEAT_TIMING
PRINT_TIMER(CalcTimer)
PRINT_RTIMER(CalcTimer,RNUM)
   printf("The roots of: %.0lfx**2 + %.0lfx + %.0lf\n",anum,bnum,cnum);
   printf("Root1: %.0f + %.0fi\n", creal(rootList[0]), cimag(rootList[0]));
   printf("Root2: %.0f + %.0fi\n", creal(rootList[1]), cimag(rootList[1]));
   freePoly(&p);
*/
} /* End main */


 /*---------------------------------------------------------------------------
  Returns the two roots from a quadratic polynomial
  
    =  -b +-sqrt(b**2-4ac)
       ----------------------
                 2a
  
  Where: polynomial *p              - Pointer to a 2nd order polynomial
  Returns: double complex* rootList - A pointer to a complex root pair.
  Errors:  prints an error and exits
---------------------------------------------------------------------------*/
void quadraticRoots(polynomial *p, double complex *rootList){
  rootList[0] = (-1.0*p->polyCoef[1] + csqrt(p->polyCoef[1]*p->polyCoef[1] - 4.0*p->polyCoef[0]*p->polyCoef[2])) / (2.0*p->polyCoef[0]); 
  rootList[1] = (-1.0*p->polyCoef[1] - csqrt(p->polyCoef[1]*p->polyCoef[1] - 4.0*p->polyCoef[0]*p->polyCoef[2])) / (2.0*p->polyCoef[0]); 
  
}


/*---------------------------------------------------------------------------
  This function allocates an array of "nterm" double complex elements and then
  initializes the terms of the polynomial to NAN (not a number).
  We initialize the terms of the polynomial to NAN to prevent the users from
  accidentally using the polynomial before valid values are set.
  
  Where: polynomial *p       - Pointer to polynomial data structure to create
         unsigned int nterms - The number of elements to create
  Returns: nothing
  Errors:  prints an error and exits
---------------------------------------------------------------------------*/
void initPoly(polynomial *p, unsigned int nterms){
  p->nterms = nterms;
  p->polyCoef = malloc(nterms*sizeof(double complex));
  //error checking
  if(p->polyCoef == NULL) {
   printf("polyCoef not allocated");
   exit(MALLOC_ERROR);
   }
  for(int i = 0; i<nterms; i++) {
    p->polyCoef[i] = NAN;
   }  
}

/*---------------------------------------------------------------------------
  Destroys/frees a polynomial
  
  Where: polynomial *p - Pointer to polynomial data structure to destroy
  Returns: nothing
  Errors:  none
---------------------------------------------------------------------------*/
void freePoly(polynomial *p){
  free(p->polyCoef);
  p->nterms = 0;
  p->polyCoef = NULL;
}


