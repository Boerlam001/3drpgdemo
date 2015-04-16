#if !defined(_H____INCLUDED_)
#define _H____INCLUDED_


#include "mymonster.h"

#include "NetClient.h"

#include "mycharactermgr.h"


/************************************************************************/
// 
//		������������
//		
//
/************************************************************************/


class MyCharacterMgr;
class MySceneManager;

class MyMonstersMgr
{
public:
	MyMonstersMgr(  MySceneManager* mysmgr,Socket::CNetClient* net);
	~MyMonstersMgr(void);
	//�����¼�
	 void OnEvent (const irr::SEvent& e);

	 //�������й����Ƿ�ɼ�
	 void setAllMonsterVisiable(bool v);

	 //������������ݵ���
	void insertMonsterData(const char* pData,const unsigned int DataLength);

	void AddMonster(MonsterProperty prop);
	MyMonster* GetMonsterByID(int id);

	//�Ƴ��������߹���.�����л�����ʱ��.
	void RemoveAllMonsters();
	
	//��������������еĹ�����Ϣ
	void getMonsterCMD_MonsterAll();

	int getAllMonsterNum(){return monster_list.getSize();};

	void Update();
	void UIRender();

	void SetCharacter(MyCharacter* _user);

	MyMonster* GetMonster(ISceneNode* node);

	bool GetNodeIsselected(){return Nodeselected;};
	MyMonster* GetselectedMonster(){return selectednode;};

	void Quit(){m_bquit=true;};

private:

void MyMonstersMgr::MonsterCMD_LOGIN_PROC(char* pData,unsigned long length);
void MyMonstersMgr::MonsterCMD_UPDATE_PROC(char* pData,unsigned long length);
void MyMonstersMgr::MonsterCMD_UnderAttack_PROC(char* pData,unsigned long length);

	void  DoListThread( );



	MySceneManager* m_pMySceneMgr;

	CRITICAL_SECTION g_cs_msglist; //�ٽ�
	core::list<ClientMsg*> msglist;    //��server��������Ϣ��,���¿ͻ���Ϣ��


	CRITICAL_SECTION g_cs_monsterlist; //�ٽ�
		//�����������
	core::list<MyMonster*>  monster_list;
	core::list<MyMonster*>::Iterator list_oper;

	//����ָ��
	IrrlichtDevice *device;		

	Socket::CNetClient* net;

	//��������
	scene::ISceneManager* smgr;


	//��ǰ��ɫ
	MyCharacter* user;

	//�����ʰȡ�Ĺ���
	MyMonster* selectednode;
	bool Nodeselected;
	
	ITimer* timer;
	u32 lasttime;


	//��ʾ��ѡ�����text

	vector2d<s32> MonsterTextShowPos;

	bool m_bquit; //�˳�

};

#endif