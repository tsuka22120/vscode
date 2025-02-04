#define DIGIT 1000

#define RADIX 1000000000
#define RADIX_LEN 9
#define MARGIN 100

#define ROOT

#ifdef ROOT
#ifndef KETA
#define KETA (DIGIT + MARGIN) * 4 / RADIX_LEN + 1
#endif
#endif

#ifdef FACTORIAL
#ifndef KETA
#define MARGIN 3  // 余裕を持たせる
#define KETA DIGIT / RADIX_LEN + MARGIN
#endif
#endif

#ifdef DOUBLEFACTORIAL
#ifndef KETA
#define MARGIN 3  // 余裕を持たせる
#define KETA DIGIT + MARGIN
#endif
#endif

#ifdef MULTIPLE
#ifndef KETA
#define MARGIN 3  // 余裕を持たせる
#define KETA DIGIT / RADIX_LEN + MARGIN
#endif
#endif

#define PLUS1
#define ZERO 0
#define MINUS -1

#define TRUE 1
#define FALSE 0

#define RADIX_T long long

typedef struct NUMBER {
    RADIX_T n[KETA];  // 各桁の変数
    int sign;      // 符号変数 -1: 負, 0: 0, 1: 正
} Number;

void clearByZero(Number *);
void dispNumber(const Number *);
void dispNumberZeroSuppress(const Number *);
void dispNumberInB(const Number *, int);
void setRnd(Number *, int);
void copyNumber(Number *, const Number *);
void getAbs(const Number *, Number *);
int isZero(const Number *);
int mulBy10(const Number *, Number *);
int mulBy10SomeTimes(const Number *, Number *, int);
int divBy10(const Number *, Number *);
void divBy10SomeTimes(const Number *, Number *, int);
int setInt(Number *, long);
int getInt(const Number *, int *);
int setSign(Number *, int);
int getSign(const Number *);
int numComp(const Number *, const Number *);
int numCompWithInt(const Number *, int);
void swap(Number *, Number *);
int add(const Number *, const Number *, Number *);
int sub(const Number *, const Number *, Number *);
int increment(Number *, Number *);
int decrement(Number *, Number *);
int simpleMultiple(int, int, int *);
int multiple(const Number *, const Number *, Number *);
int fastMultiple(const Number *, const Number *, Number *);
int simpleDivide(int, int, int *, int *);
int divide(const Number *, const Number *, Number *, Number *);
int divideWithoutRemainder(const Number *, const Number *, Number *);
int divideWithoutQuotient(const Number *, const Number *, Number *);
int divideByInverse(const Number *, const Number *, Number *);
int inverse2(const Number *, Number *);
int inverse3(const Number *, Number *);
int sqrt_mp(const Number *, Number *);
int sqrt_newton(const Number *, Number *);
int sqrtThree(Number *);
int power(const Number *, int, Number *);
int p_recursive(int x, int n);
int fastpower(const Number *, int, Number *);
int factorial(int, Number *);
int doubleFactorial(int, Number *);
void gcd(const Number *, const Number *, Number *);
int lcm(const Number *, const Number *, Number *);
int arctan(const Number *, Number *);
int getLen(const Number *);
int comparePi(const Number *);
int compareRootThree(const Number *);