#include "StdAfx.h"
#include ".\myscenemanager.h"

MySceneManager* sm;




char filestr[255]="vector.txt";
	ITimer* timer;
	u32 lasttime;

MySceneManager::MySceneManager(  Socket::CNetClient* client)
{
sm=this;

this->client=client;

myCamera=NULL;
monster_mgr=NULL;
char_mgr=NULL;
npc_mgr=0;
item_mgr=0;
myGUI_Mgr=0;

dev=getIrrDevice();
smgr=getIrrSmgr();
drv=getIrrDriver();

mouseDownL=false;
mouseDownR=false;

muoseclick=0;
lastmouseclick=0;

timer=dev->getTimer();
lasttime=timer->getRealTime();

//��ʼ������������,�����л�������Դ
myscene_loader=0;
myscene_loader=new MySceneLoader();

changeworld=false;

}

MySceneManager::~MySceneManager(void)
{
}

void MySceneManager::Render()
{
   		//�����ṩһ������--------------------------------------------------------------------------------------------------------------------------
		core::matrix4 mat;
		video::SMaterial material;
		material.TextureLayer[0].Texture= 0;
		material.Lighting = false;
		material.Thickness=2; //���ô�ϸ
		dev->getVideoDriver()->setTransform(video::ETS_WORLD, mat);
		dev->getVideoDriver()->setMaterial(material);

		//-----------------------------------------------------------------------------------------------------------------------------------------	
		//ѭ���������ѡȡ��������
		core::list<core::triangle3df*>::Iterator  list_oper;
		for(list_oper=myscene_loader->mylist.begin();list_oper!=myscene_loader->mylist.end();++list_oper)
		{
				core::triangle3df* temp_triangle;
				temp_triangle= *list_oper;
				drv->draw3DTriangle(*temp_triangle,video::SColor(255, 255, 0, 0));
		}
}


//ж�ص�ǰ����
void MySceneManager::DropCurrScene( )
{
   myscene_loader->DropCurrScene();
}

//���س���
void MySceneManager::LoadScene(int id)
{
	//���ó�������������
	myscene_loader->LoadScene(id,myCamera->getNode());

	//�������.�������ý�ɫ��Ҫ�ĵ�ͼָ��.������߶�.
	if(char_mgr->GetMainCharacter()){
		char_mgr->GetMainCharacter()->sceneloader=myscene_loader;
	}

}

//��ʼ��npc������ 
void MySceneManager::InitNpcMgr()
{
	npc_mgr=new MyNPCMgr(this);
}

//��ʼ�������
void MySceneManager::InitCamera()
{
	myCamera=new My3rdCamera(0);
}

//��ʼ����ɫ������
void MySceneManager::InitCharacterMgr()
{
	char_mgr=new MyCharacterMgr(this);	
}


/*
��ӹ��������
*/
void MySceneManager::InitMonsterMgr()
{
	//��Ҫ֪��device�ͽ�ɫ��Ϣ
	monster_mgr=new MyMonstersMgr(this,client);
}

void MySceneManager::InitItemMgr()
{
	//��ʼ����Ʒ����
	item_mgr=new MyItemMgr(this,client);
}

void MySceneManager::InitGUIMgr()
{
  myGUI_Mgr=new MyGUIManager(this);
  myGUI_Mgr->LoadGUI();

}

