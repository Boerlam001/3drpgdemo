#include ".\MyGUIDlgSysMenu.h"



MyGUIDlgSysMenu::MyGUIDlgSysMenu()
{
	this->dev=getIrrDevice();

	//�����gui������
	mouseInGui=false;

	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();
	drv=dev->getVideoDriver();

	config_dlg=0;
}

MyGUIDlgSysMenu::~MyGUIDlgSysMenu(void)
{
}

void MyGUIDlgSysMenu::update()
{
  if(config_dlg) config_dlg->update();
}

void MyGUIDlgSysMenu::drawAll()
{
  if(config_dlg) config_dlg->drawAll();
}

bool MyGUIDlgSysMenu::LoadGUI()
{
	win = ui->addWindow(core::rect<s32>(0,0,200,220), false, L"");
	win->setRelativePosition(position2di(300,180));
	win->setVisible(false);

	win->getCloseButton()->setVisible(false);
	//win->getCloseButton()->setToolTipText(L"");
	//win->getCloseButton()->setPosition(vector2d<s32>(0,-2)));

	//�����϶�
	win->setDraggable(false);

	//�����������Ե㰴ť
	IGUIButton* exit_btn=ui->addButton(core::rect<s32>(0,0,15*6,15), win, 30, L"��������" );
	//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
	position2d<s32> p1(50,25*2);
	exit_btn->setRelativePosition(p1);

	exit_btn=ui->addButton(core::rect<s32>(0,0,15*6,15), win, 31, L"�˳�" );
	//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
	position2d<s32> p2(50,25*3);
	exit_btn->setRelativePosition(p2);

	
	exit_btn=ui->addButton(core::rect<s32>(0,0,15*6,15), win, 32, L"������Ϸ" );
	//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
	position2d<s32> p3(50,25*4);
	exit_btn->setRelativePosition(p3);


	config_dlg=new MyGUIDlgConfig();
	config_dlg->LoadGUI();


	return true;
}


void MyGUIDlgSysMenu::OnEvent (const SEvent& e) 
{

	if(config_dlg) config_dlg->OnEvent(e);
	if(config_dlg&& config_dlg->mouseInGui){
		mouseInGui=true;
		return ;
	}

	// ��������¼�
	if (e.EventType == EET_KEY_INPUT_EVENT) {

		//ESC�¼�
		if(e.KeyInput.Key==KEY_ESCAPE && e.KeyInput.PressedDown==false) {
			if(win->isVisible()){
				mouseInGui=false;
				win->setVisible(false);
			}else
			{
				mouseInGui=true;
				win->setVisible(true);
				//��ǰ��
				ui->setFocus(win);
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
				//�˳�
				if(id==31){
					dev->closeDevice();

					break;
				}

				//gui����
				if(id==30){
					//��ʾgui���ô���
					config_dlg->ShowDlg(true);

					break;
				}

				//������Ϸ
				if(id==32){
					win->setVisible(false);
					mouseInGui=false;

					break;
				}
			}
		}
	}


}
