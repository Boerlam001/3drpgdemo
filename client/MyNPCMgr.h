#pragma once

#include "stdafx.h"
#include "MyNPC.h"

#include "MySceneManager.h"
/************************************************************************/
// 
//		NPC������.
//		
//
/************************************************************************/


class MyNPCMgr
{
public:
	MyNPCMgr( MySceneManager* mm);
	~MyNPCMgr(void);


	void MyNPCMgr::setVisiable(bool v);

	//����npc��Ϣ������,���Է�����
	void insertNPCData(char* pData,int DataLength);

	//�����¼�
	void OnEvent (const irr::SEvent & e);



	//���һ��npc��������
	void AddNPC(NPCProperty prop);
	
	//����id�õ�npc
	MyNPC* GetNpcByID(int id);

	//�Ƴ���������NPC.�����л�����ʱ��.
	void RemoveAllNPC();

	//����npc����
	void LoadSceneNPC(int worldMap);

	//����npc����
	void update();

	void UIRender();


	bool IsselectedNPC(){return NPCselected;};
	MyNPC* GetselectedNPC(){return selectedNPCnode;};

	bool MouseInNPC_GUI;
private:
	IrrlichtDevice* dev;
	irr::scene::ISceneManager *smgr; 

	MySceneManager* m_pMySceneMgr;

	std::vector<ClientMsg*> msglist;    //��server��������Ϣ��,���¿ͻ���Ϣ��

	CRITICAL_SECTION g_cs_npclist,g_cs_msglist; //�ٽ�

	std::vector<MyNPC*> npc_list;  //list�浱ǰ��������npc

	//��ǰnpc����������ͼid
	int currWorldMap;

	//�����ʰȡ��npc
	bool NPCselected;
	MyNPC* selectedNPCnode;
};
