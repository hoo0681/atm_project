#pragma once
struct ID_
{
	unsigned short id_num;
	unsigned short PW;
};

typedef union ID_ST
{
	struct ID_ id;
	unsigned long Serial_No;
}ID;
typedef struct Member
{
	union ID_ST id;
	char name[100];
	unsigned long long balance;
}member;