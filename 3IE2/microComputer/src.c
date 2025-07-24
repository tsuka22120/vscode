/***********************************************************************/
/*  FILE        :memes_final.c                                         */
/***********************************************************************/
#include <stdlib.h>

#include "iodefine.h"
#include "typedefine.h"

#define printf ((int (*)(const char *, ...))0x00007c7c)

#define SW6 (PD.DR.BIT.B18)
#define SW5 (PD.DR.BIT.B17)
#define SW4 (PD.DR.BIT.B16)

#define LED6 (PE.DR.BIT.B11)
#define LED_ON (0)
#define LED_OFF (1)

#define DIG1 (PE.DR.BIT.B3)
#define DIG2 (PE.DR.BIT.B2)
#define DIG3 (PE.DR.BIT.B1)

#define SPK (PE.DR.BIT.B0)

#define LCD_RS (PA.DR.BIT.B22)
#define LCD_E (PA.DR.BIT.B23)
#define LCD_RW (PD.DR.BIT.B23)
#define LCD_DATA (PD.DR.BYTE.HH)

#define NMROF_ROCKS 6

enum STS { STOP, RUN, PAUSE1, PAUSE2, PAUSE3 };

int score;

struct position {
    int x;
    int y;
    int active;
};

void wait_us(_UINT);
void LCD_inst(_SBYTE);
void LCD_data(_SBYTE);
void LCD_cursor(_UINT, _UINT);
void LCD_putch(_SBYTE);
void LCD_putstr(_SBYTE *);
void LCD_cls(void);
void LCD_init(void);
void missBeep(void);
void startBeep(void);

// --------------------
// -- 使用する関数群 --
// --------------------
void wait_us(_UINT us) {
    _UINT val;

    val = us * 10 / 16;
    if (val >= 0xffff) val = 0xffff;

    CMT0.CMCOR = val;
    CMT0.CMCSR.BIT.CMF &= 0;
    CMT.CMSTR.BIT.STR0 = 1;
    while (!CMT0.CMCSR.BIT.CMF);
    CMT0.CMCSR.BIT.CMF = 0;
    CMT.CMSTR.BIT.STR0 = 0;
}

void LCD_inst(_SBYTE inst) {
    LCD_E = 0;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_E = 1;
    LCD_DATA = inst;
    wait_us(1);
    LCD_E = 0;
    wait_us(40);
}

void LCD_data(_SBYTE data) {
    LCD_E = 0;
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_E = 1;
    LCD_DATA = data;
    wait_us(1);
    LCD_E = 0;
    wait_us(40);
}

void LCD_cursor(_UINT x, _UINT y) {
    if (x > 15) x = 15;
    if (y > 1) y = 1;
    LCD_inst(0x80 | x | y << 6);
}

void LCD_putch(_SBYTE ch) { LCD_data(ch); }

void LCD_putstr(_SBYTE *str) {
    _SBYTE ch;

    while (ch = *str++) LCD_putch(ch);
}

void LCD_cls(void) {
    LCD_inst(0x01);
    wait_us(1640);
}

void LCD_init(void) {
    wait_us(45000);
    LCD_inst(0x30);
    wait_us(4100);
    LCD_inst(0x30);
    wait_us(100);
    LCD_inst(0x30);

    LCD_inst(0x38);
    LCD_inst(0x08);
    LCD_inst(0x01);
    wait_us(1640);
    LCD_inst(0x06);
    LCD_inst(0x0c);
}

// --------------------------------------------
// -- ゲーム用の関数群 --

