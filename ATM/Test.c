#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atm.h"

int main()
{
	// ϵͳ������� ����������Ҫ�õ�
	srand((unsigned)(time(NULL)));

	// �ļ����ؽ��ڴ�
	User* UserList = (User*)malloc(sizeof(User));
	LoadUserInfo(UserList);
	Deal* DealList = (Deal*)malloc(sizeof(Deal));
	LoadDealInfo(DealList);
}