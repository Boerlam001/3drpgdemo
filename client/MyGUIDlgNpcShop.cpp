#include ".\myguidlgnpcshop.h"



MyGUIDlgNpcShop::MyGUIDlgNpcShop( MySceneManager* mgr)
{
	this->dev=getIrrDevice();
	this->mgr=mgr;

	//�����gui������
	mouseInGui=false;

	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();
	drv=dev->getVideoDriver();



	//��겻�ڰ�������   
	mouseOnItem.X=-1;
	mouseOnItem.Y=-1;

}

MyGUIDlgNpcShop::~MyGUIDlgNpcShop(void)
{
}

void MyGUIDlgNpcShop::ShowDlg(bool fl)
{
	win->setVisible(fl);
	//��ǰ��
	ui->setFocus(win);
}


bool MyGUIDlgNpcShop::LoadGUI()
{
	//��Ʒ�򱳾�
	items_bg=drv->getTexture("ui/items.tbj");
	item_detail=drv->getTexture("ui/black.tbj");
	
	//������
	xbj_pic=drv->getTexture("ui/XBJ2.tbj");

	//����ͼƬ
	item_pic=drv->getTexture("ui/exclusive_knight.tbj");
	item_pic2=drv->getTexture("ui/Exclusive_Infinity.tbj"); 

	//ʹ��Ʒ hp mp��
	items_pic=drv->getTexture("ui/item.tbj");

	win = ui->addWindow(core::rect<s32>(0,0,240,200), false, L"");
	win->setRelativePosition(position2di(200,200));

	win->setVisible(false);

	win->getCloseButton()->setVisible(false);
	win->getCloseButton()->setToolTipText(L"");
	//win->getCloseButton()->setPosition(vector2d<s32>(0,-2)));
	
	//���ڵ�x 35��� �����ر�
	IGUIButton* btn=ui->addButton(core::rect<s32>(0,0,15,14), win, 35, L"X" );
	btn->setRelativePosition(position2d<s32>(225,0));
	btn->setToolTipText(L"");
	
	return true;
}


//���ʰȡ��Ʒ��
void MyGUIDlgNpcShop::SelectItem()
{
	//������ָ����ĳ��Ʒ,��������Ʒ,����.���ƶ���Ʒ��λ��..

	//�Ӵ��ڵ�����õ���Ʒ������
	int x=r.UpperLeftCorner.X+10;
	int y=20+r.UpperLeftCorner.Y;

	//��
	for(int a=0;a<4;a++)
	{
		//��
		for(int b=0;b<6;b++)
		{
			//�����������
			rect<s32> rr(x+b*35,y+a*35,x+b*35+35,y+a*35+35);
			//�ж�����Ƿ�ָ������Ʒ,��ʾ��һ�ε�����ĳ��Ʒ�� 

			//��Ʒ������ ʰȡ��Ʒ.����
			if(rr.isPointInside(cursor) )
			{
				//ʰȡ����Ʒ����Ʒ�ǿյ�,����
				if( shop.itembox[a][b]==0) break;
				//�����¼�µ����Ʒid
				
				//�����ɫ��������Ʒ��ʰ��.���ȴ��ָ����npc�̵�����.��ʾ�û��������Ʒ.��������npc�̵���Ʒ.
				//if(mgr->myGUI_Mgr->getCharPackage()->selectedItemId!=0){
				//		MessageBox(0,"��ɫ��������","",0);				
				//	return ;//����
				//}
				mouseOnItem.X=a;
				mouseOnItem.Y=b;

				//�������̵���Ʒ.������Ʒ���ڵ�x,y
			
				shop.cmd=CMD_C2S_UserBuyShop;
				shop.row1=b;
				shop.col1=a;
				

				mgr->client->SendMsg((char*)&shop,6);
			}
		}
	}


}


void MyGUIDlgNpcShop::OnEvent (const SEvent& e) 
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
					SelectItem();
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

				//���˴������Ͻǵ�X
				if(id==35){

					//�̵괰�ڹرյ�ͬʱ,��ɫ����Ҳ�Զ��ر�.Ҳ���Ժͽ�ɫ������x��ť����һ��id.ֻҪ����id��ť�͹ر�(����)��������
					if(win->isVisible()){
						mgr->myGUI_Mgr->getCharPackage()->ShowDlg(false);
					}
					win->setVisible(!win->isVisible());
					if(win->isVisible()==false){
						mouseInGui=false;
					}
				}
				break;
			}

		}
	}


}

