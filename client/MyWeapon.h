#pragma once

#include "MyHLSLEffect.h"

/************************************************************************/
// 
//		 ������
//		
//
/************************************************************************/


class MyWeapon
{
public:
	MyWeapon( );
	~MyWeapon(void);
	void drop();

	IAnimatedMeshSceneNode* getNode(){return weaponNode;};
	void setNode(IAnimatedMeshSceneNode* n){weaponNode=n;};
	void ChangeWeapon(int id);
	void setPosition(core::vector3df pos){weaponNode->setPosition(pos);}; 
	void HLSL();//ʹ��hlsl
	s32 newMaterialType1 ;//hlsl����
	s32 oldMaterialType; //�������������
	void setUseHLSL(bool b,bool transparentMeta , int weaponType); //�����Ƿ�ʹ��hlsl weaponType��ʾ��������������
	bool getUseHLSL(){return usehlsl;}; //�õ��Ƿ�ʹ��hlsl
	void AddLight();


	void useBillboard(void);

	MyHLSLEffect* getEffect(){return effect;};

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

MyHLSLEffect* effect; //Ч����

	bool usehlsl;


	////�������ӷ�����
	scene::IParticleEmitter* em;

};
