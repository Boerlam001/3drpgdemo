#include ".\myscenegrass.h"




MySceneGrass::MySceneGrass(int worldMap)
{


  this->device=getIrrDevice();
  this->worldMap=worldMap;

  //���������ļ�
  char configFilePath[255]="scene//scene.ini";

  char inBuf[255];     //���ڱ����ȡ���ַ���
  char temp[255]="";
  sprintf(temp,"scene%d",worldMap); 

  //��ȡ�ݵ�ģ��
  bool ret=IniGetString(configFilePath,temp,"grass_model",inBuf);  //��
  //δ���òݵ��ļ�
  if(ret==false){
	  m_bUseGrass=false;
  }else{
	  //�ݵ�ģ��·��
	  sprintf(grass_model_path,"%s",inBuf);
	  m_bUseGrass=true;
  }

  //��ȡ�ݵ�����ֲ������ļ�
   ret=IniGetString(configFilePath,temp,"grass_list",inBuf);  //��
  //δ���òݵ��ļ�
  if(ret==false){
	  m_bUseGrass=false;
  }else{
	  //�ݵ�ģ��·��
	  sprintf(grass_list_path,"%s",inBuf);
	   m_bUseGrass=true;
  }


}

void MySceneGrass::setVisible(bool v)
{
	core::list<irr::scene::IAnimatedMeshSceneNode*>::Iterator  list_oper;
	for(list_oper=mygrass_list.begin();list_oper!=mygrass_list.end();++list_oper)
	{

		irr::scene::IAnimatedMeshSceneNode* no=(*list_oper);//��core::triangle3df* temp_triangle; temp_triangle= *list_oper;triangle3df t=*(temp_triangle);
		no->setVisible(v);
		
	}
}

MySceneGrass::~MySceneGrass(void)
{
}
void MySceneGrass::DrawAGrass(vector3df pos)
{
	struct _timeb timebuffer;//����һ���ṹ
	_ftime(&timebuffer);//��ʼ��timebuffer
	srand(timebuffer.millitm);//timebuffer.millitm��ú���


	




	irr::scene::IAnimatedMeshSceneNode* no= device->getSceneManager()->addAnimatedMeshSceneNode(
		device->getSceneManager()->getMesh(grass_model_path),0,0,pos);  
	no->setMaterialFlag(video::EMF_LIGHTING, false);//����
	no->setScale(vector3df(5,5,5));
	no->setMaterialFlag(video::EMF_FOG_ENABLE,true);//����fog����
	//no->setMaterialTexture(0,device->getVideoDriver()->getTexture("SAND1.BMP"));
	no->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );// ���������͸����..
//	no->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR ); EMT_TRANSPARENT_ALPHA_CHANNEL EMT_TRANSPARENT_VERTEX_ALPHA


	no->setMaterialFlag(video::EMF_BACK_FACE_CULLING ,false); //�رձ����޳�

	mygrass_list.push_back(no);
	
}


void  MySceneGrass::DrawAllGrass()
{
	//�õ�ͼ�����ļ�δʹ�òݵ�
	if(m_bUseGrass==false) return;

	ReadFile();

	//������ļ�
	core::list<core::vector3df>::Iterator  list_oper;
	for(list_oper=mylist.begin();list_oper!=mylist.end();++list_oper)
	{

		vector3df pos(*list_oper);//��core::triangle3df* temp_triangle; temp_triangle= *list_oper;triangle3df t=*(temp_triangle);
		DrawAGrass(pos);
	}
}

//���ļ���ȡ�ݵ�������ķֲ�����
void  MySceneGrass::ReadFile()
{

	FILE* log;
	log = fopen(grass_list_path, "a+");
	if (log == NULL)
		return ;

	char strtemp[255]="";
	GetTxtByRowNum(grass_list_path,strtemp,1);

	int size=atoi(strtemp);
	printf("size:%d\n",size);

	for(int i=1;i<=size;i++){

		GetTxtByRowNum(grass_list_path,strtemp,1+i);
		vector3df s;
		sscanf(strtemp, "%f %f %f", 
			&s.X,&s.Y,&s.Z
			); 

		mylist.push_back(s);
	}
	//

}

void MySceneGrass::drop()
{
	core::list<irr::scene::IAnimatedMeshSceneNode*>::Iterator  list_oper;
	for(list_oper=mygrass_list.begin();list_oper!=mygrass_list.end();++list_oper)
	{

		irr::scene::IAnimatedMeshSceneNode* no=(*list_oper);//��core::triangle3df* temp_triangle; temp_triangle= *list_oper;triangle3df t=*(temp_triangle);
		no->removeAnimators();
		no->removeAll();
		no->remove();
	}
}
