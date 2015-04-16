
/************************************************************************/
// 
//		��ͷ�ļ�Ϊ���ݽṹ���� �������ݽṹ���ڴ˶���
//		
//
/************************************************************************/



//��ɫ����
typedef struct tag_RoleProperty
{
	char cmd; //����
	unsigned short sock;
	char worldMap_id; // ��ɫ���ĸ������ͼ
	char charSex; //��ɫ�Ա� 1 �� 2 Ů
	unsigned short Level; //�ȼ�
	int Exp; //��ǰ����
	int NextLevelExp; //����һ�����辭��
	unsigned short usePoint;	//�������Ե���
	unsigned short Power_Point; //��������
	unsigned short Minjie_Point; //���ݵ���
	unsigned short Tili_Point;  //��������
	unsigned short HP;		//Ѫ 
	unsigned short MAX_HP;  //���
	unsigned short Defense; //������
	unsigned short Attack;  //������
	irr::core::vector3df pos;  //����
	irr::core::vector3df rot;  //��ת
	irr::core::vector3df target; //Ҫ�ƶ���Ŀ��
	bool RunMode;   //��ģʽ ������;
	bool isDeath;			//�ѹ�
	char roleName[20];    //��ɫ��
	char currState;		//��ǰ����
}RoleProperty;


