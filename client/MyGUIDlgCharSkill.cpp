#include ".\myguidlgcharskill.h"

MyGUIDlgCharSkill::MyGUIDlgCharSkill(MySceneManager* mgr)
{
	this->dev=getIrrDevice();
	smgr=dev->getSceneManager();
	ui=dev->getGUIEnvironment();
	drv=dev->getVideoDriver();

	this->mgr=mgr;

	mouseInGui=false;

	m_timer=dev->getTimer();
	lasttime=m_timer->getRealTime();
}

MyGUIDlgCharSkill::~MyGUIDlgCharSkill(void)
{
}
void MyGUIDlgCharSkill::OnEvent (const irr::SEvent& e)
{
	// ��������¼�
	if (e.EventType == EET_KEY_INPUT_EVENT) {

		//��/�رմ���
		if(e.KeyInput.Key==KEY_KEY_K && e.KeyInput.PressedDown==false ) {
			win->setVisible(!win->isVisible());
			if(win->isVisible()==false){
				mouseInGui=false;
			}else{
				//��ǰ����ʾ
				ui->setFocus(win);

				//��ʾ�����������
				RoleProperty srp;
				memset((char*)&srp,'\0',sizeof(RoleProperty));
				srp.cmd=CMD_C2S_Request_RoleSkillTable; //�����������Ϣ
				mgr->client->SendMsg((char*)&srp,sizeof(RoleProperty));
			}
		}


	}



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
				if(id==38){
					win->setVisible(!win->isVisible());
					if(win->isVisible()==false){
						mouseInGui=false;
					}
					break;
				}


			}

		}
	}






}


void MyGUIDlgCharSkill::update()
{

}


void MyGUIDlgCharSkill::drawAll()
{
	SColor color = ui->getSkin()->getColor((EGUI_DEFAULT_COLOR)1);
	alpha=color.getAlpha();

	//�ż��ܿ�ı���
	drv->draw2DImage(drv->getTexture("ui/Interface_main.tbj"),
		vector2d<s32>(5,60), //���������ָ�����Ƶ����� ����λ���Ͻ�λ�û���ͼƬ
		rect<s32>(0,164,40,220),0, //�������Դͼ���ȡͼƬҪ��ʾ������ ���س�ͼƬ�Ĵ�С
		SColor(alpha,255,255,255),true);



	//��ñ�����ľ�������
	win_rect=win->getAbsolutePosition();

	//�������ɼ�
	if(win->isVisible()){
		

		int x=win_rect.UpperLeftCorner.X+10;
		int y=20+win_rect.UpperLeftCorner.Y;


		int col=9;
		int row=2;

		//��ɫ����
		drv->draw2DImage(drv->getTexture("ui/black.tbj"),
			vector2d<s32>(position2di(x-3,y-3)), //���������ָ�����Ƶ����� ����λ���Ͻ�λ�û���ͼƬ
			rect<s32>(0,0,225,35+5),0, //�������Դͼ���ȡͼƬҪ��ʾ������ ���س�ͼƬ�Ĵ�С
			SColor(alpha,255,255,255),true);

		//���Ƽ���ͼƬ
		drv->draw2DImage(drv->getTexture("ui/skill_2.tbj"),
			vector2d<s32>(x,y), //���������ָ�����Ƶ�����
			rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
			SColor(alpha,255,255,255),true);


		//��Ʒ���Ƶ�����.����
		vector2d<s32> textPos(position2di(x+40,y+10));

		TextLeft( "��������:" ,textPos,SColor(alpha,255,255,255),12,0);
		textPos.X+=12*5;
		TextLeft( "[���⻤��]" ,textPos,SColor(alpha,255,255,0),12,0);


//--------------------------------------------------------------------------------------------------------
		//��ɫ����
		drv->draw2DImage(drv->getTexture("ui/black.tbj"),
			vector2d<s32>(position2di(x-3,y+40+3)), //���������ָ�����Ƶ����� ����λ���Ͻ�λ�û���ͼƬ
			rect<s32>(0,0,225,35+5),0, //�������Դͼ���ȡͼƬҪ��ʾ������ ���س�ͼƬ�Ĵ�С
			SColor(alpha,255,255,255),true);

		 col=5;
		 row=2;
		//���Ƽ���ͼƬ
		drv->draw2DImage(drv->getTexture("ui/skill_magic3.tbj"),
			vector2d<s32>(x,y+40+3+3), //���������ָ�����Ƶ�����
			rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
			SColor(alpha,255,255,255),true);

		//��Ʒ���Ƶ�����.����
		textPos.X=x+40;
		textPos.Y=y+40+10+10;

		TextLeft( "��������:" ,textPos,SColor(alpha,255,255,255),12,0);
		textPos.X+=12*5;
		TextLeft( "[ʱ�շ���]" ,textPos,SColor(alpha,255,255,0),12,0);





	}

}

bool MyGUIDlgCharSkill::LoadGUI()
{
	win = ui->addWindow(core::rect<s32>(0,0,240,300), false, L"");
	win->setRelativePosition(position2di(500,200));
	//win->setText(L"Skill Tool");


	win->setVisible(false);

	win->getCloseButton()->setVisible(false);
	win->getCloseButton()->setToolTipText(L"");

	//���ڵ�x 24��� �����ر�
	IGUIButton* btn=ui->addButton(core::rect<s32>(0,0,15,14), win, 38, L"X" );
	btn->setRelativePosition(position2d<s32>(225,0));


	return true;
}