// -- 自分を移動 --
void move_me(struct position *me, struct position rock[]) {
    int i;
    struct position old_position;

    old_position.x = me->x;
    old_position.y = me->y;
    me->active = 1;

    if (AD0.ADDR0 < 0x4000) {
        // -- ジョイスティック上 --
        me->y = 0;
    } else if (AD0.ADDR0 > 0xc000) {
        // -- ジョイスティック下 --
        me->y = 1;
    }
    if (AD0.ADDR1 > 0xc000 && me->x > 0) {
        me->x--;
    } else if (AD0.ADDR1 < 0x4000 && me->x < 15) {
        me->x++;
    }

    if (old_position.y != me->y || old_position.x != me->x) {
        // -- 移動したとき .. 古い表示を消す --
        LCD_cursor(old_position.x, old_position.y);
        LCD_putch(' ');
    }
    for (i = 0; i < NMROF_ROCKS; i++) {
        if (rock[i].active) {
            if ((old_position.x == rock[i].x && old_position.y == rock[i].y) ||
                (me->x == rock[i].x &&
                 me->y == rock[i].y)) {  // プレイヤーに触れたら岩を消す
                score -= 5;
                if (score < 0) score = 0;
                rock[i].active = 0;
                LCD_cursor(rock[i].x, rock[i].y);
                LCD_putch(' ');
                me->active = 0;
                missBeep();
                break;
            }
        }
    }
    if (me->active) {
        LCD_cursor(me->x, me->y);
        LCD_putch('>');
    } else {
        LCD_cursor(me->x, me->y);
        LCD_putch(' ');
    }
}

// -- 岩を移動 --
void move_rock(struct position rock[]) {
    int i;

    for (i = 0; i < NMROF_ROCKS; i++) {
        if (rock[i].active) {
            // 画面上に岩が存在する
            LCD_cursor(rock[i].x, rock[i].y);
            LCD_putch(' ');
            if (rock[i].x == 0) {
                // 消去
                score++;
                rock[i].active = 0;
            } else {
                rock[i].x--;
                LCD_cursor(rock[i].x, rock[i].y);
                LCD_putch('*');
            }
        }
    }
}

// -- 新しい岩を作る --
void new_rock(struct position rock[]) {
    int i;

    for (i = 0; i < NMROF_ROCKS; i++) {
        if (rock[i].active == 0) {
            // -- 新しい岩 --
            rock[i].active = 1;
            rock[i].x = 15;
            rock[i].y = rand() % 2;
            LCD_cursor(rock[i].x, rock[i].y);
            LCD_putch('*');
            break;
        }
    }
}

void do_7seg() {
    static int keta;
    int num1 = score % 10;
    int num2 = (score / 10) % 10;
    int num3 = score / 100;
    PA.DR.BYTE.HL &= 0xf0;
    DIG1 = DIG2 = DIG3 = 0;

    if (keta == 0) {
        PA.DR.BYTE.HL |= num1;
        DIG1 = 1;
        keta++;
    } else if (keta == 1) {
        PA.DR.BYTE.HL |= num2;
        if (num2 == 0 && num3 == 0) {
            DIG2 = 0;
        } else {
            DIG2 = 1;
        }
        keta++;
    } else if (keta == 2) {
        PA.DR.BYTE.HL |= num3;
        if (num3 == 0) {
            DIG2 = 0;
        } else {
            DIG3 = 1;
        }
        keta = 0;
    }
}

void missBeep() {
    int i = 0;

    // MTU2 ch3 sound
    MTU23.TCR.BIT.TPSC = 0;
    MTU23.TCR.BIT.CCLR = 1;
    MTU23.TGRA = 10000 - 1;
    MTU2.TSTR.BIT.CST3 = 1;

    while (i < 100) {
        if (MTU23.TSR.BIT.TGFA = 0) {
            SPK ^= 1;
            i++;
        }
    }
    MTU2.TSTR.BIT.CST3 = 0;
}

void startBeep() {
    int i = 0;

    // MTU2 ch3 sound
    MTU23.TCR.BIT.TPSC = 0;
    MTU23.TCR.BIT.CCLR = 1;
    MTU23.TGRA = 5000 - 1;
    MTU2.TSTR.BIT.CST3 = 1;

    while (i < 100) {
        if (MTU23.TSR.BIT.TGFA = 0) {
            SPK ^= 1;
            i++;
        }
    }
    wait_us(100000);
    i = 0;
    while (i < 100) {
        if (MTU23.TSR.BIT.TGFA = 0) {
            SPK ^= 1;
            i++;
        }
    }
    MTU2.TSTR.BIT.CST3 = 0;
}

