#include ".\mynpcmgr.h"

MyNPCMgr::MyNPCMgr( MySceneManager* mm)
{
	this->dev=getIrrDevice();

	this->m_pMySceneMgr=mm;

	smgr=getIrrSmgr();


	::InitializeCriticalSection(&g_cs_npclist);//��ʼ���ٽ�������

	::InitializeCriticalSection(&g_cs_msglist);//��ʼ���ٽ�������

	NPCselected=false;
	selectedNPCnode=0;

	MouseInNPC_GUI=false;
}

MyNPCMgr::~MyNPCMgr(void)
{
}

//����npc��Ϣ������,���Է�����
void MyNPCMgr::insertNPCData(char* pData,int DataLength)
{
	printf(" MyNPCMgr::insertNPCData\n");
	ClientMsg* m=new ClientMsg();
	char* tmp=new char[DataLength];
	memcpy(tmp,pData,DataLength);
	m->pData=tmp;
	m->size=DataLength;


	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_msglist);
	msglist.push_back(m); //��Ӵ��������
	::LeaveCriticalSection(&g_cs_msglist);
	//////---------------------------------------------------------------------------------------------///////////////	


}

void MyNPCMgr::setVisiable(bool v)
{
	::EnterCriticalSection(&g_cs_npclist);
	std::vector<MyNPC*>::iterator list_oper;
	for(list_oper=npc_list.begin();list_oper!=npc_list.end();++list_oper)
	{

		MyNPC *p=*list_oper;

		if(p) 
		{
			p->getNode()->setVisible(v);

		}
	}


	::LeaveCriticalSection(&g_cs_npclist);
}


//�����¼�
void MyNPCMgr::OnEvent (const irr::SEvent & e)
{
	bool r=false;
	::EnterCriticalSection(&g_cs_npclist);
	std::vector<MyNPC*>::iterator list_oper;
	for(list_oper=npc_list.begin();list_oper!=npc_list.end();++list_oper)
	{

		MyNPC *p=*list_oper;

		if(p) 
		{
			p->OnEvent(e);
			if(r==false){

				//���ָ��npc��npc�ĶԻ���
				if(p->mouseCurNPC_Dlg)
				{
					r=true;
				}
			}
			
		}
	}


	::LeaveCriticalSection(&g_cs_npclist);
	//////---------------------------------------------------------------------------------------------///////////////	

	MouseInNPC_GUI=r;
}

//�Ƴ���������NPC.�����л�����ʱ��.
void MyNPCMgr::RemoveAllNPC()
{

	::EnterCriticalSection(&g_cs_npclist);
	std::vector<MyNPC*>::iterator list_oper;
	for(list_oper=npc_list.begin();list_oper!=npc_list.end();++list_oper)
	{

		MyNPC *p=*list_oper;

		if(p) 
		{
			p->drop();
			delete p;
			p=0;
		}
	}

	npc_list.clear();
	
	::LeaveCriticalSection(&g_cs_npclist);
	//////---------------------------------------------------------------------------------------------///////////////	

}

/*

���һ��npc��������

*/
void MyNPCMgr::AddNPC(NPCProperty prop)
{

	::EnterCriticalSection(&g_cs_npclist);
	MyNPC* n=new MyNPC(prop,m_pMySceneMgr->client);
	npc_list.push_back(n); //��ӽ����� ����ģ��.��Ϊnpc�����������߳���ȫ���������.
	//beast->SetNetServer(this->net);

	::LeaveCriticalSection(&g_cs_npclist);

	//	beast->GetNode()->setDebugDataVisible(scene::EDS_BBOX ); //������ʾ��Χ��

	printf("npc%d��ȫ��Ϣ������!\n",prop.ID);

}

