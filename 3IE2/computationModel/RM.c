/* ===================================================================
  「計算モデル論」 RMシミュレータ RM.c

   機能：1) 命令読込・解読・実行サイクルの実装
        2) 命令の実行過程の表示
        3) ファイルからプログラムの読み込み (*.ram, *.rm)
        4) オプションの処理 (-s, -t)
        5) コメント対応   //...
        6) 正常終了，連続実行への切替機能 c, q
        7) 命令名の変更（add1->succ, sub1->pred）
                               2017/09/18      作成者 T.Inomata
        8) 命令の追加（PLUS, MINUS）即値との加算・減算
                               2018/04/24      作成者 T.Inomata
        9) 配列名称・印字文字変更（ R[]<-->M[] ）
           プログラムの印字（命令コード形式）オプション -p 追加
                               2018/08/07      作成者 T.Inomata
       10) 命令名の変更（setd->setc）
                               2018/08/31      作成者 T.Inomata     
       11) 命令の追加（JEQ0）
　                              2019/03/01      作成者 T.Inomata     
       12) 最終行に改行文字がない場合に対応
           HALTが複数個ある場合にも対応
                               2019/05/08      作成者 T.Inomata
       13) コメントがない行の場合に対応
                               2020/05/21      作成者 T.Inomata
       14) PRED, SUB, MINUS での Acc の負判定の追加
                               2021/04/27      作成者 T.Inomata
 --------------------------------------------------------------------
実行の仕方:
   RMプログラム書かれたファイル名を sample.ram とした場合：
   $ RM [-s -t]  sample.ram
       -s : ワンサイクル実行（リターンキーで再開） 
       -t : ワンサイクル毎にレジスタの内容印字
       -r n : レジスタ表示個数 n の指定（デフォルト 7）

    プログラムの強制終了は，Cntrl-c 
====================================================================== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VERSION "2.4"    // バージョン番号 2.3 --> 2.4       2021/04/27
#define MEMORY_MAX 100  // レジスタ群（データ領域）の最大サイズ
#define INST_MAX    15   // RM命令の種類  *************
#define INSTNAME_MAX 7  // 命令名の最大長
#define OP           0  // 命令レジスタのオペレータ指定添字
#define ORD          1  // 命令レジスタのオペランド指定添字
#define RUN          0  // シミュレータの実行モード(開始)
#define STEP       100  // シミュレータの実行モード(ワンサイクル単位)
#define TRACE      200  // シミュレータの実行モード(レジスタ内容印字)
#define PRINT      300  // プログラムの印字
#define EOS        '\0' // 文字列の終端

#define LOAD    1 // RM命令
#define STORE   2 // RM命令
#define JUMP    3 // RM命令
#define JZERO   4 // RM命令
#define HALT    5 // RM命令
#define SETC    6 // RM命令
#define SUCC    7 // RM命令
#define PRED    8 // RM命令
#define ADD     9 // RM命令
#define SUB    10 // RM命令
#define LOADI  11 // RM命令
#define STOREI 12 // RM命令
#define PLUS   13 // RM命令 *************
#define MINUS  14 // RM命令 *************
#define JEQ0   15 // RM+命令 *************

int  RM_State = RUN; // RMシミュレータ実行モード
int  Program_Max = 0; // プログラム命令数
int  Reg_Max = 11;     // デバッグ時のデータ領域印字サイズ（デフォルト）
int  N_Cycle = 0;     // 命令実行サイクルカウンタ
int  Ic = 0;          // 命令ポインタ
int  Acc = 0;         // アキュムレータ（累算器）
int  InstReg[2] = {0, 0}; // 命令レジスタ[オペレータ，オペランド]
int  M[MEMORY_MAX] ; // プログラム領域  
int  R[MEMORY_MAX] ; // レジスタ群　（データ領域） 

char *Inst_Table[] =  // プログラム読み込み時の命令コード変換表
  {     "NOP",    //  #0: ダミー命令(No Operation)
        "LOAD",   //  #1: Acc <-- M[x] 
        "STORE",  //  #2: M[x] <-- Acc
        "JUMP",   //  #3: Ic <-- x               無条件ジャンプ
        "JZERO",  //  #4: (Acc=0 ?) ==> Ic <-- x ゼロ判定ジャンプ
        "HALT",   //  #5: quit　    実行終了
        "SETC",   //  #6: Acc <-- x
        "SUCC",   //  #7: Acc <-- Acc + 1 後者
        "PRED",   //  #8: Acc <-- Acc - 1 前者
        "ADD",    //  #9: Acc <-- Acc + M[x] 加算
        "SUB",    // #10: Acc <-- Acc - M[x] 減算
        "LOADI",  // #11: Acc <-- M[M[x]] 間接アドレス
        "STOREI",  // #12: M[M[x]] <-- Acc 間接アドレス
        "PLUS",    // #13: Acc <-- Acc + x 加算（即値x）
        "MINUS",   // #14: Acc <-- Acc - x 減算（即値x）
        "JEQ0"   // #15: (Acc=M[0] ?) ==>  Ic<--x
  };

void  print_program();  // デバッグ用に関数宣言追加 2020/05/21 ###
  
// ======= ファイルからのRMプログラム読み込み ==========

/*  コマンドラインの引数の分割　　 get_args("a b", args)     */
/*                   args[0]="a"  args[1]="b"  args[2]='\0' */
void get_args(char *str, char **args) 
{ while ((*str != EOS) && (*str != '\n'))
  { while ((*str == ' ') || (*str == '\t'))
      { *str++ = EOS; } // 空白，タブをすべて EOS に置換
     *args++ = str;
     while ((*str != EOS) && (*str != ' ') && (*str != '\t'))
      { str++; }
   }
   *args = NULL;
}

