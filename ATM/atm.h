#ifndef _ATM_H_2023_12_23
#define _ATM_H_2023_12_23
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>  //获取系统时间
#include <conio.h> // 随机产生数字字符串
typedef enum ErrorMsg
{
    EM_NULL = 0, // 无错误码
    EM_InsufficientBalance = 1, // 余额不足
    EM_HaveRegistered = 2, // 已经注册过了
    EM_Password = 3, // 密码错误
    EM_NoRegister = 4, // 用户未注册
    EM_UnknownError = 100, // 未知错误
} EM;

typedef enum DealType
{
    TansferIn,  // 转入
    TansferOut,   // 转出
    Deposit,  // 存钱
    Withdraw // 取钱
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
    char name[20]; // 用户姓名
    char identity[20]; // 身份证号
    char phone[13];  // 手机号码
    char account[17];  // 账号
    char password[7];  // 账号密码
    double balance;  // 余额
    struct User* next;
}User;

typedef struct Deal
{
    char account[17];  // 账号
    char type[6];   // 交易类型
    double money;   // 交易值
    int time_year;
    int time_month;
    int time_day;
    int time_hour;
    int time_min;
    int time_sec;
    double balance;  // 余额
    struct Deal* next;
}Deal;

// 测试数据
void PrintUserInfo(User* UserList);

// 信息处理部分

// 将user信息从文本加载到内存中，用链表保存
void LoadUserInfo(User* UserList);

void WriteUserInfo(User* UserList);

void WriteDealInfo(Deal* DealList);

void LoadDealInfo(Deal* DealList);

// 功能函数
// 注册账号函数
int UserRegister(User* UserList, User* newUser);

int UserLogin(User* UserList, User* user,char* account,char* password);

int UserDeposit(User* UserList, Deal* DealList, User* user, double deposit);

int UserWithdraw(User* UserList, Deal* DealList, User* user, double withdraw);
// out 转出方，in 收款方
void Transfer(User* UserList, Deal* DealList, User* out,User* in,double money);

void ReferUserInfo(User* user);

void ReferDealInfo(Deal* DealList, User* user);

void ChangeUserInfo(User* UserList,User* user,char* info,CT type);


// Utils 函数

// 时间戳写入
void CreateTimeStamp(Deal* node);

// 输入密码做保护，不做要求
void InputPassword(char* pwd);
#endif
