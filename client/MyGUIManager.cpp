#include "StdAfx.h"
#include ".\myguimanager.h"



MyGUIManager::MyGUIManager (MySceneManager* m)
{
	dev=getIrrDevice();
	mgr=m;
	ui=dev->getGUIEnvironment();
	drv=dev->getVideoDriver();
	smgr=dev->getSceneManager();

	 for(int x=0; x<irr::KEY_KEY_CODES_COUNT; x++) keys[x] = false; 
	 mouseDownL=false; 
	 mouseDownM=false; 
	 mouseDownR=false; 
	cursorOld=dev->getCursorControl()->getPosition();
	cursor=cursorOld;

	 last_time = dev->getTimer ()->getRealTime (); 
	 guieditInput=false;

	 editbox=0;

	 m_pGUIDlg_charPackage=0;
	 m_pGUIDlg_charProp=0;
	 m_pGUIDlg_sysMenu=0;
	 m_pGUIDlg_npcShop=0;
	 m_pGUIDlg_skill=0;

}

MyGUIManager::~MyGUIManager(void)
{
}

//����gui��Ϣ,���Է�����
void MyGUIManager::insertGUIData(const char* pData,const unsigned int DataLength)
{
	printf(" MyGUIManager::insertGUIData\n");
	
	unsigned char cmd=pData[0];
	if(cmd==CMD_S2C_NPC_Shop){
		ShopPackage sp;
		memcpy((char*)&sp,pData,sizeof(ShopPackage));

		//npc�̵���������
		m_pGUIDlg_npcShop->setShopPackage(&sp);
		
		//npc�̵괰�ڿ���
		m_pGUIDlg_npcShop->ShowDlg(true);
	
		//��ɫ�������ڿ���
		m_pGUIDlg_charPackage->ShowDlg(true);
	}




}

//�û������ķ���,��msg�ַ�����ʾ��listbox��
void MyGUIManager::PostMsg(const wchar_t* msg)
{
	msglist->addItem(msg);

	msglist->setSelected(msglist->getItemCount());
}

