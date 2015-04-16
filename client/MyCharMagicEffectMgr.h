#pragma once
#include "stdafx.h"

#include "MyCharMagicEffect.h"
#include "MyCharMagicEffect2.h"


namespace Magic
{

/************************************************************************/
// 
//		��Ч������.�����Ч,ɾ����Ч,
//		
//
/************************************************************************/


#define FollowCircle 1  //�����ɫ������ ��Ȧ��
#define FollowPlane 2   //�����ɫ����.  ֻ����ת��.




class MyCharMagicEffectMgr
{
public:
	MyCharMagicEffectMgr(void);
	~MyCharMagicEffectMgr(void);

	//���һ��ħ����Ч
	void AddMagic(int effect,ISceneNode* parenetNode,vector3df pos,float speed,vector3df rot ,ITexture* tex);

	void update();

	void drop();


private:

	irr::core::list<IMyCharMagicEffect*> magic_list;//����ħ����Ч��


};

}// end namespace
