#pragma once

#include "../stdafx.h"


/************************************************************************/
// 
//		��½ʱ�� ��ɫ��װģ�͹����� ����ɫ��װ��3���� ����+�ֱ� ���� Ь��
//		
//
/************************************************************************/
namespace Login
{

class MyLoginCharClothMgr
{
public:
	MyLoginCharClothMgr( irr::IrrlichtDevice * device,int id ,int charType); //1�ǽ�ɫsock ��ʶ 2�ǽ�ɫ���� �� Ů

	~MyLoginCharClothMgr(void);

	void setClothVisible(bool v);

	//���������˫��
	bool LoadBody(int id);

	//���ؿ���
	bool LoadTrousers(int id);

	//����Χ��
	bool LoadDress(int id);

	//����Ь��
	bool LoadShoes(int id);

	//������body������
	void setPosition(vector3df pos);
	void setRotation(vector3df rot);
	vector3df getPosition( );
	vector3df getRotation( );
	vector3df getAbsolutePosition();

	//������
	void Animate(int speed,int start,int end ,bool loop);

	//�õ���ɫ��node
	IAnimatedMeshSceneNode* getRootNode(){return root;};

	//ж�����н�ɫ��װ��ģ��
	void DropAll();


private:
	
	//��ɫΨһ�ı�־
	int char_id;

	//��ɫ�Ա�
	int charSex;

	char modelPath[255];

	//���ڵ�
	IAnimatedMeshSceneNode* root;

	//��ɫ��node
	IAnimatedMeshSceneNode* body;     


	//����
	IAnimatedMeshSceneNode* trousers;

	//Ь��
	IAnimatedMeshSceneNode* shoes;

	//Χ���ӵ�Χ��
	IAnimatedMeshSceneNode* dress;

	//���浱ǰ�����Ĺؼ�֡ ����,�����ٴμ�������ģ��ʱ��ȡ
	int currStart,currEnd,speed;
	bool m_bloop;

	//����core����
	IrrlichtDevice* dev;					
	ISceneManager* smgr;
};


}