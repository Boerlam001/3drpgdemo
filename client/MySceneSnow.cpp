#include "StdAfx.h"
#include ".\myscenesnow.h"

MySceneSnow::MySceneSnow( ICameraSceneNode* c)
{
	device=getIrrDevice();
	cam=c;

	x_offset=0;
	y_offset=0;

	snow_downspeed=-0.16f;

		// ���� ����ϵͳ	
	
		ps = device->getSceneManager()->addParticleSystemSceneNode(false); //����һ������ϵͳ,��ʹ���Զ���ķ�����
		ps->setPosition(c->getPosition()+vector3df(0,50,0));//λ��
		//ps->setScale(core::vector3df(2,2,2));//����
		ps->setParticleSize(core::dimension2d<f32>(1.0f, 2.0f));//�������Ӵ�С
		////�������ӷ�����
		 em = ps->createBoxEmitter(
			core::aabbox3d<f32>(-400,-400,-400,400,400,400),//���ú��ӵ�6������
			core::vector3df(0.0f,snow_downspeed,0.0f),//���÷��䷽����ٶ�
			500,700,//ÿ����С������80,���100
			video::SColor(0,0,0,0), video::SColor(0,255,255,255),//��ʼ��ɫ�ͽ�����ɫ
			1000,1000);//���ʱ��,800-2000����
		ps->setEmitter(em);//����ϵͳ���÷�����
		em->drop();

		scene::IParticleAffector* paf =ps->createFadeOutParticleAffector();
		ps->addAffector(paf);
		paf->drop();

		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, device->getVideoDriver()->getTexture("textures/flare.bmp"));
		ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

MySceneSnow::~MySceneSnow(void)
{
}

void MySceneSnow::setVisible(bool v)
{
   ps->setVisible(v);
}

/*
  ������ѩ״̬,������ѩ����,��ѩ������λ��
 */
void MySceneSnow::Update()
{
	
	ps->setPosition(cam->getPosition() + vector3df(0,50,0));//λ��

	vector3df dir=cam->getTarget()-cam->getPosition();

//ָ�����������

     int RANGE_MIN = -3;
     int RANGE_MAX = 3;
	 int i;
     for (i = 0;    i < 3; i++ )
     {
         float rand100 = (((double) rand() / 
                         (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);
     //    printf( "  %6d\n", rand100);
		 
		 //���ƫ�Ʒ���
		 if(i==0) dir.X+=rand100;
		 if(i==1) dir.Y+=rand100;
		 if(i==2)  dir.Z+=rand100;
     }

	
	dir.normalize();
	

	//�������䷽��
	  em->setDirection(dir);
	
	
}



void MySceneSnow::drop()
{
    ps->removeAllAffectors();
	ps->removeAll();
	ps->remove();
}