void MyGUIDlgNpcShop::DrawAllItem()
{
	irr::core::rect<s32> r=win->getAbsolutePosition();
	int x=r.UpperLeftCorner.X+10;
	int y=20+r.UpperLeftCorner.Y;

	//35.75 
	if(win->isVisible()){
		//��
		for(int a=0;a<4;a++){
			//��
			for(int b=0;b<6;b++){
				rect<s32> rr(x+b*35,y+a*35,x+b*35+35,y+a*35+35);

				//0��ű�ʾ��������Ʒ.�򲻻���
				if((int)shop.itembox[a][b]==0){
					//printf("itembox[%d][%d]����Ʒ\n",a,b);
				}else{
					DrawItem(rr,shop.itembox[a][b]);
					//drv->draw2DRectangleOutline(rr,SColor(255,250,0,250));
				}
			}
		}
	}


}


//��װ����ͼƬ���к���,�Լ�Ҫ���ƵĿ�ʼ����.���Ͻ�
void MyGUIDlgNpcShop::draw2dImage(int row,int col,rect<s32> re)
{
	drv->draw2DImage(item_pic,
		vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
		rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
		SColor(alpha,255,255,255),true);
}


//����������ź;��Ի���rect.
void MyGUIDlgNpcShop::DrawItem(rect<s32> re,int itemID)
{

	switch(itemID)
	{
		//˫�н�
	case SRJ_Weapon:
		{

			int col=8; //��   ���ƿ��x
			int row=4; //�� �±�0��ʼ�� ���Ƹ߶�y
			draw2dImage(row,col,re);

			break;
		}

		//���޽�
	case TWJ_Weapon:
		{
			int col=11; //��   ���ƿ��x ���ŵ�
			int row=3; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			draw2dImage(row,col,re);
			break;
		}

		//������
	case CWJ_Weapon:
		{
			int col=11; //��   ���ƿ��x ���ŵ�
			int row=2; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			draw2dImage(row,col,re);
			break;
		}

		//��е����
	case JXKJ_Weapon:
		{
			int col=9; //��   ���ƿ��x ���ŵ�
			int row=4; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			draw2dImage(row,col,re);
			break;
		}


		//������Ͻ�
	case DMGSJ_Weapon:
		{
			int col=6; //��   ���ƿ��x ���ŵ�
			int row=5; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			draw2dImage(row,col,re);
			break;
		}


		//������
	case XBJ_Weapon:
		{
			drv->draw2DImage(xbj_pic,
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(0,0,34,34),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//��ɏ��
	case BLD_Weapon:
		{
			int col=12; //��   ���ƿ��x ���ŵ�
			int row=2; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			draw2dImage(row,col,re);
			break;
		}

		//������
	case STD_Weapon:
		{
			int col=12; //��   ���ƿ��x ���ŵ�
			int row=3; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			draw2dImage(row,col,re);
			break;
		}

		//7�ʽ�
	case Cai7_Weapon:
		{
			int col=0; //��   ���ƿ��x ���ŵ�
			int row=4; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(item_pic2,
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}

		//�޳ݽ�
	case JC_Weapon:
		{
			int col=2; //��   ���ƿ��x ���ŵ�
			int row=4; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(item_pic2,
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//��˫�н�
	case BSRJ_Weapon:
		{
			int col=1; //��   ���ƿ��x ���ŵ�
			int row=4; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(drv->getTexture("ui/Exclusive_Infinity.tbj"),
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//���н�
	case WRJ_Weapon:
		{
			int col=1; //��   ���ƿ��x ���ŵ�
			int row=1; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(drv->getTexture("ui/funny_weapon.tbj"),
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}

		//�����н�
	case LWRJ_Weapon:
		{
			int col=2; //��   ���ƿ��x ���ŵ�
			int row=1; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(drv->getTexture("ui/funny_weapon.tbj"),
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//������
	case LHJ_Weapon:
		{
			int col=6; //��   ���ƿ��x ���ŵ�
			int row=1; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(drv->getTexture("ui/funny_weapon.tbj"),
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//������
	case BLJ_Weapon:
		{
			int col=12; //��   ���ƿ��x ���ŵ�
			int row=4; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(item_pic,
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//����
	case 17:
		{
			int col=7; //��   ���ƿ��x ���ŵ�
			int row=0; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(drv->getTexture("ui/funny_weapon.tbj"),
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


		//������ҩ
	case 1000:
		{
			int col=6; //��   ���ƿ��x ���ŵ�
			int row=0; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(items_pic,
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}

		//����ħ��ҩ
	case 1001:
		{
			int col=8; //��   ���ƿ��x ���ŵ�
			int row=0; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(items_pic,
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}

		//�в���
	case 2000:
		{
			int col=3; //��   ���ƿ��x ���ŵ�
			int row=2; //�� �±�0��ʼ�� ���Ƹ߶�y ���ŵ�
			drv->draw2DImage(drv->getTexture("ui/itemui.tbj"),
				vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
				rect<s32>(36*col,36*row,36*(col+1),36*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
				SColor(alpha,255,255,255),true);
			break;
		}


	}
}


void MyGUIDlgNpcShop::drawAll()
{
	//��ȡ�����������
	r=win->getAbsolutePosition();
	if(win->isVisible()){
		//��ȡguiƤ��͸����
		SColor col = ui->getSkin()->getColor((EGUI_DEFAULT_COLOR)1);
		alpha=col.getAlpha();

		//���ư������ӱ���ͼƬ
		drv->draw2DImage(items_bg, core::position2d<s32>(r.UpperLeftCorner.X+10 ,20+r.UpperLeftCorner.Y ),
			rect<s32>(0,0,212,143),0,SColor(alpha,255,255,255),true);
	}

	//���Ʊ�������뵽װ����,ѡ���ĸ���ͻ��Ƹ����� ��ɫ��ʾ
	position2d<s32> pos=dev->getCursorControl()->getPosition();
	int x=r.UpperLeftCorner.X+10;
	int y=20+r.UpperLeftCorner.Y;
	//35.75 
	if(win->isVisible())
	{
		bool isin=false;
		//��
		for(int a=0;a<4;a++)
		{
			//��
			for(int b=0;b<6;b++)
			{
				rect<s32> rr(x+b*35,y+a*35,x+b*35+35,y+a*35+35);
				if(rr.isPointInside(pos))
				{
					//	drv->draw2DRectangleOutline(rr,SColor(alpha,0,0,205),SColor(alpha,0,0,205),SColor(alpha,0,0,205),SColor(alpha,0,0,205));
					drv->draw2DRectangleOutline(rr,SColor(alpha,255,255,0 ));
					//ֻ����һ��..Ȼ�󷵻�.�õ��������±�
					mouseOnItem.X=a; //��
					mouseOnItem.Y=b; //��

					isin=true;
					break;
				}else{
					mouseOnItem.X=-1; //��
					mouseOnItem.Y=-1; //��
				}
			}
			if(isin) break;
		}
	}

	DrawAllItem();


	//��ʾ��Ʒ��ϸ��Ϣ,������ָ������Ʒ���Ļ�
	if(win->isVisible() && mouseOnItem.X!=-1 && mouseOnItem.Y!=-1){

		//�õ���ǰ�����ָ����Ʒid
		int itemid=shop.itembox[mouseOnItem.X][mouseOnItem.Y];

		//��Ʒ���յ�
		if(itemid==0){
			return ;
		}

		//��Ʒ�Ĳ���1
		int itemparam1=shop.itemParam1[mouseOnItem.X][mouseOnItem.Y];
		int itemparam2=shop.itemParam2[mouseOnItem.X][mouseOnItem.Y];
		int itemparam3=shop.itemParam3[mouseOnItem.X][mouseOnItem.Y];
		int itemparam4=shop.itemParam4[mouseOnItem.X][mouseOnItem.Y];
		int itemparam5=shop.itemParam5[mouseOnItem.X][mouseOnItem.Y];
		int itemparam6=shop.itemParam6[mouseOnItem.X][mouseOnItem.Y];

		drv->draw2DImage(item_detail,
			vector2d<s32>(position2di(pos.X-160,pos.Y-110)), //���������ָ�����Ƶ����� ����λ���Ͻ�λ�û���ͼƬ
			rect<s32>(0,0,200,250),0, //�������Դͼ���ȡͼƬҪ��ʾ������ ���س�ͼƬ�Ĵ�С
			SColor(alpha,255,255,255),true);
		//��Ʒ���Ƶ�����.����
		vector2d<s32> textPos(position2di((pos.X-150+75 //��ȥͼƬ���,�ټ���һ���Ⱦ���ʵ�ʾ��е�x����
			),pos.Y-100));
		char* itemName=getItemNameById(itemid);
		char temp[255];

		//��ͨ����
		if(itemparam1==0 && itemid<1000 )
		{ 
			char strtemp[255];
			sprintf(strtemp,"%s �۸�:%d",itemName,shop.itemPrice[mouseOnItem.X][mouseOnItem.Y]);
			TextCenter( strtemp ,textPos,SColor(alpha,255,255,255),15,700);
		}else if(itemparam1>0 && itemid<1000){
				//1000���� ����
			char strtemp[255];
			sprintf(strtemp,"[׿Խ]%s �۸�:%d",itemName,shop.itemPrice[mouseOnItem.X][mouseOnItem.Y]);

			TextCenter( strtemp ,textPos,SColor(alpha,0,255,0),15,700);
		}else if( itemid>=1000 && itemid<2000){
			char strtemp[255];
			sprintf(strtemp,"%s �۸�:%d",itemName,shop.itemPrice[mouseOnItem.X][mouseOnItem.Y]);
			TextCenter( strtemp ,textPos,SColor(alpha,255,255,255),15,700);
		}else if( itemid>=2000 && itemid<3000){
			char strtemp[255];
			sprintf(strtemp,"%s �۸�:%d",itemName,shop.itemPrice[mouseOnItem.X][mouseOnItem.Y]);
			TextCenter( strtemp ,textPos,SColor(alpha,255,255,255),15,700);
		}


		//1000���ڵ���Ʒid������
		if(itemid<1000){
			//�õ���ǰ�����ָ��װ���Ĺ�����
			int attack=itemparam2; //����ʵ�ʵĹ�����
			

			sprintf(temp,"������:%d",attack);
			textPos.Y+=15;
			TextCenter( temp ,textPos,SColor(alpha,255,255,255),14,500);
		}

		
		textPos.Y+=15;
		if(itemid<1000){
			sprintf(temp,"��������1:%d",itemparam1);
			if(itemparam1==1)
				//��ɫ
				sprintf(temp,"����:���");
			else if(itemparam1==2)
				//����Ļ�
				sprintf(temp,"����:��",itemName);

			else if(itemparam1==3)
				//����ı�
				sprintf(temp,"����:��",itemName);

			else if(itemparam1==4)
				//����Ķ�
				sprintf(temp,"����:��",itemName);
			else if(itemparam1==5)
				//7��
				sprintf(temp,"����:�߲�",itemName);
		}else if(itemid==1000){
			sprintf(temp,"HP�����ָ�:%d",itemparam1);
		}else if(itemid==1001){
			sprintf(temp,"MP�����ָ�:%d",itemparam1);	
		}else if(itemid>=2000){
			sprintf(temp,"param1:%d",itemparam1);	
		}

		TextCenter( temp ,textPos,SColor(alpha,255,255,255),15,100);

		//if(itemparam1==1){
		//	//��ɫ
		//	sprintf(temp,"����:���");
		//	TextCenter(ui, temp ,textPos,SColor(alpha,255,255,255),15,700);
		//}else if(itemparam1==2){
		//	//����Ļ�
		//	sprintf(temp,"����:��",itemName);
		//	TextCenter(ui, temp ,textPos,SColor(alpha,255,255,255),15,700);
		//}else if(itemparam1==3){
		//	//����ı�
		//	sprintf(temp,"����:��",itemName);
		//	TextCenter(ui, temp ,textPos,SColor(alpha,255,255,255),15,700);
		//}else if(itemparam1==4){
		//	//����Ķ�
		//	sprintf(temp,"����:��",itemName);
		//	TextCenter(ui, temp ,textPos,SColor(alpha,255,255,2550),15,700);
		//}else if(itemparam1==5){
		//	//7��
		//	sprintf(temp,"����:�߲�",itemName);
		//	TextCenter(ui, temp ,textPos,SColor(alpha,255,255,2550),15,700);
		//}

		textPos.Y+=15;
		if(itemid<1000){
			sprintf(temp,"��������2:%d",itemparam2);
		}else if(itemid>=1000 && itemid<2000){
			sprintf(temp,"����:%d",itemparam2);
		}else if(itemid>=2000 ){
			sprintf(temp,"param2:%d",itemparam2);
		}

		TextCenter( temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param3:%d",itemparam3);
		TextCenter( temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param4:%d",itemparam4);
		TextCenter( temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param5:%d",itemparam5);
		TextCenter( temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param6:%d",itemparam6);
		TextCenter( temp ,textPos,SColor(alpha,255,255,255),15,100);


		delete itemName;

	}


}

char* MyGUIDlgNpcShop::getItemNameById(int itemID)
{

	//��Ʒ������Ϣ
	char FilePath[255]="scene\\item.ini";
	char *inBuf=new char[80];     //���ڱ����ȡ���ַ���
	char temp[25]="";
	sprintf(temp,"ItemID:%d",itemID); //id

	if(IniGetString(FilePath,temp,"Name",inBuf)){
		return inBuf;
	}else{
		return 0;
	}


}


void MyGUIDlgNpcShop::update()
{
	
	if(win->isVisible()){

	}

}
