#include "StdAfx.h"
#include ".\mymonstersmgr.h"

MyMonstersMgr::MyMonstersMgr( MySceneManager* mysmgr,Socket::CNetClient* net)
{
	//�������
	device=getIrrDevice();						//����ָ��
	smgr=getIrrSmgr();		//��������

	this->m_pMySceneMgr=mysmgr;

	//����
	this->net=net;

	//��ѡ��Ĺ���
	selectednode=0;
	Nodeselected=false;


	 //��ʱ��
	 timer=device->getTimer();
	 lasttime=timer->getRealTime();


	 ::InitializeCriticalSection(&g_cs_msglist);//��ʼ���ٽ�������

	 
	::InitializeCriticalSection(&g_cs_monsterlist);//��ʼ���ٽ�������

	//��Ϣ���
	msglist.clear();

	//���������б����
	monster_list.clear();


}

MyMonstersMgr::~MyMonstersMgr(void)
{

}

//�Ƴ��������߹���.�����л�����ʱ��.
void MyMonstersMgr::RemoveAllMonsters()
{
	::EnterCriticalSection(&g_cs_monsterlist);
	for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
	{
		
		MyMonster *p=*list_oper;
		p->drop();
		delete p;
		p=0;
	}
	monster_list.clear();

	::LeaveCriticalSection(&g_cs_monsterlist);

}

MyMonster* MyMonstersMgr::GetMonsterByID(int id)
{
	::EnterCriticalSection(&g_cs_monsterlist);
		for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
		{
				
			    MyMonster *p=*list_oper;
				//����������Ƴ�����
				
				if(p->GetMonsterId()==id){
					::LeaveCriticalSection(&g_cs_monsterlist);
					return p;
				}
		}
	::LeaveCriticalSection(&g_cs_monsterlist);
		return 0;
}



//�������й����Ƿ�ɼ�
void MyMonstersMgr::setAllMonsterVisiable(bool v)
{
	::EnterCriticalSection(&g_cs_monsterlist);
	for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
	{
		 MyMonster *p=*list_oper;
		 if(p->GetNode())p->GetNode()->setVisible(v);
	}

	::LeaveCriticalSection(&g_cs_monsterlist);
}

/*

	���һ�����ﵽ������
	
*/
void MyMonstersMgr::AddMonster(MonsterProperty prop)
{
	
::EnterCriticalSection(&g_cs_monsterlist);
	MyMonster* beast=new MyMonster(prop,"zombie//zombie.b3d");
	monster_list.push_back(beast); //��ӽ�����
	::LeaveCriticalSection(&g_cs_monsterlist);
	beast->Draw(); //���ع���ģ����Ϣ
	beast->SetNetServer(this->net);
	beast->SetInitRotValue(90);
	
//	beast->GetNode()->setDebugDataVisible(scene::EDS_BBOX ); //������ʾ��Χ��

	printf("����%d��ȫ��Ϣ������!\n",prop.ID);

}



/*
  �������й���
 */
