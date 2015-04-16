#pragma once
#include "stdafx.h"

#include "NetClient.h"


/************************************************************************/
// 
//		npc�Ի�����,����npc��ĳ�Ա. ��Ϸ��Ľ�ɫ���npc�󵯳��öԻ���.��ʾ��Ӧnpc˵�Ļ�.������̵�npc.���й���ť.�㰴ť������������������������
//		
//
/************************************************************************/



class MyGUIDlgNpcTalk
{
public:
	MyGUIDlgNpcTalk(NPCProperty* npcprop , Socket::CNetClient* client);
	~MyGUIDlgNpcTalk(void);

	void OnEvent (const irr::SEvent& e);
	void update();//����
	void drawAll();
	bool LoadGUI();
	
	void ShowDlg(bool v); 
	//����
	void drop();

	bool mouseInGui;

private:
	irr::IrrlichtDevice *dev;
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;

	Socket::CNetClient* client;

	NPCProperty* npcprop;

	//�������
	vector2d<s32> cursor;


	gui::IGUIButton* btn;
	gui::IGUIWindow* win ;
};
