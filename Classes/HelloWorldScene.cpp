#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
// #include "Data/Roles.h"
// #include "Data/Levels.h"
// #include "RoleSprite.h"
#include "GameLayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
// 
// 	//auto role =  Roles::getInstance()->getRoleById(0);
// 
// 	for (auto role : Roles::getInstance()->roles)
// 	{
// 		CCLOG("wight, %d, height, %d, type, %d, image_name, %s, id, %d", role.width, role.height, role.type, role.imageName.getCString(), role.id);
// 	}
// 
// 	for (auto level : Levels::getInstance()->levels)
// 	{
// 		for (auto role : level)
// 		{
// 			//CCLOG("row %d, col %d, id %d", role.row, role.col, role.roleId);
// 
// 			auto roleSprite = RoleSprite::createById(role.roleId);
// 			addChild(roleSprite);
// 		}
// 		CCLOG("---------------------------------------");
// 	}
	auto layer = GameLayer::create();
	addChild(layer);
	
	auto button = (ui::Button*)rootNode->getChildByTag(15);
	button->addClickEventListener([=](Ref*){layer->previous(); });




    return true;
}
