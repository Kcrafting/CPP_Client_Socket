// Client.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>  
#include <stdio.h>  
#include <windows.h> //一定要包含该头文件
#pragma comment(lib, "WS2_32.lib")  //windwows下的socket编程函数库
using namespace std;
int main()
{
	WSADATA wsaData;//
	WORD sockVersion = MAKEWORD(2, 2);
	//windows网络编程库的版本号信息
	SOCKET sock = 0;  //TCP通信的socket数据结构 
	if (WSAStartup(sockVersion, &wsaData) != 0)///
		//WSAStartup函数是在程序中初始化并加载Windows网络
	{
		cout << "initlization failed!" << endl;
		exit(0);
		//如果WSAStartup返回值为1的话就表示ws2_32.dll文件有问题，程序退出
	}

	sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//在本机上创建一个socket  
	if (sock == INVALID_SOCKET)  //判断socket是否创建成功
	{
		cout << "failed socket!" << endl;
		return 0;  //如果创建失败就在程序中返回0结束程序
	}

	sockaddr_in sin;
	//创建一个socket编程类型的网络地址数据结构以便connect函数对本机创建的socket数据
	//结构进行初始化。
	sin.sin_family = AF_INET;   //设置网络协议族类型
	sin.sin_port = htons(55533);  //设置远程计算机的端口号
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//设置远程计算机的IP地址 
	if (connect(sock, (sockaddr*)&sin, sizeof(sockaddr)) == -1)
		//初始化socket并连接远程计算机
	{
		cout << "connect failed!" << endl;
		return 0;  //连接失败就返回0到程序
	}
	char buffer[256] = "\0";  //声明一个从网络接收数据的缓存区
	int  nRecv = 0;  //声明一个从网络接收到的数据字节长度   
	
	//recv是一个接收网络的TCP数据包函数，nRecv是从网络接收到数
	//据的字节长度 
	while (true) {
		nRecv = recv(sock, buffer, 256, 0);
		if (nRecv > 0)
		{
			buffer[nRecv] = '\0';
			//如果接收到网络数据包长度大于0的话就在接收到的数据包未尾添加一个字符串
			//结束符  
			cout << "reveive data: " << buffer << endl;
			//按字符串格式输出接收到的数据 
		}
	}
	closesocket(sock);  //关闭这个TCP网络通信连接
	WSACleanup();  //释放ws2_32.dll动态库
}