// --------------------------------------------
// -- メイン関数 --
void main() {
    struct position me;                 // 自分の車の座標
    struct position rock[NMROF_ROCKS];  // 岩の座標
    char strPrint[16];
    int move_timing, new_timing;
    int ad, i;
    int stop_sw, run_sw, pause_sw;
    int status;

    score = 0;

    STB.CR4.BIT._AD0 = 0;
    STB.CR4.BIT._CMT = 0;
    STB.CR4.BIT._MTU2 = 0;

    CMT0.CMCSR.BIT.CKS = 1;

    // MTU2 ch0
    MTU20.TCR.BIT.TPSC = 3;   // 1/64選択
    MTU20.TCR.BIT.CCLR = 1;   // TGRAのコンペアマッチでクリア
    MTU20.TGRA = 31250 - 1;   // 100ms
    MTU20.TIER.BIT.TTGE = 1;  // A/D変換開始要求を許可

    // AD0
    AD0.ADCSR.BIT.ADM = 3;    // シングルモード
    AD0.ADCSR.BIT.CH = 1;     // AN0
    AD0.ADCSR.BIT.TRGE = 1;   // MTU2からのトリガ有効
    AD0.ADTSR.BIT.TRG0S = 1;  // TGRAコンペアマッチでトリガ

    // MTU2 ch1
    MTU21.TCR.BIT.TPSC = 3;  // 1/64選択
    MTU21.TCR.BIT.CCLR = 1;  // TGRAのコンペアマッチでクリア
    MTU21.TGRA = 31250 - 1;  // 100ms

    // MTU2 ch2 7seg
    MTU22.TCR.BIT.TPSC = 3;
    MTU22.TCR.BIT.CCLR = 1;
    MTU22.TGRA = 1000 - 1;

    LCD_init();

    MTU2.TSTR.BIT.CST0 = 1;  // MTU2 CH0スタート
    MTU2.TSTR.BIT.CST1 = 1;  // MTU2 CH1スタート
    MTU2.TSTR.BIT.CST2 = 1;  // MTU2 CH2スタート

    PFC.PAIORH.BYTE.L |= 0x0F;
    PFC.PEIORL.BIT.B1 = 1;
    PFC.PEIORL.BIT.B2 = 1;
    PFC.PEIORL.BIT.B3 = 1;

    me.x = me.y = 0;
    for (i = 0; i < NMROF_ROCKS; i++) rock[i].active = 0;

    status = STOP;
    move_timing = new_timing = 0;
    while (1) {
        if (MTU21.TSR.BIT.TGFA) {
            MTU21.TSR.BIT.TGFA = 0;

            // 100msに1回、スイッチを読む
            stop_sw = SW4;
            pause_sw = SW5;
            run_sw = SW6;

            if (status == RUN) {
                // ゲーム中
                move_me(&me, rock);  // 自分移動
                if (move_timing++ >= 2) {
                    move_timing = 0;
                    move_rock(rock);  // 岩を移動
                    if (new_timing-- <= 0) {
                        new_timing = rand() * 2 / (RAND_MAX + 1) + 1;
                        new_rock(rock);  // 新しい岩が出現
                    }
                }
                if (pause_sw) {
                    status = PAUSE1;
                    LCD_cls();
                    LCD_cursor(0, 0);
                    LCD_putstr("PAUSE");
                    LCD_cursor(0, 1);
                    LCD_putstr("PUSH switch5");
                }
                if (stop_sw) {
                    status = STOP;
                }
            } else if (status == PAUSE1) {
                if (!pause_sw)        // pause_sw が OFF なら
                    status = PAUSE2;  // status を PAUSE2 へ
            } else if (status == PAUSE2) {
                if (pause_sw)         // pause_sw が ON
                    status = PAUSE3;  // status を PAUSE3 へ
            } else if (status == PAUSE3) {
                if (!pause_sw){  // pause_sw が OFF なら
                    startBeep();
                LCD_cls();
				}
                status = RUN;  // sutatus を RUN へ
            } else { // statusがSTOPのとき
                LCD_cls();
                LCD_cursor(0, 0);
                LCD_putstr("MEMES GAMES");
                LCD_cursor(0, 1);
                LCD_putstr("PUSH switch6");
                // 停止中
                if (run_sw) {
                    startBeep();
                    status = RUN;
                    LCD_cls();
                }
            }
        }
        // if (@@@@@) として 7セグ用のタイマフラグ を見るようにするとよい
        if (MTU22.TSR.BIT.TGFA) {
            MTU22.TSR.BIT.TGFA = 0;
            do_7seg();
        }
    }
}