#pragma once

#include "loginHLSLEffect.h"

/************************************************************************/
// 
//		 ������
//		
//
/************************************************************************/

namespace Login
{


class MyWeapon2
{
public:
	MyWeapon2( irr::IrrlichtDevice * device);
	~MyWeapon2(void);
	void drop();

	IAnimatedMeshSceneNode* getNode(){return weaponNode;};
	void setNode(IAnimatedMeshSceneNode* n){weaponNode=n;};
	void ChangeWeapon(int id);
	void setPosition(core::vector3df pos){weaponNode->setPosition(pos);}; 
	
	s32 newMaterialType1 ;//hlsl����
	s32 oldMaterialType; //�������������
	void setUseHLSL(bool b,bool transparentMeta , int weaponType); //�����Ƿ�ʹ��hlsl weaponType��ʾ��������������
	bool getUseHLSL(){return usehlsl;}; //�õ��Ƿ�ʹ��hlsl
	void AddLight();

	LoginHLSLEffect* getEffect(){return effect;};

	void useParticleEffect();

	void update();

		scene::IParticleSystemSceneNode* ps ;//����ϵͳ
private:
	IrrlichtDevice* device;
    irr::video::IVideoDriver *drv; 
	ISceneManager* smgr ;

	scene::IAnimatedMesh* weaponmesh;						//����mesh
	scene::IAnimatedMeshSceneNode* 	weaponNode;				//�����ڵ�
	int weaponType; //����Ч������

LoginHLSLEffect* effect; //Ч����

	bool usehlsl;

	ISceneNode*Plane;

	////�������ӷ�����
	scene::IParticleEmitter* em;

public:
	void useBillboard(void);
};

}