//  fname からの読み込み ==========
void read_program(char *fname)   // fname 定義ファイル名
{ int i, j, k, ord;
  char op[INSTNAME_MAX], line[80], ch;
  char *inst[INSTNAME_MAX];
  FILE *fp;
  // ファイル名が存在しているかどうかのチェック
  if ((fp = fopen(fname, "r")) == NULL)
  { printf("ERROR : file name [%s] not found !!\n", fname);
    exit(0);    // ファイルが存在しないときには終了
  }
  i = 0;
  while (1)   // ファイルからプログラムの読み込み
    { k=0;
      while(((ch = getc(fp)) != '\n') && (ch != EOF)) //###2019/05/08
            line[k++] = ch; //「改行またはEOF」以外の場合   ###2019/05/08
      if (k==0) return ;    // 行頭が「EOF」の場合 2020/05/21 ###
      else line[k] = EOS;   // 2020/05/21 ###
#ifdef DEBUG
      printf("---  line=%s ch=%c|k=%d.\n", line, ch, k);
#endif
	k=0;
	while ((line[k] != '/') && (line[k] != EOS)){ k++;} // コメントの有無検出
	if (line[k] == '/')  line[k] = EOS;  // コメント削除
        get_args(line, inst);   //  命令とオペランドの分割
        strcpy(op, inst[OP]);   //  命令（名前）代入
        if (inst[ORD] != EOS) {ord = atoi(inst[ORD]);}// オペランド代入
	else { ord = 0;}
#ifdef DEBUG
  printf("              op=%s| ord=%d\n", op, ord);
#endif
       for(j=1; j <= INST_MAX;j++)
	 { if (strcmp(op, Inst_Table[j])==0) // 命令を検索
           { R[i]= j;                        // 命令コードの格納
             R[i+1]= ord;                    // オペランドの格納
             i = i+2;                        // 命令番地の更新
             Program_Max = Program_Max + 2;  //
             break;
           }
         }
#ifdef DEBUG
       print_program(); // デバッグ用 2020/05/21 ###
#endif       
       if (ch == EOF) return; // ファイルの最後(EOF)であれば読み込み終了###2019/05/08
    }
    return;
}

// ======= RMの初期設定 ==========================
void init_RM()
{ int i;
  for (i = 0; i < MEMORY_MAX; i++) { M[i] = 0; }
  Acc = 0;
  Ic  = 0;
  InstReg[OP] = 0;
  InstReg[ORD] = 0;
  RM_State = RUN;
}

// ======== 命令読込み ==================
void read_inst()
{ int i;
  InstReg[OP]  = R[Ic];
  InstReg[ORD] = R[Ic+1];
  Ic = Ic +2;
}
// ======== 命令解読・実行 ==================
void decode_exec()
{ int operator = InstReg[OP];
  int operand  = InstReg[ORD];
  switch ( operator ) {
     case LOAD  : Acc = M[operand];       break;
     case STORE : M[operand] = Acc;       break;
     case JUMP  : Ic = operand;           break;
     case JZERO : if (Acc == 0)
                    Ic = operand;         break;
     case HALT  : RM_State = HALT;       break;
     case SETC  : Acc = operand;          break;
     case SUCC  : Acc = Acc + 1;          break;
     case PRED  : Acc = Acc - 1;
                  if (Acc < 0) Acc = 0;   break;//*****2021/05/27
     case ADD   : Acc = Acc + M[operand]; break;
     case SUB   : Acc = Acc - M[operand]; 
                  if (Acc < 0) Acc = 0;   break;//*****2021/05/27
     case LOADI : Acc = M[M[operand]];    break;
     case STOREI: M[M[operand]] = Acc;    break;
     case PLUS  : Acc = Acc + operand; break;  //****************
     case MINUS : Acc = Acc - operand;
                  if (Acc < 0) Acc = 0;   break;//*****2021/05/27
     case JEQ0  : if (M[0] == Acc)
                   Ic = operand; break;  //****************
     default    : break; 
   }
}
// ==== デバッグ用：プログラム領域印字
void  print_program()
{ int i;
  printf("    = R ==========\n");
  for (i=0; i < Program_Max; i=i+2)
  {   printf("     %2d |%3d %3d\n", i, R[i], R[i+1] );
  }
  printf("    ==============\n");
}
// ==== デバッグ用：命令レジスタ群印字
void print_inst()
{ printf(" ___________________________________________\n");
  printf(" Cycle=%3d\n", N_Cycle);
  printf("  IC［%3d］  IR［%s %3d］",
                 Ic, Inst_Table[InstReg[0]], InstReg[1]);
  printf("  Acc【%3d】\n", Acc);
  printf(" ___________________________________________\n");  
}
// ==== デバッグ用：レジスタ（データ領域）印字
void  print_register()
{ int i;
  printf("              M ----------\n");
  for (i=0; i < Reg_Max; i++)
  {   printf("              | %2d | %3d |\n", i, M[i]);
  }
  printf("              ------------\n");
}

