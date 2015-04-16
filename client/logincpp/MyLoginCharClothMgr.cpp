
#include "mylogincharclothmgr.h"

namespace Login
{


MyLoginCharClothMgr::MyLoginCharClothMgr(irr::IrrlichtDevice * device,int char_id ,int charSex)
{
	dev=device;
	smgr=dev->getSceneManager();

	this->char_id=char_id;
		

	body=0;
	trousers=0;
	dress=0;
	shoes=0;


	this->charSex=charSex;
	if(charSex==1){
		sprintf(modelPath,"man");
	}
	else if(charSex==2) {
		sprintf(modelPath,"girl");
	}

	


}

void MyLoginCharClothMgr::setClothVisible(bool v)
{

	if(body){
		body->setVisible(v); 
	}

	if(dress){
		dress->setVisible(v); 
	}

	if(trousers){
		trousers->setVisible(v); 
	}

	if(shoes){
		shoes->setVisible(v); 
	}
}

MyLoginCharClothMgr::~MyLoginCharClothMgr(void)
{
}

void MyLoginCharClothMgr::setPosition(core::vector3df pos)
{
      root->setPosition(pos); 
}

vector3df MyLoginCharClothMgr::getAbsolutePosition()
{
   return root->getAbsolutePosition(); 
}

vector3df MyLoginCharClothMgr::getPosition( )
{
	return root->getPosition(); 
}

void MyLoginCharClothMgr::setRotation(vector3df rot)
{
	  root->setRotation(rot); 
}

vector3df MyLoginCharClothMgr::getRotation()
{
	return root->getRotation(); 
}

//����
bool MyLoginCharClothMgr::LoadBody(int id)
{
	char strrootmesh[255]="";
	sprintf(strrootmesh,"%s//%d//root.ms3d",modelPath,id);

	root=smgr->addAnimatedMeshSceneNode(smgr->getMesh(strrootmesh));

	root->setScale(core::vector3df(0.2,0.2,0.2));//ģ������
	root->setAnimationSpeed(11);
	root->setLoopMode(false); 
	root->setID(char_id); //����id
	root->setFrameLoop(21,22);


	char strmesh[255]="";
	sprintf(strmesh,"%s//%d//body.ms3d",modelPath,id);

	//����Ѽ��ع�������Ь��,�����Ƴ�
	if(body){
		body->removeAll();
		body->remove();
		//scene::ISceneNodeAnimator* anim = 0;
		//shoes->addAnimator(anim=dev->getSceneManager()->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�

	}

	body=smgr->addAnimatedMeshSceneNode(smgr->getMesh(strmesh),root);

	body->setMaterialFlag(video::EMF_LIGHTING, false); //������
	//body->setScale(core::vector3df(0.2,0.2,0.2));//ģ������
	body->getMaterial(0).NormalizeNormals=true;

	body->addShadowVolumeSceneNode(0,0,false);
	smgr->setShadowColor(video::SColor(80,0,0,0));
	body->setID(char_id); //����id
	body->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	body->setMaterialFlag(video::EMF_ANTI_ALIASING,true);//���������

	ITriangleSelector* selector= smgr->createTriangleSelector(body);
	body->setTriangleSelector(selector);//����ѡ����
	////	node->setDebugDataVisible(scene::EDS_BBOX);
	//		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF );
	//	node->setDebugDataVisible(scene::EDS_BBOX ); //������ʾ��Χ��

	body->setAnimationSpeed(speed);
	body->setLoopMode(false); 
	body->setFrameLoop(21,22);
	body->setCurrentFrame(21);


	//����root����.�����Լ���
	ISkinnedMesh* rootmesh=(ISkinnedMesh*)root->getMesh();
	ISkinnedMesh* bodymesh=(ISkinnedMesh*)body->getMesh();
//	bool ret=bodymesh->useAnimationFrom(rootmesh);



	//ÿ�ζ�Ҫ����Χ��.
//	LoadDress(id);

	return true;
}

//����
bool MyLoginCharClothMgr::LoadTrousers(int id)
{
	char strmesh[255]="";
	sprintf(strmesh,"%s//trousers%d.ms3d",modelPath,id);

	//����Ѽ��ع�������Ь��,�����Ƴ�
	if(trousers){
		trousers->removeAll();
		trousers->remove();
		//scene::ISceneNodeAnimator* anim = 0;
		//shoes->addAnimator(anim=dev->getSceneManager()->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�

	}

	trousers = smgr->addAnimatedMeshSceneNode( smgr->getMesh(strmesh) ,root);
	trousers->setMaterialFlag(video::EMF_LIGHTING, false);//����	
	trousers->setMaterialFlag(video::EMF_ANTI_ALIASING,true);//���������
	ITriangleSelector* selector= smgr->createTriangleSelector(trousers);
	trousers->setTriangleSelector(selector);//����ѡ����
	trousers->addShadowVolumeSceneNode(0,0,false);
	trousers->setID(char_id); //����id

	trousers->setAnimationSpeed(speed);
	trousers->setLoopMode(false); 
	trousers->setFrameLoop(21,22);
	trousers->setCurrentFrame(21);


	//����root����.�����Լ���
	ISkinnedMesh* rootmesh=(ISkinnedMesh*)root->getMesh();
	ISkinnedMesh* trousersmesh=(ISkinnedMesh*)trousers->getMesh();
	bool ret=trousersmesh->useAnimationFrom(rootmesh);

	return true;
}

//Χ��
bool MyLoginCharClothMgr::LoadDress(int id)
{
	char strmesh[255]="";
	sprintf(strmesh,"%s//%d//dress.ms3d",modelPath,id);

	dress = smgr->addAnimatedMeshSceneNode( smgr->getMesh(strmesh) );
	dress->addShadowVolumeSceneNode(0,0,false);
	dress->setMaterialFlag(video::EMF_LIGHTING, false);//����
	dress->setMaterialFlag(video::EMF_ANTI_ALIASING,true);//���������
	ITriangleSelector* selector= smgr->createTriangleSelector(dress);
	dress->setTriangleSelector(selector);//����ѡ����

	dress->setMaterialFlag(EMF_BACK_FACE_CULLING ,false); //�رձ����޳�



	dress->setID(char_id); //����id
	scene::ISceneNode* pJointNode =0;
	pJointNode = body->getMS3DJointNode("joint1");  //  
	if(pJointNode)
	{
		// ��ҪremoveAll ��Ϊjoint1�Ǹ��ڵ㰡
		//	pJointNode->removeAll();
		//	n->setPosition(vector3df(0,1,0));
		//�󶨵�����
		body->addChild(dress );
	}

	dress->setAnimationSpeed(speed);
	dress->setLoopMode(false); 
	dress->setFrameLoop(1,2);
	dress->setCurrentFrame(1);

	return true;
}


//����Ь��
bool MyLoginCharClothMgr::LoadShoes(int id)
{
	char strmesh[255]="";
	sprintf(strmesh,"%s//%d//shoes.ms3d",modelPath,id);
	
//	smgr->getMesh("man//shoes//shoes1.ms3d") ;
//	smgr->getMesh("man//shoes2.ms3d") ;

	//����Ѽ��ع�������Ь��,�����Ƴ�
	if(shoes){
		shoes->removeAll();
		shoes->remove();
		//scene::ISceneNodeAnimator* anim = 0;
		//shoes->addAnimator(anim=dev->getSceneManager()->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�
		
	}

	shoes = smgr->addAnimatedMeshSceneNode( smgr->getMesh(strmesh) ,root);
	shoes->setMaterialFlag(video::EMF_LIGHTING, false);//����	
	shoes->setMaterialFlag(video::EMF_ANTI_ALIASING,true);//���������
	shoes->addShadowVolumeSceneNode(0,0,false);
	ITriangleSelector* selector= smgr->createTriangleSelector(shoes);
	shoes->setTriangleSelector(selector);//����ѡ����

	shoes->setID(char_id); //����id

	shoes->setAnimationSpeed(speed);
	shoes->setLoopMode(false); 
	shoes->setFrameLoop(21,22);
	shoes->setCurrentFrame(21);

	//��Ь�Ӷ���ͬ��




	//����root����.�����Լ���
	ISkinnedMesh* rootmesh=(ISkinnedMesh*)root->getMesh();
	ISkinnedMesh* shoesmesh=(ISkinnedMesh*)shoes->getMesh();
	bool ret=shoesmesh->useAnimationFrom(rootmesh);

	return true;
}

//������
void MyLoginCharClothMgr::Animate(int speed,int start,int end,bool loop)
{
	currStart=start;
	currEnd=end;
	speed=speed;
	this->m_bloop=loop;


	root->setAnimationSpeed(speed);
	root->setLoopMode(loop); 
	root->setFrameLoop(start,end);
	


	if(body){
		body->setAnimationSpeed(speed); 
		body->setLoopMode(loop); 
		body->setFrameLoop(start,end); 
	}

	if(dress){
		dress->setAnimationSpeed(speed); 
		dress->setLoopMode(loop); 
		dress->setFrameLoop(start,end); 
	}

	if(trousers){
		trousers->setAnimationSpeed(speed); 
		trousers->setLoopMode(loop); 
		trousers->setFrameLoop(start,end); 
	}

	if(shoes){
		shoes->setAnimationSpeed(speed); 
		shoes->setLoopMode(loop); 
		shoes->setFrameLoop(start,end); 
	}

}

//ж�����н�ɫ��װ��ģ��
void MyLoginCharClothMgr::DropAll()
{
	scene::ISceneNodeAnimator* anim = 0;

	if(root)
		root->addAnimator(anim=dev->getSceneManager()->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�

	//���������岿�ֲ������ֶ�ɾ��,��Ϊ���Ƕ���root���ӽڵ�.���ڵ�ɾ����.���ǻ��Զ�ɾ����.


	anim->drop();

}


}