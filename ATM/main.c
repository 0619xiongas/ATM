#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atm.h"
void RegLoginView();
void OperationView();
void view_third();
void view_forth();
int Register(User* UserList);
int Login(User* UserList,User* user);

int main()
{
	// ϵͳ������� ����������Ҫ�õ�
	srand((unsigned)(time(NULL)));

	User* UserList = (User*)malloc(sizeof(User));
	LoadUserInfo(UserList);
	User* user = (User*)malloc(sizeof(User));
	RegLoginView();
	int loginStep = 0;
	int operateStep = 0;
	scanf("%d", &loginStep);
	while (loginStep)
	{
		switch (loginStep)
		{
		case 1:
			Register(UserList);
			loginStep++;
			break;
		case 2:
		{
			int ret = Login(UserList, user);
			if (ret == EM_NoRegister)
			{
				loginStep--;
			}
		}
		break;
		case 3:
			return 0;
		default:
			break;
		}
	}

	return 0;
}

void RegLoginView()
{
	printf("*****************************\n");
	printf("**��ӭʹ��ATM�Զ�ȡ���ϵͳ**\n");
	printf("*****************************\n");
	printf("������������������������������\n");
	printf("|         1 ����             |\n");
	printf("������������������������������\n");
	printf("|         2 ��½             |\n");
	printf("������������������������������\n");
	printf("|         3 �˳�             |\n");
	printf("������������������������������\n");
	printf("|      ��ѡ����������        |\n");
	printf("������������������������������\n");
}

void OperationView()
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
	int time = 3;
	int ret = 0;
	do
	{
		system("CLS");
		char account[17];
		char password[7];
		printf("�����������˺�\n");
		scanf("%s", account);
		printf("�������������루������6λ),������%d�λ���\n",time);

		InputPassword(password);
		ret = UserLogin(UserList, user, account, password);
		--time;
	} while (time > 0 && ret == EM_Password);

	return ret;
}

