#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<conio.h>
#include <Windows.h>
#include <string.h>
#include <io.h>
#include "Disp.h"/*디스플레이 함수정의*/
#include "ATM_type.c"/*사용될 데이터형식 정의*/

#define NOERR 0 /*에러 없음*/
#define NOACCOUNT 1 /*계좌 없음*/
#define PWERR 2/*비밀번호 틀림*/
#define BALANCE_ERR 3 /*잔액부족*/
#define CANCEL 4 /*취소*/

#define GABANK "01"
#define	KWBANK "02"
////계좌번호가 계좌 파일 이름 
////파일 구성 : 계좌번호.txt <계좌번호비번 이름 잔액>
typedef BANK char;
ID USER;//사용자 계좌 번호, 비밀번호 입력용 변수
member MEMBER;//계좌 정보 변수

int ckID_num(unsigned short id_num, BANK* bank);//없은 id면 1을 리턴
int CK_ID(ID id, member* ret, BANK bank);//성공 0, 계좌 없음 1, 비번오류 2
int deposit(member* user, unsigned long long money);//성공시 0 
int withdraw(member* user, unsigned long long money);//성공시 0, 잔액부족 3
int transfer(member* user, unsigned short dest_id_num, unsigned long long money);//성공시 0, 잔액 부족 3
int writeData(member user);//성공시 0
int userSet(ID* id, member* user, BANK* bank);//성공시 0
int bankck(BANK* bank);

void no_err(void);//에러 없음
void cancel(void);//취소됨
void non_account(void);//계좌가 존재하지 않음
void wrong_pw(void);//잘못된 비밀번호
void insufficient_balance(void);//잔액 부족

void(*errFunc[5])(void) = { no_err ,non_account,wrong_pw,insufficient_balance, cancel };
//에러 처리함수포인터 배열

#if 1
int MK_ID(ID id, member* ret, BANK bank) {
	char path[20] = { 0 };
	if (ckID_num(id.id.id_num) == 0)return CANCEL; //계좌 존재

	_ultoa(id.id.id_num, path, 10);
	strcat(path, ".txt");
	ret->id.Serial_No = id.Serial_No;
	printf("이름은? \n");
	scanf("%s", ret->name);
	ret->balance = (unsigned long long)0;
	FILE *fp;
	fp = fopen((const char*)path, "w");
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%lu %s %llu", (ret->id.Serial_No), ret->name, (ret->balance));
	fclose(fp);
	return NOERR;
}
#endif

void main(void) {
	ID tmp;
	int errcode = 0;
	unsigned short id_num = 0;
	unsigned long long money = 0;
        BANK tmpbank;
	for (;;) {
		Disp_main();
		switch (_getch())
		{
		case '1':/*입금*/
			printf("\n입금\n");
			errcode = userSet(&USER, &MEMBER,&bank);//사용자 정보입력
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_money_input(&money))//금액입력
			{
				errFunc[CANCEL]();
				break;
			}
			deposit(&MEMBER, money);//입금
			writeData(MEMBER);//저장

			errcode = CK_ID(USER, &MEMBER,&bank);//정보 불러오기
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//정보 출력
			break;
		case '2':/*출금*/
			printf("\n출금\n");
			errcode = userSet(&USER, &MEMBER, &bank);//사용자 정보입력
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_money_input(&money))//금액 입력
			{
				errFunc[CANCEL]();
				break;
			}
			errcode = withdraw(&MEMBER, money);//출금
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			writeData(MEMBER);//저장

			errcode = CK_ID(USER, &MEMBER,bank);//정보불러오기
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//정보출력
			break;
		case '3':/*계좌 이체*/
			printf("\n계좌 이체\n");
			errcode = userSet(&USER, &MEMBER, &bank);//사용자 정보입력
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
                        if (Disp_Bank_input(&tmpbank))//받는 사람 은행 입력
			{
				errFunc[CANCEL]();
				break;
			}
			if (Disp_ID_input(&tmp))//받는 사람 계좌 입력
			{
				errFunc[CANCEL]();
				break;
			}
			errcode = ckID_num(tmp.id.id_num, tmpbank);//받는 사람 계좌존재확인
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_name_ck(tmp.id.id_num))//받는 사람의 이름 확인
			{
				errFunc[CANCEL]();
				break;
			}
			Disp_LookUp(MEMBER);//사용자 잔고 출력
			errcode = Disp_money_input(&money);//이체금액 입력 
			if (errcode)
			{
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_Transfer_ck(MEMBER, tmp.id.id_num, money))//이체여부 확인
			{
				errFunc[CANCEL]();
				break;
			}
			errcode = transfer(&MEMBER, tmp.id.id_num, money,tmpbank);//이체
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			writeData(MEMBER);//저장

			errcode = CK_ID(USER, &MEMBER);//정보 불러오기
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//정보출력
			break;
		case '4':/*조회*/
			printf("\n조회\n");
			errcode = userSet(&USER, &MEMBER,&bank);//사용자 정보입력
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//정보 출력
			break;
#if 1
		case '5':
			if (Disp_ID_input(&USER))
			{
				errFunc[CANCEL]();
				break;
			}
			if (Disp_PW_input(&USER))
			{
				errFunc[CANCEL]();
				break;
			}
			MK_ID(USER, &MEMBER,bank);
			break;
