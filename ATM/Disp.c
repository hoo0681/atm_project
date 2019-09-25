#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include<conio.h>
#include "ATM_type.c"
void Disp_main(void) {
	printf("1:입금,2:출금,3:계좌이체,4:조회\n");
  }
int Disp_ID_input(ID* id_num) {
	printf("\n계좌번호를 입력하시오.\n");

	scanf("%hu", &(id_num->id.id_num));
	while (getchar() != '\n');
	printf("확인은 아무키나, 취소는 4번을 누르시오\n");
	if (_getch() == '4')return 4;
	else return 0;
	//id_num의 id_num에 입력받은 값을 입력 PW는 없음
}
int Disp_PW_input(ID* pw) {
	char password[6];
	char key;
	printf("다시쓰기 r, 메인화면으로 c\n");
	printf("PW:");
	for (int i = 0; i < 5; i++) {
		key = _getch();
		
		if (key == '\b') {
			i-=2;
			printf("\b \b");
		}
		else if (key == 'r') {
			for (i; i > 0; i--) {
				printf("\b \b");
			}
			i = -1;
			//while (getchar() != EOF);
		}
		else if (key == 'c') {
			return 4;
		}
		else if (key >= '0'&&key <= '9'){
			password[i] = key;
			printf("*");
		}
		else {
			i--;
		}
	}
	password[5] = '\0';
	pw->id.PW = (unsigned short)strtol(password, NULL, 10);
	return 0;
	//pw의 pw에 입력받은 값을 대입
}

int Disp_money_input(unsigned long long* money) {
	printf("\n 금액입력 \n");
	printf("                                     \\");
	for (int i = 0; i < 35; i++) {
		printf("\b");
	}
	
	scanf("%llu", money);
	while (getchar() != '\n');
	return 0;
}//입력받은 돈의 값을 대입
void Disp_LookUp(member user) {
	fprintf(stdout, "\n이름 %s 잔액%llu \n", user.name, (user.balance));
	_getch();
  }
int Disp_Transfer_ck(member user, unsigned short id_num, unsigned long long money) {
	printf("이름 %s 잔액%llu 입니다.\n", user.name, (user.balance));
	printf("계좌 번호: %hu 에 %llu 원을 보내시겠습니까?\n", id_num,money);
	if (user.balance < money)return 3;
	printf("예상잔액은 %llu입니다\n", user.balance - money);
	printf("취소는 4번을 누르세요 다른 키를 누르시면 다음으로 진행됩니다.\n");
	if(_getch()=='4')return 4;
	else return 0;
}
//계좌 이체 확인
void Disp_cancel(void) {
	printf("취소하셨습니다.\n 매인화면으로 돌아갑니다\n");
	return;
  }
void Disp_Wrong_input(void) {
	printf("1~4사이의 값을 입력하세요\n");
  }
int Disp_name_ck(unsigned short id_num) {
	char path[20] = { 0 };
	member ret;
	_ultoa(id_num, path, 10);
	strcat(path, ".txt");
	FILE *fp;
	fp = fopen((const char*)path, "r+");
	fscanf(fp, "%lu %s %llu", &(ret.id.Serial_No), ret.name, &(ret.balance));
	fclose(fp);
	printf("\n예금주 명: %s \n", ret.name);
	printf("취소하려면 4번누르세요\n 맞다면 다른 키를 누르세요\n");
	if (_getch() == '4')return 4;
	else return 0;

}
//계좌 이체시 상대 이름 확인
void Disp_NO_account(void) {
	printf("없는 계좌입니다\n 메인화면으로 돌아갑니다.\n");
	return ;
  }
void Disp_Wrong_PW(void) {
	printf("잘못된 비밀번호 입니다.\n 메인화면으로 돌아갑니다.\n");
	return ;
  }
void Disp_insufficient_balance(void) {
	printf("잔액이 부족합니다.\n 메인화면으로 돌아갑니다.\n");
	return ;
  }