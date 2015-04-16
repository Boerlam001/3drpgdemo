#include ".\myguidlgconfirm.h"

MyGUIDlgConfirm::MyGUIDlgConfirm()
{
	this->dev=getIrrDevice();
	//�����gui������
	mouseInGui=false;

	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();
	drv=dev->getVideoDriver();
}

MyGUIDlgConfirm::~MyGUIDlgConfirm(void)
{
}

void MyGUIDlgConfirm::ShowDlg(bool v)
{
	win->setVisible(v);
	//��ǰ��
	ui->setFocus(win);
}


bool MyGUIDlgConfirm::LoadGUI()
{
	win = ui->addWindow(core::rect<s32>(0,0,200,220), false, L"");
	win->setRelativePosition(position2di(350,100));
	win->setVisible(true);

	win->getCloseButton()->setVisible(false);
	//	win->getCloseButton()->setToolTipText(L"");
	//	win->getCloseButton()->setRelativePosition(vector2d<s32>(0,-2));


	//���ڵ�x 33��� �����ر�
	IGUIButton* btn=ui->addButton(core::rect<s32>(0,0,15,14), win, 35, L"X" );
	btn->setRelativePosition(position2d<s32>(185,0));

	//��ť

	IGUIButton* btn_yes=ui->addButton(core::rect<s32>(0,0,15*4,16), win, 36 , L"ȷ��"  );
	//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
	position2d<s32> p1(50,25*3);
	btn_yes->setRelativePosition(p1);

	IGUIButton* btn_no=ui->addButton(core::rect<s32>(0,0,15*4,16), win, 37 , L"ȡ��"  );
	//����ֻ��Ҫ�����������,��Ϊ��ָ���˸�����
	position2d<s32> p2(120,25*3);
	btn_no->setRelativePosition(p2);


	return true;
}

void MyGUIDlgConfirm::OnEvent (const irr::SEvent& e)
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
				//x��ť
				if(id==35){
					win->setVisible(false);
					mouseInGui=false;
					break;
				}

				//yes�İ�ť
				if(id==36){
					//����������
					win->setVisible(false);
					mouseInGui=false;

					break;
				}
				
				//no�İ�ť
				if(id==36){
					//����������
					win->setVisible(false);
					mouseInGui=false;

					break;
				}


			}
		}
	}
}