#endif
		default:
			Disp_Wrong_input();
			break;
		}


	}
	return;
}
int userSet(ID* id, member* user,BANK* bank) {
	if (Disp_ID_input(id))//계좌 입력
	{
		return CANCEL;
	}
	if (Disp_PW_input(id))//비밀번호 입력
	{
		return CANCEL;
	}
        if (Disp_Bank_input(bank))//계좌 입력
	{
		return CANCEL;
	}
	return CK_ID(*id, user,*bank);//비밀번호 확인

}
int ckID_num(unsigned short id_num, BANK bank) {
	char fullpath[40] = { 0 };//계좌 경로
	char id[20] = { 0 };//계좌
	_ultoa(id_num, id, 10);//파일이름 추가 
	strcat(fullpath, (const char)bank);
	strcat(fullpath, "/");
	strcat(fullpath, (const char*)id);
	strcat(fullpath, ".txt");
	int flag = _access(fullpath, 0);
	if (flag)return NOACCOUNT;//존재안함
	else return NOERR;//존재
}
int CK_ID(ID id, member* ret,BANK bank) {
	char path[20] = { 0 };//계좌 경로
	ID curr;
	if (ckID_num(id.id.id_num, bank) == NOACCOUNT)return NOACCOUNT; //계좌 존재 여부 확인
        strcat(path, (const char)bank);
	strcat(path, "/");
	_ultoa(id.id.id_num, path, 10);//파일이름 추가 
	strcat(path, ".txt");//확장자 추가
	FILE *fp;//포인터 선언
	fp = fopen((const char*)path, "r");//파일 읽기
	fscanf(fp, "%lu", &curr.Serial_No);//시리얼 넘버 받아오기

	if (id.Serial_No ^ curr.Serial_No)return PWERR;// 베타적 논리합으로 비번확인

	fseek(fp, 0, SEEK_SET);//읽는 위치 수정
	fscanf(fp, "%lu %s %llu", &(ret->id.Serial_No), ret->name, &(ret->balance));//계좌 정보 복사
	fclose(fp);
	return NOERR;
}
int deposit(member* user, unsigned long long money) {//입금
	user->balance += money;//잔액을 수정
	return NOERR;
}
int withdraw(member* user, unsigned long long money) {//출금
	if (user->balance < money) {//출금 가능 확인
		return BALANCE_ERR;
	}
	else
	{
		user->balance -= money;//잔액 수정
		return NOERR;
	}
}
int transfer(member* user, unsigned short dest_id_num, unsigned long long money,BANK bank) {//이체

	if (withdraw(user, money) == BALANCE_ERR)return BALANCE_ERR; //잔액부족 확인

	char path[20] = { 0 };//경로 문자열 준비
	member ret;//받는 사람 변수 준비
        strcat(path, (const char)bank);
	strcat(path, "/");
	_ultoa(dest_id_num, path, 10);//파일이름 추가 
	strcat(path, ".txt");//확장자 추가
	FILE *fp;//포인터 선언
	fp = fopen((const char*)path, "r+");//파일 열기
	fscanf(fp, "%lu %s %llu", &(ret.id.Serial_No), ret.name, &(ret.balance));//정보읽기
	ret.balance += money;//입금
	fseek(fp, 0, SEEK_SET);//읽는 위치변경
	fprintf(fp, "%lu %s %llu", (ret.id.Serial_No), ret.name, (ret.balance));//저장
	fclose(fp);//파일 닫기

	return NOERR;

}
int writeData(member user) {
	char path[20] = { 0 };//경로 문자열 준비
        strcat(path, (const char)user.bank);
	strcat(path, "/");
	_ultoa(user.id.id.id_num, path, 10);//파일이름 추가 
	strcat(path, ".txt");//확장자 추가
	FILE *fp;//포인터 선언
	fp = fopen((const char*)path, "r+");//파일 열기
	fseek(fp, 0, SEEK_SET);//읽는 위치변경
	fprintf(fp, "%lu %s %llu", (user.id.Serial_No), user.name, (user.balance));//저장
	fclose(fp);//파일 닫기
	return NOERR;
}
void no_err(void) {//에러 없음
	return;
}
void cancel(void) {//취소 
	Disp_cancel();//취소 메시지 출력
	USER.Serial_No = 0;//사용자 정보 초기화
	memset((void*)&MEMBER, 0, sizeof(member));//사용자 정보 초기화
	return;
}
void non_account(void) {//계좌 없음
	Disp_NO_account();//에러 메시지 출력
	//_getch();
	USER.Serial_No = 0;//사용자 정보 초기화
	memset((void*)&MEMBER, 0, sizeof(member));//사용자 정보 초기화
	return;
}
void wrong_pw(void) {//잘못된 비밀번호
	Disp_Wrong_PW();//에러 메시지 출력
	//_getch();
	USER.Serial_No = 0;//사용자 정보 초기화
	memset((void*)&MEMBER, 0, sizeof(member));//사용자 정보 초기화
	return;
}
void insufficient_balance(void)//잔액부족
{
	Disp_insufficient_balance();//에러 메시지 출력
	//_getch();
	USER.Serial_No = 0;//사용자 정보 초기화
	memset(&MEMBER, 0, sizeof(member));//사용자 정보 초기화
	return;
}
