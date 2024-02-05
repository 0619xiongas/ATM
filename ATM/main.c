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
	// 系统随机种子 其他函数需要用到
	srand((unsigned)(time(NULL)));

	// 文件加载进内存
	User* UserList = (User*)malloc(sizeof(User));
	LoadUserInfo(UserList);
	Deal* DealList = (Deal*)malloc(sizeof(Deal));
	LoadDealInfo(DealList);


	User* user = (User*)malloc(sizeof(User));
	int isLogin = 0; // 判断是否登录成功
	int isExit = 0; // 判断是否退出系统
	 // 注册登录部分
	isLogin = CheckLoginRegister(UserList, user);
	// 操作部分
	while (isLogin && !isExit)
	{
		OperationView();
		int step = 0;
		scanf("%d", &step);
		system("CLS");
		switch (step)
		{
		case 1:// 存钱
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
	printf("**  1 存款  **********  2 取款  **\n");
	printf("**********************************\n");
	printf("**  3 转账  ******  4 修改信息  **\n");
	printf("**********************************\n");
	printf("**  5 查询  **********  6 退出  **\n");
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
	char *username = (char*)malloc(sizeof(20));
	char *identity = (char*)malloc(sizeof(20));
	char *phone = (char*)malloc(sizeof(7));
	do 
	{
		printf("请输入您的名字（不超过6个字);\n");
		scanf("%s", username);
		if (strlen(username) > 6)
		{
			printf("\n名字大于6个字!!!\n");
		}
	} while (strlen(username) > 6);

	do 
	{
		printf("请输入您的身份证（不超过18位);\n");
		scanf("%s", identity);
		if (strlen(identity) > 18)
		{
			printf("\n身份证超过18位\n");
		}
	} while (strlen(identity) > 18);
	do 
	{
		printf("请输入您的电话号码（不超过11位);\n");
		scanf("%s", phone);
		if (strlen(phone) > 11)
		{
			printf("\n电话号码超过11位\n");
		}
	} while (strlen(phone) > 11);

	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->identity, identity) == 0)
		{
			printf("你已经注册过了，请登录!");
			return EM_HaveRegistered;
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
	if (EM_RegisterSuccess == UserRegister(UserList, user))
	{
		printf("您已经成功注册账号！\n");
		printf("您的账号为：%s,初始密码为：%s,余额为：%lf\n", user->account, user->password, user->balance);
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
	printf("请输入您的账号\n");
	scanf("%s", account);
	int i = 0;
	for (; i < time; ++i)
	{
		printf("请输入您的密码（不超过6位),您还有%d次机会\n", time - i);
		InputPassword(password);
		ret = UserLogin(UserList, user, account, password);
		if (ret == EM_Password)
		{
			printf("\n您的密码错误，请重新输入：\n");
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
			printf("欢迎来到注册界面，请根据提示录入信息：\n");
			Register(UserList);
			step = 2;
		}
		if (step == 2)
		{
			system("ClS");
			printf("欢迎来到登录界面，请根据提示输入信息：\n");
			int ret = Login(UserList, user);
			if (ret == EM_NoRegister)
			{
				printf("您还未注册，请先注册!\n");
				step = 1;
			}
			if (ret == EM_Password)
			{
				continue;
			}
			if (ret == EM_LoginSuccess)
			{
				printf("\n登录成功！！\n");
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
	printf("欢迎来到存款界面，请输入你要存入的金额：\n");
	double money;
	scanf("%lf", &money);
	int ret = UserDeposit(UserList, DealList, user, money);
	if (ret == EM_DespositSuccess)
	{
		printf("\n成功存入%lf元，当前余额为%lf\n", money, user->balance);
		return;
	}
	printf("系统故障，存入失败\n");
}

void Withdraw(User* UserList, Deal* DealList, User* user)
{
	printf("欢迎来到取款界面，请输入你要取出的金额：\n");
	double money = 0;
	while (1)
	{
		scanf("%lf", &money);
		if (money > user->balance)
		{
			printf("\n余额不足！请重新输入取出的金额或者退出！\n");
			printf("是否退出，输入1退出当前功能，输入0继续\n");
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
				printf("\n成功取出%lf元，当前余额为%lf\n", money, user->balance);
				return;
			}
			printf("系统故障，取出失败\n");
			return;
		}
	}
}

