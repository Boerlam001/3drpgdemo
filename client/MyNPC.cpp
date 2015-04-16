#include ".\mynpc.h"

MyNPC::MyNPC( NPCProperty p,Socket::CNetClient* client)
{
	dlg=0;

	this->dev=getIrrDevice();
	this->client=client;
	
	smgr=getIrrSmgr();

	//npc����
	memset((char*)&npc_prop,0,sizeof(NPCProperty));
	memcpy((char*)&npc_prop,(char*)&p,sizeof(NPCProperty));

	//����

	node=smgr->addAnimatedMeshSceneNode(smgr->getMesh("npc/npc1.ms3d"));

	node->setPosition(p.pos);
	node->setRotation(p.rot);
	node->setID(p.ID);

	node->getMaterial(0).SpecularColor.set(0,0,0,0);//��ɫ
	node->setMaterialFlag(video::EMF_LIGHTING, false);//������
	node->setScale(core::vector3df(0.80f,0.80f,0.80f));//ģ������
	node->setMaterialFlag(video::EMF_ANTI_ALIASING,true);//���������
	//	node->setDebugDataVisible(scene::EDS_BBOX);
	node->setAnimationSpeed(10);
	node->getMaterial(0).NormalizeNormals=true;
	node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	//node->setPosition(npc_prop.pos);

	node->setAnimationSpeed(1);
	node->setFrameLoop(1, 10);

	//��ģ�ʹ�����������ѡ����������ڳ�����ײ��������ʰȡģ��
	scene::ITriangleSelector* selector;		//��ײѡ����
	selector= smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);//����ѡ����


	mouseCurNPC_Dlg=false;


	//------------------------------------------------------------------------------------------------------------
	//  ��ʾnpc���Ƶ�
	//char tmp[512];
	//GetWindowsDirectory(tmp,511);
	//strcat(tmp,"\\fonts\\SIMSUN.TTC");  //SIMSUN.TTC����,������         SIMKAI.TTF����     \STXIHEI.TTF   Fixedsys

	gui::IGUIFont *font;
	//SIMSUN.TTC����,������         SIMKAI.TTF����     \STXIHEI.TTF   Fixedsys
	//font = dev->getGUIEnvironment()->getFont(tmp,17, true,false);

	WCHAR * pwStr = ConvertLPCSTRToLPWSTR( npc_prop.strNPCName ); 

	font = dev->getGUIEnvironment()->getDXFont("����",true,15,0,800);

		char_textnode= smgr->addTextSceneNode(font,	pwStr, 	video::SColor(255,255,255,0), node);
	
	char_textnode->setPosition(vector3df(0,-5,0));

	delete pwStr;

}

MyNPC::~MyNPC(void)
{
}

//����npc�ĶԻ���.
void MyNPC::ShowTalkDlg()
{
	//�Ի���û��ʼ��,��ʾ��һ�ε��npc
	if( 0 ==dlg){
		//npc�ĶԻ���.��Ҫ֪��npc������
		dlg=new MyGUIDlgNpcTalk(&npc_prop,client);
		dlg->LoadGUI();
	}else{
		
		//�ٴε��npc.�Ի���ֱ����ʾ
		dlg->ShowDlg(true);
	}
}

void MyNPC::OnEvent(const SEvent& e)
{
	if(dlg){
		dlg->OnEvent(e);
		if(dlg->mouseInGui){
			mouseCurNPC_Dlg=true;
		}else{
			mouseCurNPC_Dlg=false;
		}

	}
	
}

void MyNPC::UIRender()
{
	if(dlg) dlg->drawAll();


	
}

void MyNPC::update()
{
	dlg->update();


}

//ж��
void MyNPC::drop()
{
	if(dlg){
		dlg->drop();
	}
	scene::ISceneNodeAnimator* anim;
	anim = smgr->createDeleteAnimator(1);  //ɾ��
	node->addAnimator(anim);
	anim->drop();	
}