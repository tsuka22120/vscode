#include <limits.h>
#include <stdio.h>

#define BIT_RANGE 32

#define practice6

void printBinaryNumber(int num) {
    int i;
    for (i = BIT_RANGE - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int complementOn2(int num) { return ~num + 1; }
#ifdef practice1
int main(void) {
    printf("number of bits\n");
    printf("size of int is %ld\n", sizeof(int) * 8);
    printf("size of char is %ld\n", sizeof(char) * 8);
    printf("size of short is %ld\n", sizeof(short) * 8);
    printf("size of long is %ld\n", sizeof(long) * 8);
    printf("size of long long is %ld\n", sizeof(long long) * 8);
    printf("size of float is %ld\n", sizeof(float) * 8);
    printf("size of double is %ld\n", sizeof(double) * 8);
    printf("size of long double is %ld\n", sizeof(long double) * 8);
    return 0;
}
#endif

#ifdef practice2_1
int main(void) {
    printf("number range\n");
    printf("unsigned int = %u ~ %u\n", 0, UINT_MAX);
    printf("signed int = %d ~ %d\n", INT_MIN, INT_MAX);
    printf("unsigned char = %u ~ %u\n", 0, UCHAR_MAX);
    printf("signed char = %d ~ %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned short = %u ~ %u\n", 0, USHRT_MAX);
    printf("signed short = %d ~ %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned long = %u ~ %lu\n", 0, ULONG_MAX);
    printf("signed long = %ld ~ %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long long = %u ~ %llu\n", 0, ULLONG_MAX);
    printf("signed long long = %lld ~ %lld\n", LLONG_MIN, LLONG_MAX);
    return 0;
}
#endif

#ifdef practice2_2
int main(void) {
    int max, min;
    max = INT_MAX;
    min = INT_MIN;
    printf("int max = %d\n", max);
    printf("int max + 1 = %d\n", max + 1);
    printf("int min = %d\n", min);
    printf("int min - 1 = %d\n", min - 1);
    return 0;
}
#endif

#ifdef practice2_3
int main(void) {
    int max, min;
    max = UINT_MAX;
    min = 0;
    printf("unsigned int max = %u\n", max);
    printf("unsigned int max + 1 = %u\n", max + 1);
    printf("unsigned int min = %u\n", min);
    printf("unsigned int min - 1 = %u\n", min - 1);
    return 0;
}
#endif

#ifdef practice3_1
int main(void) {
    int num = 0x00000000;
    printf("num = ");
    printBinaryNumber(num);
    printf("complement num = ");
    printBinaryNumber(~num);
    printf("complement num + 1 (complement on 2)= ");
    printBinaryNumber(complementOn2(num));
    return 0;
}
#endif

#ifdef practice3_2
int main(void) {
    int a = -123;
    int b = complementOn2(a);
    printf("a = %d\n", a);
    printf("a = ");
    printBinaryNumber(a);
    printf("b = %d\n", b);
    printf("b = ");
    printBinaryNumber(b);
    printf("a + b = %d\n", a + b);
    return 0;
}
#endif

#ifdef practice3_3
int main(void) {
    int a = 115;
    int b = -115;
    printf("a = %d\n", a);
    printf("a = ");
    printBinaryNumber(a);
    printf("b = %d\n", b);
    printf("b = ");
    printBinaryNumber(b);
    printf("complement on 2 b = %d\n", complementOn2(b));
    return 0;
}
#endif

#ifdef practice4
int main(void) {
    int num = 123;
    int num1 = 1000 - num;  // 10の補数
    int num2 = 999 - num;   // 9の補数
    printf("num = %d\n", num);
    printf("complement on 10 num = %d\n", num1);
    printf("complement on 9 num = %d\n", num2);
    printf("num + complement on 10 num = %d\n", num + num1);
    printf("num + complement on 9 num = %d\n", num + num2);
    return 0;
}
#endif

//ここからpage16

#ifdef practice5_1
int main(void) {
    // 2進数で-6
    int num = 0b00000110;
    printf("num = %d\n", num);
    printf("-6 * 4 = %d\n", num << 2);
    return 0;
}
#endif

//ここからpage18

#ifdef practice6
int main(void){
    int x = -123456; // -123456 = 0xfffe1dc0
    unsigned char *p = (unsigned char *)&x; // ポインタpをxの先頭アドレスに設定
    printf("16進数で表示\n");
    printf("%02x %02x %02x %02x\n", *(p + 3), *(p + 2), *(p + 1), *p);
    printf("10進数で表示\n");
    printf("%d %d %d %d\n", *(p + 3), *(p + 2), *(p + 1), *p);
    printf("2進数で表示\n");
    //未実装
    return 0;
}
#endif