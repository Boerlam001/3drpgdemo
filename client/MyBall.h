#pragma once

#include "stdafx.h"


/*

  ������

 */


class MyBall  : public video::IShaderConstantSetCallBack
{
public:
	MyBall(	 ISceneNode* parentNode);
	~MyBall(void);

	void update();

	bool init();

	void drop();

	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);

	s32 get();



private:

	//����core����
	IrrlichtDevice* dev;	
	irr::video::IVideoDriver *drv; 
	irr::gui::IGUIEnvironment* ui;
	irr::scene::ISceneManager *smgr; 

	 ISceneNode* parentNode;
	 ISceneNode* sphere;




	 float num;
	 float mAlpha;
};
