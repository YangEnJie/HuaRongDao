#include "RoleSprite.h"
#include "Data/Roles.h"

RoleSprite* RoleSprite::createById(int id)
{

	auto roleSprite = new RoleSprite();
	if (roleSprite && roleSprite->init(id))
	{
		roleSprite->autorelease();
		return roleSprite;
	}
	else
	{
		delete roleSprite;
		return nullptr;
	}
}
bool RoleSprite::init(int id)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	
	auto role = Roles::getInstance()->getRoleById(id);
	m_id = id;
	m_hight = role.height;
	m_width = role.width;
	m_type = role.type;
	this->setSpriteFrame(role.imageName.getCString());
	this->setAnchorPoint(Vec2::ZERO);
	return true;

}