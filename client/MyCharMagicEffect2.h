#pragma once
#include "stdafx.h"

#include "IMyCharMagicEffect.h"

/************************************************************************/
// 
//		ħ��Ч��.Բ���� һ����.����һ��Բͼ��.��͸����.hlsl��ɫ�仯
//		
//
/************************************************************************/



namespace Magic
{

class MyCharMagicEffect2  : public IMyCharMagicEffect
{
public:
	MyCharMagicEffect2(vector3df rotspeed);
	~MyCharMagicEffect2(void);


	void update();

	bool init(ISceneNode* parentNode,vector3df pos, float speed, ITexture* tex);

	void drop();

	 virtual void setParentNode(ISceneNode* parentNode);

	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);

	s32 get();

	ISceneNode* parentNode;
private:

	float RandNum2(float  begin,float end,float vlaue);


	//����core����
	IrrlichtDevice* dev;	
	irr::video::IVideoDriver *drv; 
	irr::gui::IGUIEnvironment* ui;
	irr::scene::ISceneManager *smgr; 

	ITexture* tex;
	scene::IAnimatedMeshSceneNode* node;
	float speed;

	vector3df pos;

	vector3df rotspeed;

	float num;
	float mAlpha;


};


} // namespace Magic