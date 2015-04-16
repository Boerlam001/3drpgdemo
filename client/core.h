#ifndef CORE_H 
#define CORE_H 


#include "stdafx.h"



#include "shadercpp/effectwrapper.h"

//#include "effectHandler.h"

#include "myscenemanager.h"


#include "realisticwater.h" 



#include "NetClient.h"

class GameMain: public irr::IEventReceiver { 
public: 
	GameMain (SLogin*); 
	~GameMain (); 
	virtual      bool OnEvent (const irr::SEvent& e); 
	void Run (); 

	void Login(); // ����ģ��


	SLogin* slogin;

	bool InitNetWork();

	//����������͵�½����
	void SendLoginRequest();

	//�ȴ���������Ӧ��½,������
	bool WaitForServerLoginResponse();
	HANDLE m_h_LoginEvent; //�ȴ���½����Ӧ�¼�����

	MySceneManager* myScene_Mgr;
private: 
	irr::IrrlichtDevice *device; 
	irr::video::IVideoDriver *drv; 
	irr::gui::IGUIEnvironment* ui;
	irr::scene::ISceneManager *smgr; 
	irr::u32 last_time; 

	Socket::CNetClient client;  //����

	char temp[255];



	RealisticWaterSceneNode* water;

	scene::IVolumeLightSceneNode * n;









	screenEffect::effectHandler* effect;

	gui::IGUIMeshViewer* v;


	bool	uesBlur;

	bool HideOther;

}; 

#endif // CORE_H