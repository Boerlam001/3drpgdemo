#pragma once






#include "VxHealthSceneNode.h"

#include "mycharheadermsg.h" //��ʾ������

#include "MyMonster.h"

#include "NetClient.h"

#include "mycharclothmgr.h"

#include "mysceneloader.h"


#include "MyWeaponMgr.h"   //����

#include "MyBall.h"

#include "MyCharMagicEffectMgr.h"

/************************************************************************/
// 
//		��ɫ�� ��Ϸ�������ɫ���������߽�ɫ���ô���
//		
//
/************************************************************************/




#define ANIMATION_SPEED 11

class MyMonster   ;
class MyWeaponMgr;

class MyCharacter : public irr::scene::IAnimationEndCallBack  
{
public:
	  
	
	MyCharacter( RoleProperty p,bool isMaincharacter ,MySceneLoader* sceneloader); 
	

	//���ؽ�ɫ/����ģ��,�����Ľڵ�
	void Draw();

	~MyCharacter(void);

    enum eAttacktype{ 
                 MagicAttack,  //ħ������
                 PowerAttack,  //������
    }; 

	//��ǰ����
	MySceneLoader* sceneloader;

	//���湥������
	eAttacktype curAttackType; 

	//��ɫ��װģ�͹�����
	MyCharClothMgr* m_charClothMgr; 

	//����������
	MyWeaponMgr* m_weapon_mgr;
	//�õ���ǰ����id
	int getCurWeapon(){return m_weapon_mgr->getCurWeaponId();};

	//���õ�ǰ�õ�����,��������������������
	void setCurWeapon(int weaponid,int weaponparam1){
		m_weapon_mgr->ChangeWeapon(weaponid,weaponparam1);
	};


	//���������ͼ
	void MyCharacter::SetWorldMap(int worldMap);

	//��ɫ���մ����Լ�����Ϣ
	void OnEvent (const irr::SEvent& e); 

	//��ɫ��������ʾ������
	void ShowAttackTextNum(int num);

	//�û�����
	void PostMsg(const wchar_t* msg);



	//ж��
	void drop();

	//ui����
	void UIRender();

	//�ܲ�����.
	void run(bool checkState);

	void stop()
	{
		isArrived=true;
		idle(true);
	}

	void OneTimeDie();
	bool isDieAnimation;//�Ѿ�ִ���������ض�����

	//�ı��ܲ�/��ģʽ
	void ChangeRunMode();

	//�õ�Ѫ�ٷֱ�
	f32 getHPper(){return f32 ((float)property.HP/(float)property.MAX_HP);};

	//��������
	void attack(vector3df attackpos,eAttacktype e); 

	//վ������
	void idle(bool checkState);  

	//����Ԥ������
	void readyAttack(bool checkState); 

	//ȡ������
	void CancelAttack();

	//�ı�״̬����Ԥ��/ս��
	void ChangeState();

	//�õ���ɫͷ��hp��
	VxHealthSceneNode* getHPBar(){return m_pgHealthBar;};

	//��ɫ����?
	bool isDeath(){return property.isDeath;};

	//��ɫ���ܹ���,�������˺�ֵ
	void UnderAttack( int damage);

	//����Ҫ�����Ĺ���
	void SetWantToAttackTarget(MyMonster* m){monster=m;isfollow=true;};
	//���ٹ���
	void FollowAndAttackTarget();
	MyMonster* monster;//�빥���Ĺ���
	bool isfollow; //�Ƿ��ڸ���?
	//�����Ƿ��ڽ�ɫ������Χ��
	bool getDistenceFromMonster(ISceneNode* monster);



	irr::scene::IAnimatedMeshSceneNode* getNode(); 
	core::vector3df faceTarget(irr::core::vector3df targetpos);
	void setPosition(core::vector3df pos); 
	void setRotate(core::vector3df rot); 
	core::vector3df getPosition(); 
	core::vector3df getRotate(); 

	int getState();
	void setState(int newState);

	//�õ�Ҫ�ƶ���������
	vector3df getTarget(){return property.target;};

	//��ʼ�ƶ�
	void Beginmove(core::vector3df pos);

	//����
	void update(); 
	void MyCharacter::Onlyupdate() ;





	//-----------------------------------------------------------------------------------
	//�����������ʾ�������߽�ɫ��.���������ڵ�ǰ����ɫ
	bool runstate;
	bool lastRunmode;
	void setRunAnimation( )
	{
		if(runstate==false ){
			runstate=true;			////ģʽδ�ı�
		}else if(runstate && lastRunmode==property.RunMode){
			return;
		}else if(lastRunmode!=property.RunMode){
			lastRunmode=property.RunMode;
		}
		//��?��
		if(property.RunMode){
			fSpeed = 0.7f; //�ٶ�
			m_charClothMgr->Animate(ANIMATION_SPEED+2,61,79,true);

		}else{
			fSpeed = 0.350f; //�ٶ�
			m_charClothMgr->Animate(ANIMATION_SPEED+1,1,19,true);
		}
	}
	//--------------------------------------------------------------------


	//������ɵ�callback
	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node) ;

	//����
	Socket::CNetClient* cnet;

	//�Ƿ�������ɫ
	bool isMain;

	//����,���͸���������
	void SetNetServer(Socket::CNetClient* net)
	{
		cnet=net;
	};

	//���½�ɫ��Ϣ�������� CMD_UserUPDATE
	void ReoprtToServer( );



	void setHP(int hp)
	{
		property.HP=hp;
	};

	int getMoney()
	{
		return package.money;
	};

	void setMoney(int moeny)
	{
		package.money=moeny;
	};

	//ֻ���½�ɫ�����������.
	void setPropPlane(RoleProperty* rr);

	//��ɫ�����Ե�.�����������
	void AddPoint(int proptype);


	//������ϵ�����Ʒ,����
	void CollectDropItem();

	RoleProperty getRoleproperty(){return property;};
	void setRoleproperty(RoleProperty pp){
		memcpy((char*)&property,(char*)&pp,sizeof(RoleProperty));
	};

	//��ɫ����������������
	void UpdateByProperty();


	ITimer* timer;
	u32 lasttime;
	u32 lastattacktime;

	u32 lastRecvtime; //���һ�ν��յ���ɫ��Ϣ��ʱ��


Package* getPackage()
{
	return &package;
};

void setPackage(Package p)
{
	memcpy((char*)&package,(char*)&p,sizeof(Package));
};

//���ָ���˽�ɫ
bool mouseCurCharacter;
     

float getMoveSpeed (){ return fSpeed;};

 private: 

	 MyBall* ball;
	 Magic::MyCharMagicEffectMgr* m_pMagic_Mgr;
	 //Magic::IMyCharMagicEffect* magic3;
	 //Magic::IMyCharMagicEffect* magic;
	 //Magic::IMyCharMagicEffect* magic2;

	 //��ʾ��ɫ���ֵ�text �ڽ�ɫģ������
	 ITextSceneNode* char_textnode;

	 irr::scene::VxHealthSceneNode* m_pgHealthBar;  //��ʾhp

	 RoleProperty property; //��ɫ����
	 Package package; //��ɫ����

	 //��ɫ�ƶ��ٶ�
	 float fSpeed;


	 //����core����
	 IrrlichtDevice* dev;						
	 ISceneManager* smgr;


	 int laststate;//����״̬


protected:
	void move();  //���Լ��ڲ�����
	bool isArrived;			//�Ƿ��ѵ���Ŀ�ĵ�


	//��ɫ�ƶ�
	void moveto(irr::scene::ISceneNode *node, //node to move 
		irr::core::vector3df vel); //velocity vector 


};
