#pragma once

#include "stdafx.h"

/*
  
  �����˳��������

 
 1.��ʼ�� 
  // setup the camera 
 myCamera=new My3rdCamera(dev,rolenode); //����device��Ҫ����Ľ�ɫ�ڵ�
 
 2.�����¼�
 ��
bool Core::OnEvent (const SEvent& e) { 
	if(myCamera) myCamera->OnEvent(e); //�����¼���camera�ﴦ��

	   
        return false; 
} 


 3.ѭ������
 
	while (dev->run () && !quit) { 
                if (dev->isWindowActive ()) { 

					    myCamera->Run(); //����camera
                        drv->beginScene (true, true, SColor (150, 50, 50, 50)); 
                        smgr->drawAll (); ...
                        drv->endScene (); ...
                } 
        } 
 */



class My3rdCamera
{
public:
	My3rdCamera(scene::IAnimatedMeshSceneNode* rolenode);

	//����Ŀ��ڵ�.���ú��˺�,�Ϳ�����ת�鿴�ڵ���
	void setTargetNode(scene::IAnimatedMeshSceneNode*r){rolenode=r;};
	
	~My3rdCamera(void);
    bool OnEvent (const irr::SEvent& e);
	void update();
	ICameraSceneNode* 	getNode(){return myCamera;};

	f32 getcameraDistance(){return cameraDistance;};
private:
	
    ICameraSceneNode* myCamera;
	scene::IAnimatedMeshSceneNode* rolenode;	//Ҫ����Ľ�ɫ�ڵ�

	// camera registry 
	f32 cameraOrbit ;
	f32 cameraAngle ;
	f32 cameraDistance ;
	f32 cameraOrbitOld ;
	f32 cameraAngleOld ;

	// player registry 
	f32 playerX ;
	f32 playerY ;
	f32 playerZ ;
	f32 playerCompass ;
	f32 playerTurnTo ;
	f32 playerTurnSpeed ;
	f32 playerMoveSpeed ;

	bool smooth;
	//Ŀ��߶�
	float  target_Height;
	float lasty;

	// keyboard registry 
	bool keys[irr::KEY_KEY_CODES_COUNT];
	    
	// mouse registry 
	bool mouseDownL; 
	bool mouseDownM; 
	bool mouseDownR;
	f32 lastWheelMovement;
	position2d<f32> cursor;
	position2d<f32> cursorOld;
	position2d<f32> cursorDelta;

	vector3df My3rdCamera::sphericalXYZ(f32 compassAngle, f32 elevationAngle, f32 radius);
};