void MyMonstersMgr::Update()
{

	//�ȴ�������������Ĺ�����Ϣ
	DoListThread();


//////---------------------------------------------------------------------------------------------///////////////	
		::EnterCriticalSection(&g_cs_monsterlist);
		for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
		{
		

			    MyMonster *p=*list_oper;
				////����������Ƴ�����
				if(p->IsDead() || p->getMonsterProperty()->HP<=0){
					
					if(p->isdrop==false)
					{
						if(p->GetNode() ) p->GetNode()->setVisible(false);
						p->AddGhostFlyEffect();
					}

					
					
					////��ֹ�����Ƴ��˶���,��ɫ�����monster���ô���.�������ж�.Ȼ�����ø��ո���main_char���п�
					//if(m_pMySceneMgr->char_mgr->GetMainCharacter()->monster!=0){
					//	if(m_pMySceneMgr->char_mgr->GetMainCharacter()->monster->GetMonsterId()==p->GetMonsterId()){
					//		m_pMySceneMgr->char_mgr->GetMainCharacter()->SetWantToAttackTarget(0);
					//		m_pMySceneMgr->char_mgr->GetMainCharacter()->readyAttack(true);
					//		m_pMySceneMgr->char_mgr->GetMainCharacter()->ReoprtToServer();
					//		//	//MessageBox(0,"AddGhostFlyEffect�����������0","",0);
					//	}
					//}
					
					p->drop();
					delete p;
					p=0;
					monster_list.erase(list_oper);
					break;
				}
				
				//���ù����Լ��ĸ��·���
				if(p) p->Update();

		//-------------------------------------------------------------------------------------
				//�õ�����pos
				p->line.start=p->getMonsterProperty()->pos;
				p->line.start.Y+=10;
				//�õ������������ 
				p->line.end = m_pMySceneMgr->myCamera->getNode()->getPosition();
				//line.end.Y+=10;
				vector3df vec=m_pMySceneMgr->char_mgr->GetMainCharacter()->getPosition()-p->getMonsterProperty()->pos;
				vec.normalize();
				//	p->line.end-=vec*5;
				//	p->line.start-=vec*5;

				core::triangle3df triangle;
				const ISceneNode* outnode;
				//��npc���������3d�߶κͳ�������,����ģ����ײ.�����.��˵������֮�����ڵ�.�Ͱ�npc����.
				if (getIrrSmgr()->getSceneCollisionManager()->getCollisionPoint(
					p->line, //[in] ����
					m_pMySceneMgr->myscene_loader->getMeta(), //[in] �����ڵ��������ѡ����
					p->line.end, //[out] ������ײ��
					triangle,outnode)) //[out] ������ײ������
				{
					//printf("monstermgr select id:%d\n",outnode->getID());

					if(p && p->GetNode())
						p->GetNode()->setVisible(false);
					
				}else{
					if(p && p->GetNode())
						p->GetNode()->setVisible(true);
				}
				//------------------------------------------------------------------------------------------

		}
	   ::LeaveCriticalSection(&g_cs_monsterlist);
//////---------------------------------------------------------------------------------------------///////////////	
			scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();

	    //��ʱ
		u32 usetime=timer->getRealTime()-lasttime;
		if( usetime<50) return;

			lasttime=timer->getRealTime();

			//if(selectednode) selectednode->GetNode()->setDebugDataVisible(scene::EDS_OFF ); //��off��Χ��
			
			//�õ���Ļ���ת����3d������һ������
			vector2d<s32> curpos=device->getCursorControl()->getPosition();
			core::line3d<f32> line,line2;
			line=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(curpos);
			curpos.Y-=8;
			line2=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(curpos);

			
			//�õ���ѡȡ�Ľڵ㷽��1.
			//ISceneNode* m=smgr->getSceneCollisionManager()->getSceneNodeFromRayBB(line);
			
			//ISceneNode *m=0;
			//for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
			//{
			//		
			//		MyMonster *p=*list_oper;
			//		
			//		aabbox3d<f32> box=p->GetNode()->getBoundingBox();
			//		
			//	//	box.MaxEdge+=vector3df(5,5,5);
			//	//	box.MinEdge+=vector3df(-5,-5,-5);

			//		if(box.intersectsWithLine(line)){
			//			m=p->GetNode();
			//		   break;
			//		}else{
			//		  
			//		}
			//}
				
			//����2.
			core::vector3df intersection;
			core::triangle3df hitTriangle;
			ISceneNode * m =collMan->getSceneNodeAndCollisionPointFromRay(
					line,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					0, // This ensures that only nodes that we have
							// set up to be pickable are considered
					0); // Check the entire scene (this is actually the implicit default)

			//ʰȡ�˹���
			 if(m){
				 	//���ݽڵ�õ�������
					selectednode=GetMonster(m);
					//�����������,�Ͳ���ʾ�ɹ���
					if( selectednode==NULL || selectednode->IsDead()){
							Nodeselected=false;
						//	printf("һ�� false\n");
					}else{
							//node->setDebugDataVisible(scene::EDS_BBOX ); //������ʾ��Χ��
							//printf("һ�� true\n");
							Nodeselected=true;
							
							
							//���㱻ѡ����������,������,����ui��ʾtext������
							vector3df userpos=selectednode->GetNode()->getPosition();    //selectednode->getHPBar()->getAbsolutePosition();
							MonsterTextShowPos= smgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(userpos);
							

							return;
					}
			 }else{
				 Nodeselected=false;
				// printf("һ�� false\n");
			    
			 }


			 m =collMan->getSceneNodeAndCollisionPointFromRay(
					line2,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					0, // This ensures that only nodes that we have
							// set up to be pickable are considered
					0); // Check the entire scene (this is actually the implicit default)

			//ʰȡ�˹���
			 if(m){
				 	//���ݽڵ�õ�������
					selectednode=GetMonster(m);
					//�����������,�Ͳ���ʾ�ɹ���
					if( selectednode==NULL || selectednode->IsDead()){
							Nodeselected=false;
						//	printf("���εõ������� false\n");
					}else{
							//node->setDebugDataVisible(scene::EDS_BBOX ); //������ʾ��Χ��
						//	printf("���� true\n");
							Nodeselected=true;
							
							
							//���㱻ѡ����������,������,����ui��ʾtext������
							vector3df userpos=selectednode->GetNode()->getPosition();    //selectednode->getHPBar()->getAbsolutePosition();
							MonsterTextShowPos= smgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(userpos);
							
							return;
					}
			 }else{
				 Nodeselected=false;
				// printf("���� false\n");
			    
			 }

	

}


