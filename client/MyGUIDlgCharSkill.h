#pragma once

#include "stdafx.h"



/************************************************************************/
// 
//		 ��ɫ������� ��K����
//		
//
/************************************************************************/

#include "MySceneManager.h"


class MyGUIDlgCharSkill
{
public:
	MyGUIDlgCharSkill( MySceneManager* mgr);
	~MyGUIDlgCharSkill(void);
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


	rect<s32> win_rect;

	u32 alpha; //gui��͸���� 

	ITimer* m_timer;
	u32 lasttime;




};
