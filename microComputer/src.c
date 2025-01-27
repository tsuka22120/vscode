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
void move_me(struct position *me) {
    int i;
    struct position old_position;

    old_position.x = me->x;
    old_position.y = me->y;

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
    LCD_cursor(me->x, me->y);
    LCD_putch('>');
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
    AD0.ADCSR.BIT.ADM = 0;    // シングルモード
    AD0.ADCSR.BIT.CH = 0;     // AN0
    AD0.ADCSR.BIT.TRGE = 1;   // MTU2からのトリガ有効
    AD0.ADTSR.BIT.TRG0S = 1;  // TGRAコンペアマッチでトリガ

    // MTU2 ch1
    MTU21.TCR.BIT.TPSC = 3;  // 1/64選択
    MTU21.TCR.BIT.CCLR = 1;  // TGRAのコンペアマッチでクリア
    MTU21.TGRA = 31250 - 1;  // 100ms

    LCD_init();

    MTU2.TSTR.BIT.CST0 = 1;  // MTU2 CH0スタート
    MTU2.TSTR.BIT.CST1 = 1;  // MTU2 CH1スタート

    me.x = me.y = 0;
    for (i = 0; i < NMROF_ROCKS; i++) rock[i].active = 0;

    status = STOP;
    move_timing = new_timing = 0;
    while (1) {
        if (MTU21.TSR.BIT.TGFA) {  // ゲーム用のタイマのフラグ
            // MTU2 ch1 コンペアマッチ発生(100ms毎)
            MTU21.TSR.BIT.TGFA = 0;  // フラグクリア

            // 100msに1回、スイッチを読む
            stop_sw = SW4;
            pause_sw = SW5;
            run_sw = SW6;

            if (status == RUN) {
                // ゲーム中
                move_me(&me);  // 自分移動
                if (move_timing++ >= 2) {
                    move_timing = 0;
                    move_rock(rock);  // 岩を移動
                    if (new_timing-- <= 0) {
                        new_timing = rand() * 5 / (RAND_MAX + 1) +
                                     1 new_rock(rock);  // 新しい岩が出現
                    }
                }
                if (pause_sw) {
                    status = PAUSE1;
                    for (i = 0; i < 16; i++) {
                        LCD_cursor(i, 0);
                        LCD_putch(' ');
                        LCD_cursor(i, 1);
                        LCD_putch(' ');
                    }
                    strPrint[16] = "MEMES GAME";
                    LCD_cursor(0, 0);
                    LCD_putstr(strPrint);
                    strPrint[16] = "PUSH switch6";
                    LCD_cursor(0, 1);
                    LCD_putstr(strPrint);  // 文字列の扱いがよくわからない
                }
            } else if (status == PAUSE1) {
                if (!pause_sw)        // pause_sw が OFF なら
                    statue = PAUSE2;  // status を PAUSE2 へ
            } else if (status == PAUSE2) {
                if (pause_sw)         // pause_sw が ON なら
                    status = PAUSE3;  // status を PAUSE3 へ
            } else if (status == PAUSE3) {
                if (!pause_sw)    // pause_sw が OFF なら
                    status = RUN  // sutatus を RUN へ
            } else {
                // 停止中
                if (run_sw) status = RUN;
            }
        }
        // if (@@@@@) として 7セグ用のタイマフラグ を見るようにするとよい
    }
}