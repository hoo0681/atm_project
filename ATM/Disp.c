#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include<conio.h>
#include "ATM_type.c"
void Disp_main(void) {
	printf("1:�Ա�,2:���,3:������ü,4:��ȸ\n");
  }
int Disp_ID_input(ID* id_num) {
	printf("\n���¹�ȣ�� �Է��Ͻÿ�.\n");

	scanf("%hu", &(id_num->id.id_num));
	while (getchar() != '\n');
	printf("Ȯ���� �ƹ�Ű��, ��Ҵ� 4���� �����ÿ�\n");
	if (_getch() == '4')return 4;
	else return 0;
	//id_num�� id_num�� �Է¹��� ���� �Է� PW�� ����
}
int Disp_PW_input(ID* pw) {
	char password[6];
	char key;
	printf("�ٽþ��� r, ����ȭ������ c\n");
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
	//pw�� pw�� �Է¹��� ���� ����
}

int Disp_money_input(unsigned long long* money) {
	printf("\n �ݾ��Է� \n");
	printf("                                     \\");
	for (int i = 0; i < 35; i++) {
		printf("\b");
	}
	
	scanf("%llu", money);
	while (getchar() != '\n');
	return 0;
}//�Է¹��� ���� ���� ����
void Disp_LookUp(member user) {
	fprintf(stdout, "\n�̸� %s �ܾ�%llu \n", user.name, (user.balance));
	_getch();
  }
int Disp_Transfer_ck(member user, unsigned short id_num, unsigned long long money) {
	printf("�̸� %s �ܾ�%llu �Դϴ�.\n", user.name, (user.balance));
	printf("���� ��ȣ: %hu �� %llu ���� �����ðڽ��ϱ�?\n", id_num,money);
	if (user.balance < money)return 3;
	printf("�����ܾ��� %llu�Դϴ�\n", user.balance - money);
	printf("��Ҵ� 4���� �������� �ٸ� Ű�� �����ø� �������� ����˴ϴ�.\n");
	if(_getch()=='4')return 4;
	else return 0;
}
//���� ��ü Ȯ��
void Disp_cancel(void) {
	printf("����ϼ̽��ϴ�.\n ����ȭ������ ���ư��ϴ�\n");
	return;
  }
void Disp_Wrong_input(void) {
	printf("1~4������ ���� �Է��ϼ���\n");
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
	printf("\n������ ��: %s \n", ret.name);
	printf("����Ϸ��� 4����������\n �´ٸ� �ٸ� Ű�� ��������\n");
	if (_getch() == '4')return 4;
	else return 0;

}
//���� ��ü�� ��� �̸� Ȯ��
void Disp_NO_account(void) {
	printf("���� �����Դϴ�\n ����ȭ������ ���ư��ϴ�.\n");
	return ;
  }
void Disp_Wrong_PW(void) {
	printf("�߸��� ��й�ȣ �Դϴ�.\n ����ȭ������ ���ư��ϴ�.\n");
	return ;
  }
void Disp_insufficient_balance(void) {
	printf("�ܾ��� �����մϴ�.\n ����ȭ������ ���ư��ϴ�.\n");
	return ;
  }