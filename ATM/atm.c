#include "atm.h"
#include <assert.h> // 断言头文件，不做要求

void PrintUserInfo(User* UserList)
{
	User* Node = UserList;
	while (Node)
	{
		printf("%s %s %s %s %s %lf\n", Node->name, Node->identity, Node->phone, Node->account, Node->password, Node->balance);
		Node = Node->next;
	}
}

void SaveFile(User* UserList, Deal* DeaList)
{
	WriteDealInfo(DeaList);
	WriteUserInfo(UserList);
}

void LoadUserInfo(User* UserList)
{
	FILE* fp = NULL;
	if ((fp = fopen("./resources/userInfo.txt", "r")) == NULL)
	{
		printf("userInfo 无法打开\n");
		return;
	}

	// 尾插法加节点；
	User* Tail = UserList;
	if (IsFileEmpty(fp))
	{
		fclose(fp);
		return;
	}

	while (!feof(fp))
	{
		
	}

	//while (fscanf(fp, "%s %s %s %s %s %lf",
	//	Tail->name, Tail->identity, Tail->phone, Tail->account, Tail->password, &Tail->balance) == 6)
	//{
	//	User* Node = (User*)malloc(sizeof(User));
	//	if (fscanf(fp, "%s %s %s %s %s %lf",
	//		Node->name, Node->identity, Node->phone, Node->account, Node->password, &Node->balance) == 6)
	//	{
	//		Tail->next = Node;
	//		Tail = Node;
	//		Node->next = NULL;
	//	}
	//	else
	//	{
	//		free(Node);  // 如果 fscanf 失败，释放已分配的内存
	//		break;       // 如果 fscanf 失败，退出循环
	//	}
	//}

	fclose(fp);
}

void LoadDealInfo(Deal* DealList)
{
	FILE* fp = NULL;
	if ((fp = fopen("./resources/dealInfo.txt", "r")) == NULL)
	{
		printf("dealInfo 无法打开\n");
		return;
	}

	Deal* Tail = DealList;

	while (fscanf(fp, "%s %s %lf %d %d %d %d:%d:%d %lf",
		Tail->account, Tail->type, &Tail->money,
		&Tail->time_year, &Tail->time_month, &Tail->time_day,
		&Tail->time_hour, &Tail->time_min, &Tail->time_sec,
		&Tail->balance) == 10)
	{
		Deal* Node = (Deal*)malloc(sizeof(Deal));
		if (fscanf(fp, "%s %s %lf %d %d %d %d:%d:%d %lf",
			Node->account, Node->type, &Node->money,
			&Node->time_year, &Node->time_month, &Node->time_day,
			&Node->time_hour, &Node->time_min, &Node->time_sec,
			&Node->balance) == 10)
		{
			Tail->next = Node;
			Tail = Node;
			Node->next = NULL;
		}
		else
		{
			free(Node);  
			break;       
		}
	}

	fclose(fp);
}

void WriteUserInfo(User* UserList)
{
	FILE* fp = NULL;
	if ((fp = fopen("./resources/userInfo.txt", "w")) == NULL)
	{
		printf("userInfo cant be opened\n");
		return;
	}
	User* Node = UserList;
	while (Node)
	{
		// 特殊处理写入最后一行不需要\n
		if (Node->next == NULL)
		{
			fprintf(fp, "%s %s %s %s %s %lf", Node->name, Node->identity, Node->phone, Node->account, Node->password, Node->balance);
			break;
		}
		fprintf(fp, "%s %s %s %s %s %lf\n", Node->name, Node->identity, Node->phone, Node->account, Node->password, Node->balance);
		Node = Node->next;
	}
	fclose(fp);
}