//����npc����
void MyNPCMgr::LoadSceneNPC(int worldMap)
{
	//���õ�ǰ������ͼid
  this->currWorldMap=worldMap;
	
  //���������ļ�
  char FilePath[255]="scene//scene.ini";

  char inBuf[255];     //���ڱ����ȡ���ַ���
  char temp[255]="";
  sprintf(temp,"scene%d",currWorldMap); 

  //�˳���npc����
  int sceneNpcNum=0;
  sceneNpcNum=IniGetInt(FilePath,temp,"npc_num");
	
  //ѭ����ӵ�ǰ������ͼ������npc
  for (int i=1;i<=sceneNpcNum;i++)
  {	
	  NPCProperty p;
	  p.cmd=0;
	  p.ID=i;

	  char str[255];
	  sprintf(str,"npc%d_POS",i); //��ȡ��i��npc������
	  if( IniGetString(FilePath,temp,str,inBuf) ){
		
		  sscanf(inBuf, "%f,%f,%f",   &p.pos.X,&p.pos.Y,&p.pos.Z  ); 
		 
	  }
	
	  sprintf(str,"npc%d_name",i); //��ȡ��i��npc��name
	  if( IniGetString(FilePath,temp,str,inBuf) ){
		
		 strcpy(p.strNPCName,inBuf);
	  }

	  sprintf(str,"npc%d_Rot",i); //��ȡ��i��npc����ת
	  if( IniGetString(FilePath,temp,str,inBuf) ){

		  sscanf(inBuf, "%f,%f,%f",   &p.rot.X,&p.rot.Y,&p.rot.Z); 

	  }

	  sprintf(str,"npc%d_talk",i); //��ȡ��i��npc�Ķ����˵�Ļ�
	  if( IniGetString(FilePath,temp,str,p.strNpcTalk) ){

	  }

	  sprintf(str,"npc%d_btnText",i); //��ȡ��i��npc�ĶԻ���ť������
	  if( IniGetString(FilePath,temp,str,p.strBtnText) ){
			//MessageBox(0,p.strBtnText,"",0);
	  }else{
		  //��ȡʧ��,˵����npcû�н�һ�����¼�.
		strcpy(p.strBtnText,"");
	  }



	  sprintf(str,"npc%d_btnClickcmd",i); //��ȡ��i��npc�İ�ť��Ӧ���¼�����

	   p.cmd=IniGetInt(FilePath,temp,str);
		
	  

		AddNPC(p);
  }


}


MyNPC*  MyNPCMgr::GetNpcByID(int id)
{
	MyNPC* p_npc=0;
	::EnterCriticalSection(&g_cs_npclist);
	std::vector<MyNPC*>::iterator list_oper;
	for(list_oper=npc_list.begin();list_oper!=npc_list.end();++list_oper)
	{
		MyNPC *p=*list_oper;

		//id��ȷ�ͷ���
		if(p->getProp().ID==id) 
		{
			p_npc=p;
		}
	}
	::LeaveCriticalSection(&g_cs_npclist);

	return p_npc;
}


