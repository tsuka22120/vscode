#define KETA 25

#define RADIX 1000000000
#define RADIX_LEN 9

#define PLUS 1
#define ZERO 0
#define MINUS -1

#define TRUE 1
#define FALSE 0

typedef struct NUMBER {
    long n[KETA];  // 各桁の変数
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
int divBy10(const Number *, Number *);
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
int simpleDivide(int, int, int *, int *);
int divide(const Number *, const Number *, Number *, Number *);
int sqrt_mp(const Number *, Number *);
int power(const Number *, int, Number *);
int p_recursive(int x, int n);
int fastpower(const Number *, int, Number *);
int factorial(int, Number *);
void gcd(const Number *, const Number *, Number *);
int lcm(const Number *, const Number *, Number *);