#include ".\myguidlgcommon.h"

MyGUIDlgNpcTalk::MyGUIDlgNpcTalk(   NPCProperty* npcprop ,Socket::CNetClient* client)
{
	this->dev=getIrrDevice();
	
	this->npcprop=npcprop;

	this->client=client;

	//�����gui������
	mouseInGui=false;

	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();
	drv=dev->getVideoDriver();
}

MyGUIDlgNpcTalk::~MyGUIDlgNpcTalk(void)
{

}

void MyGUIDlgNpcTalk::ShowDlg(bool v)
{
   win->setVisible(v);
   //��ǰ��
   ui->setFocus(win);
}

void MyGUIDlgNpcTalk::OnEvent (const irr::SEvent& e)
{

	if(e.EventType ==irr::EET_MOUSE_INPUT_EVENT)//����¼�
	{
		switch (e.MouseInput.Event)//�ж�����¼�
		{
			//�������
		case EMIE_LMOUSE_PRESSED_DOWN :
			{
				cursor.X = e.MouseInput.X; 
				cursor.Y = e.MouseInput.Y; 
				if(win->isVisible()){
					if( win->isPointInside(cursor)){
						mouseInGui=true;
					}else{
						mouseInGui=false;
					}
				}

				break;
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

		case EGET_BUTTON_CLICKED:
			{
				//�������Ͻ��˳�X��ť
				if(id==33){
					win->setVisible(false);
					mouseInGui=false;
					break;
				}

				//npc�İ�ť
				if(id==34){
					//����������
					win->setVisible(false);
					mouseInGui=false;

					//���͵�������.����˴�npc������
				//	if(npcprop->cmd==CMD_C2S_UserRequest_NPC)
				//		npcprop->cmd=CMD_C2S_UserRequest_NPC;
					client->SendMsg((char*)npcprop, (6) ); //ֻ��Ҫ����ǰ6λ.����npcID worldMap
					
					break;
				}


			}
		}
	}
}

void MyGUIDlgNpcTalk::update() //����
{

}

void MyGUIDlgNpcTalk::drop()
{
  win->remove();
}


void MyGUIDlgNpcTalk::drawAll()
{
	rect<s32> win_rect=win->getAbsolutePosition();
	int x=win_rect.UpperLeftCorner.X;
	int y=win_rect.UpperLeftCorner.Y;
	if(win->isVisible()){
		SColor col = ui->getSkin()->getColor((EGUI_DEFAULT_COLOR)1);
		float	alpha=col.getAlpha();

		//��ʾnpc˵�Ļ�
		TextLeft(npcprop->strNpcTalk,vector2d<s32>(x+20,y+25), SColor(alpha,255,255,255),13,0,180); //ÿ��180��� �������Զ�����
	}

}

bool MyGUIDlgNpcTalk::LoadGUI()
{
	win = ui->addWindow(core::rect<s32>(0,0,200,220), false, L"");
	win->setRelativePosition(position2di(350,100));
	win->setVisible(true);

	win->getCloseButton()->setVisible(false);
//	win->getCloseButton()->setToolTipText(L"");
//	win->getCloseButton()->setRelativePosition(vector2d<s32>(0,-2));


	//���ڵ�x 33��� �����ر�
	btn=ui->addButton(core::rect<s32>(0,0,15,14), win, 33, L"X" );
	btn->setRelativePosition(position2d<s32>(185,0));


	rect<s32> win_rect=win->getAbsolutePosition();
	int x=win_rect.UpperLeftCorner.X;
	int y=win_rect.UpperLeftCorner.Y;


	//��ť

	//������-1 ��ʾ�а�ťҪ�����¼�
	if(npcprop->cmd!=-1){
	
		
		WCHAR * pwStr = ConvertLPCSTRToLPWSTR((char*)npcprop->strBtnText); 

		IGUIButton* buy_btn=ui->addButton(core::rect<s32>(0,0,15*4,16), win, 34 , pwStr  );
		//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
		position2d<s32> p1(50,25*3);
		buy_btn->setRelativePosition(p1);

		delete pwStr;
	}
	


	return true;
}