#ifndef table_h //防止w头文件重复包含和编译
#define table_h
#include <string.h>
#include <stdio.h>

void Permutation(int *,int *,int ,int *);
void XOR(int *,int *,int ,int *);
void shift(int *,int *,int ,int );
void DToB(int ,int *);
void get_subkey(int *,int subkey[][48]);
void E(int *, int *);
void S(int b[8][6], int *c,int s[8][4][16], int i);
void P(int *c, int *ans);
void F(int *a, int *key, int *cip);

#endif 
