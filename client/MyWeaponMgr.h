#pragma once


#include "myweapon.h"



/************************************************************************/
// 
//		����������.. �ɽ�ɫ�ڲ�ʹ��.����Ҫ�ͽ�ɫ���໥����.�����ڽ�ɫ��hһ����
//		
//
/************************************************************************/



class MyWeaponMgr
{
public:
	MyWeaponMgr(IAnimatedMeshSceneNode* parentNode);
	~MyWeaponMgr(void);

	//ж����������
	void DropAll();

	//�л�����
	void ChangeWeapon(int id,int param1);

	//���ݽ�ɫ״̬����������ʾ
	void update(int state );
	void updateUseLastState();

	void setWeaponVisible(bool v);

	//Ϊ��ǰ����ʹ��hlslЧ��
	void OpenHlslEffect(bool use,int weaponType);

	//��ѯ�Ƿ���ʹ��hlslЧ��
	bool IsOpenHlslEffect(){return isusehlsleffect;};

	MyWeapon* getHandWeapon(){return handweapon;};
	MyWeapon* getBackWeapon(){return backweapon;};


	int getCurWeaponId(){return currentWeaponid;};

	void MyWeaponMgr::setParentNode(IAnimatedMeshSceneNode* p);
private:
	IrrlichtDevice* device;
	irr::video::IVideoDriver *drv; 
	ISceneManager* smgr ;

	IAnimatedMeshSceneNode* parentNode;

	//�����ɫ״̬
	int state;
	//�������
	int currentWeaponid;
	int currparam1;

	MyWeapon* handweapon;//��
	MyWeapon* backweapon;//��

	bool isusehlsleffect; //�Ƿ���ʹ��hlslЧ��

};
