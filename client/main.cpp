// 1to2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "core.h"

#include "logincpp/loginscene.h"


//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
//
//					PSTR szCmdLine, int iCmdShow)
//
//{


int _tmain(int argc, _TCHAR* argv[])
{
	
Login::LoginCore c;
	
SLogin* login =c.Run();

if(login!=0)
{
	GameMain cb(login);
	delete login;
	cb.Run();

}

	//while(1){
	//	printf("��������? y\n");
	//	char ch=getchar();
	//	if(ch=='y'){
	//		Core c;
	//		c.Run();

	//	}
	//	
	//	Sleep(100);
	//}

	return 0;
}

