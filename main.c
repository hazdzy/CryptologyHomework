//  main.c
//  DES
//  Created by 翔誉 on 2019/3/19.
#include <stdio.h>
#include <string.h>
#include "table.h"
int IP[64]={58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7};
int IP_[64]={40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25};

int main()

{
    int key[64],subkey[17][48],input[64],temp[64]={0},output[64],L[17][32],R[17][32];
    /*输入输出分析：明文转16进制数，输入8字节的16进制数，转成64位0-1bit串存在input里，计算，输出反之；实际上用<stdint.h>更好，下次吧！
     明文=iloveyou 转成16进制(utf-8)是0x696c6f7665796f75，1字母1字节；
     二进制0110100101101100011011110111011001100101011110010110111101110101
     秘钥=0000111000110010100100100011001011101010011011010000110101110011
     */
    char M[]="0110100101101100011011110111011001100101011110010110111101111101";
    char K[]="0000111000110010100100100011001011101010011011010000110101110011";
    //存储字符串，然后转化类型交给程序
    for(int i=0;i<64;i++){
        input[i]=M[i]-'0';//字符0的ASCII编码是48不是0
        key[i]=K[i]-'0';
    }
    
    //加密过程
    Permutation(input,temp,64,IP);
    for(int i=0;i<64;i++)//分两段
    {
        if(i<32)
            L[0][i]=temp[i];
        else
            R[0][i-32]=temp[i];
    }
    get_subkey(key,subkey);//生成子秘钥
   
    for(int i=1;i<=16;i++)//16轮加密
    {
        F(R[i-1],subkey[i],temp);
        XOR(temp, L[i-1], 32, R[i]);

        for(int j=0;j<32;j++){
        L[i][j]=R[i-1][j];
        }
        printf("%d:",i);
        for (int z=0;z<32;z++)                   //第一问（未解决）
            printf("%d",(L[i][z])%2);
        for (int z=0;z<32;z++)
            printf("%d",(R[i][z])%2);
        printf("\n");
    }
    
    for(int i=0;i<64;i++){
        if(i<32)
            temp[i]=R[16][i];
        else
            temp[i]=L[16][i-32];
    }
    
    Permutation(temp,output,64,IP_);//IP逆置换

    printf("密文：");
    for(int i=0;i<64;i++)
    printf("%d",output[i]);
    printf("\n");
    
    //解密过程
    int L2[17][32],R2[17][32];
    Permutation(output,temp,64,IP);//得到R16L16

    for(int i=0;i<64;i++)//分两段
    {
        if(i<32)
            L2[0][i]=temp[i];
        else
            R2[0][i-32]=temp[i];
    }
    for(int i=1;i<=16;i++)//16轮解密
    {
        for(int j=0;j<32;j++){
            L2[i][j]=R2[i-1][j];
        }
        F(L2[i],subkey[17-i],temp);
        XOR(temp, L2[i-1], 32, R2[i]);
    }
    for(int i=0;i<64;i++){
        if(i<32)
            temp[i]=R2[16][i];
        else
            temp[i]=L2[16][i-32];
    }
    Permutation(temp,input,64,IP_);//IP置换
    printf("明文：");
    for(int i=0;i<64;i++)
        printf("%d",input[i]);
    printf("\n");
    
    return 0;
}

