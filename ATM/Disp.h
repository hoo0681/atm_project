#pragma once
//#include "Disp.c"
#include "ATM_type.c"
extern void Disp_main(void);
extern int Disp_ID_input(ID* id_num);//id_num�� id_num�� �Է¹��� ���� �Է� PW�� ����
extern int Disp_PW_input(ID* pw);//pw�� pw�� �Է¹��� ���� ����
extern int Disp_money_input(unsigned long long* money);//�Է¹��� ���� ���� ����
extern void Disp_LookUp(member user);//user�� �ִ� ���� ���� ���
extern int Disp_Transfer_ck(member user, unsigned short id_num, unsigned long long money);//���� ��ü Ȯ��
extern void Disp_cancel(void);//���
extern void Disp_Wrong_input(void);//�߸��� ���Է½�
extern int Disp_name_ck(unsigned short id_num,BANK bank);//���� ��ü�� ��� �̸� Ȯ��
extern void Disp_NO_account(void);//���°� ���� ���
extern void Disp_Wrong_PW(void);//�߸��� ��й�ȣ
extern void Disp_insufficient_balance(void);//�ܾ׺���
extern int Disp_Bank_input(BANK* bank);
