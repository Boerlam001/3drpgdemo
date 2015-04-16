#pragma once


#include "MySceneManager.h"

#include "guicpp/CGUIProgressBar.h"
#include "guicpp/CImageGUISkin.h"
#include "guicpp/SkinLoader.h"

#include "myguidlgsysmenu.h"	//ϵͳ�˵����

#include "myguidlgcharpackage.h"	//�������

#include "myguidlgcharprop.h" //��ɫ�������

#include "MyGUIDlgCharSkill.h" //��ɫ�������

#include "MyGUIDlgNpcShop.h"  //npc�̵����

/************************************************************************/
// 
//		 gui�ܹ�����
//		
//
/************************************************************************/


class MyGUIDlgCharPackage;
class MyGUIDlgCharProp;
class MyGUIDlgSysMenu;
class MyGUIDlgNpcShop;
class MyGUIDlgCharSkill;

class MyGUIManager
{
public:
	MyGUIManager (MySceneManager* m);
	 void OnEvent (const irr::SEvent& e);
	 void update();//����
	 void drawAll();
	 bool LoadGUI();

	 void insertGUIData(const char* pData,const unsigned int DataLength);


	 //�û������ķ���,��msg�ַ�����ʾ��listbox��
	 void PostMsg(const wchar_t* msg);

	~MyGUIManager(void);

	bool GetEditIsInput(); //�������ui,��س�,��������ģʽ?

	//�õ���ɫ����guiָ��
	MyGUIDlgCharPackage* getCharPackage(){return m_pGUIDlg_charPackage;};

	//�õ�npc�̵�guiָ��
	MyGUIDlgNpcShop* getNpcShop(){return m_pGUIDlg_npcShop;};


private:
	irr::IrrlichtDevice *dev; 
	irr::video::IVideoDriver *drv; 
	 irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;

	MySceneManager* mgr;
//-����������-----------------------------------------------------------
	// keyboard registry 
	bool keys[irr::KEY_KEY_CODES_COUNT]; 

	// mouse registry 
	bool mouseDownL; 
	bool mouseDownM; 
	bool mouseDownR; 
	f32 lastWheelMovement; 
	position2d<s32> cursor; 
	position2d<s32> cursorOld; 

//---------------------------------------------------------
	//uiԪ�ر���
	IGUIListBox * msglist;
	IGUIEditBox* editbox;



	u32 last_time;
	bool guieditInput; //�������ui,��س�,��������ģʽ


	MyGUIDlgCharPackage* m_pGUIDlg_charPackage;
	MyGUIDlgCharProp* m_pGUIDlg_charProp;
	MyGUIDlgSysMenu* m_pGUIDlg_sysMenu;
	MyGUIDlgNpcShop* m_pGUIDlg_npcShop;
	MyGUIDlgCharSkill* m_pGUIDlg_skill;
//---------------------------------------------------------
public:

video::ITexture*  tex_HP,*tex_HPBG;
	float blood_per;  //Ѫ�İٷֱ�


video::ITexture* bottom_bar; //����Ŀ����




};