//��ɫ�����ṹ
typedef struct tag_Package
{
	char cmd;
	unsigned short sock;

	unsigned short currWeapon; //��ǰ��ɫ���ϵ�����
	unsigned short weaponparam1;//������6������
	unsigned short weaponparam2;
	unsigned short weaponparam3;
	unsigned short weaponparam4;
	unsigned short weaponparam5;
	unsigned short weaponparam6;

	char row1;
	char col1;
	char row2;
	char col2;

	int money;			    //��ɫ��Ǯ

	unsigned short itembox[4][6]; //4��6�� ��Ʒ���,��������,����,����Ʒ.
	unsigned short itemParam1[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam2[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam3[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam4[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam5[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam6[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���

}Package;


#define Skill_1 1   //�������
#define Skill_2 2   //ʱ��֮��


//��ɫ�ļ��ܱ�ṹ
typedef struct tag_RoleSkillTable
{
	char cmd;
	unsigned short sock;
	unsigned short skill[10]; //10������  -1��ʾ�� 0��ʾ��δѧϰ 1��ʾ�����ȼ� ���9�� .������Чʱ����ȼ�������ӳ�

}RoleSkillTable;


//��������
typedef struct tag_MonsterProperty
{
	char cmd;				//����
	unsigned short ID;		//id 
	char worldMap_id;		// �������ĸ������ͼ
	char Name[20];    //������
	unsigned short HP;		//Ѫ 
	unsigned short MAX_HP;  //���
	unsigned short Defense; //������
	unsigned short Attack;  //������
	bool isDeath;			//�ѹ�
	irr::core::vector3df pos;  //����
	irr::core::vector3df rot;  //��ת
	char currState; //��ǰ����
	irr::core::vector3df target; //Ҫ�ƶ���Ŀ��
	unsigned short damage; //���������˺�
	unsigned short killedByUser; //���ĸ���ɫɱ���� �ͻ��˲���
}MonsterProperty;


//������Ʒ�ṹ��Ϣ
typedef struct tag_SItem
{
	unsigned short item_index ;		 //��Ʒ���,1000���ڶ������� 1000-2000 ������Ʒ		 2000-3000 ��װ��	
	unsigned short itemParam1; 
	unsigned short itemParam2; 
	unsigned short itemParam3; 
	unsigned short itemParam4; 
	unsigned short itemParam5; 
	unsigned short itemParam6; 

	int itemPrice;			 //��Ʒ�۸�
	char itemName[25];               //��Ʒ����
}SItem;


//NPC����
typedef struct tag_NPCProperty
{
	char cmd;					//����
	unsigned short ID;			//id 
	char worldMap_id;			// npc���ĸ������ͼ
	irr::core::vector3df pos;   //����
	irr::core::vector3df rot;   //��ת
	char strNPCName[25];		//npc����
	char strNpcTalk[255];		//npc�Խ�ɫ˵�Ļ�
	char strBtnText[25];        //�Ի���ť�ϵ���
}NPCProperty;

//����npc����NPCProperty.���հ���ShopPackage.���̵�


//�̵�����ṹ
typedef struct tag_ShopPackage
{
	char cmd;

	char worldMap_id;			// ��������npc
	unsigned short ID;			// NPC ID

	char row1;
	char col1;

	unsigned short itembox[4][6]; //4��6�� ��Ʒ���,��������,����,����Ʒ.
	unsigned short itemParam1[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam2[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam3[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam4[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam5[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	unsigned short itemParam6[4][6]; //4��6�� ��Ʒ��Ӧ�Ĳ���
	int itemPrice[4][6];			 //��Ʒ�۸�

}ShopPackage;


//msglist�ṹ
typedef struct tag_ClientMsg
{
	int size; //pData��С 
	char* pData; 
}ClientMsg;




typedef struct tag_ServerRoleMSG
{ 
	char cmd; //����
	int sock; 
	char msg[255]; //��󺰻�����
}ServerRoleMSG;


#define  cRun   1		//��
#define  cWalk  2	//��
#define  cAttack  3	//����
#define  cIdle  4		//ս��
#define  cReadyAttack  5//Ԥ������
#define  cDeath  6 //����
#define  cAttack2  7	//����2


#define CMD_C2S_UserRequest_LOGIN  1 //��ɫ����½ ����������Ϣ
#define CMD_UserUPDATE  2 //��ɫ������Ϣ������� 
#define CMD_S2C_User_LOGIN  3 //�õ�����ɫ������Ϣ
#define CMD_S2C_NEWUSER  4  //��ɫ������Ϣ,���͸������˵�.
#define CMD_QUIT  5	 //��ɫ�˳�
#define CMD_USERMSG  6  //��ɫ����
#define CMD_C2S_UNKNOWUSER  7  //����δ֪��ɫ��Ϣ
#define CMD_S2C_USERUNDERATTACK  8  //��ɫ��������Ϣ
#define CMD_C2S_USERCollectItem  9  //��ɫ�������Ʒ
#define CMD_S2C_USERMoneyUpdate  10 //��ɫ��Ǯ���� 
#define CMD_C2S_Request_AddPoint  11 //��ɫ��������Ե� 
#define CMD_C2S_Request_Prop  12 //��ɫ�������������Ϣ,����hp ������,������. ����,����,����.����
#define CMD_S2C_Response_Prop  13 //�������Խ�ɫ�������������Ϣ����
//#define CMD_S2C_Response_AllOnlineRole 0x15  //��������Ӧ14����
#define CMD_C2S_Request_ChangeWeapon  14  //�ͻ��Է�������������
#define CMD_S2C_Response_ChangeWeapon  15  //��������Ӧ,�㲥���������߽�ɫ
#define CMD_C2S_Request_Package  16  //�ͻ��Է���������װ������
#define CMD_S2C_Response_Package  17  //��������Ӧװ������
#define CMD_C2S_Request_ChangePackageItem  18  //�ͻ����������������Ʒ����λ��
#define CMD_S2C_Response_ChangeWorld  19  //������Ҫ��ͻ��л���ͼ
#define CMD_C2S_Request_DropPackageItem  20 //�ͻ��������ٰ�����ĳ��Ʒ
#define CMD_C2S_Request_UsePackageHPItem  21  //�ͻ��Է���������ʹ��װ�������������Ʒ,����hp,mp�ָ�
#define CMD_C2S_Request_SellPackageItem 22  //�ͻ�������۸���Ʒ
#define CMD_C2S_Request_RoleSkillTable 23; //�����������Ϣ
#define CMD_C2S_Request_AllOnlineRole 24   //�ͻ��Է����������������߽�ɫ


#define MonsterCMD_LOGIN  40 //���¹������
#define MonsterCMD_UPDATE  41 //���������Ϣ
#define MonsterCMD_UnderAttack   42 //���ﱻ����
#define MonsterCMD_UNKNOWMONSTER   43 //����δ֪�������Ϣ
#define MonsterCMD_MonsterAll   44 //�������й�����Ϣ,һ������һ��



//������Ʒ��Ϣ
#define SceneCMD_ITEMDROP  50 //�е�����Ʒ���
#define SceneCMD_ITEMDROPAll   51 //�������е�����Ʒ��Ϣ,һ��SceneItem����һ��
#define SceneCMD_ITEMDROPAllNum 52 //�������е�����Ʒ��,����SceneItemNum�ṹ
#define SceneCMD_ITEMDROPRemove   53 //ĳ��Ʒ��ʧ



#define CMD_C2S_UserRequest_NPC 70 //��ɫ����npc��Ϣ
#define CMD_S2C_NPC_Shop		71 //npc�̵귢�͸��ͻ�
#define CMD_C2S_UserBuyShop     72 //��ɫ������npc���̵�


#define ITEMType_Money  1 //���
#define ITEMType_Item   2 //��Ʒ
//��Ʒ�ṹ
typedef struct tag_SceneItem
{
	char cmd; //������Ʒ��Ϣ
	char worldMap_id; // ��Ʒ���ĸ������ͼ
	char item_Type; //��Ʒ���� ������ 1��� 2��Ʒ
	unsigned short item_index;	   //��Ʒ����
	char itemName[20]; //��Ʒ����
	vector3df pos; //��Ʒ����
	unsigned short param1;
	unsigned short param2;
	unsigned short param3;
	unsigned short param4;
	unsigned short param5;
	unsigned short param6;
}SceneItem;


//��Ʒ�ṹ
typedef struct tag_SceneItemNum
{
	char cmd; //������Ʒ��Ϣ
	int itemnum; //��Ʒ����
}SceneItemNum;

//�����½ʱѡ��Ľ�ɫ��Ϣ.
typedef struct
{
	int charSex; //�Ա� 0�� 1Ů
	char* rolename; //����
}SLogin;





//��Ʒ��Ŷ��� ����weaponmgr itemgui
#define SRJ_Weapon  1  //˫�н�
#define TWJ_Weapon  2  //���޽�
#define CWJ_Weapon  3  //������
#define JXKJ_Weapon  4  //��е����
#define DMGSJ_Weapon  5  //������Ͻ�
#define XBJ_Weapon  6  //������
#define BLD_Weapon  7  //��ɏ��
#define STD_Weapon  8  //������
#define Cai7_Weapon  9  //7�ʽ�
#define JC_Weapon  10  //�޳ݽ�
#define BSRJ_Weapon  11  //��˫�н�
#define WRJ_Weapon  12 //���н�
#define LWRJ_Weapon  13  //�����н�
#define BJ_Weapon  14  //�⽣
#define LHJ_Weapon  15  //������
#define BLJ_Weapon  16  //������


#define Man_Body1 0x20		 //������
#define Man_Trousers1 0x21   //�п���
#define Man_Legs1 0x22		 //�л���
#define Man_Shoes1 0x23		 //��ѥ��


