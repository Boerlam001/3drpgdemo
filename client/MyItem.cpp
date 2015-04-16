#include "StdAfx.h"
#include "myitem.h"

MyItem::MyItem(  char* meshPath,SceneItem item)
{

	dev=getIrrDevice();
	smgr=getIrrSmgr();

	modelPath=meshPath;
	
	node=0;

	memcpy((char*)&this->item,(char*)&item,sizeof(SceneItem));

}

MyItem::~MyItem(void)
{
}


void MyItem::Draw()
{

	node = smgr->addAnimatedMeshSceneNode(smgr->getMesh(modelPath)); 
	//	node->setMaterialTexture(0,device->getVideoDriver()->getTexture("a.bmp"));
	//node->setScale(vector3df(20,20,20));
	node->setPosition(item.pos);
	node->setMaterialFlag(video::EMF_LIGHTING, false);//����
	//node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);// ���������͸����..
	//	selecter= smgr->createOctTreeTriangleSelector(node->getMesh(), node , 128);
	//		selecter= smgr->createTriangleSelector(node->getMesh(), node );
	//	node->setTriangleSelector(selecter);//����ѡ����
	//	node->setDebugDataVisible(scene::EDS_BBOX ); //������ʾ��Χ��
	//	node->setMaterialFlag(video::EMF_ZBUFFER, true); //��ѡ
	//node->setAutomaticCulling( EAC_BOX  );

	if(item.item_Type==ITEMType_Money){
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);// ���������͸����.	
	}

}

void MyItem::UIRender()
{
	if(node==0 ) return ;

    TextShowPos= smgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(item.pos);
	
	
	//��ʾ��Ʒ����.������server��������.ֱ����ʾ��
	if(node && node->isTrulyVisible()  )
	{
		TextCenter(item.itemName,TextShowPos,SColor(1,255,255,0),14,600);
	}

}

void MyItem::drop()
{
	//if(node==0) return ;

scene::ISceneNodeAnimator* anim = 0;
node->addAnimator(anim=smgr->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�,�����ڵ�
anim->drop();



}