#include ".\myweaponmgr.h"

MyWeaponMgr::MyWeaponMgr(IAnimatedMeshSceneNode* parent)
{
	device=getIrrDevice();

	smgr=getIrrSmgr();

	parentNode=parent;


	//��ʼ��������,�ֱ������Ϻͱ��ϵ�
	handweapon=new MyWeapon();
	backweapon=new MyWeapon();

	//�����Ȼ�����
	ChangeWeapon(1,0);

	handweapon->getNode()->setVisible(false);
	backweapon->getNode()->setVisible(false);


}

void MyWeaponMgr::setWeaponVisible(bool v)
{
	updateUseLastState();
}

void MyWeaponMgr::OpenHlslEffect(bool use,int weaponType) //weaponType ����������������
{
	isusehlsleffect=use;

	//������Ч������Щ..
	if(currentWeaponid==XBJ_Weapon){
		
		handweapon->setUseHLSL(use,true,weaponType);
		backweapon->setUseHLSL(use,true,weaponType);
	}else{
		handweapon->setUseHLSL(use,false,weaponType);
		backweapon->setUseHLSL(use,false,weaponType);
		
	}


	
}

//weaponparam1��ʾЧ������
void MyWeaponMgr::ChangeWeapon(int id,int weaponparam1)
{
	currentWeaponid=id;
	currparam1=weaponparam1;

	//��ʾҪж������...��������ֻ��������
	if(id==0){
		if(handweapon->getNode()) handweapon->getNode()->setVisible(false);
		if(backweapon->getNode()) backweapon->getNode()->setVisible(false);
		return;
	}

	bool usehlsl=false;
	if(weaponparam1==0){
		//��ͨ����Ч��
	}else{
		usehlsl=true;
	}

	//�õ��������Ĺؽ�,��			//��ɫ->��װ������->root����
	scene::ISceneNode* pJointNode =parentNode->getMS3DJointNode("weapon");  //weapon���� 
	if(pJointNode)
	{
		handweapon->ps=0;

		//�Ƴ����ϵ������ڵ�
		pJointNode->removeAll();
		//��������
		handweapon->ChangeWeapon(abs(id));
		handweapon->getNode()->setID(101);
		// handweapon->setUseHLSL(true);
		handweapon->getNode()->setScale(vector3df(6,6,6));
		handweapon->getNode()->setRotation(vector3df(180,0,90));
		handweapon->setPosition(vector3df(0,0,0));

		//�󶨵�����
		pJointNode->addChild( handweapon->getNode() );
	} 


	pJointNode = parentNode->getMS3DJointNode("joint23");  //   joint23 �Ǳ�
	if(pJointNode)
	{
		backweapon->ps=0;

		//�Ƴ����ϵ������ڵ�
		pJointNode->removeAll();
		//��������
		backweapon->ChangeWeapon(abs(id));
		backweapon->getNode()->setID(101);
		//backweapon->setUseHLSL(true);
		backweapon->getNode()->setScale(vector3df(6,6,6));
		backweapon->getNode()->setRotation(vector3df(180,-5,110));
		backweapon->setPosition(vector3df(0,-2,0));
		//�󶨵�����
		pJointNode->addChild( backweapon->getNode() );
	}

	if(currentWeaponid==XBJ_Weapon){
		//handweapon->setUseHLSL(true,true);
		//backweapon->setUseHLSL(true,true); //ʼ�տ���hlsl,͸��Ч��
		
		handweapon->HLSL();
		backweapon->HLSL();

		////���ñ�����
		//handweapon->getNode()->setMaterialTexture(1,device->getVideoDriver()->getTexture("weapon/w52.tga"));
		//backweapon->getNode()->setMaterialTexture(1,device->getVideoDriver()->getTexture("weapon/w52.tga"));
	}

	
	if(usehlsl && XBJ_Weapon!=id){
		//��ʾ����
		handweapon->setUseHLSL(true,false,weaponparam1);
		backweapon->setUseHLSL(true,false,weaponparam1);
	}

	

}
void MyWeaponMgr::updateUseLastState(  )
{
	//�õ���ɫ״̬


	//��ʾж��������,������������
	if(currentWeaponid==0){
		if(handweapon->getNode()) handweapon->getNode()->setVisible(false);
		if(backweapon->getNode()) backweapon->getNode()->setVisible(false);
		return;
	}

	//վ��,�Ͱ����ϵ���������,���ϵ���ʾ
	if(state == cIdle) //վ
	{
		handweapon->getNode()->setVisible(false);
		backweapon->getNode()->setVisible(true);
	}else if(state==  cRun){//��
		handweapon->getNode()->setVisible(false);
		backweapon->getNode()->setVisible(true);
	}else if(state ==  cReadyAttack){//����Ԥ��
		handweapon->getNode()->setVisible(true);
		backweapon->getNode()->setVisible(false);
	}else if(state ==  cAttack){//����
		handweapon->getNode()->setVisible(true);
		backweapon->getNode()->setVisible(false);
	}else if(state ==  cDeath){
		handweapon->getNode()->setVisible(false);
		backweapon->getNode()->setVisible(true);
	}

}

void MyWeaponMgr::update(int state )
{
//	if(handweapon->getNode()==0 || backweapon->getNode()==0) return;

	//�õ���ɫ״̬
	this->state=state;


	//��ʾж��������,������������
	if(currentWeaponid==0){
		if(handweapon->getNode()) handweapon->getNode()->setVisible(false);
		if(backweapon->getNode()) backweapon->getNode()->setVisible(false);
		return;
	}

	//վ��,�Ͱ����ϵ���������,���ϵ���ʾ
	if(state == cIdle) //վ
	{
		handweapon->getNode()->setVisible(false);
		backweapon->getNode()->setVisible(true);
	}else if(state==  cRun){//��
		handweapon->getNode()->setVisible(false);
		backweapon->getNode()->setVisible(true);
	}else if(state ==  cReadyAttack){//����Ԥ��
		handweapon->getNode()->setVisible(true);
		backweapon->getNode()->setVisible(false);
	}else if(state ==  cAttack){//����
		handweapon->getNode()->setVisible(true);
		backweapon->getNode()->setVisible(false);
	}else if(state ==  cDeath){
		handweapon->getNode()->setVisible(false);
		backweapon->getNode()->setVisible(true);
	}

	handweapon->update();
	backweapon->update();

}

MyWeaponMgr::~MyWeaponMgr(void)
{
}

void MyWeaponMgr::setParentNode(IAnimatedMeshSceneNode* p)
{

	DropAll();

	this->parentNode=p;

	ChangeWeapon(currentWeaponid,currparam1);
}

//ж����������
void MyWeaponMgr::DropAll()
{
//	if(parentNode==0){
//		return;
//	}

	scene::ISceneNode* pJointNode = parentNode->getMS3DJointNode("weapon");  //weapon���� 
	if(pJointNode)
	{
		//�Ƴ����ϵ������ڵ�
		pJointNode->removeAll();
		handweapon->setNode(0);
	}

	
	pJointNode = parentNode->getMS3DJointNode("joint23");  //   joint23 �Ǳ�
	if(pJointNode)
	{
			//�Ƴ����ϵ������ڵ�
			pJointNode->removeAll();
			backweapon->setNode(0);
	}

	
	


}