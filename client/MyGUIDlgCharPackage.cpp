#include ".\myguidlgcharpackage.h"


//����ɫָ�� �ú�����д���ⳤ����
#define 	main_char mgr->char_mgr->GetMainCharacter()

MyGUIDlgCharPackage::MyGUIDlgCharPackage(  MySceneManager* mgr)
{
	this->dev=getIrrDevice();
	this->mgr=mgr;

	//�����gui������
	mouseInGui=false;

	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();
	drv=dev->getVideoDriver();

	//û��װ����ѡȡ.������
	selectedItemBox=false;

	//��겻�ڰ�������   
	mouseOnItem.X=-1;
	mouseOnItem.Y=-1;




}

MyGUIDlgCharPackage::~MyGUIDlgCharPackage(void)
{
}

bool MyGUIDlgCharPackage::LoadGUI()
{
	//װ���򱳾�
	items_bg=drv->getTexture("ui/items.tbj");
	//����ͼƬ
	item_pic=drv->getTexture("ui/exclusive_knight.tbj");
	item_pic2=drv->getTexture("ui/Exclusive_Infinity.tbj"); 

	//������
	xbj_pic=drv->getTexture("ui/XBJ2.tbj");

	//ʹ��Ʒ hp mp��
	items_pic=drv->getTexture("ui/item.tbj");

	item_detail=drv->getTexture("ui/black.tbj");

	win = ui->addWindow(core::rect<s32>(0,0,260,360), false, L"");
	win->setRelativePosition(position2di(470,200));
	win->setVisible(false);

	win->getCloseButton()->setVisible(false);
	win->getCloseButton()->setToolTipText(L"");
	//win->getCloseButton()->setPosition(vector2d<s32>(0,-2)));


	//���ڵ�x 23��� �����ر�
	IGUIButton* btn=ui->addButton(core::rect<s32>(0,0,15,14), win, 23, L"X" );
	btn->setRelativePosition(position2d<s32>(245,0));

	//��ʾ ��Ǯ:  ��text
	IGUIStaticText* s=ui->addStaticText(L"��Ǯ:",rect<s32>(0,0,70,20),false,true,win);
	s->setRelativePosition(position2d<s32>(5,330));

	
	//��ʾ��Ǯ����
	money_text=ui->addStaticText(L"0",rect<s32>(0,0,50,20),false,true,win);
	money_text->setRelativePosition(position2d<s32>(80,330));
	money_text->setOverrideColor(SColor(255,0,0,0));



	return true;
}

//�洢��ѡ�����Ʒa,b��,���±�,��ֵ����ʱ����
void MyGUIDlgCharPackage::StorePackItemValue(int a,int b)
{
	selectedItemId=main_char->getPackage()->itembox[a][b];
	selectedItemparam1=main_char->getPackage()->itemParam1[a][b];
	selectedItemparam2=main_char->getPackage()->itemParam2[a][b];
	selectedItemparam3=main_char->getPackage()->itemParam3[a][b];
	selectedItemparam4=main_char->getPackage()->itemParam4[a][b];
	selectedItemparam5=main_char->getPackage()->itemParam5[a][b];
	selectedItemparam6=main_char->getPackage()->itemParam6[a][b];
}


//��ѡ�����Ʒ����ʱ�������ð�a,b���еİ�����
void MyGUIDlgCharPackage::UseStorePackItemValue(int a,int b)
{
	//����Ʒ���뵽ָ��������
	main_char->getPackage()->itembox[a][b]=selectedItemId;

	main_char->getPackage()->itemParam1[a][b]=selectedItemparam1;
	main_char->getPackage()->itemParam2[a][b]=selectedItemparam2;
	main_char->getPackage()->itemParam3[a][b]=selectedItemparam3;
	main_char->getPackage()->itemParam4[a][b]=selectedItemparam4;
	main_char->getPackage()->itemParam5[a][b]=selectedItemparam5;
	main_char->getPackage()->itemParam6[a][b]=selectedItemparam6;
}


