#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atm.h"

int main()
{
	// 系统随机种子 其他函数需要用到
	srand((unsigned)(time(NULL)));

	// 文件加载进内存
	User* UserList = (User*)malloc(sizeof(User));
	LoadUserInfo(UserList);
	Deal* DealList = (Deal*)malloc(sizeof(Deal));
	LoadDealInfo(DealList);
}