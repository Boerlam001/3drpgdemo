#pragma once
#include "stdafx.h"
#include "MyCharacter.h"

#include "Myscenemanager.h"




/************************************************************************/
// 
//		��ɫ������.��������ɫ���������߽�ɫ.
//		
//
/************************************************************************/


class MySceneManager;

class MyCharacterMgr
{
public:
	MyCharacterMgr(MySceneManager* mm );
	~MyCharacterMgr(void);

		//�����¼�
	void OnEvent (const irr::SEvent & e);

	//����ɫ��½
	void CMD_USERLOGIN_PROC(const char* pData,const unsigned long length);

	//���������ɫ
	void AddCharacter(char* pData,unsigned long length);

	//�Ƴ��������߽�ɫ.�����л�����ʱ��.
	void RemoveAllCharacter();

	//�������н�ɫ������ʾ?
	void setAllRoleWeaponVisible(bool v);

	void setAllRoleClothVisible(bool v);


	//�õ�����ɫ
	MyCharacter*  GetMainCharacter(){return character;};
	void  SetMainCharacter(MyCharacter* c){character=c;};

	//����sock�õ���ɫ sock�ǽ�ɫ��Ψһ��־
	MyCharacter*  GetCharacterByID(int sock);
	
	void RemoveCharacter(int id);
	void update();

	void UIRender();

	//�õ���ɫlist��
	int getOnlineCharacterNum(){return char_list.getSize();};

	//������������������߽�ɫ
	void getOnlineAllCharacter();

	//�н�ɫ�������¼�����
	void insertCharData(const char* pData ,const int DataLength);

	//�õ�charlistָ��
	irr::core::list<MyCharacter*>* getCharListPointer(){return &char_list;};

	void Quit(){m_bquit=true;};

private:
	//�������ɫ
	void AddMainCharacter(const char* pData,const unsigned long length);

	//����ɫ��������
	void CMD_S2C_Response_Package_PROC(char* pData,unsigned long length);
	//������Ҫ���ɫ�л���ͼ
	void CMD_S2C_Response_ChangeWorld_PROC(char* pData,unsigned long length);
	
	//����������ɫ������
	void CMD_Response_ChangeWeapon_PROC(char* pData,unsigned long length);
	//��ɫ��������Ϣ
	void CMD_USERUNDERATTACK_PROC(char* pData,unsigned long length);
	//��ɫ��Ǯ������Ϣ
	void CMD_USERMoneyUpdate_PROC(char* pData,unsigned long length);
	void CMD_QUIT_PROC(char* pData,unsigned long length);


	void CMD_NEWUSER_PROC(char* pData,unsigned long length);
	void CMD_UserUPDATE_PROC(char* pData,unsigned long length );
	void CMD_USERMSG_PROC(char* pData,unsigned long length );

	void CMD_ServerResponse_Prop_PROC(char* pData,unsigned long length);

	//��������������Ľ�ɫ��Ϣ
	void  DoListThread( );

	irr::core::list<ClientMsg*> msglist;    //��server��������Ϣ��,���¿ͻ���Ϣ��

	CRITICAL_SECTION g_cs_charlist,g_cs_msglist; //�ٽ�

	irr::core::list<MyCharacter*> char_list;  //list�浱ǰ�����˽�ɫ


	MyCharacter* character; //����ɫ


	//����ָ��
	IrrlichtDevice *dev;		

	//��������
	scene::ISceneManager* smgr;
	
	//
	MySceneManager* myScene_Mgr;

	bool mouseDownL;


	ITimer* timer;

	bool m_bquit; //�˳�
};
