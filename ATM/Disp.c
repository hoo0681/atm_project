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
void Disp_main(void) {//���� ȭ��
	printf("1:�Ա�,2:���,3:������ü,4:��ȸ\n");
}
int Disp_ID_input(ID* id_num) {//���¹�ȣ �Է�
	printf("���¹�ȣ�� �Է��Ͻÿ�.\n");

	scanf("%hu", &(id_num->id.id_num));//�Է¹ޱ�
	while (getchar() != '\n');//�Է¹��� ����
	printf("Ȯ���� �ƹ�Ű��, ��Ҵ� 4���� �����ÿ�\n");
	if (_getch() == '4')return CANCEL;//���?
	else return NOERR;
	//id_num�� id_num�� �Է¹��� ���� �Է� PW�� ����
}
int Disp_PW_input(ID* pw) {//��й�ȣ �Է¹ޱ�
	char password[6];//��й�ȣ ����
	char key;//�Է¹��� Ű
	printf("�ٽþ��� r, ����ȭ������ c\n");
	printf("PW:");
	for (int i = 0; i < 5; i++) {//��й�ȣ�� 5�ڸ�
		key = _getch();

		if (key == '\b'&&i > 0) {//�����
			i = i > 0 ? i - 2 : 0;
			printf("\b \b");
		}
		else if (key == 'r') {//ó������ �ٽ� ����
			for (i; i > 0; i--) {
				printf("\b \b");
			}
			i = -1;
		}
		else if (key == 'c') {//����ȭ������
			return CANCEL;
		}
		else if (key >= '0'&&key <= '9') {//�Է¹��� ���� ����?
			password[i] = key;
			printf("*");//ȭ�鿡�� *�� ǥ��
		}
		else {
			i--;//�߸��� ���� ����
		}
	}
	printf("\n");
	password[5] = '\0';//�������� �ι��� �ֱ�
	pw->id.PW = (unsigned short)strtol(password, NULL, 10);//���ڿ��� ��ȯ
	return NOERR;
	//pw�� pw�� �Է¹��� ���� ����
}

int Disp_money_input(unsigned long long* money) {
	printf("\n �ݾ��Է� \n");
	printf("                                     \\");
	printf("\r");

	scanf("%llu", money);
	while (getchar() != '\n');
	return NOERR;
}//�Է¹��� ���� ���� ����
void Disp_LookUp(member user) {
	fprintf(stdout, "\n�̸� %s �ܾ�%llu \n", user.name, (user.balance));
	_getch();
}
int Disp_Transfer_ck(member user, unsigned short id_num, unsigned long long money) {
	if (user.balance < money)return BALANCE_ERR;
	printf("�̸� %s �ܾ�%llu �Դϴ�.\n", user.name, (user.balance));
	printf("���� ��ȣ: %hu �� %llu ���� �����ðڽ��ϱ�?\n", id_num, money);
	printf("�����ܾ��� %llu�Դϴ�\n", user.balance - money);
	printf("��Ҵ� 4���� �������� �ٸ� Ű�� �����ø� �������� ����˴ϴ�.\n");
	if (_getch() == '4')return CANCEL;
	else return NOERR;
}
//���� ��ü Ȯ��

int Disp_name_ck(unsigned short id_num,BANK bank) {
	char path[20] = { 0 };
	member ret;
	char id[20] = { 0 };//����
	_ultoa(id_num, id, 10);//�����̸� �߰� 
	strcat(path, (const char*)&bank);
	strcat(path, "/");
	strcat(path, (const char*)id);
	strcat(path, ".txt");
	FILE *fp;
	fp = fopen((const char*)path, "r+");
	fscanf(fp, "%lu %s %llu", &(ret.id.Serial_No), ret.name, &(ret.balance));
	fclose(fp);
	printf("\n������ ��: %s \n", ret.name);
	printf("����Ϸ��� 4����������\n �´ٸ� �ٸ� Ű�� ��������\n");
	if (_getch() == '4')return CANCEL;
	else return NOERR;

}
//���� ��ü�� ��� �̸� Ȯ��
int Disp_Bank_input(BANK* bank) {
	char key = 0;//�Է¹��� ����
	int flag = 0;//�����Է��÷���
	printf("������ �Է��Ͻÿ�.\n");
	char* banks[] = {"GABANK","KWBANK"};//��������
	for (int i = 0; i < 2; i++) {
		printf("[%d] %s \n", i + 1, banks[i]);//���೪��
	}
	
	do
	{
		key =_getch();
		switch (key)
		{
		case '1'://�Ϲ��̸� 
			*bank = '1';
			flag = 1;
			break;
		case '2'://2���̸�
			*bank = '2';
			flag = 2;
			break;
		default://�׿�
			flag = 0;
			break;
		}
	} while (!flag);
	printf("%s�� �����ϼ̽��ϴ�.\n", banks[flag - 1]);//������ �������
	printf("Ȯ���� �ƹ�Ű��, ��Ҵ� 4���� �����ÿ�\n");
	if (_getch() == '4')return CANCEL;//���?
	else return NOERR;
}
void Disp_NO_account(void) {
	printf("���� �����Դϴ�\n ����ȭ������ ���ư��ϴ�.\n");
}
void Disp_Wrong_PW(void) {
	printf("�߸��� ��й�ȣ �Դϴ�.\n ����ȭ������ ���ư��ϴ�.\n");
}
void Disp_insufficient_balance(void) {
	printf("�ܾ��� �����մϴ�.\n ����ȭ������ ���ư��ϴ�.\n");
}
void Disp_cancel(void) {
	printf("����ϼ̽��ϴ�.\n ����ȭ������ ���ư��ϴ�\n");
	return;
}
void Disp_Wrong_input(void) {
	printf("1~4������ ���� �Է��ϼ���\n");
}