bool MyGUIManager::LoadGUI()
{



blood_per=1;
	tex_HP= drv->getTexture("ui/ui2.tbj");
	tex_HPBG= drv->getTexture("ui/ui.tbj");
drv->makeColorKeyTexture(tex_HPBG, core::position2d<s32>(1,1)); //ָ���ؼ�ɫ��argb
drv->makeColorKeyTexture(tex_HP, core::position2d<s32>(1,1)); //ָ���ؼ�ɫ��argb
	//msglist = ui->addListBox(rect<s32>(0, 540, 400, 645),0,1);
	//msglist->addItem(L"welcome to game world!");

bottom_bar=drv->getTexture("ui/bar.tbj");

io::IFileSystem* filesys = dev->getFileSystem();

// Load GUI
gui::SImageGUISkinConfig guicfg = LoadGUISkinFromFile(filesys, drv, "ui/guiskin.cfg");
gui::CImageGUISkin* skin = new gui::CImageGUISkin(drv, ui->getSkin());
skin->loadConfig(guicfg);


char tmp[512];
GetWindowsDirectory(tmp,511);
strcat(tmp,"\\fonts\\SIMSUN.TTC");  //SIMSUN.TTC����,������         SIMKAI.TTF����     \STXIHEI.TTF   Fixedsys

gui::IGUIFont *font;
//	gui::IGUISkin* skin;
//SIMSUN.TTC����,������         SIMKAI.TTF����     \STXIHEI.TTF   Fixedsys
font = ui->getFont(tmp,14, true,false);




ui->setSkin(skin);
skin->drop();



stringw t=L"��ǰ��������:";
t+=mgr->char_mgr->getOnlineCharacterNum();
t+=L" ������:";
t+=mgr->monster_mgr->getAllMonsterNum();


msglist=ui->addListBox(rect<s32>(0,450,300,580),0,-1,true);


msglist->addItem(L"-----------------------------------------------------------");
msglist->addItem(L"��ӭ����game world!");
//msglist->addItem(t.c_str());
msglist->addItem(L"-----------------------------------------------------------");
msglist->setSelected(1);
//msglist->setItemOverrideColor(1,SColor(255,0,255,5));


	editbox= ui->addEditBox(L"", rect<s32>(0, 580, 400, 600),true,0,2);
	editbox->setVisible(false);

	 //SIMSUN.TTC����,������         SIMKAI.TTF����        Fixedsys
//	irr::gui::IGUIFont*	font = ui->getDXFont("����",true,16,0,900);


//	msg=smgr->addTextSceneNode (font,L"123",SColor(255,255,255,0),mgr->char_mgr->GetMainCharacter()->getNode(),vector3df(0,90,0));
//	msg->setVisible(true);

	//��ʼ���������
	m_pGUIDlg_charPackage=new MyGUIDlgCharPackage(mgr);
	m_pGUIDlg_charPackage->LoadGUI();

	//��ʼ����ɫ�������
	m_pGUIDlg_charProp=new MyGUIDlgCharProp(mgr);
	m_pGUIDlg_charProp->LoadGUI();

	//��ʼ����ɫ�������
	m_pGUIDlg_skill=new MyGUIDlgCharSkill(mgr);
	m_pGUIDlg_skill->LoadGUI();

	//��ʼ��ϵͳ�˵�
	m_pGUIDlg_sysMenu=new MyGUIDlgSysMenu();
	m_pGUIDlg_sysMenu->LoadGUI();

	//��ʼ���̵괰��
	m_pGUIDlg_npcShop=new MyGUIDlgNpcShop(mgr);
	m_pGUIDlg_npcShop->LoadGUI();



	return true;
}
//editbox����������
bool MyGUIManager::GetEditIsInput()
{
	return	guieditInput;
}
void MyGUIManager::OnEvent (const SEvent& e) 
{
	if(m_pGUIDlg_sysMenu) m_pGUIDlg_sysMenu->OnEvent(e);
	//ϵͳ�˵���,�����ľͲ������¼���
	if(m_pGUIDlg_sysMenu && m_pGUIDlg_sysMenu->mouseInGui){
		guieditInput=true;
		return;
	}

	if(m_pGUIDlg_charPackage) m_pGUIDlg_charPackage->OnEvent(e);
	if(m_pGUIDlg_charProp) m_pGUIDlg_charProp->OnEvent(e);

	if(m_pGUIDlg_charPackage && m_pGUIDlg_charPackage->mouseInGui){
     guieditInput=true;
	 return;
	}else if(m_pGUIDlg_charProp && m_pGUIDlg_charProp->mouseInGui){
		guieditInput=true;
		return;
	}

	if(m_pGUIDlg_npcShop) m_pGUIDlg_npcShop->OnEvent(e);
	if(m_pGUIDlg_npcShop && m_pGUIDlg_npcShop->mouseInGui){
		guieditInput=true;
		return;
	}

	if(m_pGUIDlg_skill) m_pGUIDlg_skill->OnEvent(e);
	if(m_pGUIDlg_skill && m_pGUIDlg_skill->mouseInGui){
		guieditInput=true;
		return;
	}
	


	// ��������¼�
	if (e.EventType == EET_KEY_INPUT_EVENT) {
		
		//�س��¼�
		if(e.KeyInput.Key==KEY_RETURN && e.KeyInput.PressedDown==false) {

			//
			if(editbox->isVisible())
			{ 
				//�������
				editbox->setVisible(false);
				guieditInput=false;
			}
			else{
				//��ʼ����
				guieditInput=true;
				editbox->setEnabled(true);
				editbox->setVisible(true);
				editbox->setText(L"");
			}
			
		}
		if(editbox->isVisible())
		{
			editbox->OnEvent(e);
		}



	//	if(e.KeyInput.Key==KEY_RETURN && e.KeyInput.PressedDown==false) {
			//	debug_info=!debug_info;
	//	}

		 keys[e.KeyInput.Key] = e.KeyInput.PressedDown; 
	
	}


	if(e.EventType ==irr::EET_MOUSE_INPUT_EVENT)//����¼�
	{
		switch (e.MouseInput.Event)//�ж�����¼�
		{
		case EMIE_LMOUSE_PRESSED_DOWN :

			cursor.X = e.MouseInput.X; 
			cursor.Y = e.MouseInput.Y; 

			if(msglist->isPointInside(cursor) || editbox->isPointInside(cursor)){
					guieditInput=true;
			}else{
					guieditInput=false;
			}
			
		break;
		case EMIE_LMOUSE_LEFT_UP:
			mouseDownL=false;
			//device->setWindowCaption(L"���mouse����");
			break;
		case EMIE_RMOUSE_PRESSED_DOWN :
			//device->setWindowCaption(L"�Ҽ�mouse����");
				mouseDownR=true;
			break;
		case EMIE_RMOUSE_LEFT_UP :
				mouseDownR=false;
			//device->setWindowCaption(L"�Ҽ�mouse����");
			break;
		case EMIE_MMOUSE_PRESSED_DOWN  :
			//device->setWindowCaption(L"�м�mouse����");
			mouseDownM=true;
			break;
		case EMIE_MMOUSE_LEFT_UP   :
			//device->setWindowCaption(L"�м�mouse����");
			mouseDownM=false;
			break;
			// mouse move check 
		case EMIE_MOUSE_MOVED   :
			{ 
					cursor.X = e.MouseInput.X; 
					cursor.Y = e.MouseInput.Y; 
			}
		}
	}

	//gui�¼�
	if (e.EventType == EET_GUI_EVENT)
	{
		s32 id = e.GUIEvent.Caller->getID();//Ԫ�ض����id
		//e.GUIEvent.Caller���Ƿ����¼���guiԪ�ض���.
		switch(e.GUIEvent.EventType)
		{
		case EGET_EDITBOX_ENTER:
			if (id == 2) //����editbox�Ļس��¼� 
			{
				if(editbox->getText()==L""){
					return;
				}
				
				WCHAR * pwStr = ConvertLPCSTRToLPWSTR(mgr->char_mgr->GetMainCharacter()->getRoleproperty().roleName); 
				stringw w="";
				w+=pwStr;
				w+=L":";
				w+=editbox->getText();

				msglist->addItem(w.c_str());
	
				msglist->setSelected(msglist->getItemCount());


				//msg->setVisible(true);
				stringw s=L"";
				s.append(editbox->getText());
				//���ؿͻ�����ʾmsg
				if(mgr->char_mgr->GetMainCharacter())  mgr->char_mgr->GetMainCharacter()->PostMsg(s.c_str());
				//�༭���ַ�����
				editbox->setText(L"");

				//���췢��msg����
				ServerRoleMSG msg;
				memset((char*)&msg,'/0',sizeof(ServerRoleMSG));
				msg.cmd=CMD_USERMSG;
				msg.sock=123;
				//�ַ�ת��
				char* te=WCharToMByte(s.c_str());
				strcpy(msg.msg,te);

				//���͸�������
				mgr->client->SendMsg((char*)&msg,sizeof(ServerRoleMSG));

				break;
			}

		
		}
	}


}


