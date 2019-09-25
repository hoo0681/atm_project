#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<conio.h>
#include <Windows.h>
#include <string.h>
#include <io.h>
#include "Disp.h"/*���÷��� �Լ�����*/
#include "ATM_type.c"/*���� ���������� ����*/

#define NOERR 0 /*���� ����*/
#define NOACCOUNT 1 /*���� ����*/
#define PWERR 2/*��й�ȣ Ʋ��*/
#define BALANCE_ERR 3 /*�ܾ׺���*/
#define CANCEL 4 /*���*/

#define GABANK "01"
#define	KWBANK "02"
////���¹�ȣ�� ���� ���� �̸� 
////���� ���� : ���¹�ȣ.txt <���¹�ȣ��� �̸� �ܾ�>

ID USER;//����� ���� ��ȣ, ��й�ȣ �Է¿� ����
member MEMBER;//���� ���� ����

int ckID_num(unsigned short id_num, char* bank);//���� id�� 1�� ����
int CK_ID(ID id, member* ret);//���� 0, ���� ���� 1, ������� 2
int deposit(member* user, unsigned long long money);//������ 0 
int withdraw(member* user, unsigned long long money);//������ 0, �ܾ׺��� 3
int transfer(member* user, unsigned short dest_id_num, unsigned long long money);//������ 0, �ܾ� ���� 3
int writeData(member user);//������ 0
int userSet(ID* id, member* user);//������ 0

void no_err(void);//���� ����
void cancel(void);//��ҵ�
void non_account(void);//���°� �������� ����
void wrong_pw(void);//�߸��� ��й�ȣ
void insufficient_balance(void);//�ܾ� ����

void(*errFunc[5])(void) = { no_err ,non_account,wrong_pw,insufficient_balance, cancel };
//���� ó���Լ������� �迭

