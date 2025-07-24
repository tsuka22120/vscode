/* ===================================================================
      �ַ׻���ǥ����� ���塼��󥰵��� turing.c

          ��ǽ��1) ���ޥ�ɹԤˤ���������ե�����λ���
               2) �ơ��פν�����֤�����Ū������
               3) ����ɽ�����ѹ� [x]
               4) ��λ��ˡ���ѹ� �ʥơ������ϻ���"quit"�Ǥ����ޤ���

                                2019/03/01
                                ������ T.Inomata
      --------------------------------------
�¹Ԥλ���:
   ���塼��󥰵�����������񤫤줿�ե�����̾�� M-2.tm �Ȥ�����硧
   $ TM M-2.tm
   Sigma = {0, 1, *, N, Y, _}
   Input Initial Tape ? 01
 [ 0] : _01__________________
         ^

    �����ǡ���01�פϥơ��פν�����֤Ȥ��Ƥε�����(���ϸ������)
           ����ʸ���ϡ�_�ס�
           ���ϸ������˶��򵭹��ư��������
           ������֤Ǥϥإåɡ�^�פ����ϸ����Ƭʸ���ΰ��֡�    
            [ i] �� i �ϡ����֡�0,1,�������ˤ�ɽ����a
    
    �ץ������򽪤���ϡ�quit�פ����Ϥ��롥
====================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAPE_MAX   100  // �ơ��פΥޥ��ܤκ�����(����Υ�����)
#define SYMBOL_MAX  20  // ����μ���κ�����(����Υ�����)
#define STATE_MAX   20  // ���֤μ�����κ�����(����Υ�����)
#define BLANK ('_');

int  State_Num;        //  ���֤μ����(����ե�����ǻ���)
int  Symbol_Num;       //  ����μ����(����ե�����ǻ���)
char Symbol_Table[SYMBOL_MAX]; //  �������̤��뤿��μ����ֹ�(0,1,2,...)�Ȥ��б�ɽ

// �ơ��פ�ɽ��
int  Max_Tape = 20;  //  ���ߥ�졼����󤹤��оݤε����(ξü�ζ������ޤ�)
char Tape[TAPE_MAX]; //  �ơ��פε�������Ǽ��������
int  Head = 1;       //  ���ߤΥإåɤΰ��֡�����ͤ�1

// TM �ξ��֤�ɽ��
int Init_State = 0;// ������֤�ɽ���ѿ����ͤ� 0
int Now_State;     // ���ߤξ��֤�ɽ���ѿ�(0,1,2,3,...)
int Halt_State;    // ��߾��֤Τ�ɽ���ѿ�(���֤μ����������ե�����������)

struct Action_Data {   // ư��ؿ���ɽ������ι�¤��
  int  st;   // ���֤�������
  char sym;  // �񤭹��ߵ���
  int  dir;  // �إåɤΰ�ư����  R or L
} Action_Func[STATE_MAX][SYMBOL_MAX];  // ư��ؿ���ɽ������������
// ���ߤξ��� i, �ɹ��ߵ��� j �ˤĤ��ơ�
//           Action_Func[i][j].st  ���ξ��� 
//           Action_Func[i][j].sym ����ߵ��� 
//           Action_Func[i][j].sym �إåɤΰ�ư���� 

//  �ڥơ��פ���Υإåɰ��֤ε�����ɹ���ؿ���
//      �ɹ����������б����뼱���ֹ��꥿����
//      Action_Func[i][j] ��ź�� j �Ȥ����Ѥ�����
int input()
{
  char c;
  int i;
  c = Tape[Head];
  for (i = 0; i < Symbol_Num; i++)
    if (Symbol_Table[i] == c)  return i;

  return Symbol_Num - 1;
}

// �ڸ��ߤξ��֤򹹿�����ؿ���
void action_state(int now, char c)
{
  Now_State = Action_Func[now][c].st;
}

// �ڥإåɾ�Υޥ��ܤ˵��������ؿ���
void action_write(int now, char c)
{
  Tape[Head] = Action_Func[now][c].sym;
}

// �ڥإåɤ򣱥ޥ���ư����ؿ���
void action_head(int now, char c)
{
  Head = Head + Action_Func[now][c].dir;
}


// �ڥơ��פε�������������ؿ���
void print_tape()
{
  int i;
  printf(" [%2d] : ", Now_State); // ���ߤξ��֤��qx�פȤ��ư�����x �Ͼ����ֹ� 
  for (i = 0; i <= Max_Tape; i++) // �ơ��׵������ Max_Tape ʸ��ʬ�����
    printf("%c", Tape[i]);
  printf("\n");
  printf("        ");
  for (i = 0; i < Head; i++) // �إåɰ��֤����
    printf(" ");
  printf("^\n");
}

// ������ե����뤫��TM��������Ƥ��ɹ���ǥǡ�����¤�˳�Ǽ����ؿ���
void init(char *fname)   // fname ����ե�����̾
{
  int i, j, k;
  char c, d;
  FILE *fp;

  // �ե�����̾��¸�ߤ��Ƥ��뤫�ɤ����Υ����å�
  if ((fp = fopen(fname, "r")) == NULL)
  {
    printf("ERROR : file name [%s] not found !!\n", fname);
    return;    // �ե����뤬¸�ߤ��ʤ��Ȥ��ˤ϶�����λ
  }

  fscanf(fp, "%d", &State_Num); // ����ե����뤫��־��֤μ�����פ��ɹ���
  Init_State = 0;             // ������֤��ֹ��� 0�פˤ���
  Halt_State = State_Num - 1; // ��߾��֤��ֹ�򡤡־��֤μ����-1�פˤ���
  //    (���֤��ֹ�� 0 �����դ��Ϥ᤿����)

  fscanf(fp, "%d", &Symbol_Num); // ����ե����뤫��ֵ���μ�����פ��ɹ���
  for (i = 0; i < Symbol_Num; i++)
  {
    fscanf(fp, " %c", &c); // ����ե����뤫�鵭������ɹ���
    Symbol_Table[i] = c;   // �����ֹ� 0,1,2,...���դ�������ǵ������Ƥ���
  }
  for (i = 0; i < State_Num; i++) // ����ե����뤫��ư��ؿ��γ����Ǥ��ɹ���
    for (j = 0; j < Symbol_Num; j++)
    {
      fscanf(fp, "%d %c %c", &k, &c, &d);// ���� i���ɹ��ߵ��� j ��ư��ؿ����ɹ���
      Action_Func[i][j].st = k;          // ���ξ��� k
      Action_Func[i][j].sym = c;         // ����ߵ��� c
      Action_Func[i][j].dir = d == 'R' ? 1 : (-1); // �إåɤΰ�ư���� d
    }
}

// �ڥ��塼��󥰵����ν�����֤����ꤹ��ؿ���
void init_TM()
{
  int i;
  for (i = 0; i < TAPE_MAX; i++)
    Tape[i] = BLANK;
  Now_State = Init_State; // ���ߤξ��֤������֤�����
  Head = 1;               // �إåɤΰ��֤�ʸ���ܤ�����
  return;
}

// �����ϸ���ɹ���ؿ���
void read_tape()
{
  int i;
  printf("Sigma = {"); // ����ν���ΰ���
  printf("%c", Symbol_Table[0]);
  for (i = 1; i < Symbol_Num; i++)
  {
    printf(", %c", Symbol_Table[i]);
  }
  printf("}\n");
  printf("Input Initial Tape ? "); // ���ϸ���ɹ���
  scanf("%s", Tape + 1);
//printf(" ? |%s|\n", Tape);
  if (strcmp(Tape+1, "quit")==0)   // quit �����ϡ�
     { printf("bye.\n"); exit(0);} //����λ
  for (i = strlen(Tape); i < TAPE_MAX; i++)
    Tape[i] = BLANK;
}

// �ڥ��塼��󥰵�����ư��Υ��ߥ�졼�����򤹤�ؿ���
void TM_simulation()
{
  int x;

  Max_Tape = 20;
  while (1)
  {
    init_TM();
    read_tape();   // �ơ��פν�����֤�����
    do
    {
      print_tape();                //  ���ߤΥơ��פΰ���
      x = input();                 //  �إåɾ�ε�����ɹ���
      action_write(Now_State, x);  //  ����ν���� 
      action_head(Now_State, x);   //  �إåɤΰ�ư
      action_state(Now_State, x);  //  ���֤�����
    } while (Now_State != Halt_State); // ���ߥ�졼���������Ƚ��
    print_tape();
    printf(" Halt ! \n\n");
  }
}

// �ڥᥤ��ؿ���
int main(int argc, char *argv[])
{
  char fname[80];

  if (argc > 1) init(argv[1]); // ���ޥ�ɰ����θĿ������å� 
  else                         //  ����������ե�����̾�Ȥ����ɹ��߳���
  {
    printf("Usage : %s file_name\n", argv[0]);
    return 1;
  }

  TM_simulation();   // ���ߥ�졼�����γ���
  return 0;
}
