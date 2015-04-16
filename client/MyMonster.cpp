#include "StdAfx.h"


#include "mymonster.h"


float MyMonster::getradian(float x,float y)
{
		static float EPSILON=0.0001f;
		if(fabs(x)<=EPSILON&&y>0)return 90.0f;
		if(fabs(x)<=EPSILON&&y<0)return 270.0f;
		if(fabs(y)<=EPSILON&&x>0)return 0.0f;
		if(fabs(y)<=EPSILON&&x<0)return 180.0f;

		float rel = asinf(fabsf(y));
		rel = rel*180.0f / PI;
		if(x>0&&y>0)return rel;
		if(x<0&&y>0)return 180.0f - rel;
		if(x<0&&y<0)return 180.0f + rel;
		if(x>0&&y<0)return 360.0f - rel;

		return 0;
}


MyMonster::~MyMonster(void)
{
	
}

MyMonster::MyMonster( MonsterProperty pp,const c8* filename )
{

	device=getIrrDevice();
	smgr=getIrrSmgr();

	file=filename;


	yrot=90.0f;	//Ĭ����ת-90��

	movespeed=0.35;
	 //��ʱ��
	 timer=device->getTimer();
	 lasttime=timer->getRealTime();
lastattacktime=timer->getRealTime();
//------------------------------------------------------------------------------------------------------
	setMonsterProperty(pp);	 
		//prop.ID=pp.ID;
	 // prop.pos=pp.pos; //λ��
	 // prop.worldMap_id=pp.worldMap_id;
	 // prop.rot=pp.rot;
	 // prop.currState=pp.currState;	//Ĭ�Ͻ�ɫ����
	 // prop.MAX_HP=pp.MAX_HP;
	 // prop.HP=pp.HP;	    //���ﵱǰhp
	 // prop.Attack=pp.Attack;	//������
	 // prop.Defense=pp.Defense;		//������
	 // prop.isDeath=pp.isDeath;;		//�Ƿ�����

	 // lastState=prop.currState;
	
//-----------------------------------------------------------------------------------------------------

	  isdrop=false;

	  node=0;
	  m_pgHealthBar=0;

}

//����ģ����ת��,���ڽ���ģ�Ͳ���Ӧ
void MyMonster::SetInitRotValue(float rot)
{
	yrot=rot;
}

void MyMonster::Draw()
{	
	   //����
	
		node=smgr->addAnimatedMeshSceneNode(smgr->getMesh(file));
		//if(picpath) node->setMaterialTexture(0,device->getVideoDriver()->getTexture(picpath));
		node->getMaterial(0).SpecularColor.set(0,0,0,0);//��ɫ
		node->setMaterialFlag(video::EMF_LIGHTING, false);//������
		node->setScale(core::vector3df(0.80f,0.80f,0.80f));//ģ������
		node->setMaterialFlag(video::EMF_ANTI_ALIASING,true);//���������
	//	node->setDebugDataVisible(scene::EDS_BBOX);
		node->setAnimationSpeed(10);
		node->getMaterial(0).NormalizeNormals=true;
		node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
		node->setPosition(prop.pos);



		//��ģ�ʹ�����������ѡ����������ڳ�����ײ��������ʰȡģ��
		scene::ITriangleSelector* selector;		//��ײѡ����
		selector= smgr->createTriangleSelector(node);
		node->setTriangleSelector(selector);//����ѡ����


		node->setFrameLoop(1, 19);


//��ʼ��Ѫ��
m_pgHealthBar =new irr::scene::VxHealthSceneNode( 
this->node, // parent node 
smgr, // scene manager 
-1, // id 
smgr->getSceneCollisionManager(), // collision manager 
50, // width 
6, // height 
core::vector3df(0,20,0), // position 
video::SColor(255,0,200,0), // bar color 
video::SColor(255,220,0,0), // background color 
video::SColor(255,255,255,255) ); // boarder color 
//set percent of health 
s32 per=100*(int)prop.HP/(int)prop.MAX_HP;
//printf("����per%d\n",per);
m_pgHealthBar->setProgress( per );
//-----------------------------------------------------------------------------------------------------



}

//ģ������
void MyMonster::SetScale(float scale)
{
	node->setScale(vector3df(scale,scale,scale));
}