// ===== RMシミュレーション：Read-Decode-Evalループ ========
void RM_simulation()
{ int x;
  char c;
  while (RM_State != HALT)
  { N_Cycle++;
    //　### デバックモード：レジスタの印字？
    if ((RM_State == TRACE) || (RM_State == STEP))
    {  print_inst();
       print_register();
    } //　### デバックモード：実行停止？
    if (RM_State == STEP)
    {  printf(" --(1サイクル実行：Return  連続実行：c   終了： q) ? ");
       c = getchar();
       if (c=='q') 
       { printf("bye.\n"); exit(0);} //　終了 
       else if (c=='c') 
       { RM_State = TRACE; } //　1サイクル終了，連続実行（トレース有）
    }
    // ***  命令読み込み Read ***
    read_inst();
    // *** 命令解読・実行 Decode-Eval ***
    decode_exec();
  }
}

//    s=".ram", r="foo.ram" --> 1
//    s=".ram", r="foo.c"   --> 0
//    部分文字列の照合
int substrcmp(char *s, char *r)
{ int rl=strlen(r);
  int sl=strlen(s);
  int i=0;
  if (sl > rl) return 0;
  while((*s != EOS) && (*r != EOS))
  { if(*s == *r)
      { for(i=0;i<sl; i++)
	  if (*s++ != *r++)  return 0;
        return 1;
      }
    else {r++;}
  }
  return 0;
}

// ========== オプションの処理 ========================
//   -s : ワンサイクル（ステップ）実行（リターン入力で再開）
//   -t : レジスタ情報（命令，データ）のワンサイクル毎の印字
//   -r n : レジスタ表示個数 n の指定（デフォルト 7）
//   -p : プログラム（R[]の内容）の表示（命令コード），表示後終了
void set_sim_option(int argc, char *args[], char *fname) 
{   int i= 1;
    for(i=0; i < argc; i++)
    { if (!strcmp("-s", args[i]))      //  -s オプションの有無
      {  RM_State = STEP; }
      else if(!strcmp("-t", args[i]))  //  -t オプションの有無
      {  RM_State = TRACE;}
      else if(!strcmp("-r", args[i]))  //  -r オプションの有無
      {  Reg_Max = atoi(args[i+1]);
         i++;                      }
      else if(!strcmp("-p", args[i]))  //  -p オプションの有無
      {   RM_State = PRINT;} // 印字後終了
      else if(   substrcmp(".ram", args[i]) 
              || substrcmp(".rm", args[i])) // プログラムファイルの有無
      {  strcpy(fname, args[i]);  }      
  }
  return;
}

// ====================== 【メイン関数】===========================
int main(int argc, char *argv[])
{ char fname[80];
  init_RM();  // RM パラメータの初期設定
  // ********* オプション処理 ***************
  if (argc > 1) // コマンド引数の個数チェック(1以上でオプションあり)
  { set_sim_option(argc, argv, fname);
    read_program(fname);         
  } else  //  プログラムファイル名は必須であることを印字
  { printf("Usage : %s [-s -t] file_name\n", argv[0]);
    return 1;
  }
#ifdef DEBUG
 print_program(); // RM プログラムの印字
#endif
  // ***** プログラムの印字と終了 ***********
  if (RM_State == PRINT)
  { print_program(); // RM プログラムの印字
    exit(0);
  }//************************************
  // ***** シミュレーションの開始 ***********
  RM_simulation();
  // ***** プログラム停止時のレジスタ印字 ****  
  print_inst();
  print_register();
  return 0;
}
