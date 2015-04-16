#include ".\mycharactermgr.h"

MyCharacterMgr::MyCharacterMgr(MySceneManager* scenemgr)
{

	this->dev=getIrrDevice();
	myScene_Mgr=scenemgr;
	smgr=dev->getSceneManager();

	mouseDownL=false;

	character=0;//����ɫ

	timer=dev->getTimer();

	::InitializeCriticalSection(&g_cs_charlist);//��ʼ���ٽ�������

	::InitializeCriticalSection(&g_cs_msglist);//��ʼ���ٽ�������

	//��Ϣ���
	msglist.clear();

	//���߽�ɫ�б����
	char_list.clear();

}

MyCharacterMgr::~MyCharacterMgr(void)
{
}

//�����û���Ϣ,���Է�����
void MyCharacterMgr::insertCharData(const char* pData,const int DataLength)
{
	printf(" MyCharacterMgr::insertCharData\n");
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

//��������������Ľ�ɫ��Ϣ
void  MyCharacterMgr::DoListThread( )
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

			//����ɫ��½
			if(cmd==CMD_S2C_User_LOGIN){
				CMD_USERLOGIN_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
				//�������߽�ɫ��½
			}else if(cmd==CMD_S2C_NEWUSER){
				CMD_NEWUSER_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
				//����ɫ��������ɫ����
			}else if(cmd==CMD_UserUPDATE){
				////MessageBox(0,"��ɫ����!","",0); ����������.�ȵ�
				CMD_UserUPDATE_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_USERMSG){
				CMD_USERMSG_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_QUIT){
				CMD_QUIT_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_S2C_USERUNDERATTACK){
				CMD_USERUNDERATTACK_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_S2C_USERMoneyUpdate){
				////MessageBox(0,"��ɫ��Ǯ������Ϣin!","",0);
				//����,������ķ���д���˱�������proc
				CMD_USERMoneyUpdate_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_S2C_Response_Prop){
				//��������Ӧ��ɫ��������������Ϣ
				CMD_ServerResponse_Prop_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_S2C_Response_ChangeWeapon){
				//MessageBox(0,"�������������߽�ɫ������!!!","",0);
				//�������������߽�ɫ������
				CMD_Response_ChangeWeapon_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_S2C_Response_Package){
				//���������ؽ�ɫ�İ���
				CMD_S2C_Response_Package_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else if(cmd==CMD_S2C_Response_ChangeWorld){
				//������Ҫ���ɫ�л���ͼ
				CMD_S2C_Response_ChangeWorld_PROC((*msg_oper)->pData,(*msg_oper)->size);
				delete (*msg_oper)->pData;
				delete (*msg_oper);
				msglist.erase(msg_oper);
				break;
			}else{
				char temp[255];
				sprintf(temp,"��δ֪��cmd:%d",cmd);
				MessageBox(0,temp,"",0);
			}



		}
	}

	::LeaveCriticalSection(&g_cs_msglist);
	//////---------------------------------------------------------------------------------------------///////////////	

	

}

//����ɫ������������������߽�ɫ
void MyCharacterMgr::getOnlineAllCharacter()
{
	RoleProperty p;
	memset((char*)&p,'\0',sizeof(RoleProperty));
	p.cmd=CMD_C2S_Request_AllOnlineRole;
	myScene_Mgr->client->SendMsg((char*)&p,4); //͵��4λ�̶���С��.����ûʲô��Ҫ����

}

//�������н�ɫ������ʾ?
void MyCharacterMgr::setAllRoleWeaponVisible(bool v)
{
	character->m_weapon_mgr->setWeaponVisible(v);

	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{

		MyCharacter *p=*list_oper;
		p->m_weapon_mgr->setWeaponVisible(v);
	}
	::LeaveCriticalSection(&g_cs_charlist);
	//////---------------------------------------------------------------------------------------------///////////////	


}

//�������н�ɫ��װ��ʾ?
void MyCharacterMgr::setAllRoleClothVisible(bool v)
{
	character->m_charClothMgr->setClothVisible(v);

	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{

		MyCharacter *p=*list_oper;
		p->m_charClothMgr->setClothVisible(v);
	}
	::LeaveCriticalSection(&g_cs_charlist);
	//////---------------------------------------------------------------------------------------------///////////////	

}

