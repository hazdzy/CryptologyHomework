//
//  main.c
//  AES_implementation
//
//  Created by 翔誉 on 2019/3/22.
//  Copyright © 2019 胡义臻. All rights reserved.
//

#include <stdio.h>
#include "function.h"

int main() {
    //明文=iloveyouiloveyou,对应的16进制表示是696c6f7665796f75696c6f7665796f75
    char *text="iloveyouiloveyou";
    uint32_t encodeKey[44], decodeKey[44];//存加解密秘钥
    const uint32_t *p,*q;
    uint8_t state[4][4];/*char字节可以直接给uint8_t，因为a它就是用这个定义的；
                         16、32、64位对应的标准输出符是%hu,%u,%llu*/
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            state[j][i]=*text;
            text++;
        }
    //秘钥
    uint32_t key[4]={0x798c6fea,0x6d4b6f35,0x6e7c5f76,0x34bc3f75};//注意要补上0x表示16进制
    GenerateKey(key, encodeKey, decodeKey);//确实是倒序
    p=encodeKey;
    q=decodeKey;
    //加密
    AddRoundKey(state,p);//Round 1
    for(int i=0;i<9;i++){//Round 2-10
        p+=4;
        SubBytes(state);
        ShiftRows(state);
        MixColumn(state);
        AddRoundKey(state, p);
    }
    SubBytes(state);//Round11
    ShiftRows(state);
    p+=4;
    AddRoundKey(state, p);
    printf("密文：\n");
    for(int i=0;i<4;i++)//展示密文
        for(int j=0;j<4;j++)
            printf("%x ",state[j][i]);//打印了15个，因为有一个空格，x比char方便的多，16进制容易看
    printf("\n");
    

    //解密
    AddRoundKey(state,q);//Round 1

    for(int i=0;i<9;i++){//Round 2-10
        q+=4;
        ShiftRows_(state);
        SubBytes_(state);
        AddRoundKey(state, q);
        MixColumn_(state);
    }
    ShiftRows_(state);
    SubBytes_(state);//Round11
    q+=4;
    AddRoundKey(state, q);
    printf("明文\n");
    for(int i=0;i<4;i++)//展示原文
        for(int j=0;j<4;j++)
            printf("%x ",state[j][i]);
    printf("\n");
    return 0;
}