void MyNPCMgr::update()
{

	::EnterCriticalSection(&g_cs_npclist);
	std::vector<MyNPC*>::iterator list_oper;
	for(list_oper=npc_list.begin();list_oper!=npc_list.end();++list_oper)
	{

		MyNPC *p=*list_oper;

		if(p) 
		{
			//�ȱ�־δ���ָ��npc 
			p->mouseCurNPC=false;

			//�ȶ��ɼ�
			p->getNode()->setVisible(true);

			p->update();

//---------------------------------------------------------------------------------------------------------------------
	//�˴��������ڻ��npc��cam���߶�.Ȼ��ͳ���ģ����ײ.�������ײ��˵�������ڵ���.��npc����
			//�õ�npc���� �ǹ̶��˵�
			p->line.start=p->getProp().pos;
			p->line.start.Y+=10;
			//�õ������������ 
			p->line.end= m_pMySceneMgr->myCamera->getNode()->getPosition();
			//line.end.Y+=10;
			vector3df vec=m_pMySceneMgr->char_mgr->GetMainCharacter()->getPosition()-p->getProp().pos;
			vec.normalize();
		//	p->line.end-=vec*5;
		//	p->line.start-=vec*5;

			core::triangle3df triangle;
			const ISceneNode* outnode;
			//��npc���������3d�߶κͳ�������,����ģ����ײ.�����.��˵������֮�����ڵ�.�Ͱ�npc����.
			if (smgr->getSceneCollisionManager()->getCollisionPoint(
				p->line, //[in] ����
				m_pMySceneMgr->myscene_loader->getMeta(), //[in] �����ڵ��������ѡ����
				p->line.end, //[out] ������ײ��
				triangle,outnode)) //[out] ������ײ������
			{
			   //printf("npc select id:%d\n",outnode->getID());
				
				p->getNode()->setVisible(false);
			}
	//---------------------------------------------------------------------------------------------------------------------

			/*
			ISceneNode * select_npc_node =smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
				line,
				intersection, // This will be the position of the collision
				hitTriangle, // This will be the triangle hit in the collision
				0, // This ensures that only nodes that we have
				// set up to be pickable are considered
				0); // Check the entire scene (this is actually the implicit default)

			//ʰȡ��ĳ�ڵ�
			if(select_npc_node){

				printf("npc select id:%d\n",select_npc_node->getID());
				MyNPC* sel_npc=GetNpcByID(select_npc_node->getID());

				//ʰȡ�Ĳ���npc
				if( sel_npc==NULL ){

					//���������npc.��Ϊ�ڵ���
					//p->getNode()->setVisible(false);
				}else{
					printf("npc%sδ�ڵ�\n",p->getProp().strNPCName);
					p->getNode()->setVisible(true);
				}
				////��õĽڵ���npc�Ļ�,��ʾ�м�û���ڵ�
				//if(select_npc_node==p->getNode()){
				//	p->getNode()->setVisible(true);
				//}else{
				//	//���������npc.��Ϊ�ڵ���
				//	p->getNode()->setVisible(false);
				//}
			}else{
				//���������npc.��Ϊ�ڵ���
				//p->getNode()->setVisible(false);
			}
	
*/


		}
	}
	::LeaveCriticalSection(&g_cs_npclist);
	//////---------------------------------------------------------------------------------------------///////////////	



	//////---------------------------------------------------------------------------------------------///////////////	
	//���ʰȡnpc Ȼ���ý�ɫ�Ի�����
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	//�õ���Ļ���ת����3d������һ������
	vector2d<s32> curpos=dev->getCursorControl()->getPosition();
	core::line3d<f32> line;
	line=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(curpos);
	//����2.
	core::vector3df intersection;
	core::triangle3df hitTriangle;
	ISceneNode * select_npc_node =collMan->getSceneNodeAndCollisionPointFromRay(
		line,
		intersection, // This will be the position of the collision
		hitTriangle, // This will be the triangle hit in the collision
		0, // This ensures that only nodes that we have
		// set up to be pickable are considered
		0); // Check the entire scene (this is actually the implicit default)

	//ʰȡ��npc
	if(select_npc_node){
		//printf("ʰȡ%d!\n",select_npc_node->getID() );
		//���ݽڵ�õ�������
		MyNPC* sel_npc=GetNpcByID(select_npc_node->getID());
		
		//ʰȡ�Ĳ���npc
		if( sel_npc==NULL ){
			NPCselected=false;

			MouseInNPC_GUI=false;
		}else {
			NPCselected=true;	
			selectedNPCnode=sel_npc;

			sel_npc->mouseCurNPC=true;
			

			MouseInNPC_GUI=true;

			//printf("ʰȡ��Npc%s \n", sel_npc->getProp().strNPCName );
		}
	}else{
		NPCselected=false;

		MouseInNPC_GUI=false;
		// printf("ʰȡʧ��!!!!\n");
	}

}

void MyNPCMgr::UIRender()
{
	::EnterCriticalSection(&g_cs_npclist);
	std::vector<MyNPC*>::iterator list_oper;
	for(list_oper=npc_list.begin();list_oper!=npc_list.end();++list_oper)
	{
		MyNPC *p=*list_oper;
		if(p) 	p->UIRender();



		//��Ⱦcam��npc֮���3dline.����
		//�����ṩһ������--------------------------------------------------------------------------------------------------------------------------
		/*
		core::matrix4 mat;
		video::SMaterial material;
		material.TextureLayer[0].Texture= 0;
		material.Lighting = false;
		material.Thickness=2; //���ô�ϸ
		dev->getVideoDriver()->setTransform(video::ETS_WORLD, mat);
		dev->getVideoDriver()->setMaterial(material);

		getIrrDriver()->draw3DLine(p->line.start,p->line.end,video::SColor(255, 255, 250, 0));
		*/
		//-----------------------------------------------------------------------------------------------------------------------------------------	
		
		
		


		
	}
	::LeaveCriticalSection(&g_cs_npclist);
	//////---------------------------------------------------------------------------------------------///////////////	

}
