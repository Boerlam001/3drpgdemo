#pragma once


#include<stdlib.h> 
#include<stdio.h> 
#include<time.h>

/************************************************************************/
// 
//		��ѩЧ����  
//					//��ʼ����ѩ	Snow=new MySnowEffect(dev,camera);
//						���·���			Snow->Update();
//
/************************************************************************/


class MySceneSnow
{
public:
	MySceneSnow(ICameraSceneNode* cam);
	~MySceneSnow(void);
	
	void drop();

	void Update( );

	void setVisible(bool v);

private:

	irr::IrrlichtDevice *device;
	scene::IParticleSystemSceneNode* ps ;//����ϵͳ

	//����� ����ѩʼ�ճ������������Ŀ�괵
	ICameraSceneNode* cam;

	////�������ӷ�����
	scene::IParticleEmitter* em;

	

	float x_offset,y_offset;//
	float snow_downspeed;
};
