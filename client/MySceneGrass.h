#pragma once

#include "stdafx.h"


/************************************************************************/
// 
//		�����Ĳ�
//		
//
/************************************************************************/


class MySceneGrass
{
public:
	MySceneGrass( int worldMap);
	~MySceneGrass(void);

	void DrawAllGrass();
	void drop();

	void setVisible(bool v);

private:
	IrrlichtDevice* device;
	irr::core::list<irr::core::vector3df> mylist;  //list��Ҫˢ�Ĳ�����

	irr::core::list<irr::scene::IAnimatedMeshSceneNode*> mygrass_list; //�洢����grass

	void ReadFile();
	void DrawAGrass(vector3df pos);

	//�ݵ������ĸ������ͼ��
	int worldMap;

	//����ݵ�ģ��·��
	char grass_model_path[255];
	//�ݵطֲ���������б��ļ�·��
	char grass_list_path[255];

	bool m_bUseGrass; //��ͼ�Ƿ�ʹ���˲ݵ�
};
