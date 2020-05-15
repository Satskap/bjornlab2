#ifndef __LAB2_H__
#define __LAB2_H__
#include "lab2_funcs.h"

#define ARRAY_LEN	50

/* new data types */
typedef struct var {
  char n;
  double v;
} matlab_var_t;

typedef struct arr {
  char n;
  double v[ARRAY_LEN];
} matlab_arr_t;

/* global variables, beware */
extern matlab_var_t vars[6];
extern matlab_arr_t arrs[6];


/* function declarations */
//Find_arr och find_var deklararas här eftersom de använder strukterna ovan.
int processLine(char line[50]);
matlab_var_t *find_var(char var);
matlab_arr_t *find_arr(char var);

#endif /* __LAB2_H__ */

