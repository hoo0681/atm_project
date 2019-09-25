#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<conio.h>
#include <Windows.h>
#include <string.h>
#include <io.h>
//#include "ATM_type.c"
#include "Disp.h"
////���¹�ȣ�� ���� ���� �̸� 
////���� ���� : ���¹�ȣ.txt <���¹�ȣ��� �̸� �ܾ�>
ID USER;
member MEMBER;
int ckID_num(unsigned short id_num);//���� id�� 1�� ����
int CK_ID(ID id, member* ret);//���� 0, ���� ���� 1, ������� 2
int deposit(member* user, unsigned long long money);//������ 0 
int withdraw(member* user, unsigned long long money);//������ 0, �ܾ׺��� 3
int transfer(member* user, unsigned short dest_id_num, unsigned long long money);//������ 0, �ܾ� ���� 3
int writeData(member user);//������ 0

void no_err(void);
void cancel(void);
void non_account(void);
void wrong_pw(void);
void insufficient_balance(void);

void(*errFunc[5])(void) = {no_err ,non_account,wrong_pw,insufficient_balance, cancel};

#if 1
int MK_ID(ID id, member* ret) {
	char path[20] = { 0 };
	//int flag;

	if (ckID_num(id.id.id_num) == 0)return 4; //���� ����

	_ultoa(id.id.id_num, path, 10);
	strcat(path, ".txt");
	ret->id.Serial_No = id.Serial_No;
	printf("�̸���? \n");
	scanf("%s", ret->name);
	ret->balance = (unsigned long long )0;
	FILE *fp;
	fp = fopen((const char*)path, "w");
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%lu %s %llu", (ret->id.Serial_No), ret->name, (ret->balance));
	fclose(fp);
	return 0;
}
#endif
void main(void) {
	ID tmp;
	int errcode = 0;
	unsigned short id_num=0;
	unsigned long long money=0;
	for (;;) {
		Disp_main();
		switch (_getch())
		{
		case '1':/*�Ա�*/
			if (Disp_ID_input(&USER))
			{
				errFunc[4]();
				break;
			}
			if (Disp_PW_input(&USER))
			{
				errFunc[4]();
				break;
			}
			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_money_input(&money))
			{
				errFunc[4]();
				break;
			}
			deposit(&MEMBER, money);
			writeData(MEMBER);

			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);
			break;
		case '2':/*���*/
			if (Disp_ID_input(&USER))
			{
				errFunc[4]();
				break;
			}
			if (Disp_PW_input(&USER))
			{
				errFunc[4]();
				break;
			}
			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_money_input(&money))
			{
				errFunc[4]();
				break;
			}
			errcode = withdraw(&MEMBER, money);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			writeData(MEMBER);

			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);
			break;
		case '3':/*���� ��ü*/
			if (Disp_ID_input(&USER))
			{
				errFunc[4]();
				break;
			}
			if (Disp_PW_input(&USER))
			{
				errFunc[4]();
				break;
			}
			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);
			if (Disp_ID_input(&tmp))
			{
				errFunc[4]();
				break;
			}
			errcode = ckID_num(tmp.id.id_num);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_name_ck(tmp.id.id_num))
			{
				errFunc[4]();
				break;
			}
			if (Disp_money_input(&money))
			{
				errFunc[4]();
				break;
			}
			errcode = Disp_Transfer_ck(MEMBER, tmp.id.id_num, money);
			if (errcode)
			{
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			errcode = transfer(&MEMBER, tmp.id.id_num, money);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			writeData(MEMBER);
			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);
			break;
		case '4':/*��ȸ*/
			if (Disp_ID_input(&USER))
			{
				errFunc[4]();
				break;
			}
			if (Disp_PW_input(&USER))
			{
				errFunc[4]();
				break;
			}
			errcode = CK_ID(USER, &MEMBER);
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);
			break;
#if 1
		case '5':
			if (Disp_ID_input(&USER))
			{
				errFunc[4]();
				break;
			}
			if (Disp_PW_input(&USER))
			{
				errFunc[4]();
				break;
			}
			MK_ID(USER, &MEMBER);
			break;
#endif
		default:
			Disp_Wrong_input();
			break;
		}
		

	}
	return;
}
int ckID_num(unsigned short id_num) {
	char fullpath[40] = { 0 };
	char id[20] = { 0 };
	_ultoa(id_num,id,10 );
	strcat(fullpath, "");
	strcat(fullpath, (const char*)id);
	strcat(fullpath, ".txt");
	int flag=_access(fullpath, 0);
	if (flag)return 1;//�������
	else return 0;//����
}
int CK_ID(ID id, member* ret) {
	char path[20] = { 0 };
	//int flag;
	ID curr;
	if ( ckID_num(id.id.id_num)== 1)return 1; //���� �������
	
	_ultoa(id.id.id_num, path, 10);
	strcat(path, ".txt");
	FILE *fp;
	fp = fopen((const char*)path, "r");
	fscanf(fp, "%lu",&curr.Serial_No);

	if (id.Serial_No != curr.Serial_No)return 2;// ���Ȯ�� �Ϸ�

	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%lu %s %llu", &(ret->id.Serial_No), ret->name, &(ret->balance));
	fclose(fp);
	return 0;
}
int deposit(member* user, unsigned long long money) {
	user->balance += money;
	return 0;
}
int withdraw(member* user, unsigned long long money) {
	if (user->balance  < money) {
		return 3;
	}
	else
	{
		user->balance -= money;
		return 0;
	}
}
int transfer(member* user, unsigned short dest_id_num, unsigned long long money) {
	//if (ckID_num(dest_id_num) == 1)return 1;// ��밡 ����
	if (withdraw(user, money) == 3)return 3; //�ܾ׺���

	char path[20] = { 0 };
	member ret;
	_ultoa(dest_id_num, path, 10);
	strcat(path, ".txt");
	FILE *fp;
	fp = fopen((const char*)path, "r+");
	fscanf(fp, "%lu %s %llu", &(ret.id.Serial_No), ret.name, &(ret.balance));
	ret.balance += money;
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%lu %s %llu", (ret.id.Serial_No), ret.name, (ret.balance));
	fclose(fp);

	return 0;
	
}
int writeData(member user) {
	char path[20] = { 0 };
	_ultoa(user.id.id.id_num, path, 10);
	strcat(path, ".txt");
	FILE *fp;
	fp = fopen((const char*)path, "r+");
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%lu %s %llu", (user.id.Serial_No), user.name, (user.balance));
	fclose(fp);
	return 0;
}
void no_err(void) {
	return;
}
void cancel(void) {
	Disp_cancel();
	_getch();
	USER.Serial_No = 0;
	memset((void*)&MEMBER, 0, sizeof(member));
	return;
}
void non_account(void) {
	Disp_NO_account();
	_getch();
	USER.Serial_No = 0;
	memset((void*)&MEMBER, 0, sizeof(member));
	return;
}
void wrong_pw(void) {
	Disp_Wrong_PW();
	_getch();
	USER.Serial_No = 0;
	memset((void*)&MEMBER, 0, sizeof(member));
	return;
}
void insufficient_balance(void)
{
	Disp_insufficient_balance();
	_getch();
	USER.Serial_No = 0;
	memset((void*)&MEMBER, 0, sizeof(member));
	return;
}