//���ʰȡ��Ʒ��
void MyGUIDlgCharPackage::SelectItem()
{
	//������ָ����ĳ��Ʒ,��������Ʒ,����.���ƶ���Ʒ��λ��..

	//�Ӵ��ڵ�����õ���Ʒ������
	int x=r.UpperLeftCorner.X+10;
	int y=143+r.UpperLeftCorner.Y;



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
			if(rr.isPointInside(cursor) && selectedItemBox==false)
			{
				//ʰȡ����Ʒ����Ʒ�յ�,����
				if(main_char->getPackage()->itembox[a][b]==0) break;
				//��¼�µ����Ʒid
				selectedItemBox=true;
				
				//�洢��ѡ�����Ʒֵ����ʱ����
				StorePackItemValue(a,b);
				
				main_char->getPackage()->itembox[a][b]=0;
				sel_x=a;
				sel_y=b;

				drop_x=a;
				drop_y=b;

				return;
			}else if(rr.isPointInside(cursor) && selectedItemBox && main_char->getPackage()->itembox[a][b]==0){
				//��ʾ�ڶ��ε���ĳ��.���ҿ���û��Ʒ.�ͰѸղŵ����˵���Ʒװ��ȥ

				//��ʾ�ȵ�������Ʒ,Ȼ���ֵ㵽ԭ����λ��. ͬһ������.������������.��Ʒ�ָ���ԭ���ĵط�,ʰȡ״̬false
				if(sel_x==a && sel_y==b){
					selectedItemBox=false;

					//�洢��ѡ�����Ʒֵ����ʱ����
					UseStorePackItemValue(a,b);
					
					return ;
				}

				//����ж�µ������� sel_x���ϴ�����������������ʱ��־��-1
				if(sel_x==-1 && sel_y==-1){
					selectedItemBox=false;
					
					//����������
					main_char->getPackage()->currWeapon=0;
					//��ɫ����ģ�Ϳ���ʾ
					main_char->setCurWeapon(0,0);
					
					//��ʰȡ����Ʒ(����������)�������
					UseStorePackItemValue (a,b);

					//������ж�µ�ָ��������
					//main_char->getPackage()->itembox[a][b]=selectedItemId;
					//��ж�������Ĳ������浽��Ӧ������
					//main_char->getPackage()->itemParam1[a][b]=selectedItemparam1;

					char tem[222];
					sprintf(tem,"ж������! ��%d ��%d",a,b);

					//����ж��������ŵĵط�
					memset((char*)&pack,'\0',sizeof(Package));
					pack.cmd=CMD_C2S_Request_ChangeWeapon; //����ͻ�������Ϣ
					pack.col1=b;
					pack.row1=a;
					pack.currWeapon=main_char->getPackage()->currWeapon;
					//���ͷ�����,��ɫж������
					mgr->client->SendMsg((char*)&pack,sizeof(Package));
					return;
				}

				//��ʰȡ����Ʒ�������
				UseStorePackItemValue(a,b);

				//��Ʒ������ ������Ʒ.����,����.λ�ñ���..�ҷ��µ��������ǿյ�
				//main_char->getPackage()->itembox[a][b]=selectedItemId;
				//ʰ����Ʒ�Ĳ�������
				//main_char->getPackage()->itemParam1[a][b]=selectedItemparam1;

				//������Ʒ������.��Ҫ��������ύ����
				
				memset((char*)&pack,'\0',sizeof(Package));
				pack.cmd=CMD_C2S_Request_ChangePackageItem; //����ͻ�������Ϣ
				pack.col1=sel_y;
				pack.row1=sel_x;
				pack.row2=a;
				pack.col2=b;
				mgr->client->SendMsg((char*)&pack,sizeof(Package));

				selectedItemBox=false;
				return;
			}
		}
	}

	//
	//��Ʒ��������.Ȼ���򳡾��ﶪ��.,��ʾ�û��붪����Ʒ.
	if(selectedItemBox //��־����Ʒ�ѱ����� 
		 &&  selectedItemId!=0  //��ʾ��ѡ����������Ʒid��Ϊ��,��ѡȡ����Ʒ ��Ϊ0����Ϊ����Ʒ
		&&	win->isPointInside(cursor)==false  //������겻�ڽ�ɫ��������.�� 
		&& sel_y!=-1 &&  sel_x!=-1  // ��������������-1��ʾʰȡ����Ʒ���ڰ�����. ������-1��ʾʰȡ����Ʒ���ڰ����� .������жϷ�ֹ����ʰȡ��������������
		 //��ǰ��ɫû��npc�̵�.
		&&  mgr->myGUI_Mgr->getNpcShop()->win->isVisible() ==false
		){
			
			//״̬�ָ� 
			selectedItemBox=false;
			selectedItemId=0;

			sel_y=-1;
			sel_x=-1;

			//������Ʒ.
			pack.cmd=CMD_C2S_Request_DropPackageItem;
			//��Ʒ�ڰ�������±�
			pack.row1=drop_x;
			pack.col1=drop_y;
			
			printf("��ɫ����Ʒ! ��%d ��%d\n",sel_x,sel_y); 
			//MessageBox(0,tem,"",0);
			//���ͷ�����������Ʒ
			mgr->client->SendMsg((char*)&pack,22); //����Ҫ���������ݰ�����.ֻ��Ҫ��22.����row col�����ݶ���


	}


		//��Ʒ��������.Ȼ����npc�̵�����������,��ʾ�û���������Ʒ��npc.
		if(selectedItemBox &&  //��־����Ʒ�ѱ����� 
			selectedItemId!=0  //��ʾ��ѡ����������Ʒid��Ϊ��,��ѡȡ����Ʒ ��Ϊ0����Ϊ����Ʒ
			&&	win->isPointInside(cursor)==false  //������겻�ڽ�ɫ��������.�� 
			&& sel_y!=-1 &&  sel_x!=-1  // ��������������-1��ʾʰȡ����Ʒ���ڰ�����. ������-1��ʾʰȡ����Ʒ���ڰ����� .������жϷ�ֹ����ʰȡ��������������
			&& mgr->myGUI_Mgr->getNpcShop()->win->isPointInside(cursor)==true  //���������npc�̵��� 
			&&  mgr->myGUI_Mgr->getNpcShop()->win->isVisible() //npc�̵괰�ڿɼ�,˵�������̵�
			){

				//״̬�ָ� 
				selectedItemBox=false;
				sel_y=-1;
				sel_x=-1;


				//������Ʒ.
				pack.cmd=CMD_C2S_Request_SellPackageItem;
				//��Ʒ�ڰ�������±�
				pack.row1=drop_x;
				pack.col1=drop_y;

				printf("��ɫ����Ʒ! ��%d ��%d\n",sel_x,sel_y); 
				//MessageBox(0,tem,"",0);
				//���ͷ�����������Ʒ
				mgr->client->SendMsg((char*)&pack,22); //����Ҫ���������ݰ�����.ֻ��Ҫ��22.����row col�����ݶ���


		}



	//װ����������.Ȼ����װ����������.����װ������
	if(selectedItemBox && 
		selectedItemId!=0  //��ʾ��ѡ����������Ʒid��Ϊ��,��ѡȡ����Ʒ ��Ϊ0����Ϊ����Ʒ
		){
		//��������������.��ʾ�û��������װ��ȥ,���ҵ�ǰ��ɫcurWeaponID=0 ��ʾû������

		//װ�������յ�������
		if(CurWeaponRect.isPointInside(cursor) && main_char->getPackage()->currWeapon==0 
			&& selectedItemId<1000 //1000����Ϊ��������װ������
			){
			//����ɫ�����ϵ�������Ÿ���
			main_char->getPackage()->currWeapon=selectedItemId;
			main_char->getPackage()->weaponparam1=selectedItemparam1;
			main_char->getPackage()->weaponparam2=selectedItemparam2;
			main_char->getPackage()->weaponparam3=selectedItemparam3;
			main_char->getPackage()->weaponparam4=selectedItemparam4;
			main_char->getPackage()->weaponparam5=selectedItemparam5;
			main_char->getPackage()->weaponparam6=selectedItemparam6;

			selectedItemBox=false;
			selectedItemId=0;
			selectedItemparam1=0;
			selectedItemparam2=0;
			selectedItemparam3=0;
			selectedItemparam4=0;
			selectedItemparam5=0;
			selectedItemparam6=0;

			//���ظ�����ʾ.  �ҵ�����ɫ,װ������������.ֻ��������ģ��
			main_char->setCurWeapon(main_char->getPackage()->currWeapon,
				main_char->getPackage()->weaponparam1);

			//����ϴε����������±�-1��ʾ���λ�ò��ڰ�����,����������.�����װ����������Ϊ �ȵ���������������,�ֵ��������
			if(sel_x==-1 && sel_y==-1){
				//������Ϣû�б仯.ֻ���ظ�����ʾ��������.
				return ;
			}

			//�����˵��ȷʵ��������Ʒ�����������,�ٵ㵽��������.����Ҫ�����������װ�����Ķ�����
			pack.cmd=CMD_C2S_Request_ChangeWeapon;
			//ֻ��Ҫ������id����.��Ϊ�������������͸���������Ϣ.
			pack.currWeapon=main_char->getPackage()->currWeapon;
			pack.row1=sel_x;
			pack.col1=sel_y;
			char tem[222];
			sprintf(tem,"װ������! ��%d ��%d",sel_x,sel_y); // ��ʱ���� -1 -1 ��ʾ�ȵ���������,�ֵ����������.���ڰ�����.�����±���-1-1
		//	//MessageBox(0,tem,"",0);
			//���ͷ�����װ������
			mgr->client->SendMsg((char*)&pack,sizeof(Package));


			return;
		}
	}



	//�ж�����Ƿ����������, ���û��Ƿ���ж������
	if(CurWeaponRect.isPointInside(cursor) && selectedItemBox==false)
	{
		//������û����.����ʲô
		if(main_char->getPackage()->currWeapon==0){

		}else if(main_char->getPackage()->currWeapon!=0){
			//������������,����ʰ��,׼��������Ʒ������
			//��־,����Ʒ��ʰ��
			selectedItemBox=true;
			//ʰ��������id���浽��ʱ����
			selectedItemId=main_char->getPackage()->currWeapon;
			//ʰ�������Ĳ�������
			selectedItemparam1=main_char->getPackage()->weaponparam1;
			selectedItemparam2=main_char->getPackage()->weaponparam2;
			selectedItemparam3=main_char->getPackage()->weaponparam3;
			selectedItemparam4=main_char->getPackage()->weaponparam4;
			selectedItemparam5=main_char->getPackage()->weaponparam5;
			selectedItemparam6=main_char->getPackage()->weaponparam6;

			//��ǰ������id���
			main_char->getPackage()->currWeapon=0;
			main_char->getPackage()->weaponparam1=0;
			main_char->getPackage()->weaponparam2=0;
			main_char->getPackage()->weaponparam3=0;
			main_char->getPackage()->weaponparam4=0;
			main_char->getPackage()->weaponparam5=0;
			main_char->getPackage()->weaponparam6=0;

			//��ʾ���ǵ����˰��������Ʒ.����������
			sel_y=-1;
			sel_x=-1;
			//�ҵ�����ɫ,ж������������.ֻ���ظ�����ʾ����ģ��
			main_char->setCurWeapon(0,0);
			

		}
	}



}




