#pragma once



/************************************************************************/
// 
//		 ϵͳ�˵��� ��ESC����. ģʽ�Ի���
//		
//
/************************************************************************/


#include "stdafx.h"
#include "MyGUIDlgConfig.h"  //����gui���Դ���



class MyGUIDlgSysMenu
{
public:
	MyGUIDlgSysMenu( );
	~MyGUIDlgSysMenu(void);


void OnEvent (const irr::SEvent& e);
void update();//����
void drawAll();
bool LoadGUI();

bool mouseInGui;
private:
	irr::IrrlichtDevice *dev;
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;


	MyGUIDlgConfig* config_dlg;

	gui::IGUIWindow* win ;

};