void WriteDealInfo(Deal* DealList)
{
	FILE* fp = NULL;
	if ((fp = fopen("./resources/dealInfo.txt", "w")) == NULL)
	{
		printf("dealInfo cant be opened\n");
		return;
	}
	Deal* Node = DealList;
	while (Node)
	{
		// 特殊处理 写入最后一行不需要\n
		if (Node->next == NULL)
		{
			fprintf(fp, "%s %s %lf %d %d %d %d:%d:%d %lf\n", Node->account, Node->type, Node->money,
				Node->time_year, Node->time_month, Node->time_day, Node->time_hour, Node->time_min, Node->time_sec, Node->balance);
			break;
		}
		fprintf(fp, "%s %s %lf %d %d %d %d:%d:%d %lf\n", Node->account, Node->type, Node->money,
			Node->time_year, Node->time_month, Node->time_day, Node->time_hour, Node->time_min, Node->time_sec, Node->balance);
		Node = Node->next;
	}
	fclose(fp);
}



int UserRegister(User* UserList, User* newUser)
{
	User* cur = UserList;
	while (cur)
	{
		if (cur->next == NULL)
		{
			// 将user插入UserList尾部
			cur->next = newUser;
			newUser->next = NULL;
			WriteUserInfo(UserList);
			return EM_RegisterSuccess;
		}
		cur = cur->next;
	}
	return EM_UnknownError;
}

int UserLogin(User* UserList, User* user, char* account, char* password)
{
	User* Cur = UserList;
	while (Cur)
	{
		if (strcmp(Cur->account, account) == 0)
		{
			if (strcmp(Cur->password, password) == 0)
			{
				// 成功
				strcpy(user->name, Cur->name);
				strcpy(user->identity, Cur->identity);
				strcpy(user->phone, Cur->phone);
				strcpy(user->account, Cur->account);
				strcpy(user->password, Cur->password);
				user->balance = Cur->balance;
				user->next = NULL;
				return EM_LoginSuccess;
			}
			else
			{
				return EM_Password;
			}
			break;
		}
		Cur = Cur->next;
	}
	return EM_NoRegister;
}

int UserDeposit(User* UserList, Deal* DealList, User* user, double deposit)
{
	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->account,user->account) == 0 && 
			strcmp(cur->identity,user->identity) == 0)
		{
			user->balance += deposit;
			cur->balance += deposit;
			WriteUserInfo(UserList);

			Deal* dCur = DealList;

			while (dCur)
			{
				if (dCur->next == NULL)
				{
					Deal* node = (Deal*)malloc(sizeof(Deal));
					strcpy(node->account, user->account);
					strcpy(node->type, "存入");
					node->money = deposit;
					node->balance = user->balance;
					CreateTimeStamp(node);

					// node插入链表尾部
					dCur->next = node;
					node->next = NULL;
					WriteDealInfo(DealList);
					return EM_DespositSuccess;
				}
				dCur = dCur->next;
			}
		}
		cur = cur->next;
	}
	return EM_UnknownError;
}

int UserWithdraw(User* UserList, Deal* DealList, User* user, double withdraw)
{
	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->account, user->account) == 0 && 
			strcmp(cur->identity, user->identity) == 0)
		{
			user->balance -= withdraw;
			cur->balance -= withdraw;
			WriteUserInfo(UserList);

			Deal* dCur = DealList;

			while (dCur)
			{
				if (dCur->next == NULL)
				{
					Deal* node = (Deal*)malloc(sizeof(Deal));
					strcpy(node->account, user->account);
					strcpy(node->type, "取出");
					node->money = withdraw;
					node->balance = user->balance;
					CreateTimeStamp(node);

					// node 插入链表尾部
					dCur->next = node;
					node->next = NULL;
					WriteDealInfo(DealList);

					return EM_WithdrawSuccess;
				}
				dCur = dCur->next;
			}

		}
		cur = cur->next;
	}
	return EM_UnknownError;
}

