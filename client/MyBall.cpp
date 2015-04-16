#include ".\myball.h"



void MyBall::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{

	// set inverted world matrix(������������)
	// if we are using highlevel shaders (the user can select this when(�������Ҫ�ø߼���ɫ��Ⱦ,���Ǳ�������constants������)
	// starting the program), we must set the constants by name.


	// set clip matrix ���ü��þ���
	core::matrix4 worldViewProj;
	worldViewProj = drv->getTransform(video::ETS_PROJECTION);			
	worldViewProj *= drv->getTransform(video::ETS_VIEW);
	worldViewProj *= drv->getTransform(video::ETS_WORLD);


	services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);




	//͸����
	//mAlpha=0.30f;
	mAlpha+=0.001;
	if(mAlpha>=1.0f) mAlpha=0.1f;
	//printf("mAlpha:%3.1f \n",mAlpha);

	num+=0.005;
	services->setPixelShaderConstant("fTime", reinterpret_cast<f32*>(&num), 1);



}

s32 MyBall::get(){


	c8* vsFileName = 0; // filename for the vertex shader
	c8* psFileName = 0; // filename for the pixel shader

	video::E_DRIVER_TYPE driverType ;
	driverType=drv->getDriverType();

	switch(driverType)
	{
	case video::EDT_DIRECT3D9:
		psFileName = "textures/ball/ball.hlsl";
		vsFileName = psFileName; // both shaders are in the same file
		break;
	default:
		return 0;
		break;
	}

	//���Ӳ���Ƿ�֧����ɫ
	if (!drv->queryFeature(video::EVDF_PIXEL_SHADER_1_1) &&
		!drv->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1))
	{
		dev->getLogger()->log("WARNING: Pixel shaders disabled "\
			"because of missing driver/hardware support.");
		psFileName = 0;
	}

	if (!drv->queryFeature(video::EVDF_VERTEX_SHADER_1_1) &&
		!drv->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1))
	{
		dev->getLogger()->log("WARNING: Vertex shaders disabled "\
			"because of missing driver/hardware support.");
		vsFileName = 0;
	}


	s32 newMaterialType1;

	// create materials

	video::IGPUProgrammingServices* gpu = drv->getGPUProgrammingServices();
	if (gpu)
	{

		newMaterialType1 = gpu->addHighLevelShaderMaterialFromFiles(
			psFileName, "vertexMain", video::EVST_VS_2_0,
			psFileName, "pixelMain", video::EPST_PS_2_0,
			this, video::EMT_TRANSPARENT_ADD_COLOR);//EMT_TRANSPARENT_ADD_COLOR EMT_SOLID

	}


	return newMaterialType1;
}


MyBall::MyBall( ISceneNode* parentNode)
{
	this->dev=getIrrDevice();

	this->parentNode=parentNode;
	drv=dev->getVideoDriver();
	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();

	mAlpha=1.0f;
	num=0.1f;
}

MyBall::~MyBall(void)
{
}

void MyBall::update()
{
  sphere->setPosition(parentNode->getAbsolutePosition()+core::vector3df(0,5,0));

}


bool MyBall::init()
{


	sphere =smgr->addSphereSceneNode(5,32,0);
	if (sphere)
	{
		//sphere->setParent(parentNode);
		sphere->setPosition(parentNode->getAbsolutePosition()+core::vector3df(0,5,0));  //����ģ�͵�����
	//	sphere->setScale(core::vector3df(0.2,0.2,0.2));//ģ������
		sphere->setMaterialTexture(0, drv->getTexture("textures//ball//1a130f10.tga"));
		sphere->setMaterialTexture(1, drv->getTexture("textures//ball//1e360b90.tga"));
		sphere->setMaterialTexture(2, drv->getTexture("textures//ball//1eac7210.tga"));

		sphere->setMaterialFlag(video::EMF_LIGHTING, false);

	
		//���������ϲ���EMT_SPHERE_MAP
		//	sphere->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		sphere->setMaterialType((video::E_MATERIAL_TYPE)get());
		//	sphere->getMaterial(0).SpecularColor.set(0,255,0,0);//��ɫ

		//sphere->setMaterialFlag(EMF_BACK_FACE_CULLING ,false); //�رձ����޳�



		sphere->setScale(vector3df(2,2,2));
		//	gun->setRotation(vector3df(0,180,0));

		//��ת������
		//scene::ISceneNodeAnimator* anim;
		//anim = smgr->createRotationAnimator(
		//	core::vector3df(0,0.3f,0));  //��Y����ת �ٶ�0.3
		//sphere->addAnimator(anim);
		//anim->drop();

	}	

	return true;
}

void MyBall::drop()
{
	if(sphere) {
		scene::ISceneNodeAnimator* anim = 0;

		sphere->addAnimator(anim=smgr->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�

		anim->drop();
	}
}