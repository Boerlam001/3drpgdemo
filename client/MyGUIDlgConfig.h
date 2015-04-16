#pragma once



/************************************************************************/
// 
//		 gui���ô���   ��ESC����ϵͳ�˵�,�д��� "gui����"
//		
//
/************************************************************************/

#include "stdafx.h"



class MyGUIDlgConfig
{
public:
	MyGUIDlgConfig();
	~MyGUIDlgConfig(void);


	void OnEvent (const irr::SEvent& e);
	void update();//����
	void drawAll();
	bool LoadGUI();

	//��ʾ����
	void ShowDlg(bool fl);

	bool mouseInGui;
private:
	irr::IrrlichtDevice *dev;
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;



	gui::IGUIWindow* win ;
};
