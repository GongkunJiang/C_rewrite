#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

//定义IEEE754标准规定的实数的双精度二进制表示的结构体
typedef struct bin_num {
    char s[64];
    char e[64];
    char f[64];
} bn;

//使用函数前，需要在main函数前对使用的函数进行声明
bn double_precision(double num);

double real_number(bn dp);

int bin2dec(char *str);

char *left_bit_shift(char *str);

double b2_x(double num);

char *define(char *str);

char *xor(char *str1, char *str2);


int left_count;     //定义全局变量，记录左移位操作移的位数
int main() {
    bn dp;
    char *lbs, *def;
    double num4, num3, num2, num = -0.5032793119999965;
    printf("num = %.20lf\n", num);
    dp = double_precision(num);
    printf("s = %s\n", dp.s);
    printf("e = %s\n", dp.e);
    printf("f = %s\n", dp.f);
    num2 = real_number(dp);
    printf("num = %.20lf\n", num2);
    lbs = left_bit_shift(dp.f);
    printf("lbs = %s\n", lbs);
    strcpy(dp.f, lbs);
    num3 = real_number(dp);
    printf("num = %.20lf\n", num3);
    def = define(dp.f);
    printf("def = %s\n", def);
    printf("left_count = %d\n", left_count);
    num4 = b2_x(num);
    printf("num = %.20lf\n", num4);
    return 0;

}

bn double_precision(double num) {
    bn dp={{},{},{}};
    double exponent, decimal;
    int power = 0;
    if (num == 0) {
        strcpy(dp.s, "0");
        strcpy(dp.e, "0");
        strcpy(dp.f, "0");
        return dp;
    } else if (num > 0)
        strcpy(dp.s, "0");
    else {
        strcpy(dp.s, "1");
        num = -num;
    }
    while (num >= pow(2, power))
        power += 1;
    while (num < pow(2, power))
        power -= 1;
    exponent = pow(2, power);
    decimal = num - exponent;
    itoa(power + 1023, dp.e, 2);
    strcpy(dp.f, "");
    while (decimal > 0) {
        if (decimal * 2.0 >= exponent) {
            strcat(dp.f, "1");
            decimal = decimal * 2.0 - exponent;
        } else {
            strcat(dp.f, "0");
            decimal = decimal * 2.0;
        }
    }
    char fill[64];
    while (strlen(dp.e) < 11) {
        strcpy(fill, "0");
        strcat(fill, dp.e);
        strcpy(dp.e, fill);
    }
    while (strlen(dp.f) < 52)
        strcat(dp.f, "0");
    return dp;
}

double real_number(bn dp) {
    double real_num, exponent, decimal = 0;
    char *p;
    p = dp.f;
    while (*(p + strlen(p) - 1) == '0')
        *(p + strlen(p) - 1) = 0;
    p = dp.e;
    while (*p == '0')
        p++;
    strcpy(dp.e, p);
    exponent = pow(2, bin2dec(dp.e) - 1023);
    p = dp.f + strlen(dp.f) - 1;
    while (p != dp.f - 1) {
        if (*p == '1')
            decimal = (decimal + exponent) / 2;
        else
            decimal /= 2;
        p--;
    }
    real_num = exponent + decimal;
    if (*dp.s == '1')
        real_num = -real_num;
    return real_num;
}

int bin2dec(char *str) {
    int i, num = 0, len;
    len = strlen(str);
    for (i = len - 1; i >= 0; i--)
        num += (str[i] - 48) * (int)pow(2, len - 1 - i);    //'0'的ascii为48
    return num;
}

char *left_bit_shift(char *str) {
    char *p, q[64];
    p = str;
    while (*p == '0')
        p++;
    p++;
    strcpy(q, str);
    left_count = (int)(p - str);
    q[left_count] = 0;
    strcat(p, q);
    return p;
}

char *define(char *str) {
    char h[64], *l, *r;
    strcpy(h, str);
    l = str;
    l = l + 26;
    strrev(l);
    r = xor(h, l);
    strrev(l);
    strcat(r, l);
    return r;
}

char *xor(char *str1, char *str2) {
    char a[64], *p = str1, *q = str2;
    int i = 0;
    while (*p != 0) {
        if (*p == *q)
            a[i++] = '0';
        else
            a[i++] = '1';
        p++, q++;
    }
    p = a;
    p[26] = 0;
    return p;
}

double b2_x(double num) {
    bn dp = double_precision(num);
    char *bitf = define(dp.f);
    char *lbs = left_bit_shift(bitf);
    strcpy(dp.f, lbs);
    itoa(1023 - left_count, dp.e, 2);
    strcpy(dp.s, "0");
    char fill[64];
    while (strlen(dp.e) < 11) {
        strcpy(fill, "0");
        strcat(fill, dp.e);
        strcpy(dp.e, fill);
    }
    double num2 = real_number(dp);
    return num2;
}


