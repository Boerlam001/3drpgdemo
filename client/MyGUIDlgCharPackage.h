#pragma once





/************************************************************************/
// 
//		 ��ɫ������� ��I����
//		
//
/************************************************************************/



#include "stdafx.h"
#include "MySceneManager.h"

class MySceneManager;


class MyGUIDlgCharPackage
{
public:
	MyGUIDlgCharPackage(	MySceneManager* mgr);
	~MyGUIDlgCharPackage(void);
	void OnEvent (const irr::SEvent& e);
	void update();//����
	void drawAll();

	bool LoadGUI();

	//��ʾ����
	void ShowDlg(bool  v)
	{
	  win->setVisible(v);
	  //��ǰ��
	  ui->setFocus(win);
	}


	void DrawItem(rect<s32> re,int itemID);
	void DrawAllItem();

	//����������
	bool mouseInGui;
private:

	//�洢��ѡ�����Ʒa,b��,���±�,��ֵ����ʱ����
	void MyGUIDlgCharPackage::StorePackItemValue(int a,int b);
	//��ѡ�����Ʒ����ʱ�������ð�a,b���еİ�����
	void MyGUIDlgCharPackage::UseStorePackItemValue(int a,int b);


	 
	irr::IrrlichtDevice *dev; 
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 
	irr::gui::IGUIEnvironment* ui;

//������������
	MySceneManager* mgr;


	gui::IGUIWindow* win ;
	IGUIStaticText* money_text;

	//��ɫ������
	rect<s32> CurWeaponRect;

	//��ɫ��װ��
	rect<s32> CurClothRect;


	//�������
	vector2d<s32> cursor;


	//��¼�����������Ʒ�±�
	int drop_x,drop_y;

	//����Ʒ��ͼƬ
	ITexture* items_pic;

	video::ITexture* items_bg; //����ͼƬ ���ڰ�����ʾ����ƷͼƬ
	video::ITexture* item_pic,*item_pic2;
	ITexture* xbj_pic; //������

public:
	int selectedItemId; //���汻ѡ���˵���Ʒid
private:
	
	bool selectedItemBox; //�Ƿ����ѡ����ĳװ����.������һ����.������������
	int selectedItemparam1,selectedItemparam2,selectedItemparam3,selectedItemparam4,selectedItemparam5,selectedItemparam6; //���汻ѡ���˵���Ʒparam1
	int sel_x,sel_y; //�����ϴα�ѡ���������
	irr::core::rect<s32> r; //����װ�����ڵľ���rect

	u32 alpha; //gui��͸���� 

	//���ṹ
	Package pack;

	vector2d<s32> mouseOnItem;//������ָ������Ʒ.�͸������±� ������ʾ��Ʒ��ϸ��Ϣ mouseOnItem x���� y����..
	ITexture* item_detail;	// ������ʾ��Ʒ��ϸ��Ϣ�Ĵ���

	char* MyGUIDlgCharPackage::getItemNameById(int itemid);

protected:
	void draw2dImage(int row,int col,rect<s32> re);
	void SelectItem();
};