#if 1
int MK_ID(ID id, member* ret) {
	char path[20] = { 0 };
	if (ckID_num(id.id.id_num) == 0)return CANCEL; //���� ����

	_ultoa(id.id.id_num, path, 10);
	strcat(path, ".txt");
	ret->id.Serial_No = id.Serial_No;
	printf("�̸���? \n");
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
	for (;;) {
		Disp_main();
		switch (_getch())
		{
		case '1':/*�Ա�*/
			printf("\n�Ա�\n");
			errcode = userSet(&USER, &MEMBER);//����� �����Է�
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_money_input(&money))//�ݾ��Է�
			{
				errFunc[CANCEL]();
				break;
			}
			deposit(&MEMBER, money);//�Ա�
			writeData(MEMBER);//����

			errcode = CK_ID(USER, &MEMBER);//���� �ҷ�����
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//���� ���
			break;
		case '2':/*���*/
			printf("\n���\n");
			errcode = userSet(&USER, &MEMBER);//����� �����Է�
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_money_input(&money))//�ݾ� �Է�
			{
				errFunc[CANCEL]();
				break;
			}
			errcode = withdraw(&MEMBER, money);//���
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			writeData(MEMBER);//����

			errcode = CK_ID(USER, &MEMBER);//�����ҷ�����
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//�������
			break;
		case '3':/*���� ��ü*/
			printf("\n���� ��ü\n");
			errcode = userSet(&USER, &MEMBER);//����� �����Է�
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}

			if (Disp_ID_input(&tmp))//�޴� ��� ���� �Է�
			{
				errFunc[CANCEL]();
				break;
			}
			errcode = ckID_num(tmp.id.id_num);//�޴� ��� ��������Ȯ��
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_name_ck(tmp.id.id_num))//�޴� ����� �̸� Ȯ��
			{
				errFunc[CANCEL]();
				break;
			}
			Disp_LookUp(MEMBER);//����� �ܰ� ���
			errcode = Disp_money_input(&money);//��ü�ݾ� �Է� 
			if (errcode)
			{
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			if (Disp_Transfer_ck(MEMBER, tmp.id.id_num, money))//��ü���� Ȯ��
			{
				errFunc[CANCEL]();
				break;
			}
			errcode = transfer(&MEMBER, tmp.id.id_num, money);//��ü
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			writeData(MEMBER);//����

			errcode = CK_ID(USER, &MEMBER);//���� �ҷ�����
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//�������
			break;
		case '4':/*��ȸ*/
			printf("\n��ȸ\n");
			errcode = userSet(&USER, &MEMBER);//����� �����Է�
			if (errcode) {
				errFunc[errcode]();
				errcode = 0;
				break;
			}
			Disp_LookUp(MEMBER);//���� ���
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
int userSet(ID* id, member* user) {
	if (Disp_ID_input(id))//���� �Է�
	{
		return CANCEL;
	}
	if (Disp_PW_input(id))//��й�ȣ �Է�
	{
		return CANCEL;
	}
	return CK_ID(*id, user);//��й�ȣ Ȯ��

}
int ckID_num(unsigned short id_num, char* bank) {
	char fullpath[40] = { 0 };//���� ���
	char id[20] = { 0 };//����
	_ultoa(id_num, id, 10);//�����̸� �߰� 
	strcat(fullpath, (const char*)bank);
	strcat(fullpath, "/");
	strcat(fullpath, (const char*)id);
	strcat(fullpath, ".txt");
	int flag = _access(fullpath, 0);
	if (flag)return NOACCOUNT;//�������
	else return NOERR;//����
}
int CK_ID(ID id, member* ret) {
	char path[20] = { 0 };//���� ���
	ID curr;
	if (ckID_num(id.id.id_num, GABANK) == NOACCOUNT)return NOACCOUNT; //���� ���� ���� Ȯ��

	_ultoa(id.id.id_num, path, 10);//�����̸� �߰� 
	strcat(path, ".txt");//Ȯ���� �߰�
	FILE *fp;//������ ����
	fp = fopen((const char*)path, "r");//���� �б�
	fscanf(fp, "%lu", &curr.Serial_No);//�ø��� �ѹ� �޾ƿ���

	if (id.Serial_No ^ curr.Serial_No)return PWERR;// ��Ÿ�� �������� ���Ȯ��

	fseek(fp, 0, SEEK_SET);//�д� ��ġ ����
	fscanf(fp, "%lu %s %llu", &(ret->id.Serial_No), ret->name, &(ret->balance));//���� ���� ����
	fclose(fp);
	return NOERR;
}
int deposit(member* user, unsigned long long money) {//�Ա�
	user->balance += money;//�ܾ��� ����
	return NOERR;
}
int withdraw(member* user, unsigned long long money) {//���
	if (user->balance < money) {//��� ���� Ȯ��
		return BALANCE_ERR;
	}
	else
	{
		user->balance -= money;//�ܾ� ����
		return NOERR;
	}
}
int transfer(member* user, unsigned short dest_id_num, unsigned long long money) {//��ü

	if (withdraw(user, money) == BALANCE_ERR)return BALANCE_ERR; //�ܾ׺��� Ȯ��

	char path[20] = { 0 };//��� ���ڿ� �غ�
	member ret;//�޴� ��� ���� �غ�
	_ultoa(dest_id_num, path, 10);//�����̸� �߰� 
	strcat(path, ".txt");//Ȯ���� �߰�
	FILE *fp;//������ ����
	fp = fopen((const char*)path, "r+");//���� ����
	fscanf(fp, "%lu %s %llu", &(ret.id.Serial_No), ret.name, &(ret.balance));//�����б�
	ret.balance += money;//�Ա�
	fseek(fp, 0, SEEK_SET);//�д� ��ġ����
	fprintf(fp, "%lu %s %llu", (ret.id.Serial_No), ret.name, (ret.balance));//����
	fclose(fp);//���� �ݱ�

	return NOERR;

}
int writeData(member user) {
	char path[20] = { 0 };//��� ���ڿ� �غ�
	_ultoa(user.id.id.id_num, path, 10);//�����̸� �߰� 
	strcat(path, ".txt");//Ȯ���� �߰�
	FILE *fp;//������ ����
	fp = fopen((const char*)path, "r+");//���� ����
	fseek(fp, 0, SEEK_SET);//�д� ��ġ����
	fprintf(fp, "%lu %s %llu", (user.id.Serial_No), user.name, (user.balance));//����
	fclose(fp);//���� �ݱ�
	return NOERR;
}
void no_err(void) {//���� ����
	return;
}
void cancel(void) {//��� 
	Disp_cancel();//��� �޽��� ���
	USER.Serial_No = 0;//����� ���� �ʱ�ȭ
	memset((void*)&MEMBER, 0, sizeof(member));//����� ���� �ʱ�ȭ
	return;
}
void non_account(void) {//���� ����
	Disp_NO_account();//���� �޽��� ���
	//_getch();
	USER.Serial_No = 0;//����� ���� �ʱ�ȭ
	memset((void*)&MEMBER, 0, sizeof(member));//����� ���� �ʱ�ȭ
	return;
}
void wrong_pw(void) {//�߸��� ��й�ȣ
	Disp_Wrong_PW();//���� �޽��� ���
	//_getch();
	USER.Serial_No = 0;//����� ���� �ʱ�ȭ
	memset((void*)&MEMBER, 0, sizeof(member));//����� ���� �ʱ�ȭ
	return;
}
void insufficient_balance(void)//�ܾ׺���
{
	Disp_insufficient_balance();//���� �޽��� ���
	//_getch();
	USER.Serial_No = 0;//����� ���� �ʱ�ȭ
	memset(&MEMBER, 0, sizeof(member));//����� ���� �ʱ�ȭ
	return;
}