void MyGUIDlgCharPackage::OnEvent (const SEvent& e) 
{

	// ��������¼�
	if (e.EventType == EET_KEY_INPUT_EVENT) {

		//�س��¼�
		if(e.KeyInput.Key==KEY_RETURN && e.KeyInput.PressedDown==false) {

		}


		//�򿪹رմ���
		if(e.KeyInput.Key==KEY_KEY_I && e.KeyInput.PressedDown==false ) {
			win->setVisible(!win->isVisible());
			if(win->isVisible()==false){
				mouseInGui=false;
			}else{
				//��ǰ��
				ui->setFocus(win);

				//��ʾ���˰������
				Package pack;
				memset((char*)&pack,'\0',sizeof(Package));
				pack.cmd=CMD_C2S_Request_Package; //����ͻ�������Ϣ
				mgr->client->SendMsg((char*)&pack,sizeof(Package));
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
				if(id==23){
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

//�����������
void MyGUIDlgCharPackage::drawAll()
{
	//��ȡ�����������
	 r=win->getAbsolutePosition();

	 //�������ڿɼ�
	if(win->isVisible()){
		//��ȡguiƤ��͸����
		SColor col = ui->getSkin()->getColor((EGUI_DEFAULT_COLOR)1);
		 alpha=col.getAlpha();

	    //���ư������ӱ���ͼƬ
		drv->draw2DImage(items_bg, core::position2d<s32>(r.UpperLeftCorner.X+10 ,143+r.UpperLeftCorner.Y ),
		rect<s32>(0,0,212,143),0,SColor(alpha,255,255,255),true);
	}


	//���Ʊ�������뵽װ����,ѡ���ĸ���ͻ��Ƹ����� ��ɫ��ʾ
	position2d<s32> pos=dev->getCursorControl()->getPosition();
	int x=r.UpperLeftCorner.X+10;
	int y=143+r.UpperLeftCorner.Y;
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
					drv->draw2DRectangleOutline(rr,SColor(alpha,255,255,0));
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

	//��������װ����
	DrawAllItem();

	//���ƽ�ɫ��������.��ǰ����

	//�������ڴ���?
	if(win->isVisible())
	{
		//��ǰ��ɫ������ û�취,���������ڱ�Ļ�,��ҲҪ����
		CurWeaponRect=rect<s32>(r.UpperLeftCorner.X+60,r.UpperLeftCorner.Y+100,r.UpperLeftCorner.X+95,r.UpperLeftCorner.Y+135);

		TextLeft( "����:",vector2d<s32>(r.UpperLeftCorner.X+10,r.UpperLeftCorner.Y+110),SColor(alpha,255,0,255),18,0);
		
		//����������
		drv->draw2DImage(item_pic,
			vector2d<s32>(CurWeaponRect.UpperLeftCorner.X,CurWeaponRect.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
			rect<s32>(35*7,0,35*8,35),0, //�������Դͼ���ȡͼƬҪ��ʾ������
			SColor(alpha,255,255,255),true);

		DrawItem(CurWeaponRect,main_char->getPackage()->currWeapon);
	//---------------------------------------------------------------------------------------------------------------------------

		//��ǰ��ɫ������ û�취,���������ڱ�Ļ�,��ҲҪ����
		CurClothRect=rect<s32>(r.UpperLeftCorner.X+60+35,r.UpperLeftCorner.Y+60,r.UpperLeftCorner.X+95+35,r.UpperLeftCorner.Y+95);

		TextLeft( "��װ:",vector2d<s32>(r.UpperLeftCorner.X+10+35,r.UpperLeftCorner.Y+70),SColor(alpha,255,0,255),18,0);
		//����������
		drv->draw2DImage(item_pic,
			vector2d<s32>(CurClothRect.UpperLeftCorner.X,CurClothRect.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
			rect<s32>(35*7,0,35*8,35),0, //�������Դͼ���ȡͼƬҪ��ʾ������
			SColor(alpha,255,255,255),true);


	}

	//���Ʊ����������˵�װ��
	if(selectedItemBox ){

		rect<s32> a(pos.X-10,pos.Y-10,pos.X,pos.Y);
		DrawItem(a,selectedItemId);
	}

	
	//��ʾ��Ʒ��ϸ��Ϣ,������ָ������Ʒ���Ļ�
	if(win->isVisible() && mouseOnItem.X!=-1 && mouseOnItem.Y!=-1){

		//�õ���ǰ�����ָ����Ʒid
		int itemid=main_char->getPackage()->itembox[mouseOnItem.X][mouseOnItem.Y];

		//��Ʒ���յ�
		if(itemid==0){
			return ;
		}

		//��Ʒ�Ĳ���1
		int itemparam1=main_char->getPackage()->itemParam1[mouseOnItem.X][mouseOnItem.Y];
		int itemparam2=main_char->getPackage()->itemParam2[mouseOnItem.X][mouseOnItem.Y];
		int itemparam3=main_char->getPackage()->itemParam3[mouseOnItem.X][mouseOnItem.Y];
		int itemparam4=main_char->getPackage()->itemParam4[mouseOnItem.X][mouseOnItem.Y];
		int itemparam5=main_char->getPackage()->itemParam5[mouseOnItem.X][mouseOnItem.Y];
		int itemparam6=main_char->getPackage()->itemParam6[mouseOnItem.X][mouseOnItem.Y];

		//���Ƶĺ�ɫͼƬ������
		drv->draw2DImage(item_detail,
			vector2d<s32>(position2di(pos.X-140,pos.Y-110)), //���������ָ�����Ƶ����� ����λ���Ͻ�λ�û���ͼƬ
			rect<s32>(0,0,150,200),0, //�������Դͼ���ȡͼƬҪ��ʾ������ ���س�ͼƬ�Ĵ�С
			SColor(alpha,255,255,255),true);

		//��Ʒ���Ƶ�����.����
		vector2d<s32> textPos(position2di((pos.X-150+75 //��ȥͼƬ���,�ټ���һ���Ⱦ���ʵ�ʾ��е�x����
			),pos.Y-100));

		char* itemName=getItemNameById(itemid);
		char temp[255];
		
		//��ͨ���� 
		if(itemparam1==0 && itemid<1000)
		{ 
			TextCenter(   itemName ,textPos,SColor(alpha,255,255,255),15,700);
		}else if(itemparam1>0 && itemid<1000){
			sprintf(temp,"[׿Խ]%s",itemName);
			TextCenter(   temp ,textPos,SColor(alpha,0,255,0),15,700);
		}else if(itemid>=1000 ){
			TextCenter(   itemName ,textPos,SColor(alpha,255,255,255),15,700);
		}
		
		
	
		//1000���ڵ���Ʒid������
		if(itemid<1000){
			//�õ���ǰ�����ָ��װ���Ĺ�����
			int attack = itemparam2  ; //����ʵ�ʹ����� ���ڷ���˼����˵�


			sprintf(temp,"������:%d",attack);
			textPos.Y+=15;
			TextCenter(  temp ,textPos,SColor(alpha,255,255,255),14,500);
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
		
		TextCenter(  temp ,textPos,SColor(alpha,255,255,255),15,100);
		
		textPos.Y+=15;
		if(itemid<1000){
			sprintf(temp,"��������2:%d",itemparam2);
		}else if(itemid>=1000 && itemid<2000){
			sprintf(temp,"����:%d",itemparam2);
		}else if(itemid>=2000 ){
			sprintf(temp,"param2:%d",itemparam2);
		}

		TextCenter(  temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param3:%d",itemparam3);
		TextCenter(  temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param4:%d",itemparam4);
		TextCenter(  temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param5:%d",itemparam5);
		TextCenter(  temp ,textPos,SColor(alpha,255,255,255),15,100);

		textPos.Y+=15;
		sprintf(temp,"param6:%d",itemparam6);
		TextCenter(  temp ,textPos,SColor(alpha,255,255,255),15,100);

		delete itemName;
	}
}

char* MyGUIDlgCharPackage::getItemNameById(int itemID)
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

//��װ����ͼƬ���к���,�Լ�Ҫ���ƵĿ�ʼ����.���Ͻ�
void MyGUIDlgCharPackage::draw2dImage(int row,int col,rect<s32> re)
{
	drv->draw2DImage(item_pic,
		vector2d<s32>(re.UpperLeftCorner.X,re.UpperLeftCorner.Y), //���������ָ�����Ƶ�����
		rect<s32>(35*col,35*row,35*(col+1),35*(row+1)),0, //�������Դͼ���ȡͼƬҪ��ʾ������
		SColor(alpha,255,255,255),true);
}

//����������ź;��Ի���rect.
void MyGUIDlgCharPackage::DrawItem(rect<s32> re,int itemID)
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

void MyGUIDlgCharPackage::DrawAllItem()
{
	irr::core::rect<s32> r=win->getAbsolutePosition();
	int x=r.UpperLeftCorner.X+10;
	int y=143+r.UpperLeftCorner.Y;

	//35.75 
	if(win->isVisible()){
		//��
		for(int a=0;a<4;a++){
			//��
			for(int b=0;b<6;b++){
				rect<s32> rr(x+b*35,y+a*35,x+b*35+35,y+a*35+35);

				//0��ű�ʾ����
				if((int)main_char->getPackage()->itembox[a][b]==0){
					//printf("itembox[%d][%d]����Ʒ\n",a,b);
				}else{
				    DrawItem(rr,main_char->getPackage()->itembox[a][b]);
					//drv->draw2DRectangleOutline(rr,SColor(255,250,0,250));
				}
			}
		}
	}


}

void MyGUIDlgCharPackage::update()
{


	if(win->isVisible()){
		stringw t="";
		t+=main_char->getMoney();
		money_text->setText(t.c_str());

	}
	
}
