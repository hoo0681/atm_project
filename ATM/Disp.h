#pragma once
//#include "Disp.c"
#include "ATM_type.c"
extern void Disp_main(void);
extern int Disp_ID_input(ID* id_num);//id_num의 id_num에 입력받은 값을 입력 PW는 없음
extern int Disp_PW_input(ID* pw);//pw의 pw에 입력받은 값을 대입
extern int Disp_money_input(unsigned long long* money);//입력받은 돈의 값을 대입
extern void Disp_LookUp(member user);
extern int Disp_Transfer_ck(member user, unsigned short id_num, unsigned long long money);//계좌 이체 확인
extern void Disp_cancel(void);
extern void Disp_Wrong_input(void);
extern int Disp_name_ck(unsigned short id_num);//계좌 이체시 상대 이름 확인
extern void Disp_NO_account(void);
extern void Disp_Wrong_PW(void);
extern void Disp_insufficient_balance(void);

