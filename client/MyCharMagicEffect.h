#pragma once
#include "stdafx.h"


#include "IMyCharMagicEffect.h"


/************************************************************************/
// 
//		ħ��Ч��.Χ�ƽ�ɫ������
//		
//
/************************************************************************/


namespace Magic
{

class MyCharMagicEffect1  : public IMyCharMagicEffect
{
public:
	MyCharMagicEffect1();
	~MyCharMagicEffect1(void);

	void update();

	bool init( ISceneNode* parentNode,vector3df pos, float speed,ITexture* tex);

	void drop();

	void setParentNode(ISceneNode* parentNode);



	void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);

	s32 get();

	ISceneNode* parentNode;
private:

	float RandNum2(float  begin,float end,float vlaue);


	//����core����
	IrrlichtDevice* dev;	
	irr::video::IVideoDriver *drv; 
	irr::gui::IGUIEnvironment* ui;
	irr::scene::ISceneManager *smgr; 

	scene::IParticleSystemSceneNode* ps ;//����ϵͳ


	scene::IAnimatedMeshSceneNode* node;
	vector3df pos;
	 ITexture* tex;
	 float speed;

	float num;
	float mAlpha;




};


} // namespace Magic