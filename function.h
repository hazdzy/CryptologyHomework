//
//  function.h
//  AES_implementation
//
//  Created by 翔誉 on 2019/3/22.
//  Copyright © 2019 胡义臻. All rights reserved.
//

#ifndef function_h
#define function_h
#include <stdio.h>
//对长mbit的二进制串循环移n位，注意\后连注释也不能加，不然会破坏宏命令； 宏命令也有参数，是可以识别的；不用写分号，预处理不是C语言的一部分，遵循另一套规则；
#define ROTLEFT(x,n) (((x)<<(n)) | ((x)>>(32-(n))))
#define ROTRIGHT(x,n) (((x)>>(n)) | ((x)<<(32-(n))))
//4Byte y to 32bits x，y[0]是高位，这里把与和移位的顺序写反了，导致1-3字节没取到值
#define BYTETOBIT(x,y)\
do{ (x)=((uint32_t)(((y)[0]&0xff)<<24)) | ((uint32_t)(((y)[1]&0xff)<<16)) | \
((uint32_t)(((y)[2]&0xff)<<8)) | ((uint32_t)((y)[3]&0xff)); }while(0)
//4Byte y from 32bits
#define BITTOBYTE(x,y)\
do{ (y[0])=(uint8_t)(((x)>>24) & 0xff); (y[1])=(uint8_t)(((x)>>16) & 0xff); \
(y[2])=(uint8_t)(((x)>>8) & 0xff); (y[3])=(uint8_t)((x) & 0xff); }while(0)

void InitiateData(uint8_t state[4][4], uint8_t *input);
void RenturnInput(uint8_t state[4][4], uint8_t *input);
void GenerateKey(uint32_t *key,uint32_t ek[44], uint32_t dk[44]);
void AddRoundKey(uint8_t (*state)[4],const uint32_t *);
void SubBytes(uint8_t (*state)[4]);
void SubBytes_(uint8_t (*state)[4]);
void ShiftRows(uint8_t (*state)[4]);
void ShiftRows_(uint8_t (*state)[4]);
uint8_t GaloisMulti(uint8_t x,uint8_t y);
void MixColumn(uint8_t (*state)[4]);
void MixColumn_(uint8_t (*state)[4]);


uint8_t GMul(uint8_t u, uint8_t v);


#endif /* function_h */
