#pragma once


#include "mycharactermgr.h"
#include "my3rdcamera.h"
#include "myitem.h" 
#include "MyMonstersMgr.h"
#include "myitemmgr.h"
#include "MyGUIManager.h" 
#include "mysceneloader.h"

#include "MyNPCMgr.h"
/************************************************************************/
// 
//		 ����������.ͳһ����������������. .
//		
//
/************************************************************************/


class MyCharacterMgr;
class MyMonstersMgr;
class MyGUIManager;
class MyNPCMgr;
class MyItemMgr;

class MySceneManager
{
public:
	MySceneManager( Socket::CNetClient* client);
	~MySceneManager(void);
	
	//ж�ص�ǰ���糡��
	void DropCurrScene();

	//����ָ��id�����糡��
	void LoadScene(int id);

	//��ʼ�������
	void InitCamera();

	//��ʼ��������ɫ������
	void InitCharacterMgr();

	//��ʼ���������������
	void InitMonsterMgr();

	//��ʼ������npc������
	void InitNpcMgr();

	//��ʼ��������Ʒ������
	void InitItemMgr();
	
	//��ʼ��GUI���������
	void InitGUIMgr();



	//�����¼�,���ַ����ӹ�����
	void OnEvent (const irr::SEvent& e);

	//����
	void update();

	//3d��Ⱦ 
	void Render();

	//2d��Ⱦ �������2dͼƬ
	void UIRender();

	//�������
	void TextRender();

	//�л�����
	void ChangeWorld(int worldMap);


	//��Ļ��ʾ����
	void Show(char* s);

public:
		//����core
	            irr::IrrlichtDevice *dev; 
			    irr::video::IVideoDriver *drv; 
                irr::scene::ISceneManager *smgr; 


				
				
				//3rd�����
			    My3rdCamera* myCamera;

				//gui������
				MyGUIManager* myGUI_Mgr;

				//���������
				MyMonstersMgr* monster_mgr;

				//��ɫ������
				MyCharacterMgr* char_mgr; 

				//NPC������
				MyNPCMgr* npc_mgr;

				//��Ʒ������
				MyItemMgr* item_mgr; 

				//��������ж�ع�����
				MySceneLoader* myscene_loader;

				//��������
				Socket::CNetClient* client;

				
				
				// mouse registry 
				bool mouseDownL,mouseDownR; 

				void beginchange();

				bool change;

				//�Ƿ��л�����? trueʱ�л�
				bool changeworld;
				//��ǰ����id
				int worldMap;


				int muoseclick;
				int lastmouseclick;

				

};
