

//************************************************************************/
// 
//		������
//		
//
/************************************************************************/


#pragma once

#include "NetClient.h"

#include "VxHealthSceneNode.h"

#include "mycharattacknumtextshow.h" //��������Ѫ��

#include<time.h> //ʹ�������




#include "MyCharacter.h"
class MyCharacter   ;

class MyMonster : public irr::scene::IAnimationEndCallBack  
{
public:



	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node) ;

	~MyMonster(void);

	MyMonster( MonsterProperty prop,const c8* filename);

	void SetPosition(core::vector3df  pos); 
	void SetScale(float  scale);

	void SetMonsterId(int id){prop.ID=id;};
	int	 GetMonsterId(){return prop.ID;};

	bool IsDead(){return prop.isDeath;};

	//���ﱻ������ʾ������
	void ShowAttackTextNum(int num);

	//����
	Socket::CNetClient* cnet;
	//����,���͸���������
	void SetNetServer(Socket::CNetClient* net)
	{
		cnet=net;
	};

	void Draw();
	void UIRender();
	void drop();
	void Update();
	void UnderAttack(unsigned int attack);	//�������ܹ���,�����ǹ���ֵ
	void attack();
	void SetState(int s);

	void SetInitRotValue(float rot);
	scene::IAnimatedMeshSceneNode* GetNode(){return node;};


	void AddGhostFlyEffect();

	MonsterProperty* getMonsterProperty(){return &prop;};


	void setMonsterProperty(MonsterProperty p);

	void setMonsterHP(int hp){prop.HP=hp;};

	void setMonsterCMD(char cmd){prop.cmd=cmd;};

	void setMonsterDamage(int damage){prop.damage=damage;};


	 VxHealthSceneNode* getHPBar(){return m_pgHealthBar;}; //�õ�hpѪ��

	 core::line3d<f32> line;//��ײ��

	 bool isdrop; //��־�Ƿ���������ѵ�����drop
private:
	IrrlichtDevice *device;						//����ָ��c
	scene::ISceneManager* smgr;					//��������

	core::vector3df Node_scale;					//���ű���

	scene::IAnimatedMeshSceneNode* node;		//�����ڵ�
	

	MonsterProperty prop;

	const c8* file;							


	float movespeed;	//�ƶ��ٶ�

	float yrot;				//������y����ת�Ƕ�



	ITimer* timer;
	u32 lasttime;
	u32 lastattacktime;

	int lastState;//����״̬

	irr::scene::VxHealthSceneNode* m_pgHealthBar;  //��ʾhp

	float getradian(float x,float y);
};