//���й����ui��ʾ.����Ѫ�� ����
void MyMonstersMgr::UIRender()
{
//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_monsterlist);
		for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
		{
				
			    MyMonster *p=*list_oper;
				if(p) p->UIRender();
		}

//////---------------------------------------------------------------------------------------------///////////////	
	::LeaveCriticalSection(&g_cs_monsterlist);


	//��ʾ�����ѡ���˵Ĺ�������
	if(Nodeselected){
		if(selectednode && selectednode->IsDead()==false) TextCenter(selectednode->getMonsterProperty()->Name,MonsterTextShowPos,SColor(1,255,0,0),14,600);
	}

}

void MyMonstersMgr::OnEvent (const irr::SEvent& e)
{ 
 
}



// ���ݽڵ�õ�������
MyMonster* MyMonstersMgr::GetMonster(ISceneNode* node)
{
//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_monsterlist);
		for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
		{
			     MyMonster *p=*list_oper;
				 if(p->GetNode()==node)
				{
						::LeaveCriticalSection(&g_cs_monsterlist);
					return p;
				}
		}
//////---------------------------------------------------------------------------------------------///////////////	
		::LeaveCriticalSection(&g_cs_monsterlist);
return 0;
}




//�Ȱѷ����������Ĺ�����Ϣ����
void   MyMonstersMgr::DoListThread( )
{


	::EnterCriticalSection(&g_cs_monsterlist);
	//����������Ϣ.ֱ��������ŷ���..
 //   while (msglist.getSize()>0)
	{
	
		core::list<ClientMsg*>::Iterator  msg_oper;
		for(msg_oper=msglist.begin();msg_oper!=msglist.end();++msg_oper)
		{
			ClientMsg* msg=(*msg_oper);
			unsigned char cmd=msg->pData[0];

			printf("MyMonstersMgr DoListThread cmd:%d\n",cmd);
			if(cmd==MonsterCMD_LOGIN){

				MonsterCMD_LOGIN_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete msg->pData;
				delete msg;
				msg_oper=msglist.erase(msg_oper);
				break;
			}else if(cmd==MonsterCMD_UPDATE){
				MonsterCMD_UPDATE_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete msg->pData;
				delete msg;
				msg_oper=msglist.erase(msg_oper);
				break;
			}else if(cmd==MonsterCMD_UnderAttack){
				MonsterCMD_UnderAttack_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete msg->pData;
				delete msg;
				msg_oper=msglist.erase(msg_oper);
				break;
			}

		}

	}

	::LeaveCriticalSection(&g_cs_monsterlist);
	
	
}

//��������������еĹ�����Ϣ
void MyMonstersMgr::getMonsterCMD_MonsterAll()
{
    MonsterProperty p;
	memset((char*)&p,'\0',sizeof(MonsterProperty));
	p.cmd=MonsterCMD_MonsterAll;
	net->SendMsg((char*)&p,4); //͵��4λ�̶���С��.����ûʲô��Ҫ����
}