void MySceneManager::OnEvent (const irr::SEvent& e)
{
	
	//gui�����������¼�
	if(myGUI_Mgr ){
		myGUI_Mgr->OnEvent(e);
		//�Ƿ������gui��
		if( myGUI_Mgr->GetEditIsInput()==true){
			return;
		}
	}
	//npc������
	if(npc_mgr){
		npc_mgr->OnEvent(e);

		if(npc_mgr->MouseInNPC_GUI){
			return;
		}
	}

	//����������¼�
	if(myCamera)    myCamera->OnEvent(e);

	//��������������¼�
	if(monster_mgr)    monster_mgr->OnEvent(e);

	//��ɫ�����������¼�
	if(char_mgr)    char_mgr->OnEvent(e);

	
	//��������¼�
	   if (e.EventType == EET_KEY_INPUT_EVENT) {
			if (e.KeyInput.Key == KEY_DELETE && e.KeyInput.PressedDown==false) { 
				beginchange(); //change=!change;
		    }
			if (e.KeyInput.Key == KEY_END && e.KeyInput.PressedDown==false) { 
				printf("removeAllTriangleSelectors\n");
				//meta->removeAllTriangleSelectors();
				//CalculMeta();
		    }

			//ǰ��
			if (e.KeyInput.Key == KEY_KEY_W  ) { 
				float speed=char_mgr->GetMainCharacter()->getMoveSpeed();
				vector3df target_pos;
				vector3df campos=myCamera->getNode()->getPosition();
				vector3df rolpos= char_mgr->GetMainCharacter()->getPosition();
				vector3df dir=rolpos-campos;
				dir.normalize();
				target_pos=rolpos+dir*speed*15;
				//char_mgr->GetMainCharacter()->faceTarget(rolpos-dir*10);
				target_pos.Y=myscene_loader->getHeight(target_pos.X,target_pos.Z);//�����߶�
				char_mgr->GetMainCharacter()->Beginmove(target_pos);		
			}

			//����
			if (e.KeyInput.Key == KEY_KEY_S ) { 
				float speed=char_mgr->GetMainCharacter()->getMoveSpeed();
				vector3df target_pos;
				vector3df campos=myCamera->getNode()->getPosition();
				vector3df rolpos=char_mgr->GetMainCharacter()->getPosition();
				vector3df dir=rolpos-campos;
				dir.normalize();
				target_pos=rolpos-dir*speed*15;
				//char_mgr->GetMainCharacter()->faceTarget(rolpos-dir*10);
				target_pos.Y=myscene_loader->getHeight(target_pos.X,target_pos.Z);//�����߶�
				char_mgr->GetMainCharacter()->Beginmove(target_pos);		
			}


			/*
			if (e.KeyInput.Key == KEY_KEY_1 && e.KeyInput.PressedDown==false) { 
				
				this->myCamera->setTargetNode(	char_mgr->GetMainCharacter()->m_charClothMgr->getRootNode() );		

			}

			if (e.KeyInput.Key == KEY_KEY_2 && e.KeyInput.PressedDown==false) { 
				this->myCamera->setTargetNode(	char_mgr->GetMainCharacter()->m_charClothMgr->getRootNode() );		
			}

			if (e.KeyInput.Key == KEY_KEY_3 && e.KeyInput.PressedDown==false) { 
				this->myCamera->setTargetNode(	char_mgr->GetMainCharacter()->m_charClothMgr->getRootNode() );		
			}

			if (e.KeyInput.Key == KEY_KEY_4 && e.KeyInput.PressedDown==false) { 
				this->myCamera->setTargetNode(	char_mgr->GetMainCharacter()->m_charClothMgr->getRootNode() );		
			}
			*/
	   }

	   if (e.EventType == EET_MOUSE_INPUT_EVENT) 
	   {
		   if(e.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)    mouseDownL = true; muoseclick++;
		   if(e.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)    mouseDownR = true; 
		   if(e.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)	     mouseDownR = false; 
		   if(e.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)         mouseDownL = false; 
	   }

}

