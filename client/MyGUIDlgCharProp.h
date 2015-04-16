#pragma once



/************************************************************************/
// 
//		��ɫ���������  ��C����
//		
//
/************************************************************************/

#include "stdafx.h"
#include "MySceneManager.h"





class MyGUIDlgCharProp
{
public:
	MyGUIDlgCharProp( MySceneManager* mgr);
	~MyGUIDlgCharProp(void);

	void OnEvent (const irr::SEvent& e);
	void update();//����
	void drawAll();

	bool LoadGUI();

	//����������
	bool mouseInGui;

private:
	//������������
	MySceneManager* mgr;

	irr::IrrlichtDevice *dev; 
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;


	//�������
	vector2d<s32> cursor;




	gui::IGUIWindow* win ;
	IGUIButton* addpoint_1;
	IGUIButton* addpoint_2;
	IGUIButton* addpoint_3;
	
	rect<s32> win_rect;

	u32 alpha; //gui��͸���� 

	ITimer* m_timer;
	u32 lasttime;
};

