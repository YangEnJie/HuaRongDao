#ifndef GAME_LAYER_H_
#define GAME_LAYER_H_

#include "cocos2d.h"
#include "RoleSprite.h"

USING_NS_CC;


struct MoveStep 
{
	RoleSprite* roleSprite;
	Dicertion dir;
};


class GameLayer : public Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init();
	void previous(); //…œ“ª≤Ω
	

	

private:

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	bool isMove(RoleSprite* roleSprite, Dicertion dir);
	void moveAction(RoleSprite* roleSprite, Dicertion dir, bool mark = true);
	void ResetTable();
	void ResetLevel();
	void passLevel();
	bool initByLevel(int level);
	bool initByRoles();
	

private:
	int level = 0;
	bool table[5][4];
	RoleSprite* touchRole;
	Point beganPoint;
	Vector<RoleSprite*> roleSprites;
	std::vector<RowCol> rowCols;
	std::vector<MoveStep> moveMark;

};



#endif