#ifndef GAME_STRUCT_H_
#define GAME_STRUCT_H_


#include "cocos2d.h"
USING_NS_CC;


struct RowColRole
{
	int row = 0;
	int col = 0;
	int roleId = 0;
	bool isSet = false;
};

enum RoleType
{
	Type_Boss,
	Type_soldier,
	Type_General_Vertical,  //竖着的武将
	Type_General_horizontal, //垂直的武将


};


struct Role
{
	int height = 0;
	int width = 0;
	RoleType type;
	int id = 0;
	__String imageName;

};

struct RowCol
{
	int row = 0;
	int col = 0;

};
enum Dicertion
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};





















#endif