void Transfer(User* UserList, Deal* DealList, User* out, User* in, double money)
{
	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->account,out->account) == 0 && 
			strcmp(cur->identity,out->identity) == 0)
		{
			out->balance -= money;
			cur->balance -= money;

			Deal* dCur = DealList;

			while (dCur)
			{
				if (dCur->next == NULL)
				{
					Deal* node = (Deal*)malloc(sizeof(Deal));
					strcpy(node->account, out->account);
					strcpy(node->type, "转出");
					node->money = money;
					node->balance = out->balance;
					CreateTimeStamp(node);

					// node 插入链表尾部
					dCur->next = node;
					node->next = NULL;
					break;
				}
				dCur = dCur->next;
			}
		}
		if (strcmp(cur->account, in->account) == 0 && 
			strcmp(cur->identity, in->identity) == 0)
		{
			in->balance += money;
			cur->balance += money;
			Deal* dCur = DealList;

			while (dCur)
			{
				if (dCur->next == NULL)
				{
					Deal* node = (Deal*)malloc(sizeof(Deal));
					strcpy(node->account, in->account);
					strcpy(node->type, "取出");
					node->money = money;
					node->balance = in->balance;
					CreateTimeStamp(node);

					// node 插入链表尾部
					dCur->next = node;
					node->next = NULL;
					break;
				}
				dCur = dCur->next;
			}
		}
		cur = cur->next;
	}
	WriteDealInfo(DealList);
	WriteUserInfo(UserList);
}

void ReferUserInfo(User* user)
{
	printf("亲爱的用户，您的账号为：%s,您的余额为%lf\n", user->account, user->balance);
}

void ReferDealInfo(Deal* DealList, User* user)
{
	Deal* cur = DealList;
	while (cur)
	{
		if (strcmp(cur->account, user->account) == 0)
		{
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\t%lf", cur->time_year, cur->time_month, cur->time_day,
				cur->time_hour, cur->time_min, cur->time_sec, cur->type, cur->money);
		}
		cur = cur->next;
	}
}

void ChangeUserInfo(User* UserList, User* user, char* info, CT type)
{
	User* cur = UserList;
	while (cur)
	{
		if (strcmp(cur->account, user->account) == 0
			&& strcmp(cur->identity, user->identity) == 0)
		{
			switch (type)
			{
			case CT_NAME:
				assert(strlen(info) < 20); // 断言不做要求
				strcpy(user->name, info);
				strcpy(cur->name, info);
				break;
			case CT_PASSWORD:
				assert(strlen(info) < 7);
				strcpy(user->password, info);
				strcpy(cur->password, info);
				break;
			case CT_PHONE:
				assert(strlen(info) < 13);
				strcpy(user->phone, info);
				strcpy(cur->phone, info);
				break;
			case CT_IDENTITY:
				assert(strlen(info) < 20);
				strcpy(user->identity, info);
				strcpy(cur->identity, info);
			default:
				break;
			}
			break;
		}
		cur = cur->next;
	}
	WriteUserInfo(UserList);
}

void CreateTimeStamp(Deal* node)
{
	time_t tt;
	struct tm* pTime;
	time(&tt);
	pTime = gmtime(&tt);
	node->time_year = 1900 + pTime->tm_year;
	node->time_month = 1 + pTime->tm_mon;
	node->time_day = pTime->tm_mday;
	node->time_hour = pTime->tm_hour + 8;
	node->time_min = pTime->tm_min;
	node->time_sec = pTime->tm_sec;
}

void InputPassword(char* pwd)
{
	int i = 0;
	while (pwd[i] != '\n')
	{
		pwd[i] = _getch();
		if (pwd[i] == '\r')
			break;
		if (pwd[i] == '\b')
		{
			if (i == 0)
			{
				printf("\a");
				continue;
			}
			i--;
			printf("\b");
		}
		else
		{
			putchar('*');
			++i;
		}
	}
	pwd[i] = '\0';

}

int IsFileEmpty(FILE* fp)
{
	// 记录当前文件指针所在的位置
	long curIndex = ftell(fp);

	// 将文件指针移到最后
	fseek(fp, 0, SEEK_END);

	int ret = (ftell(fp) == 0 ? 1 : 0);

	// 将文件指针还原
	fseek(fp, curIndex, SEEK_SET);

	return ret;
}

