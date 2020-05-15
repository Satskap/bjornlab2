#ifndef __LAB2_FUNCS_H__
#define __LAB2_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "lab2.h"
//#include "lab2.c"

//Deklararera funktioner. NOTE: deras namn är lite ändrat för att funktionsnamnet ej ska vara upptaget (t.ex för sin).
int array(char name, double start, double stop);
int set_value(char name, double);
int clear_value(char name);
int show_value(char name);
int calc_value(char equals, char input, char smooth_operator, char input2);
int sin_calc(char name, char name2);
void show_vars(void);
void showCSV(char filename[50]);
void importCSV(char name, char filename[50]);
void exportCSV(char name, char filename[50]);
void event(char name, char name2);
void printhelp(void);

#endif /* __LAB2_FUNCS_H__ */