//������Ҫ���ɫ�л���ͼ
void MyCharacterMgr::CMD_S2C_Response_ChangeWorld_PROC(char* pData,unsigned long length)
{
	RoleProperty srp;
	memcpy((char*)&srp,(char*)pData,sizeof(RoleProperty));

	//��ɫ���������ͼid
	character->SetWorldMap(srp.worldMap_id ) ;

	//��ɫ��������
	character->setPosition(srp.pos);

	//�л�����ģ��
	myScene_Mgr->ChangeWorld(srp.worldMap_id);
}

//��ɫ��������
void MyCharacterMgr::CMD_S2C_Response_Package_PROC(char* pData,unsigned long length)
{
	//MessageBox(0,"��������.�������ҽ�ɫ","",0);

	if(sizeof(Package)!=length){
		 MessageBox(0,"CMD_S2C_Response_Package_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}
	Package pack;
	memcpy((char*)&pack,(char*)pData,sizeof(Package));

	//���ж�sock.�Ƿ�����ɫ
	if(character->getRoleproperty().sock==pack.sock){
		//MessageBox(0,"����ɫ��������","",0);

		//�����ȸ�������,���������Ÿı������ı�Ļ�.
		if(character->getPackage()->currWeapon!=pack.currWeapon || character->getPackage()->weaponparam1!=pack.weaponparam1 ){
			//������ʾ����
			character->setCurWeapon(pack.currWeapon,pack.weaponparam1);
			char temp[255];
			sprintf(temp,"��������%d",pack.currWeapon);
			////MessageBox(0,temp,"",0);


		}
		//���°���
		character->setPackage(pack);
	}


	//����������ɫ
	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{

		MyCharacter *p=*list_oper;
		if(p->getRoleproperty().sock==pack.sock)
		{
			////MessageBox(0,"������ɫ��������","",0);
			//��������
			////MessageBox(0,"CMD_Response_ChangeWeapon_PROC!!!","",0);
			if(p->getPackage()->currWeapon != pack.currWeapon) p->m_weapon_mgr->ChangeWeapon(pack.currWeapon,pack.weaponparam1);
			//���°���
			p->setPackage(pack);
			break;
		}
	}
	::LeaveCriticalSection(&g_cs_charlist);
	//////---------------------------------------------------------------------------------------------///////////////	


	
	
}

//�������߽�ɫ��������
void  MyCharacterMgr::CMD_Response_ChangeWeapon_PROC(char* pData,unsigned long length)
{
	//MessageBox(0,"�������߽�ɫ�������� ","",0);
	
	//ֻ��ȡ9�ֽ�...
	if(length!=9)
	{
		 MessageBox(0,"CMD_Response_ChangeWeapon_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
		return;
	}
	Package srp;
	memset((char*)&srp,0,sizeof(Package));
	memcpy((char*)&srp,(char*)pData, 9 );

	//����������ɫ
	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{

		MyCharacter *p=*list_oper;
		if(p->getRoleproperty().sock==srp.sock)
		{
			//��������
			//char str[255];
			p->m_weapon_mgr->ChangeWeapon(srp.currWeapon,srp.weaponparam1);
			printf("==����������ɫ%s��������param%d\n",p->getRoleproperty().roleName,srp.weaponparam1);
			//MessageBox(0,str,"",0);
			break;
		}
	}
	::LeaveCriticalSection(&g_cs_charlist);
	//////---------------------------------------------------------------------------------------------///////////////	

}

//����������
void MyCharacterMgr::CMD_ServerResponse_Prop_PROC(char* pData,unsigned long length)
{
	if(sizeof(RoleProperty)!=length){
	 	 MessageBox(0,"CMD_ServerResponse_Prop_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}
	//MessageBox(0,"����������","",0);
	RoleProperty srp;
	memcpy((char*)&srp,(char*)pData,sizeof(RoleProperty));

	//ֱ��������������������
	character->setPropPlane(&srp);
}

//��ɫ��Ǯ������Ϣ
void MyCharacterMgr::CMD_USERMoneyUpdate_PROC(char* pData,unsigned long length)
{
	if(sizeof(Package)!=length){
	  	 MessageBox(0,"CMD_USERMoneyUpdate_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}

	Package srp;
	memcpy((char*)&srp,(char*)pData,sizeof(Package));
	//printf("CMD_UserUPDATE: name:%s sock:%d  pos:%3.1f %3.1f %3.1f \n",srp.roleName,srp.sock,srp.pos.X,srp.pos.Y,srp.pos.Z);
	printf("--����ɫ%d��Ǯ������Ϣ money:%d sock:%d --\n",srp.sock,srp.money,srp.sock);
	//ֱ������
	character->setMoney(srp.money);

}


//��ɫ��������Ϣ ��������ɫ��������ɫ
void MyCharacterMgr::CMD_USERUNDERATTACK_PROC(char* pData,unsigned long length)
{
	if(sizeof(RoleProperty)!=length){
		MessageBox(0,"CMD_USERUNDERATTACK_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}

	RoleProperty srp;
	memcpy((char*)&srp,(char*)pData,sizeof(RoleProperty));
	//printf("CMD_UserUPDATE: name:%s sock:%d  pos:%3.1f %3.1f %3.1f \n",srp.roleName,srp.sock,srp.pos.X,srp.pos.Y,srp.pos.Z);


	printf("--�н�ɫ������ sock:%d--",srp.sock);

	//�ж��Ƿ�����ɫ������
	if(character->getRoleproperty().sock==srp.sock){

		printf("--����ɫ������name:%s-- hp:%d  currState:%d  \n",srp.roleName,srp.HP,srp.currState);
		//ֻ����hpֵ
		int lasthp=character->getRoleproperty().HP;
		int damage=lasthp-srp.HP;//�����˺�ֵ

		//��ʾ�˺���
		character->UnderAttack(damage);

		return;
	}

	//�Ƿ���������ɫ������
//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{
		
		MyCharacter *p=*list_oper;
		if(p->getRoleproperty().sock==srp.sock)
		{

			printf("--name:%s������--  hp:%d currState:%d \n",srp.roleName,srp.HP,srp.currState);
			//ֻ����hpֵ
			int lasthp=p->getRoleproperty().HP;
			int damage=lasthp-srp.HP;//�����˺�ֵ

			//��ʾ�˺���
			//bug ��characterд����.�����������ɫ������,����ɫҲ��������..
			p->UnderAttack(damage);
			break;
		}
	}
	::LeaveCriticalSection(&g_cs_charlist);
//////---------------------------------------------------------------------------------------------///////////////	

}

void MyCharacterMgr::CMD_QUIT_PROC(char* pData,unsigned long length)
{  
	if(sizeof(RoleProperty)!=length){
		MessageBox(0,"CMD_QUIT_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}


	RoleProperty srp;
	memcpy((char*)&srp,(char*)pData,sizeof(RoleProperty));
//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{
		MyCharacter *p=*list_oper;
		if(p->getRoleproperty().sock==srp.sock)
		{

			printf("--�����˳��� name:%s sock:%d !--\n",srp.roleName,srp.sock);
			
			p->drop();
			delete p;
			p=0;
			char_list.erase(list_oper);

			break;
		}
	}
	::LeaveCriticalSection(&g_cs_charlist);

//////---------------------------------------------------------------------------------------------///////////////	

}
void MyCharacterMgr::CMD_USERLOGIN_PROC(const char* pData,const unsigned long length)
{		
	if(sizeof(RoleProperty)!=length){
		MessageBox(0,"CMD_USERDATA_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}

	printf("����ɫ��Ϣ��ȡ��� CMD_USERDATA\n");
	
	
	//�������ɫ
	AddMainCharacter( pData, length);

	//�������������
	myScene_Mgr->myCamera->setTargetNode(character->getNode());

}

void MyCharacterMgr::CMD_NEWUSER_PROC(char* pData,unsigned long length)
{
	if(sizeof(RoleProperty)!=length){
		MessageBox(0,"CMD_NEWUSER_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}

	printf("-CMD_NEWUSER ================------------\n");
	
	AddCharacter(pData, length);
	printf("���߽�ɫ��Ϣ��ȡһ�� CMD_NEWUSER\n");
}



void MyCharacterMgr::CMD_USERMSG_PROC(char* pData,unsigned long length )
{
	if(sizeof(ServerRoleMSG)!=length){
		MessageBox(0,"CMD_USERMSG_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}

	ServerRoleMSG msg;
	memcpy((char*)&msg,(char*)pData,sizeof(ServerRoleMSG));
	printf("--���˺�����,����֪˭--\n");
//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{
		MyCharacter *p=*list_oper;
		if(p->getRoleproperty().sock==msg.sock)
		{
			printf("--���˺����� name:%s sock:%d msg:%s--\n",p->getRoleproperty().roleName,msg.sock,msg.msg);
			WCHAR * pwStr = ConvertLPCSTRToLPWSTR( msg.msg ); 
			//��ɫͷ����ʾ��
			p->PostMsg((const wchar_t*)pwStr);

			//�����ַ��� ��ɫ��:˵�Ļ�
			WCHAR * pwname = ConvertLPCSTRToLPWSTR(p->getRoleproperty().roleName ); 
			stringw temp="";
			temp+=pwname;
			temp+=":";
			temp+=pwStr;
			delete pwname;
			//��gui��listbox��ʾһ�к���
			myScene_Mgr->myGUI_Mgr->PostMsg(temp.c_str());
			delete pwStr;
			break;
			
		}
	}
	::LeaveCriticalSection(&g_cs_charlist);
//////---------------------------------------------------------------------------------------------///////////////	

}


void MyCharacterMgr::CMD_UserUPDATE_PROC(char* pData,unsigned long length )
{
	if(sizeof(RoleProperty)!=length){
		MessageBox(0,"CMD_UserUPDATE_PROC ��ȡ��С�ͽṹ��С��һ��!","",0);
	}
		RoleProperty srp;
		memcpy((char*)&srp,(char*)pData,sizeof(RoleProperty));
		//printf("CMD_UserUPDATE: name:%s sock:%d  pos:%3.1f %3.1f %3.1f \n",srp.roleName,srp.sock,srp.pos.X,srp.pos.Y,srp.pos.Z);
		
		//�ж��Ƿ�����ɫ����
		if(character->getRoleproperty().sock==srp.sock){

			printf("--����ɫ����name:%s-- hp:%d  currState:%d  \n",srp.roleName,srp.HP,srp.currState);

		//	MessageBox(0,"����ɫ����","",0);
			//����ɫ���Ը���
			character->setRoleproperty(srp);
			return;
		}
		
		
		bool found=false;//�ҵ�ָ��id��ɫ
//////---------------------------------------------------------------------------------------------///////////////		
		::EnterCriticalSection(&g_cs_charlist);
		irr::core::list<MyCharacter*>::Iterator  list_oper;
		for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
		{
			
			MyCharacter *p=*list_oper;
			if(p->getRoleproperty().sock==srp.sock)
			{
				//���ұ�־,
				found=true;

				printf("-�пͻ�����-name:%s-- HP:%d currState:%d \n",srp.roleName,srp.HP,srp.currState);
				p->lastRecvtime=timer->getRealTime();
				p->setRoleproperty(srp);
				
				//����������������
				p->UpdateByProperty();
				break;
			}
		}

		::LeaveCriticalSection(&g_cs_charlist);
//////---------------------------------------------------------------------------------------------///////////////	
		//�����δ֪��ɫ,�������������Ϣ
		if(found==false){
			printf("��δ֪��ɫ,�������������Ϣ\n");
			srp.cmd=CMD_C2S_UNKNOWUSER;
			myScene_Mgr->client->SendMsg((char*)&srp,sizeof(RoleProperty));
		}

}


void MyCharacterMgr::AddCharacter(char *pData,unsigned long length )
{
	if(sizeof(RoleProperty) != length){
			MessageBox(0,"AddCharacter ��ȡ��С�ͽṹ��С��һ��!","",0);
	}

	//��ʼ����ɫ����
	RoleProperty pp;
	memset((char*)&pp,'\0',sizeof(RoleProperty));
	memcpy((char*)&pp,pData,sizeof(RoleProperty));

	//��ʾ�б��в����ڸ�id�Ĺ���.
	if(  GetCharacterByID(pp.sock) ==NULL){
		printf("id:%d�Ľ�ɫ������,���! hp:%d\n",pp.sock,pp.HP);
		//	//MessageBox(0,"�Ĺ��ﲻ����,���!","",0);
		printf("id:%d HP:%d\n",pp.sock,pp.HP);

		//��ʼ����ɫ
		MyCharacter* c=new MyCharacter(pp,false,myScene_Mgr->myscene_loader); //���һ������ false ��ʾ�����.���ǵ�ǰ����ɫ

		//////---------------------------------------------------------------------------------------------///////////////	
		::EnterCriticalSection(&g_cs_charlist);
		char_list.push_back(c);
		::LeaveCriticalSection(&g_cs_charlist);
		//////---------------------------------------------------------------------------------------------//////////////

		c->Draw();
		//c->setPosition(pp.pos);
		c->lastRecvtime=timer->getRealTime();

	}	else{
		printf("id:%d�Ľ�ɫ�Ѵ��ڻ��������,���ظ����!\n",pp.sock);
	}


}


void MyCharacterMgr::AddMainCharacter(const char* pData,const unsigned long length)
{
	if(sizeof(RoleProperty) != length){
		MessageBox(0,"AddMainCharacter ��ȡ��С�ͽṹ��С��һ��!","",0);
	}


	//����ɫ�Ѵ��ڼ��ѵ�½,����.
	if(character){
		
		MessageBox(0,"�ҿ�,�����.��AddMainCharacter!!","",0);
		return ;
	}

    //��ʼ��������
	//���ؽ�ɫģ��
	RoleProperty main_property;
	memset((char*)&main_property,'\0',sizeof(RoleProperty));
	memcpy((char*)&main_property,pData,sizeof(RoleProperty));

	//character=new MyCharacter(dev,"by//by.ms3d",main_property,true);
	//character=new MyCharacter(dev,"yunhe//yunhe.ms3d",main_property,true);
	character=new MyCharacter(main_property,true,myScene_Mgr->myscene_loader);
	character->Draw();
	character->setPosition(main_property.pos);
	character->SetNetServer(this->myScene_Mgr->client);


	//��ʼ�л�����ģ��
	myScene_Mgr->ChangeWorld(main_property.worldMap_id);

	printf("������!����ɫ��%s sock:%d isDeath:%d\n",main_property.roleName, main_property.sock,main_property.isDeath	  );

}

//
MyCharacter*  MyCharacterMgr::GetCharacterByID(int sock)
{
	MyCharacter* p_char=0;
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{
		MyCharacter *p=*list_oper;
		if(p->getRoleproperty().sock==sock) 
		{
		   p_char=p;
		}
	}
	::LeaveCriticalSection(&g_cs_charlist);

	return p_char;
}

void MyCharacterMgr::update()
{
	
	//�ȴ�������������Ľ�ɫ��Ϣ
    DoListThread();


DWORD static startmovetime=0;


   //������, ���ûָ������npc ���ý�ɫ�ƶ�
  if(mouseDownL && myScene_Mgr->monster_mgr->GetNodeIsselected()==false && myScene_Mgr->npc_mgr->IsselectedNPC()==false 
	 ) 
  {
	
	  //����500����ŷ���
	  if(GetTickCount()-startmovetime>100){
		 startmovetime=GetTickCount();
	 
		 //  //ȡ������
		    character->CancelAttack();

		    //��ɫ�ƶ���Ŀ��
			
			//�õ���Ļ���ת����3d������һ������
			
			core::triangle3df triangle;
			core::line3d<f32> line;//��ײ��
			line=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(dev->getCursorControl()->getPosition());
			//�͵�����ײ
			
			const ISceneNode* outnode;
			if (smgr->getSceneCollisionManager()->getCollisionPoint(
				 			line, //[in] ����
				 			myScene_Mgr->myscene_loader->getMeta(), //[in] �����ڵ��������ѡ����
				 			line.end, //[out] ������ײ��
				 			triangle,outnode)) //[out] ������ײ������
			{
							vector3df target_pos;
				 			target_pos.X=line.end.X;
				 			target_pos.Z=line.end.Z;
				 			target_pos.Y=line.end.Y;
					 		 
							//�ж�ѡ����ƶ������Ƿ��ڲ����ƶ�������,����,���ɫ�ƶ�
							if(character->sceneloader->Pointisin(target_pos)){
								
							}else{
							
								//�������ѡ���ƶ���ͽ�ɫ̫��,���¶���bug
								f32 len=character->getPosition().getDistanceFrom(target_pos);
								if(len>4){
									character->Beginmove(target_pos);
								}
							}
			}


	  }


	}

  //����ɫ����
  if(character)	character->update();

//////---------------------------------------------------------------------------------------------///////////////	
	//�������߽�ɫ�������Ը���
	u32 thistime=timer->getRealTime();
	::EnterCriticalSection(&g_cs_charlist);
		irr::core::list<MyCharacter*>::Iterator  list_oper;
   		for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
		{
				
			    MyCharacter *p=*list_oper;

				if(p) 
				{
					//�ȱ�־δ���ָ���ɫ
					p->mouseCurCharacter=false;
					
					p->Onlyupdate();

					////������ģ��
					//if(p->ModelState==1){
					//	p->Draw();
					//}else if(p->ModelState==3){
					//	//��ɾ��ģ��
					//	p->drop();
					//	delete p;
					//	p=0;
					//	char_list.erase(list_oper);
					//	break;
					//}
					//else 
					  if(thistime-p->lastRecvtime >5000  || p->getRoleproperty().worldMap_id!=character->getRoleproperty().worldMap_id) {
						//����5��û��Ӧ,���϶���ɫ�˳���
					//	p->drop();
					//	delete p;
					//	p=0;
					//	char_list.erase(list_oper);
					//	break;
					}
					
				}
		}
	 ::LeaveCriticalSection(&g_cs_charlist);
//////---------------------------------------------------------------------------------------------///////////////	

	 scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	 //�õ���Ļ���ת����3d������һ������
	 vector2d<s32> curpos=dev->getCursorControl()->getPosition();
	 core::line3d<f32> line;
	 line=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(curpos);
	 //����2.
	 core::vector3df intersection;
	 core::triangle3df hitTriangle;

	 //ʰȡ�������߽�ɫ
	 ISceneNode * select_char_node =collMan->getSceneNodeAndCollisionPointFromRay(
		 line,
		 intersection, // This will be the position of the collision
		 hitTriangle, // This will be the triangle hit in the collision
		 0, // This ensures that only nodes that we have
		 // set up to be pickable are considered
		 0); // Check the entire scene (this is actually the implicit default)

	 //ʰȡ�˽�ɫ
	 if(select_char_node){
		//printf("ʰȡ%d!\n",select_char_node->getID() );
		 //���ݽڵ�õ�������
		 MyCharacter* sel_char=GetCharacterByID(select_char_node->getID());
		 if(select_char_node->getID() == GetMainCharacter()->getRoleproperty().sock){
			// printf("ʰȡ������ɫ!\n");
			return;
		 }
		 
		 if( sel_char==NULL ){
			
		 }else {

			 //��־�����ɫ�౻ʰȡ��.��������ʾѪ��
             sel_char->mouseCurCharacter=true;
			//  printf("ʰȡ�˽�ɫ%s \n", sel_char->getRoleproperty().roleName );
		 }
	 }else{
		// printf("ʰȡʧ��!!!!\n");
	 }
}


//��ɫui��Ⱦ
void MyCharacterMgr::UIRender()
{
	if(character) character->UIRender();

//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{

		MyCharacter *p=*list_oper;
		if(p) p->UIRender();
	}
	::LeaveCriticalSection(&g_cs_charlist);
//////---------------------------------------------------------------------------------------------///////////////	
}

//�Ƴ��������߽�ɫ.�����л�����ʱ��.
void MyCharacterMgr::RemoveAllCharacter()
{
	//////---------------------------------------------------------------------------------------------///////////////	
	::EnterCriticalSection(&g_cs_charlist);
	irr::core::list<MyCharacter*>::Iterator  list_oper;
	for(list_oper=char_list.begin();list_oper!=char_list.end();++list_oper)
	{

		MyCharacter *p=*list_oper;
		if(p){
			p->drop();
			delete p;
			p=0;
			
		}
	}
	char_list.clear();

	::LeaveCriticalSection(&g_cs_charlist);
	//////---------------------------------------------------------------------------------------------///////////////	
}

void MyCharacterMgr::OnEvent (const irr::SEvent& e)
{ 
	//����ɫ�����¼�
	if(character) character->OnEvent(e);

		if(e.EventType==EET_MOUSE_INPUT_EVENT)
		{
			 if(e.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)   mouseDownL = true;
		   
			 if(e.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)      mouseDownL = false; 
		}



}
