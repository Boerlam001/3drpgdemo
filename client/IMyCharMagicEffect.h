#pragma once

#include "stdafx.h"



namespace Magic
{


class IMyCharMagicEffect  : public video::IShaderConstantSetCallBack
{
public:

    virtual bool init( ISceneNode* parentNode=0, //Ч������ĸ��ڵ�.
					   vector3df pos=vector3df(0,0,0), //��������.
					   float speed=0, //�ٶ�
					   ITexture* tex=0  //������Ч������
					
		) =0;
    virtual void update() =0;
    virtual void drop() =0;
	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)=0;

	virtual void setParentNode(scene::ISceneNode* parentNode=0)=0;

};


} // end namespace