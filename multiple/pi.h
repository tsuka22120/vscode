#define DIGIT 8000

#define RADIX 1000000000
#define RADIX_LEN 9
#define MARGIN 100

#define KETA (DIGIT + MARGIN) * 4 / RADIX_LEN + 1

#define PLUS 1
#define ZERO 0
#define MINUS -1

#define TRUE 1
#define FALSE 0

#define RADIX_T long long int

typedef struct NUMBER {
    RADIX_T n[KETA];  // 各桁の変数
    int sign;         // 符号変数 -1: 負, 0: 0, 1: 正
} Number;

void clearByZero(Number *);
void dispNumber(const Number *);
void copyNumber(Number *, const Number *);
void getAbs(const Number *, Number *);
int isZero(const Number *);
int mulBy10SomeTimes(const Number *, Number *, int);
void divBy10SomeTimes(const Number *, Number *, int);
int setInt(Number *, long);
int getInt(const Number *, int *);
int setSign(Number *, int);
int getSign(const Number *);
int numComp(const Number *, const Number *);
int numCompWithInt(const Number *, int);
int add(const Number *, const Number *, Number *);
int sub(const Number *, const Number *, Number *);
int multiple(const Number *, const Number *, Number *);
int inverse3(const Number *, Number *);
int divideByInverse(const Number *, const Number *, Number *);
int sqrtThree(Number *);
int getLen(const Number *);
int comparePi(const Number *);
int compareRootThree(const Number *);