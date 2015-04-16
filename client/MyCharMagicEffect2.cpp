#include ".\mycharmagiceffect2.h"

namespace Magic
{

MyCharMagicEffect2::MyCharMagicEffect2(vector3df rotspeed)
{
	this->dev=getIrrDevice();


	parentNode=0;
	node=0;

	drv=dev->getVideoDriver();
	ui=dev->getGUIEnvironment();
	smgr=dev->getSceneManager();

	
	this->rotspeed=rotspeed;

	mAlpha=1.0f;
	num=0.1f;
}

MyCharMagicEffect2::~MyCharMagicEffect2(void)
{
}

void MyCharMagicEffect2::setParentNode(ISceneNode* parentNode)
{
	this->parentNode=parentNode;
}

void MyCharMagicEffect2::update()
{
	if(parentNode && node)
       node->setPosition(parentNode->getAbsolutePosition()+pos);

}



bool MyCharMagicEffect2::init(ISceneNode* parentNode,vector3df pos, float speed, ITexture* tex)
{
	this->parentNode=parentNode;
	this->pos=pos;
	this->speed=speed;
	if(tex) this->tex=tex;

	int weaponType=1;
	node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("model/plane/plane.ms3d"));
	//node->setMaterialTexture(0, getIrrDriver()->getTexture("textures/circle.tga"));
	if(tex) node->setMaterialTexture(0,tex);
	//scene::ISceneNode* pJointNode =node->getMS3DJointNode("joint4");  //weapon���� 
	//if(pJointNode)
	//{


	//	//�Ƴ������ڵ�
	//	pJointNode->removeAll();

	//	video::SColor startcolor,endcolor;

	//	if(weaponType==1){
	//		startcolor=video::SColor(0,0,0,0);
	//		endcolor=SColor(0,20,20,60);
	//	}else if(weaponType==2){
	//		startcolor=video::SColor(0,0,0,0);
	//		endcolor=SColor(0,80,0,0);
	//	}else if(weaponType==3){
	//		endcolor=SColor(0,40,40,45);
	//		startcolor=video::SColor(0,0,0,0);
	//	}else if(weaponType==4){
	//		startcolor=video::SColor(0,0,0,0);
	//		endcolor=SColor( 0,0,40,50);
	//	}else if(weaponType==5){
	//		startcolor=video::SColor(0,50,0,50);
	//		endcolor=SColor(0,0,40,50);
	//	}else if(weaponType==6){
	//		startcolor=video::SColor(0,0,0,50);
	//		endcolor=SColor(0,0,40,60);
	//	}



	//	////�������ӷ�����
	//	scene::IParticleEmitter* em;
	//	scene::IParticleSystemSceneNode* ps ;//����ϵͳ
	//	ps = getIrrDevice()->getSceneManager()->addParticleSystemSceneNode(false); //����һ������ϵͳ,��ʹ���Զ���ķ�����
	//	//ps->setPosition(c->getPosition()+vector3df(0,50,0));//λ��
	//	//ps->setScale(core::vector3df(0.5f,0.5f,0.5f));//����
	//	//ps->setParticleSize(core::dimension2d<f32>(0.250f, 0.250f));//�������Ӵ�С
	//	ps->setParticlesAreGlobal(true);

	//	em=ps->createPointEmitter(vector3df(0,0.001f,0),30,40,
	//		startcolor, endcolor,//��ʼ��ɫ�ͽ�����ɫ
	//		2500,3000   //���ʱ��,800-2000����
	//		);
	//	em->setMaxStartSize(core::dimension2d<f32>(4.0f, 4.0f));
	//	em->setMinStartSize(core::dimension2d<f32>(4.0f, 4.0f));
	//	////�������ӷ�����
	//	//em = ps->createBoxEmitter(
	//	//	core::aabbox3d<f32>(-4,-4,-4,4,4,4),//���ú��ӵ�6������
	//	//	core::vector3df(0.0f,0.0f,0.0f),//���÷��䷽����ٶ�
	//	//	500,700,//ÿ����С������80,���100
	//	//	video::SColor(0,0,0,0), video::SColor(0,255,255,255),//��ʼ��ɫ�ͽ�����ɫ
	//	//	500,1000);//���ʱ��,800-2000����
	//	ps->setEmitter(em);//����ϵͳ���÷�����
	//	em->drop();

	//	scene::IParticleAffector* paf =ps->createFadeOutParticleAffector();
	//	ps->addAffector(paf);
	//	paf->drop();

	//	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	//	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	//	ps->setMaterialTexture(0, getIrrDevice()->getVideoDriver()->getTexture("textures/flare.bmp"));
	//	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	//	pJointNode->addChild(ps);

	//} 

	node->setPosition(pos);
	node->setScale(vector3df(10,0,10));
	//node->setRotation(vector3df(0,0,90));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialFlag(video::EMF_ZBUFFER, false); //�������,��͸����ʾ,���ᱻ�ڵ�
	node->setMaterialFlag(EMF_BACK_FACE_CULLING ,false); //�رձ����޳�
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//
	//node->setRotation(vector3df(90,0,0));

	scene::ISceneNodeAnimator* anim;

	anim = smgr->createRotationAnimator(rotspeed);  //��Y����ת �ٶ�0.3
	node->addAnimator(anim);
	anim->drop();	


	node->setMaterialType((video::E_MATERIAL_TYPE)get());





	return true;
}

void MyCharMagicEffect2::drop()
{
	if(node) {
		scene::ISceneNodeAnimator* anim = 0;
		node->removeAnimators();
		node->removeAll();
		node->remove();

	//	node->addAnimator(anim=smgr->createDeleteAnimator(1));//����ɾ������,ɾ���Լ�

	//	anim->drop();
	}
}



void MyCharMagicEffect2::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
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


	num=RandNum2(0.1f,0.90f,0.0025);
	video::SColorf col(1-num,1-num,num,0.0f);

	//		num=RandNum2(0.1f,2.0f,0.0025);
	//		video::SColorf col(num,1.0f-num,num,0.0f);
	//if(num>1.0f){
	//            col=SColorf(2-num,2.0f-num,num-1,0.0f);
	//}else{
	//	col=SColorf(num,1.0f-num,num,0.0f);
	//}

	//video::SColorf col(1,1,1,0.0f);
	//printf("%3.1f ",num);
	services->setVertexShaderConstant("mColor", reinterpret_cast<f32*>(&col), 4);


	//
	//mAlpha=0.30f;
	mAlpha=num+0.8;


	services->setPixelShaderConstant("fTime", reinterpret_cast<f32*>(&mAlpha), 1);

}





//��begin��end֮�����صĺ���
float MyCharMagicEffect2::RandNum2(float  begin,float end,float vlaue)
{
	static float yrot=begin;
	static bool a=true;
	if(a==true)  yrot+=vlaue;
	if(a==false) yrot-=vlaue;
	if(yrot>=end) 
	{
		a=false;
	}
	else if(yrot<=begin)
	{
		a=true;
	}

	return yrot;
} 

s32 MyCharMagicEffect2::get(){


	c8* vsFileName = 0; // filename for the vertex shader
	c8* psFileName = 0; // filename for the pixel shader

	video::E_DRIVER_TYPE driverType ;
	driverType=drv->getDriverType();

	switch(driverType)
	{
	case video::EDT_DIRECT3D9:
		psFileName = "model/plane/plane.hlsl";
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




} // namespace Magic