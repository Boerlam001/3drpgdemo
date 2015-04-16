#include ".\MyGUIDlgConfig.h"



#define GUI_ID_TRANSPARENCY_SCROLL_BAR 111

MyGUIDlgConfig::MyGUIDlgConfig( )
{
	this->dev=getIrrDevice();

	//�����gui������
	mouseInGui=false;

	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();
	drv=dev->getVideoDriver();
}

MyGUIDlgConfig::~MyGUIDlgConfig(void)
{
}


void MyGUIDlgConfig::update()
{

}

void MyGUIDlgConfig::drawAll()
{

}

bool MyGUIDlgConfig::LoadGUI()
{
	win = ui->addWindow(core::rect<s32>(0,0,200,220), false, L"");
	win->setRelativePosition(position2di(350,100));
	win->setVisible(false);

	win->getCloseButton()->setVisible(false);
	//win->getCloseButton()->setToolTipText(L"");
	//win->getCloseButton()->setPosition(vector2d<s32>(0,-2)));
	

	//���ڵ�x 25��� �����ر�
	IGUIButton* btn=ui->addButton(core::rect<s32>(0,0,15,14), win, 25, L"X" );
	btn->setRelativePosition(position2d<s32>(185,0));


	//ok��ť
	IGUIButton* ok_btn=ui->addButton(core::rect<s32>(0,0,15*6,15), win, 26, L"ȷ��" );
	//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
	position2d<s32> p1(50,25*5);
	ok_btn->setRelativePosition(p1);

	
	//
	IGUIStaticText* s=ui->addStaticText(L"͸����",rect<s32>(0,0,70,20),false,true,win);
	s->setRelativePosition(position2d<s32>(5,15));


	//������
	IGUIScrollBar* scrollbar = ui->addScrollBar(true,
		rect<s32>(0, 10, 195, 25), win, GUI_ID_TRANSPARENCY_SCROLL_BAR);
	scrollbar->setMax(255);
	position2d<s32> pp(5,35);
	scrollbar->setRelativePosition(pp);

	//������Ĭ������200 ͸����
	// set scrollbar position to alpha value of an arbitrary element
	scrollbar->setPos(200);

	//Ȼ��ѭ����gui��͸������ͬ
	for (u32 i=0; i<EGDC_COUNT ; ++i)
	{
		SColor col = ui->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(200);
		ui->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}


return true;
}

void MyGUIDlgConfig::ShowDlg(bool fl)
{
  win->setVisible(fl);
  //��ǰ
  ui->setFocus(win);
}

void MyGUIDlgConfig::OnEvent (const SEvent& e) 
{



	//gui�¼�
	if (e.EventType == EET_GUI_EVENT)
	{
		s32 id = e.GUIEvent.Caller->getID();//Ԫ�ض����id
		//e.GUIEvent.Caller���Ƿ����¼���guiԪ�ض���.
		switch(e.GUIEvent.EventType)
		{


			case EGET_BUTTON_CLICKED:
			{
				//�˳���ȷ��
				if(id==25 || id==26){
					win->setVisible(false);
					break;
				}

				
			
			}

			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)e.GUIEvent.Caller)->getPos();

					for (u32 i=0; i<EGDC_COUNT ; ++i)
					{
						SColor col = ui->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
						col.setAlpha(pos);
						ui->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
					}

					break;
				}
		}
	}


}

