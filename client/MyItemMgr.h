#pragma once

#include "stdafx.h"
#include "myitem.h"
#include "NetClient.h"

#include "MySceneManager.h"

/************************************************************************/
// 
//		  ������Ʒ������ ����ͷ�����ͨѶ��������Ʒ.
//		
//
/************************************************************************/

class MySceneManager;

class MyItemMgr
{
public:
	MyItemMgr( MySceneManager* mysmgr, Socket::CNetClient* net);
	~MyItemMgr(void);


	//�Ƿ����г���������Ʒ�Ƿ�ɼ�
	void setAllItemVisiable(bool v);

	void insertItemData(const char* pData,const unsigned int DataLength);
	void SceneCMD_ITEMDROP_PROC(char* pData,unsigned long length);
	//��Ʒ��ʧ
	void MyItemMgr::SceneCMD_ITEMDROPRemoveProc(char* pData,unsigned long length);

	void Quit(){m_bquit=true;};

	//���³�����Ʒ.�������,ж��
	void update();

	////��ͼ�ĵ�����Ʒ���
	void RemoveAllItem();

	//�õ����г����ĵ�����Ʒ
	void getSceneCMD_ITEMDROPAll();

	//��ʾ��Ʒ����
	void UIRender();


private:
	IrrlichtDevice *dev;


	//�����������������Ʒ��Ϣ
	void  DoListThread( );







	std::list<MyItem*>  SceneItem_list;  //list�������Ʒ

	irr::core::list<ClientMsg*> msglist;    //��server��������Ϣ��,���³�����Ʒ��Ϣ��
	CRITICAL_SECTION g_cs_msglist,g_cs_SceneItem_list; //�ٽ�

	MySceneManager* m_pMySceneMgr;


	//����
	Socket::CNetClient* net;

	bool m_bquit; //�˳�
};