void MyGUIManager::drawAll()
{
    drv->draw2DImage(tex_HPBG, core::position2d<s32>(0,0),
				core::rect<s32>(0,0,164,59), 0, 
				video::SColor(255, 255,255,255), true);

	drv->draw2DImage(tex_HP, core::position2d<s32>(0+30,0+2),
				core::rect<s32>(0,0,(int)134*blood_per,12), 0, 
				video::SColor(255, 255,255,255), true);

	drv->draw2DImage(bottom_bar, core::position2d<s32>(420,570));

	if(m_pGUIDlg_charPackage) m_pGUIDlg_charPackage->drawAll();

	if(m_pGUIDlg_charProp) m_pGUIDlg_charProp->drawAll();

	if(m_pGUIDlg_sysMenu) m_pGUIDlg_sysMenu->drawAll();

	if(m_pGUIDlg_npcShop) m_pGUIDlg_npcShop->drawAll();

	if(m_pGUIDlg_skill) m_pGUIDlg_skill->drawAll();

}

void MyGUIManager::update()
{

	if(mgr->char_mgr->GetMainCharacter()) blood_per=mgr->char_mgr->GetMainCharacter()->getHPper();

	//��ɫ�������
	if(m_pGUIDlg_charPackage) m_pGUIDlg_charPackage->update();

	//��ɫ�������
	if(m_pGUIDlg_charProp) m_pGUIDlg_charProp->update();

	//��ɫ�������
	if(m_pGUIDlg_skill) m_pGUIDlg_skill->update();

	//ϵͳ�˵�
	if(m_pGUIDlg_sysMenu) m_pGUIDlg_sysMenu->update();

	//�̵괰�ڸ���
	if(m_pGUIDlg_npcShop) m_pGUIDlg_npcShop->update();

}
