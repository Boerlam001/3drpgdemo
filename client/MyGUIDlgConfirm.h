#pragma once

#include "stdafx.h"


/************************************************************************/
// 
//		�Ի�����.ѡ��Ի��� yes,no������
//		
//
/************************************************************************/


class MyGUIDlgConfirm
{
public:
	MyGUIDlgConfirm();
	~MyGUIDlgConfirm(void);

	void OnEvent (const irr::SEvent& e);
	void update();//����
	void drawAll();
	bool LoadGUI();

	void ShowDlg(bool v); 

	//�����gui������
	bool mouseInGui;
private:
   irr::IrrlichtDevice *dev;
   irr::video::IVideoDriver *drv; 
   irr::scene::ISceneManager *smgr; 
   irr::gui::IGUIEnvironment* ui;

   gui::IGUIButton* btn_yes,*btn_no;
   gui::IGUIWindow* win ;

   //�������
   vector2d<s32> cursor;

};
