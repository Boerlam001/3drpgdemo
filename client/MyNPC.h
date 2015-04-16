#pragma once

#include "stdafx.h"

#include "MyGUIDlgCommon.h"

#include "netclient.h"


/************************************************************************/
// 
//		npc��
//		
//
/************************************************************************/



class MyNPC
{
public:
	MyNPC( NPCProperty prop,Socket::CNetClient* client);

	~MyNPC(void);

	IAnimatedMeshSceneNode* getNode(){return node;};

	//�����¼�
	void OnEvent(const SEvent& e);

	//����
	void update();
	
	//ui����
	void UIRender();

	//
	void ShowTalkDlg();

	//ж��
	void drop();

	//�õ�npc����
	NPCProperty getProp(){return npc_prop;};

	//���ָ����npc?
	bool mouseCurNPC;

	//���ָ����npc�Ի���
	bool mouseCurNPC_Dlg;


	core::line3d<f32> line;//��ײ��

private:
	IrrlichtDevice *dev;
	ISceneManager* smgr;					//��������
	IAnimatedMeshSceneNode* node;			//�����ڵ�

	//��ʾnpc���Ƶ�text�ڵ�
	ITextSceneNode*	char_textnode;

	Socket::CNetClient* client;

	//npc������
	NPCProperty npc_prop;

	//npc�ĶԻ���
	MyGUIDlgNpcTalk* dlg;


};
