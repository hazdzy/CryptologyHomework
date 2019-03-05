//
//  main.c
//  Vegenia_Code
//  Created by 翔誉 on 2019/3/1.
//  确定秘钥字的部分是我写的，其余部分是队友把c文件给我，我经适当改写和添加注释放进去的。
#include <stdio.h>
#include <memory.h>
#include <string.h>
#define LENGTH 1000
int count=0;//记录个子字符串长度；
int countAll=0;//记录字符总数；
char text_char[LENGTH];//记录文本，允许记录长1000的文本；
float GetItsFrequency(char *);
void Get_Info(char *);

int main()
{
    float index[11][11]={0};//第一维是间距；第二维，下标0-9用来存储间距d情况各子字符串的频率，具体见下；下标10用来记录d间距情况和标准情况的偏差
    memset(text_char,'\0',sizeof(char)*LENGTH);//初始化数组
    //读取文本
    Get_Info("/Users/Huyizhen/Desktop/input.txt");

    //确定秘钥长d
    int number=1;//当前最接近标准情况（重合指数接近0.065）的间距
    float tempo=1.0;//记录当前和标准情况的距离的最小值（欧氏距离）
    for(int d=2;d<=10;d++)
    {
        for(int i=0;i<d;i++)
        {
            char text_tempo[LENGTH/d+1];
            for(int j=0;j<(LENGTH/d+1);j++)//对各个子字符串统计他们的频率并计算和标准情况的差值
                text_tempo[j]=text_char[i+j*d];
            index[d][i]=GetItsFrequency(text_tempo);
            index[d][10]+=(index[d][i]-0.065)*(index[d][i]-0.065);
        }
        index[d][10]/=d;//得到差值的平均值
        if(index[d][10]<tempo)//求最可能的间距d
        {
            tempo=index[d][10];
            number=d;
        }
    }
    printf("最有可能的循环节是：%d\n下面进行人工检查及确定秘钥位移。\n",number);
    //这次作业第六段密文的循环节基本断定是6了；
    
    //确定秘钥字
    int k0[10]={0};//就跑出来的结果看，如果秘钥长度错误的话，最后是不会输出任何数字的；
    int letter[10][26]={0};
    int length[10]={0};
    double    prob[10][26]={0};
    
    int num;
    double index2;
    
    for (num = 0; num<countAll; num++)//统计字符频率
    {
        length[num % number]++;
        letter[num % number][text_char[num]-'a']++;
    }
    
    for (int i = 0; i <number; i++)
        for (int j = 0; j <= 25; j++)
            prob[i][j] = (double)letter[i][j] / (double)length[i];
    
    for (int i = 0; i <number; i++)//计算重合互指数
        for (int k = 0; k <= 25; k++)
        {
            index2 = 0;
            for (int j = 0; j <= 25; j++)
                index2 += prob[0][(j + k) % 26] * prob[i][j]
                ;
            if ((index2 > 0.055) && index2<0.075 )//最好的情况是i=1，2……number-1的情况各有1个输出，若不然，再优化判别条件
            {
                printf("第%d位和第一位相对位移为%d的指数是：%f\n", i + 1, k, index2);
                k0[i] = k;
            }
            
        }
    
    //遍历秘钥
    char k1[number];
    FILE *fp1;
    fp1 = fopen("/Users/Huyizhen/Desktop/output.txt","w");
    for(int i = 0; i <= 25; i++)
    {
        for(int j=0;j<number;j++)
            k1[j]=(i+k0[j])%26+'a';
        printf("秘钥：%s\n", k1);
        char ch;
        int j=0;
    /*生成明文，这里直接生成了26段，可以通过计算频率，和标准频率表对比（计算二者欧氏距离取最小者）得到最可能明文；另一个办法是
    把26段可能明文都写出来，ctrl+f检索the和and的分布，进而确定明文；后者可靠一些，复杂度也不高，我们采用第二个办法了。（第一个办法的代码实现是平凡的）*/
        while((ch=text_char[j])>='a' && ch <= 'z' && j<countAll)
        {
            fprintf(fp1, "%c", (ch+k1[j%number]+26)%26+'a');
            j++;
        }
        fprintf(fp1, "%s", "下一组：/n");
    }
    fclose(fp1);

    return 0;
}

float GetItsFrequency(char *text)//计算频率
{
    float index=0;
    int rate_of_alphabet[26]={0};
    char *p=text;
    while(*p!='\0')
    {
        rate_of_alphabet[*p-'a']++;
        count++;
        p++;
    }
    if(count*2>countAll)
        countAll=count*2;
    p=NULL;
    for(int i=0;i<26;i++)
    {
        index +=(rate_of_alphabet[i]*(rate_of_alphabet[i]-1))/(float)(count*(count-1));
    }
    count=0;
    return index;
}

void Get_Info(char *s)//用于读取
{
    FILE *np=fopen(s,"r");
    if(np!=NULL){
        for(int i=0;i<LENGTH && !feof(np);i++)
                fscanf(np,"%c",&text_char[i]);
        fclose(np);
    }
    else
        printf("未找到该文件\n");
}
