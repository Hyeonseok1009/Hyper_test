#ifndef HEADER_H	
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 51

void read_line(FILE* fp, char* input, int len);
int operator_checker(char* str, int n, float* minus, int* status,float* result, int* r);
int calc(float* result, int* r, char oper);
void error(char* str);
float calcuator(char* str);

#endif