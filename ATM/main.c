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
int CheckLoginRegister(User* UserList, User* user);
void Deposit(User* UserList, Deal* DealList, User* user);
void Withdraw(User* UserList, Deal* DealList, User* user);
void TransferIn();
void TransferOut();
int main()
{
	// ϵͳ������� ����������Ҫ�õ�
	srand((unsigned)(time(NULL)));

	// �ļ����ؽ��ڴ�
	User* UserList = (User*)malloc(sizeof(User));
	LoadUserInfo(UserList);
	Deal* DealList = (Deal*)malloc(sizeof(Deal));
	LoadDealInfo(DealList);


	User* user = (User*)malloc(sizeof(User));
	int isLogin = 0; // �ж��Ƿ��¼�ɹ�
	int isExit = 0; // �ж��Ƿ��˳�ϵͳ
	 // ע���¼����
	isLogin = CheckLoginRegister(UserList, user);
	// ��������
	while (isLogin && !isExit)
	{
		OperationView();
		int step = 0;
		scanf("%d", &step);
		system("CLS");
		switch (step)
		{
		case 1:// ��Ǯ
			Deposit(UserList, DealList, user);
			break;
		case 2:
			Withdraw(UserList, DealList, user);
			break;
		case 6:
			isExit = 1;
			isLogin = 0;
			break;
		default:
			break;
		}
	}

	if (!isLogin || isExit)
	{
		SaveFile(UserList, DealList);
		free(user);
		free(UserList);
		free(DealList);
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
	printf("**  1 ���  **********  2 ȡ��  **\n");
	printf("**********************************\n");
	printf("**  3 ת��  ******  4 �޸���Ϣ  **\n");
	printf("**********************************\n");
	printf("**  5 ��ѯ  **********  6 �˳�  **\n");
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
	char *username = (char*)malloc(sizeof(20));
	char *identity = (char*)malloc(sizeof(20));
	char *phone = (char*)malloc(sizeof(7));
	do 
	{
		printf("�������������֣�������6����);\n");
		scanf("%s", username);
		if (strlen(username) > 6)
		{
			printf("\n���ִ���6����!!!\n");
		}
	} while (strlen(username) > 6);

	do 
	{
		printf("�������������֤��������18λ);\n");
		scanf("%s", identity);
		if (strlen(identity) > 18)
		{
			printf("\n���֤����18λ\n");
		}
	} while (strlen(identity) > 18);
	do 
	{
		printf("���������ĵ绰���루������11λ);\n");
		scanf("%s", phone);
		if (strlen(phone) > 11)
		{
			printf("\n�绰���볬��11λ\n");
		}
	} while (strlen(phone) > 11);

	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->identity, identity) == 0)
		{
			printf("���Ѿ�ע����ˣ����¼!");
			return EM_HaveRegistered;
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
	if (EM_RegisterSuccess == UserRegister(UserList, user))
	{
		printf("���Ѿ��ɹ�ע���˺ţ�\n");
		printf("�����˺�Ϊ��%s,��ʼ����Ϊ��%s,���Ϊ��%lf\n", user->account, user->password, user->balance);
	}
	free(username);
	username = NULL;
	free(identity);
	identity = NULL;
	free(phone);
	phone = NULL;
	return EM_RegisterSuccess;
}

int Login(User* UserList, User* user)
{
	int time = 3;
	int ret = 0;
	char* account = (char*)malloc(sizeof(17));
	char* password = (char*)malloc(sizeof(7));
	printf("�����������˺�\n");
	scanf("%s", account);
	int i = 0;
	for (; i < time; ++i)
	{
		printf("�������������루������6λ),������%d�λ���\n", time - i);
		InputPassword(password);
		ret = UserLogin(UserList, user, account, password);
		if (ret == EM_Password)
		{
			printf("\n��������������������룺\n");
		}
		else
		{
			return ret;
		}
	}
	free(account);
	free(password);
	account = NULL;
	password = NULL;
	return ret;
}

int CheckLoginRegister(User* UserList, User* user)
{
	RegLoginView();
	int step;
	scanf("%d", &step);
	while (1)
	{
		if (step == 1)
		{
			system("CLS");
			printf("��ӭ����ע����棬�������ʾ¼����Ϣ��\n");
			Register(UserList);
			step = 2;
		}
		if (step == 2)
		{
			system("ClS");
			printf("��ӭ������¼���棬�������ʾ������Ϣ��\n");
			int ret = Login(UserList, user);
			if (ret == EM_NoRegister)
			{
				printf("����δע�ᣬ����ע��!\n");
				step = 1;
			}
			if (ret == EM_Password)
			{
				continue;
			}
			if (ret == EM_LoginSuccess)
			{
				printf("\n��¼�ɹ�����\n");
				break;
			}
		}
		if (step == 3)
		{
			return 0;
		}
	}
	return 1;
}

void Deposit(User* UserList, Deal* DealList, User* user)
{
	printf("��ӭ���������棬��������Ҫ����Ľ�\n");
	double money;
	scanf("%lf", &money);
	int ret = UserDeposit(UserList, DealList, user, money);
	if (ret == EM_DespositSuccess)
	{
		printf("\n�ɹ�����%lfԪ����ǰ���Ϊ%lf\n", money, user->balance);
		return;
	}
	printf("ϵͳ���ϣ�����ʧ��\n");
}

void Withdraw(User* UserList, Deal* DealList, User* user)
{
	printf("��ӭ����ȡ����棬��������Ҫȡ���Ľ�\n");
	double money = 0;
	while (1)
	{
		scanf("%lf", &money);
		if (money > user->balance)
		{
			printf("\n���㣡����������ȡ���Ľ������˳���\n");
			printf("�Ƿ��˳�������1�˳���ǰ���ܣ�����0����\n");
			int choose = 0;
			scanf("%d", choose);
			if (choose)
			{
				return;
			}
		}
		else
		{
			int ret = UserWithdraw(UserList, DealList, user, money);
			if (ret == EM_WithdrawSuccess)
			{
				printf("\n�ɹ�ȡ��%lfԪ����ǰ���Ϊ%lf\n", money, user->balance);
				return;
			}
			printf("ϵͳ���ϣ�ȡ��ʧ��\n");
			return;
		}
	}
}

