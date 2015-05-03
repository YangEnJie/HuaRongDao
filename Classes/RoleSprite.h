#ifndef ROLE_SPRITE_H_
#define ROLE_SPRITE_H_


#include "cocos2d.h"
#include "GameStruct.h"
USING_NS_CC;


class RoleSprite : public Sprite
{
public:
	static RoleSprite* createById(int id);;
	virtual bool init(int id);

	//RowCol rowCol;

	int m_hight = 0;
	int m_width = 0;
	int m_row = 0;
	int m_col = 0;
	int m_id = 0;
	RoleType m_type = Type_soldier;

};













#endif // !ROLE_SPRITE_H_