void MySceneManager::beginchange()
{			
	//static int count=1;
	//		if(character){
	//			printf("ɾ��char count:%d\n",count);
	//			char_mgr->GetMainCharacter()->drop();
	//			char_mgr->SetMainCharacter(0);
	//			// char_mgr->GetMainCharacter()=0;	
	//				this->myCamera->setTargetNode(0);//	monster_mgr->GetFirstMonster()->GetNode());
	//				//monster_mgr->setAllMonsterNoTarget();
	//				monster_mgr->SetCharacter(0);
	//				count++;
	//		}else{
	//			printf("���char count����:%d\n",count);
	//			   	character=new MyCharacter(dev,"yunhe//yunhe.ms3d");
	//				character->setPosition(vector3df(110,0.5,110));
	//				this->myCamera->setTargetNode(	character->getNode());		
	//				//��ȡ��ͼ���ƶ������ļ�
	//				//����ɫ�����ÿ��ƶ�����������list
	//				char_mgr->GetMainCharacter()->SetTrigleList(&this->mylist);
	//		}

}

void MySceneManager::ChangeWorld(int worldMap)
{
	//��־ Ҫ�л������� ����ֱ������дж�س������صĴ���.��Ϊ����һ���̵߳��õĻ�,�ᵼ�²�ͬ��.���ɾ����,�Ǳ��ڵ���.������һ������,����run��Ⱦ�߳����л�������
	changeworld=true;
	
	this->worldMap=worldMap;
	
}


void MySceneManager::Show(char* s)
{
	drv->beginScene (true, true, SColor (150, 150, 150, 150)); 

	
	smgr->drawAll();

	dev->getGUIEnvironment()->drawAll();

	TextLeft( s,vector2d<s32>(400,400),SColor(1,0,255,0),25,0);


	drv->endScene (); 
}

void MySceneManager::update()
{

	//�������������,�������Ƿ����ѡ���˹���
	if(monster_mgr ) monster_mgr->Update();

	//��ɫ����������
	if(char_mgr)    char_mgr->update();

	//npc����������
	if(npc_mgr) npc_mgr->update();


	//camera����
	if(myCamera)  myCamera->update();

	//������Ʒ����������
	if(item_mgr) item_mgr->update();

	//gui����������
	if(myGUI_Mgr) myGUI_Mgr->update();

	//��������������
	if(myscene_loader) myscene_loader->update();
	 
	
	//��������,�ͷ���������Ϣ��
	
	//ָ��������ʾ�������ɫ�ѽ�����
	if(char_mgr->GetMainCharacter())
	{

				u32 usetime=timer->getRealTime()-lasttime;
					
					//ÿ�������������һ�ν�ɫ��Ϣ
					if( usetime > 1000)
					{
						lasttime=timer->getRealTime();

						char_mgr->GetMainCharacter()->ReoprtToServer();
					}
					
				
	}
	


	//�Ƿ�Ҫ�л�����
	if(changeworld){
		
		Show("���س���");

		changeworld=false;

		//��ɫ�ƶ����³���������
		char_mgr->GetMainCharacter()->setPosition(char_mgr->GetMainCharacter()->getPosition());

		//�����ѵ���.
		char_mgr->GetMainCharacter()->idle(false);

		//Show("ж�ص�ǰ����");

		//ж�ص�ǰ����
		DropCurrScene();

		//��ͼ����������ɫ���
		char_mgr->RemoveAllCharacter();

		//��ͼ���߹������
		monster_mgr->RemoveAllMonsters();

		//��ͼ�ĵ�����Ʒ���
		item_mgr->RemoveAllItem();

		//����npc���
		npc_mgr->RemoveAllNPC();

		//�����³���
		LoadScene(worldMap);

		//����npc����
		npc_mgr->LoadSceneNPC(worldMap);

		//Show("�����³���");
		
		//���������������߽�ɫ
		char_mgr->getOnlineAllCharacter();

		//���󳡾����й���
		monster_mgr->getMonsterCMD_MonsterAll();

		//Sleep(200);

		//���󳡾�������Ʒ
		item_mgr->getSceneCMD_ITEMDROPAll();


	}



	
  //������ �ƶ�������������
  if(mouseDownL && muoseclick!=lastmouseclick)
  {
	  lastmouseclick=muoseclick;

	  //�Ƿ����ָ���˹���,����Ǿͱ�ʾ�빥������
	   if( monster_mgr->GetNodeIsselected()){
		  printf("scene GetNodeIsselected\n");
		     char_mgr->GetMainCharacter()->curAttackType = MyCharacter::eAttacktype::PowerAttack;  //��������
		  if(monster_mgr->GetselectedMonster()->IsDead()==false) char_mgr->GetMainCharacter()->SetWantToAttackTarget( monster_mgr->GetselectedMonster());
		   //char_mgr->GetMainCharacter()->FollowAndAttackTarget();

	   }

	   //�Ƿ�ѡ����npc
	   if(npc_mgr->IsselectedNPC()){
			//ѡ���˾���ʾ�Ի���
            npc_mgr->GetselectedNPC()->ShowTalkDlg();
	   }
	 
  }

  //�Ҽ����ܹ���
  if(mouseDownR ){
	  //�Ƿ����ָ���˹���,����Ǿͱ�ʾ�빥������
	  if( monster_mgr->GetNodeIsselected()){
		  printf("scene GetNodeIsselected\n");
		   char_mgr->GetMainCharacter()->curAttackType = MyCharacter::eAttacktype::MagicAttack;  //��������
		  if(monster_mgr->GetselectedMonster()->IsDead()==false) char_mgr->GetMainCharacter()->SetWantToAttackTarget( monster_mgr->GetselectedMonster());
		 // char_mgr->GetMainCharacter()->FollowAndAttackTarget();

	  }
  }


//  printf("%3.1f %3.1f %3.1f\n", b.MaxEdge.X,b.MaxEdge.Y,b.MaxEdge.Z);

}