//���ö���
void MyMonster::SetState(int s){

	//��
	if(s==cWalk && prop.currState!=cWalk){
		if(lastState==cWalk){
			return;
		}
		lastState=cWalk;
		node->setLoopMode(true);
		node->setAnimationSpeed(10);//�ؼ�֡�ٶ�
		node->setFrameLoop(2, 20);
	//����
	}else if(s==cDeath && prop.currState!=cDeath){
		if(lastState==cDeath){
			return;
		}
		lastState=cDeath;
		node->setAnimationSpeed(10);//�ؼ�֡�ٶ�
		node->setFrameLoop(91, 103);
		node->setLoopMode(false);
		
	//�Ź���
	}else if(s==cAttack && prop.currState!=cAttack){
		if(lastState==cAttack){
			return;
		}
		lastState=cAttack;
		node->setAnimationSpeed(7);//�ؼ�֡�ٶ�
		node->setFrameLoop(106, 115);
		node->setLoopMode(true);
    //ͷ����
	}else if(s==cAttack2 && prop.currState!=cAttack2){
		if(lastState==cAttack2){
			return;
		}
		lastState=cAttack2;
		node->setAnimationSpeed(7);//�ؼ�֡�ٶ�
		node->setFrameLoop(117, 128);
		node->setLoopMode(true);
	//վ
	}else if(s==cIdle && prop.currState!=cIdle){
		if(lastState==cIdle){
			return;
		}
		lastState=cIdle;
		node->setLoopMode(true);
		node->setAnimationSpeed(10);//�ؼ�֡�ٶ�
		node->setFrameLoop(137, 169);
	}


}



//���ﱻ������ʾ������
void MyMonster::ShowAttackTextNum(int num)
{
	//��ʾ�������˶���Ѫ,0�Ļ�����ʾmiss
	MyCharAttackNumTextShow shownumtext(node->getPosition(),num);

}

//�������ܹ���,�����ǹ���ֵ
void MyMonster::UnderAttack(unsigned int attack)
{

	//������С�ڷ�����...
	if(attack<=prop.Defense){
		//��ʾ�������˶���Ѫ,0�Ļ�����ʾmiss
		MyCharAttackNumTextShow shownumtext(node->getPosition(),0);

		return;
	}

	//�������˺�ֵ,ֻ���͸�������������ĳ�˿��˹���.

	prop.cmd=MonsterCMD_UnderAttack;
	printf("����%d�ܹ���\n",prop.ID);
	cnet->SendMsg((char*)&prop,sizeof(MonsterProperty));


	if(prop.HP<=0){
	//		m_puser->GainExp(50);//��һ�þ���
		prop.isDeath=true;
		SetState(cDeath);	//�������������ñ�ǺͶ���
	
	}



}

void MyMonster::UIRender()
{
	if(m_pgHealthBar && node->isVisible()) this->m_pgHealthBar->render();
}



void MyMonster::Update()
{

	if(node==0) return;

		if(prop.isDeath)
		{
			//printf("��������!\n");
			SetState(cDeath);
			return ;
		}

		//��ɫ����������������

		  
			node->setPosition(prop.pos);
			node->setRotation(prop.rot);


			//����Ѫ��
			//ͳ��hp�ٷֱ�
			s32 per=100*((float)prop.HP/(float)prop.MAX_HP);
			this->m_pgHealthBar->setProgress(per);

			if(prop.currState==cWalk){
				prop.currState=-1;
				SetState(cWalk);
			}else if(prop.currState== cIdle ){
				prop.currState=-1;
				SetState(cIdle);
			}else if(prop.currState== cAttack ){
				prop.currState=-1;
				SetState(cAttack);
			}else if(prop.currState== cAttack2 ){
				prop.currState=-1;
				SetState(cAttack2);
			}


}
void MyMonster::OnAnimationEnd(IAnimatedMeshSceneNode* node)
{

}

void MyMonster::drop()
{
	isdrop=true;

	if(node==0) return;
	
	scene::ISceneNodeAnimator* anim;		
	node->addAnimator(anim=smgr->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�,�����ڵ�
	anim->drop();

}

void MyMonster::setMonsterProperty(MonsterProperty p){
	  memcpy(   (char*)&prop,(char*)&p,sizeof(MonsterProperty));

}

/*
  ����ɳ����Ч��
 */
void MyMonster::AddGhostFlyEffect()
{
  	IBillboardSceneNode* ghost = smgr->addBillboardSceneNode(0, core::dimension2d<f32>(10, 40));
	ghost->setMaterialFlag(video::EMF_LIGHTING, false);
	ghost->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);//EMT_TRANSPARENT_ALPHA_CHANNEL  EMT_TRANSPARENT_ADD_COLOR
	ghost->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("ghost/sc_ghost.tbj"));

	scene::ISceneNodeAnimator* a = 0;
	vector3df p=node->getPosition();
	//�Ϸ�
	a = smgr->createFlyStraightAnimator (p,p+vector3df(0,250,0),4000);
	ghost->addAnimator(a);
	
	//4.5��ɾ��
	a=smgr->createDeleteAnimator(4500);
	ghost->addAnimator(a);

	a->drop();
}
