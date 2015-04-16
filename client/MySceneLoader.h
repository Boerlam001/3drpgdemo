#pragma once

#include "stdafx.h"

#include "MysceneSnow.h"

#include "MyNPC.h"

#include "MysceneGrass.h"

#include ".\myscenevolumelight.h"



/************************************************************************/
// 
//		����������  ���ݳ��������ļ����س���
//		
//
/************************************************************************/

class MySceneLoader
{
public:
	MySceneLoader();
	~MySceneLoader(void);

	//����
	bool LoadScene(int id ,ICameraSceneNode* parentNode);

	//�õ����θ߶�
	float getHeight(float x,float z);

	//ж��
	void DropCurrScene();

	void update();

	//��ȡ��ͼ���ƶ������ļ�
	void ReadLevelCollisionFile();

	irr::core::list<irr::core::triangle3df*> mylist;  //list��ѡȡ��������

	scene::IMetaTriangleSelector * getMeta(){return meta;};

	void CalculMeta();

	void RemoveTerrain();


	//���в����ƶ������������,����һ���Ƿ����ڲ����ж�
	bool Pointisin(core::vector3df test );
	//��ɫ�����ƶ���pos��
	bool canmovehere(vector3df pos);



	//���ü��صĳ����Ƿ�ɼ�
	void setVisiable(bool v);

private:

	//�������
	irr::IrrlichtDevice *dev; 
	irr::video::IVideoDriver *drv; 
	irr::scene::ISceneManager *smgr; 


	//�洢��ɫ���ĵ�.����ʹ��camera.��Ϊcamera�����ɫ. gettarget�Ϳ��Եõ���ɫ����,getposition�Ϳ��Եõ����������.��һ����ɫnode����
	ICameraSceneNode* cameraNode;

	//��ǰ�����ͼid
	int currWorldMap; //
	
	float height;

	//����.irr������Ҫ��meta
	scene::IMetaTriangleSelector * meta;

	MySceneVolumeLight* light1;
	MySceneSnow*  Snow; //��ѩ��
	MySceneGrass* grass;
	scene::ISceneNode* skydome;


	MyNPC* m_npc; 
};
