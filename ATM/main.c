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
	// 系统随机种子 其他函数需要用到
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
	printf("**欢迎使用ATM自动取款机系统**\n");
	printf("*****************************\n");
	printf("———————————————\n");
	printf("|         1 开户             |\n");
	printf("———————————————\n");
	printf("|         2 登陆             |\n");
	printf("———————————————\n");
	printf("|         3 退出             |\n");
	printf("———————————————\n");
	printf("|      请选择您的需求        |\n");
	printf("———————————————\n");
}

void OperationView()
{
	printf("请选择您需要的业务\n");
	printf("**********************************\n");
	printf("**  1 取款  **********  2 查询  **\n");
	printf("**********************************\n");
	printf("**  3 转账  ******  4 修改信息  **\n");
	printf("**********************************\n");
	printf("**  5 存款  **********  6 退出  **\n");
	printf("**********************************\n");
}

void view_third()
{
	printf("**********************************\n");
	printf("***********1 改密码 **************\n");
	printf("**********************************\n");
	printf("***********2 改名字 **************\n");
	printf("**********************************\n");
	printf("***********3 改电话 **************\n");
	printf("**********************************\n");
}

void view_forth()
{
	printf("**********************************\n");
	printf("********* 1 按交易日期 ***********\n");
	printf("**********************************\n");
	printf("********* 2 按交易类型 ***********\n");
	printf("**********************************\n");
}

int Register(User* UserList)
{
	system("CLS");
	char username[20];
	char identity[17];
	char phone[13];

	printf("请输入您的名字（不超过6个字);\n");
	scanf("%s", username);
	printf("请输入您的身份证（不超过18位);\n");
	scanf("%s", identity);
	printf("请输入您的电话号码（不超过11位);\n");
	scanf("%s", phone);

	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->identity, identity) == 0)
		{
			printf("你已经注册过了，请登录");
			return (int)EM_HaveRegistered;
		}
		cur = cur->next;
	}
	User* user = (User*)malloc(sizeof(User));
	// 随机生成17位数的account账号
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
	strcpy(user->password, "111111"); // 初始化密码都是111111
	user->balance = 0.00;
	if (0 == UserRegister(UserList, user))
	{
		printf("您已经成功注册账号！\n");
		printf("您的账号为：%s,初始密码为：%s,余额为：%lf\n", user->account, user->password, user->balance);
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
		printf("请输入您的账号\n");
		scanf("%s", account);
		printf("请输入您的密码（不超过6位),您还有%d次机会\n",time);

		InputPassword(password);
		ret = UserLogin(UserList, user, account, password);
		--time;
	} while (time > 0 && ret == EM_Password);

	return ret;
}

