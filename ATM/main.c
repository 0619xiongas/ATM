#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atm.h"
void view_first();
void view_second();
void view_third();
void view_forth();
int Register(User* UserList);
int Login(User* UserList,User* user);

int main()
{
	// ϵͳ������� ����������Ҫ�õ�
	srand((unsigned)(time(NULL)));

	//User* UserList = (User*)malloc(sizeof(User));
	//LoadUserInfo(UserList);
	//PrintUserInfo(UserList);
	//Register(UserList);
	//User* user = (User*)malloc(sizeof(User));

	//Login(UserList, user);
	char pwd[10] = { 0 };
	InputPassword(pwd);
	return 0;
}
void view_first()
{
	printf("*****************************\n");
	printf("**��ӭʹ��ATM�Զ�ȡ���ϵͳ**\n");
	printf("*****************************\n");
	printf("������������������������������\n");
	printf("|         1 ����             |\n");
	printf("������������������������������\n");
	printf("|         2 ��½             |\n");
	printf("������������������������������\n");
	printf("|      ��ѡ����������        |\n");
	printf("������������������������������\n");
}

void view_second()
{
	printf("��ѡ������Ҫ��ҵ��\n");
	printf("**********************************\n");
	printf("**  1 ȡ��  **********  2 ��ѯ  **\n");
	printf("**********************************\n");
	printf("**  3 ת��  ******  4 �޸���Ϣ  **\n");
	printf("**********************************\n");
	printf("**  5 ���  **********  6 �˳�  **\n");
	printf("**********************************\n");
}

void view_third()
{
	printf("**********************************\n");
	printf("***********1 ������ **************\n");
	printf("**********************************\n");
	printf("***********2 ������ **************\n");
	printf("**********************************\n");
	printf("***********3 �ĵ绰 **************\n");
	printf("**********************************\n");
}

void view_forth()
{
	printf("**********************************\n");
	printf("********* 1 ���������� ***********\n");
	printf("**********************************\n");
	printf("********* 2 ���������� ***********\n");
	printf("**********************************\n");
}

int Register(User* UserList)
{
	system("CLS");
	char username[20];
	char identity[17];
	char phone[13];

	printf("�������������֣�������6����);\n");
	scanf("%s", username);
	printf("�������������֤��������18λ);\n");
	scanf("%s", identity);
	printf("���������ĵ绰���루������11λ);\n");
	scanf("%s", phone);

	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->identity, identity) == 0)
		{
			printf("���Ѿ�ע����ˣ����¼");
			return (int)EM_HaveRegistered;
		}
		cur = cur->next;
	}
	User* user = (User*)malloc(sizeof(User));
	// �������17λ����account�˺�
	int i = 0;
	char account[17];
	for (; i < 16; ++i)
	{
		account[i] = rand() % 10 + '0';
	}
	account[i] = '\0';
	strcpy(user->name, username);
	strcpy(user->identity, identity);
	strcpy(user->phone, phone);
	strcpy(user->account, account);
	strcpy(user->password, "111111"); // ��ʼ�����붼��111111
	user->balance = 0.00;
	if (0 == UserRegister(UserList, user))
	{
		printf("���Ѿ��ɹ�ע���˺ţ�\n");
		printf("�����˺�Ϊ��%s,��ʼ����Ϊ��%s,���Ϊ��%lf\n", user->account, user->password, user->balance);
	}
	return (int)EM_NULL;
}

int Login(User* UserList, User* user)
{
	system("CLS");
	char account[17];
	char password[7];
	printf("�����������˺�\n");
	scanf("%s", account);
	printf("�������������루������6λ)\n");
	InputPassword(password);

	User* cur = UserList;
	return 0;
}

