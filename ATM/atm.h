#ifndef _ATM_H_2023_12_23
#define _ATM_H_2023_12_23
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>  //��ȡϵͳʱ��
#include <conio.h> // ������������ַ���
typedef enum ErrorMsg
{
    EM_NULL = 0, // �޴�����
    EM_InsufficientBalance = 1, // ����
    EM_HaveRegistered = 2, // �Ѿ�ע�����
    EM_Password = 3, // �������
    EM_NoRegister = 4, // �û�δע��
    EM_UnknownError = 100, // δ֪����
} EM;

typedef enum DealType
{
    TansferIn,  // ת��
    TansferOut,   // ת��
    Deposit,  // ��Ǯ
    Withdraw // ȡǮ
} DealType;

typedef enum ChangeType
{
    CT_NAME = 1,
    CT_IDENTITY = 2,
    CT_PHONE = 3,
    CT_PASSWORD = 4,
}CT;
typedef struct User
{
    char name[20]; // �û�����
    char identity[20]; // ���֤��
    char phone[13];  // �ֻ�����
    char account[17];  // �˺�
    char password[7];  // �˺�����
    double balance;  // ���
    struct User* next;
}User;

typedef struct Deal
{
    char account[17];  // �˺�
    char type[6];   // ��������
    double money;   // ����ֵ
    int time_year;
    int time_month;
    int time_day;
    int time_hour;
    int time_min;
    int time_sec;
    double balance;  // ���
    struct Deal* next;
}Deal;

// ��������
void PrintUserInfo(User* UserList);

// ��Ϣ������

// ��user��Ϣ���ı����ص��ڴ��У���������
void LoadUserInfo(User* UserList);

void WriteUserInfo(User* UserList);

void WriteDealInfo(Deal* DealList);

void LoadDealInfo(Deal* DealList);

// ���ܺ���
// ע���˺ź���
int UserRegister(User* UserList, User* newUser);

int UserLogin(User* UserList, User* user,char* account,char* password);

int UserDeposit(User* UserList, Deal* DealList, User* user, double deposit);

int UserWithdraw(User* UserList, Deal* DealList, User* user, double withdraw);
// out ת������in �տ
void Transfer(User* UserList, Deal* DealList, User* out,User* in,double money);

void ReferUserInfo(User* user);

void ReferDealInfo(Deal* DealList, User* user);

void ChangeUserInfo(User* UserList,User* user,char* info,CT type);


// Utils ����

// ʱ���д��
void CreateTimeStamp(Deal* node);

// ��������������������Ҫ��
void InputPassword(char* pwd);
#endif
