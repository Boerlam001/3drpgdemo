#pragma once
#include "stdafx.h"

/************************************************************************/
// 
//		 npc�̵���� ��ʾnpc���۵���Ʒ.�����Ʒ�͹�����
//		
//
/************************************************************************/

#include "MySceneManager.h"

class MySceneManager;
class MyGUIDlgNpcShop
{
public:
	MyGUIDlgNpcShop(	MySceneManager* mgr);
	~MyGUIDlgNpcShop(void);


	void OnEvent (const irr::SEvent& e);
	void update();//����
	void drawAll();

	void ShowDlg(bool fl);

	char* getItemNameById(int itemID);

	bool LoadGUI();
	//����������
	bool mouseInGui;

	void setShopPackage(ShopPackage* pk)
	{
		memset((char*)&shop,0,sizeof(ShopPackage));
		memcpy((char*)&shop,(char*)pk,sizeof(ShopPackage));
	}

		gui::IGUIWindow* win ;

private:

		void draw2dImage(int row,int col,rect<s32> re);

		void DrawAllItem();

		void DrawItem(rect<s32> re,int itemID);
		//���ʰȡ��Ʒ��
		void SelectItem();

	irr::IrrlichtDevice *dev; 
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;

	//������������
	MySceneManager* mgr;


	ITexture* item_detail;	// ������ʾ��Ʒ��ϸ��Ϣ�Ĵ���
	video::ITexture* items_bg,*item_pic,*item_pic2; //����ͼƬ ���ڰ�����ʾ����ƷͼƬ

	ITexture* items_pic;
	ITexture* xbj_pic; //������


	rect<s32> r;

	u32 alpha;

	vector2d<s32> mouseOnItem;//������ָ������Ʒ.�͸������±� ������ʾ��Ʒ��ϸ��Ϣ mouseOnItem x���� y����..


	//�������
	vector2d<s32> cursor;

	//�̵�ṹ
	ShopPackage shop;
};
