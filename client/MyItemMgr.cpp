#include ".\myitemmgr.h"

MyItemMgr::MyItemMgr(MySceneManager* mysmgr, Socket::CNetClient* net)
{
	this->dev=getIrrDevice();
	this->net=net;

	::InitializeCriticalSection(&g_cs_SceneItem_list);//��ʼ���ٽ�������

	::InitializeCriticalSection(&g_cs_msglist);//��ʼ���ٽ�������

	SceneItem_list.clear();

	m_pMySceneMgr=mysmgr;
}

MyItemMgr::~MyItemMgr(void)
{
}

//�����������������Ʒ��Ϣ
void  MyItemMgr::DoListThread( )
{
	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_msglist);

	//����������Ϣ.ֱ��������ŷ���..
	//	while (msglist.getSize()>0)
	{

		irr::core::list<ClientMsg*>::Iterator  msg_oper;
		for(msg_oper=msglist.begin();msg_oper!=msglist.end();++msg_oper)
		{

			unsigned char cmd=(*msg_oper)->pData[0];
			printf("MyCharacterMgr DoListThread cmd:%d\n",cmd);

			//��Ʒ���
			if(cmd==SceneCMD_ITEMDROP){
				SceneCMD_ITEMDROP_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
				
			}else if(cmd==SceneCMD_ITEMDROPRemove){
				SceneCMD_ITEMDROPRemoveProc((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			
			}

		}
	}

	::LeaveCriticalSection(&g_cs_msglist);
	//////---------------------------------------------------------------------------------------------///////////////	


}


//�Ƿ����г���������Ʒ�Ƿ�ɼ�
void MyItemMgr::setAllItemVisiable(bool v)
{
	::EnterCriticalSection(&g_cs_SceneItem_list);
	std::list<MyItem*>::iterator  list_oper;
	for(list_oper=SceneItem_list.begin();list_oper!=SceneItem_list.end();++list_oper)
	{
		MyItem* t=(*list_oper);
		if(t->node) t->node->setVisible(v);
	}
	::LeaveCriticalSection(&g_cs_SceneItem_list);

}

////��ͼ�ĵ�����Ʒ���
void MyItemMgr::RemoveAllItem()
{
	::EnterCriticalSection(&g_cs_SceneItem_list);
	std::list<MyItem*>::iterator  list_oper;
	for(list_oper=SceneItem_list.begin();list_oper!=SceneItem_list.end();++list_oper)
	{
		MyItem* t=(*list_oper);
		t->drop();
		delete t;
		t=0;
	}

	SceneItem_list.clear();

	::LeaveCriticalSection(&g_cs_SceneItem_list);
}

//�õ����г����ĵ�����Ʒ
void MyItemMgr::getSceneCMD_ITEMDROPAll()
{
	printf("MySceneItemMgr �������е�����Ʒ\n");
	SceneItem item;
	item.cmd=SceneCMD_ITEMDROPAll;
	item.item_Type=0;
	strcpy(item.itemName,"a");
	item.pos=vector3df(0,0,0);
	net->SendMsg((char*)&item,sizeof(SceneItem));


}

//�����û���Ϣ,���Է�����
void MyItemMgr::insertItemData(const char* pData,const unsigned int DataLength)
{
	printf("MySceneItemMgr insertItemData\n");

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


void MyItemMgr::SceneCMD_ITEMDROP_PROC(char* pData,unsigned long length)
{

	printf("SceneCMD_ITEMDROP \n");
	SceneItem item;
	memcpy((char*)&item,(char*)pData,sizeof(SceneItem));

	//�Ȳ���һ���Ƿ��Ѵ��ڸ���Ʒ
	bool already_exist=false;
	::EnterCriticalSection(&g_cs_SceneItem_list);
	std::list<MyItem*>::iterator  list_oper;
	for(list_oper=SceneItem_list.begin();list_oper!=SceneItem_list.end();++list_oper)
	{
		MyItem* t=(*list_oper);
		if(t->item.item_Type==item.item_Type 
			&& t->item.param1==item.param1 
			&& t->item.param2==item.param2 
			&& t->item.param3==item.param3 
			&& t->item.param4==item.param4 
		    && t->item.param5==item.param5
			&& t->item.param6==item.param6 
			&& t->item.item_index==item.item_index
			&& t->item.pos==item.pos
			){
				already_exist=true;
				break;
			}
	}
	::LeaveCriticalSection(&g_cs_SceneItem_list);

	//������
	if( already_exist==false){

		printf("index:%d %3.1f %3.1f %3.1f HP:%d\n",(int)item.item_index,item.pos.X,item.pos.Y,item.pos.Z );

		//���
		if(item.item_Type==ITEMType_Money)
		{
			////MessageBox(0,"�н�ҵ���!","",0);
			::EnterCriticalSection(&g_cs_SceneItem_list);
			//////---------------------------------------------------------------------------------------------///////////////
			//ֻ������Ʒ��.��ʼ����Ʒ����,���ڸ��̼߳���ģ�͡���Ϊirr�̲߳���ȫ.ֻ������Ʒ������ģ��״̬.��update�����. update�����߳���.�ǰ�ȫ��
			MyItem* money=new MyItem("item/coin/coin.ms3d",item);
			money->Draw();
			SceneItem_list.push_back(money);
			::LeaveCriticalSection(&g_cs_SceneItem_list);
			//////---------------------------------------------------------------------------------------------///////////////
			printf("ITEM_Money \n");
		}else if(item.item_Type==ITEMType_Item){
			::EnterCriticalSection(&g_cs_SceneItem_list);
			//////---------------------------------------------------------------------------------------------///////////////
			//ֻ������Ʒ��.��ʼ����Ʒ����,���ڸ��̼߳���ģ�͡���Ϊirr�̲߳���ȫ.ֻ������Ʒ������ģ��״̬.��update�����. update�����߳���.�ǰ�ȫ��
			MyItem* money=new MyItem("item/box/box.ms3d",item);
			money->Draw();
			SceneItem_list.push_back(money);
			::LeaveCriticalSection(&g_cs_SceneItem_list);
			printf("ITEMType_Item \n");
		}

	}else{
		//�Ѵ��ڸ���Ʒ����
		printf("id:%d����Ʒ�Ѵ��ڻ��������,���ظ����!\n",item);
		return;
	}


}

//��Ʒ��ʧ
void MyItemMgr::SceneCMD_ITEMDROPRemoveProc(char* pData,unsigned long length)
{	
	printf("CMD_ITEM Remove \n");
	SceneItem item;
	memcpy((char*)&item,(char*)pData,sizeof(SceneItem));
	
//////---------------------------------------------------------------------------------------------///////////////
	::EnterCriticalSection(&g_cs_SceneItem_list);
		std::list<MyItem*>::iterator  list_oper;
		for(list_oper=SceneItem_list.begin();list_oper!=SceneItem_list.end();++list_oper)
		{
			 MyItem* t=(*list_oper);
			 if(t->item.item_Type==item.item_Type 
				 //&& t->item.param1==item.param1 
				 //&& t->item.param2==item.param2 
				 //&& t->item.param3==item.param3 
				 //&& t->item.param4==item.param4 
			  //   && t->item.param5==item.param5
				 //&& t->item.param6==item.param6 
				 && t->item.item_index==item.item_index
				 && t->item.pos==item.pos
			   ){
				  
				   //ֻ������Ʒ��ı�־ ��ɾ�� 
				   //t->ModelState=3;
				   t->drop();
				   delete t;
				   t=0;
				   SceneItem_list.erase(list_oper);
				   break;
			 }
			
		}
	
		if(SceneItem_list.size()>0){
			
		}

	::LeaveCriticalSection(&g_cs_SceneItem_list);
//////---------------------------------------------------------------------------------------------///////////////

	
}

void MyItemMgr::update()
{
	//�ȴ����������������Ʒ��Ϣ
	DoListThread();

	//return;

	//////---------------------------------------------------------------------------------------------///////////////
	::EnterCriticalSection(&g_cs_SceneItem_list);
	std::list<MyItem*>::iterator  list_oper;
	for(list_oper=SceneItem_list.begin();list_oper!=SceneItem_list.end();++list_oper)
	{
		MyItem* t=(*list_oper);
	
//-------------------------------------------------------------------------------------
		//�õ���Ʒ���� �ǹ̶��˵�
		t->line.start=t->item.pos;
		t->line.start.Y+=10;
		//�õ������������ 
		t->line.end= m_pMySceneMgr->myCamera->getNode()->getPosition();
		//line.end.Y+=10;
		vector3df vec=m_pMySceneMgr->char_mgr->GetMainCharacter()->getPosition()-t->item.pos;
		vec.normalize();
		//	p->line.end-=vec*5;
		//	p->line.start-=vec*5;

		core::triangle3df triangle;
		const ISceneNode* outnode;
		//��npc���������3d�߶κͳ�������,����ģ����ײ.�����.��˵������֮�����ڵ�.�Ͱ�npc����.
		if (getIrrSmgr()->getSceneCollisionManager()->getCollisionPoint(
			t->line, //[in] ����
			m_pMySceneMgr->myscene_loader->getMeta(), //[in] �����ڵ��������ѡ����
			t->line.end, //[out] ������ײ��
			triangle,outnode)) //[out] ������ײ������
		{
			//printf("itemmgr select id:%d\n",outnode->getID());

			t->node->setVisible(false);
		}else{
			t->node->setVisible(true);
		}
//------------------------------------------------------------------------------------------

	}

	::LeaveCriticalSection(&g_cs_SceneItem_list);
	//////---------------------------------------------------------------------------------------------///////////////

}


//��ʾ��Ʒ����
void MyItemMgr::UIRender()
{
	::EnterCriticalSection(&g_cs_SceneItem_list);
	//////---------------------------------------------------------------------------------------------///////////////
	std::list<MyItem*>::iterator  list_oper;
	for(list_oper=SceneItem_list.begin();list_oper!=SceneItem_list.end();++list_oper)
	{
		MyItem* item=(*list_oper);
		item->UIRender();
	}
	::LeaveCriticalSection(&g_cs_SceneItem_list);
	//////---------------------------------------------------------------------------------------------///////////////
}
