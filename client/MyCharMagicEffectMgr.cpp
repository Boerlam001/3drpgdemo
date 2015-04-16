#include ".\mycharmagiceffectmgr.h"

namespace Magic
{


MyCharMagicEffectMgr::MyCharMagicEffectMgr(void)
{
}

MyCharMagicEffectMgr::~MyCharMagicEffectMgr(void)
{
}

//���һ��ħ����Ч
void MyCharMagicEffectMgr::AddMagic(int e ,ISceneNode* parenetNode,vector3df pos,float speed,vector3df rot,ITexture* tex )
{
	if(e==FollowCircle){
		Magic::IMyCharMagicEffect* m=new Magic::MyCharMagicEffect1();
		m->init(parenetNode,pos,speed);

		magic_list.push_back(m);
	}else if(e==FollowPlane){
			Magic::IMyCharMagicEffect* magic=new Magic::MyCharMagicEffect2(rot);
		magic->init(parenetNode,pos,speed,tex);
		magic_list.push_back(magic);
	}

}

//��Ч����
void MyCharMagicEffectMgr::update()
{
	irr::core::list<Magic::IMyCharMagicEffect*>::Iterator  list_oper;
	for(list_oper=magic_list.begin();list_oper!=magic_list.end();++list_oper)
	{
		Magic::IMyCharMagicEffect* magic=*list_oper;
		magic->update();
	}

}


//��Чɾ��
void MyCharMagicEffectMgr::drop()
{
	irr::core::list<Magic::IMyCharMagicEffect*>::Iterator  list_oper;
	for(list_oper=magic_list.begin();list_oper!=magic_list.end();++list_oper)
	{
		Magic::IMyCharMagicEffect* magic=*list_oper;
		magic->drop();
		delete magic;
		magic=0;
	}

	magic_list.clear();

}



} // end namespace