//�������
void MySceneManager::TextRender()
{


}


//2dͼƬ����
void MySceneManager::UIRender()
{
	
	//gui��������ʾ
	if(myGUI_Mgr) myGUI_Mgr->drawAll();

	//��������� ui��ʾ ����text Ѫ��
	if(monster_mgr) monster_mgr->UIRender();

	//��ɫ��������ʾ
	if(char_mgr) char_mgr->UIRender();

	//��Ʒ��������ʾ
	if(item_mgr) item_mgr->UIRender();

	//npc��������ʾ
	if(npc_mgr) npc_mgr->UIRender();

	//����ɫ��δ�������,�����к������.
	if(char_mgr->GetMainCharacter()==NULL) return;
	
	if(monster_mgr->GetNodeIsselected() ||	char_mgr->GetMainCharacter()->isfollow || char_mgr->GetMainCharacter()->getState() == cAttack)
	{
			//core::position2d<s32> m = dev->getCursorControl()->getPosition();
			//drv->draw2DImage(cur2, core::position2d<s32>(m.X,m.Y),
			//core::rect<s32>(0,0,32,32), 0, 
			//video::SColor(255, 255,255,255), true);
			//
			long normal= (long)LoadCursor( ::GetModuleHandle(0), MAKEINTRESOURCE(IDC_CURSOR2) );
	
			SExposedVideoData exposedData=	drv->getExposedVideoData();
			HWND h = reinterpret_cast<HWND>(exposedData.D3D9.HWnd);
			::SetClassLong(h,GCL_HCURSOR,normal);


	}else{
			long normal= (long)LoadCursor( ::GetModuleHandle(0), MAKEINTRESOURCE(IDC_CURSOR3) );
	
			SExposedVideoData exposedData=	drv->getExposedVideoData();
			HWND h = reinterpret_cast<HWND>(exposedData.D3D9.HWnd);
			::SetClassLong(h,GCL_HCURSOR,normal);
			//core::position2d<s32> m = dev->getCursorControl()->getPosition();
		 // drv->draw2DImage(cur1, core::position2d<s32>(m.X,m.Y),
			//core::rect<s32>(0,0,32,32), 0, 
			//video::SColor(255, 255,255,255), true);
	}
}