void MyMonstersMgr::MonsterCMD_UnderAttack_PROC(char* pData,unsigned long length)
{
	if(length<sizeof(MonsterProperty)){

	}

	//���ﱻ����,ֻ���ձ��������˺�ֵ�͵�ǰhp.
	//��ʶ�Ƿ��ҵ�ָ��id�Ĺ���
	bool found=false;
	MonsterProperty prop;
	memset((char*)&prop,'\0',sizeof(MonsterProperty));
	memcpy((char*)&prop,(char*)pData,sizeof(MonsterProperty));
	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_monsterlist);
	for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
	{
		MyMonster *p=*list_oper;
		if(p){
			if(p->GetMonsterId()==prop.ID)
			{
				//memcpy((char*)&p->prop,(char*)pData,sizeof(MonsterProperty)); 
				//ֻ�����hp���˺�.
				p->setMonsterHP(prop.HP);
				p->setMonsterDamage(prop.damage);
				//����ʾ�˺�����
				p->ShowAttackTextNum(prop.damage);

				found=true;
				break;
			}
		}

		
	}
	//////---------------------------------------------------------------------------------------------///////////////	
	::LeaveCriticalSection(&g_cs_monsterlist);
	//�����δ֪����,�������������Ϣ
	if(found==false)
	{
		printf("��δ֪����id:%d,�������������Ϣ\n",prop.ID);
		prop.cmd=MonsterCMD_UNKNOWMONSTER;
		net->SendMsg((char*)&prop,sizeof(MonsterProperty));
	}

}


void MyMonstersMgr::MonsterCMD_UPDATE_PROC(char* pData,unsigned long length)
{
	printf("MonsterCMD_UPDATE\n");
	//��ʶ�Ƿ��ҵ�ָ��id�Ĺ���
	bool found=false;
	MonsterProperty prop;
	memset((char*)&prop,'\0',sizeof(MonsterProperty));
	memcpy((char*)&prop,(char*)pData,sizeof(MonsterProperty));
	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_monsterlist);
	for(list_oper=monster_list.begin();list_oper!=monster_list.end();++list_oper)
	{
		MyMonster *p=*list_oper;
		if(p->GetMonsterId()==prop.ID){
			printf("id:%d  %3.1f %3.1f %3.1f\n",prop.ID,prop.pos.X,prop.pos.Y,prop.pos.Z);
			p->setMonsterProperty(prop);
			found=true;
			break;
		}
	}
	//////---------------------------------------------------------------------------------------------///////////////	
	::LeaveCriticalSection(&g_cs_monsterlist);
	//�����δ֪����,�������������Ϣ
	if(found==false ){
		printf("��δ֪����id:%d,�������������Ϣ\n",prop.ID);
		prop.cmd=MonsterCMD_UNKNOWMONSTER;
		net->SendMsg((char*)&prop,sizeof(MonsterProperty));
	}
	

}

void MyMonstersMgr::MonsterCMD_LOGIN_PROC(char* pData,unsigned long length)
{

	printf("MonsterCMD_LOGIN\n");
	MonsterProperty prop;
	memset((char*)&prop,'\0',sizeof(MonsterProperty));
	memcpy((char*)&prop,(char*)pData,sizeof(MonsterProperty));


	//��ʾ�б��в����ڸ�id�Ĺ���.
	if(  GetMonsterByID(prop.ID) ==NULL){

		
		printf("id:%d�Ĺ��ﲻ����,���!\n",prop.ID);

		//	//MessageBox(0,"�Ĺ��ﲻ����,���!","",0);
		printf("id:%d %3.1f %3.1f %3.1f HP:%d\n",prop.ID,prop.pos.X,prop.pos.Y,prop.pos.Z,prop.HP);

		AddMonster(prop);
	
	}	else{
		printf("id:%d�Ĺ����Ѵ��ڻ��������,���ظ����!\n",prop.ID);
	}


}


//����֮���շ�������Ϣ,��������
void MyMonstersMgr::insertMonsterData(const char* pData,const unsigned int DataLength)
{
	ClientMsg* m=new ClientMsg();
	char* tmp=new char[DataLength];
	memcpy(tmp,pData,DataLength);
	m->pData=tmp;
	m->size=DataLength;

	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_msglist);
	msglist.push_back(m); //��ӽ���Ϣ����
	::LeaveCriticalSection(&g_cs_msglist);
	//////---------------------------------------------------------------------------------------------///////////////	




}

