#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include<conio.h>
#include "ATM_type.c"

//#include "Disp.h"
#define NOERR 0
#define NOACCOUNT 1
#define PWERR 2
#define BALANCE_ERR 3 
#define CANCEL 4
void Disp_main(void) {//메인 화면
	printf("1:입금,2:출금,3:계좌이체,4:조회\n");
}
int Disp_ID_input(ID* id_num) {//계좌번호 입력
	printf("계좌번호를 입력하시오.\n");

	scanf("%hu", &(id_num->id.id_num));//입력받기
	while (getchar() != '\n');//입력버퍼 비우기
	printf("확인은 아무키나, 취소는 4번을 누르시오\n");
	if (_getch() == '4')return CANCEL;//취소?
	else return NOERR;
	//id_num의 id_num에 입력받은 값을 입력 PW는 없음
}
int Disp_PW_input(ID* pw) {//비밀번호 입력받기
	char password[6];//비밀번호 변수
	char key;//입력받은 키
	printf("다시쓰기 r, 메인화면으로 c\n");
	printf("PW:");
	for (int i = 0; i < 5; i++) {//비밀번호는 5자리
		key = _getch();

		if (key == '\b'&&i > 0) {//지우기
			i = i > 0 ? i - 2 : 0;
			printf("\b \b");
		}
		else if (key == 'r') {//처음부터 다시 쓰기
			for (i; i > 0; i--) {
				printf("\b \b");
			}
			i = -1;
		}
		else if (key == 'c') {//메인화면으로
			return CANCEL;
		}
		else if (key >= '0'&&key <= '9') {//입력받은 값이 숫자?
			password[i] = key;
			printf("*");//화면에는 *로 표시
		}
		else {
			i--;//잘못된 값은 무시
		}
	}
	printf("\n");
	password[5] = '\0';//마지막은 널문자 넣기
	pw->id.PW = (unsigned short)strtol(password, NULL, 10);//문자열을 변환
	return NOERR;
	//pw의 pw에 입력받은 값을 대입
}

int Disp_money_input(unsigned long long* money) {
	printf("\n 금액입력 \n");
	printf("                                     \\");
	printf("\r");

	scanf("%llu", money);
	while (getchar() != '\n');
	return NOERR;
}//입력받은 돈의 값을 대입
void Disp_LookUp(member user) {
	fprintf(stdout, "\n이름 %s 잔액%llu \n", user.name, (user.balance));
	_getch();
}
int Disp_Transfer_ck(member user, unsigned short id_num, unsigned long long money) {
	if (user.balance < money)return BALANCE_ERR;
	printf("이름 %s 잔액%llu 입니다.\n", user.name, (user.balance));
	printf("계좌 번호: %hu 에 %llu 원을 보내시겠습니까?\n", id_num, money);
	printf("예상잔액은 %llu입니다\n", user.balance - money);
	printf("취소는 4번을 누르세요 다른 키를 누르시면 다음으로 진행됩니다.\n");
	if (_getch() == '4')return CANCEL;
	else return NOERR;
}
//계좌 이체 확인

int Disp_name_ck(unsigned short id_num,BANK bank) {
	char path[20] = { 0 };
	member ret;
	char id[20] = { 0 };//계좌
	_ultoa(id_num, id, 10);//파일이름 추가 
	strcat(path, (const char*)&bank);
	strcat(path, "/");
	strcat(path, (const char*)id);
	strcat(path, ".txt");
	FILE *fp;
	fp = fopen((const char*)path, "r+");
	fscanf(fp, "%lu %s %llu", &(ret.id.Serial_No), ret.name, &(ret.balance));
	fclose(fp);
	printf("\n예금주 명: %s \n", ret.name);
	printf("취소하려면 4번누르세요\n 맞다면 다른 키를 누르세요\n");
	if (_getch() == '4')return CANCEL;
	else return NOERR;

}
//계좌 이체시 상대 이름 확인
int Disp_Bank_input(BANK* bank) {
	char key = 0;//입력받을 변수
	int flag = 0;//정상입력플레그
	printf("은행을 입력하시오.\n");
	char* banks[] = {"GABANK","KWBANK"};//은행종류
	for (int i = 0; i < 2; i++) {
		printf("[%d] %s \n", i + 1, banks[i]);//은행나열
	}
	
	do
	{
		key =_getch();
		switch (key)
		{
		case '1'://일번이면 
			*bank = '1';
			flag = 1;
			break;
		case '2'://2번이면
			*bank = '2';
			flag = 2;
			break;
		default://그외
			flag = 0;
			break;
		}
	} while (!flag);
	printf("%s을 선택하셨습니다.\n", banks[flag - 1]);//선택한 은행출력
	printf("확인은 아무키나, 취소는 4번을 누르시오\n");
	if (_getch() == '4')return CANCEL;//취소?
	else return NOERR;
}
void Disp_NO_account(void) {
	printf("없는 계좌입니다\n 메인화면으로 돌아갑니다.\n");
}
void Disp_Wrong_PW(void) {
	printf("잘못된 비밀번호 입니다.\n 메인화면으로 돌아갑니다.\n");
}
void Disp_insufficient_balance(void) {
	printf("잔액이 부족합니다.\n 메인화면으로 돌아갑니다.\n");
}
void Disp_cancel(void) {
	printf("취소하셨습니다.\n 매인화면으로 돌아갑니다\n");
	return;
}
void Disp_Wrong_input(void) {
	printf("1~4사이의 값을 입력하세요\n");
}