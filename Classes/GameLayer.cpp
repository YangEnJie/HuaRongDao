#include "GameLayer.h"
#include "Data/Levels.h"
#include "GameStruct.h"

#include <iostream>











bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	level = 0;
	initByLevel(level);


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);




	return true;
}

bool GameLayer::initByLevel(int level)
{
	roleSprites.clear();
	moveMark.clear();
	ResetTable();
	auto levels = Levels::getInstance()->levels;
	if (level <= (int)levels.size())
	{
		auto currentLevel = levels.at(level);
		for (auto role : currentLevel)
		{
			auto roleSprite = RoleSprite::createById(role.roleId);
			roleSprites.pushBack(roleSprite);
			addChild(roleSprite);
			roleSprite->m_row = role.row;
			roleSprite->m_col = role.col;
			roleSprite->setPosition(role.col * 75.0f, role.row *75.0f);

			for (int i = role.row; i < role.row + roleSprite->m_hight; i++)
			{
				for (int j = role.col; j < role.col + roleSprite->m_width; j++)
				{
					table[i][j] = true;
				}
			}

		}
	}

	return true;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	beganPoint = touch->getLocation();
	for (auto rolesprite : roleSprites)
	{
		Rect roleRect = Rect(rolesprite->m_col*75.0f, rolesprite->m_row*75, rolesprite->m_width*75, rolesprite->m_hight*75);
		if (roleRect.containsPoint(touch->getLocation()))
		{
			touchRole = rolesprite;
			return true;
		}
	}
	return false;
}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point endPoint = touch->getLocation();

	if (beganPoint.getDistance(endPoint) <= 30)
	{
		return;
	}
	
	auto angle = ((int)CC_RADIANS_TO_DEGREES((endPoint - beganPoint).getAngle()) + 360) % 360;
	
	//
	Dicertion dir;
	if (angle > 315 || angle <= 45)
	{
		dir = RIGHT;
	}else if (angle > 45 && angle <= 135)
	{
		dir = UP;
	}else if (angle > 135 && angle <= 225)
	{
		dir = LEFT;
	}
	else
	{
		dir = DOWN;
	}
	CCLOG("angle %d", angle);
	CCLOG("dir %d", dir);
	moveAction(touchRole, dir);


}

bool GameLayer::isMove(RoleSprite* roleSprite, Dicertion dir)
{

	int row = roleSprite->m_row;
	int col = roleSprite->m_col;
	int targetRow = 0;
	int targetCol = 0;
	int width = roleSprite->m_width;
	int hight = roleSprite->m_hight;

	switch (dir)
	{
	case UP:
		if (row + hight < 5)
		{
			for (int i = col; i < col + width; i++)
			{
				if (table[row + hight][i])
				{
					return false;
				}
			}
			targetRow = row + 1;
			targetCol = col;
			for (int i = col; i < col + width; i++)
			{
				table[row][i] = false;
				table[row + hight][i] = true;
			}

		}
		else
		{
			return false;
		}
		break;
	case DOWN:
		if (row >= 1)
		{
			for (int i = col; i < col + width; i++)
			{
				if (table[row - 1][i])
				{
					return false;
				}
			}
			for (int i = col; i < col + width; i++)
			{
				table[row + hight - 1][i] = false;
				table[row - 1][i] = true;
			}
			targetRow = row - 1;
			targetCol = col;
		}
		else
		{
			return false;
		}
		break;
	case LEFT:
		if (col >= 1)
		{
			for (int i = row; i < row + hight; i++)
			{
				if (table[i][col - 1])
				{
					return false;
				}
			}
			targetRow = row;
			targetCol = col - 1;

			for (int i = row; i < row + hight; i++)
			{
				table[i][col + width - 1] = false;
				table[i][col - 1] = true;
			}

		}
		else
		{
			return false;
		}
		break;
	case RIGHT:
		if (col + width < 4)
		{
			for (int i = row; i < row + hight; i++)
			{
				if (table[i][col + width])
				{
					return false;
				}
			}
			targetRow = row;
			targetCol = col + 1;

			for (int i = row; i < row + hight; i++)
			{
				table[i][col] = false;
				table[i][col + width] = true;
			}
		}
		else
		{
			return false;
		}
		break;
	default:
		break;
	}

	return true;
}


void GameLayer::moveAction(RoleSprite* roleSprite, Dicertion dir, bool mark)
{

	

	int row = roleSprite->m_row;
	int col = roleSprite->m_col;
	int targetRow = 0;
	int targetCol = 0;
	int width = roleSprite->m_width;
	int hight = roleSprite->m_hight;


	if (isMove(roleSprite,dir))
	{

		switch (dir)
		{
		case UP:
			targetRow = row + 1;
			targetCol = col;
			break;
		case DOWN:
			targetRow = row - 1;
			targetCol = col;
			break;
		case LEFT:
			targetRow = row;
			targetCol = col - 1;
			break;
		case RIGHT:
			targetRow = row;
			targetCol = col + 1;
			break;
		default:
			break;
		}
// 	    std::vector<RowColRole> rowColRoles;
// 		for (auto role : roleSprites)
// 		{
// 			RowColRole rowColRole;
// 			rowColRole.row = roleSprite->m_col;
// 			rowColRole.col = roleSprite->m_col;
// 			rowColRole.roleId = roleSprite->m_id;
// 			rowColRoles.push_back(rowColRole);
// 		}
// 		moveMark.push_back(rowColRoles);
		/*moveMark.push_back(roleSprites);*/

		if (mark)
		{
			MoveStep moveStep;
			moveStep.roleSprite = roleSprite;
			moveStep.dir = dir;
			moveMark.push_back(moveStep);
		}


		roleSprite->m_col = targetCol;
		roleSprite->m_row = targetRow;
		roleSprite->runAction(MoveTo::create(0.2f, Vec2(targetCol* 75.0f, targetRow*75.0f)));
		passLevel();
		
	}

}



void GameLayer::ResetTable()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			table[i][j] = false;
		}
	}

}

void GameLayer::passLevel()
{
	rowCols.clear();
	for (auto roleSprite : roleSprites)
	{
		RowCol rowCol;
		rowCol.row = roleSprite->m_row;
		rowCol.col = roleSprite->m_col;
		rowCols.push_back(rowCol);
		if (roleSprite->m_type == Type_Boss && roleSprite->m_row == 0)
		{
			ResetLevel();
			level += 1;
			initByLevel(level);
		}
	}
}

void GameLayer::ResetLevel()
{
	for (auto role : roleSprites)
	{
		assert(role);
		role->removeFromParent();
	}
}
void GameLayer::previous()
{
	if (moveMark.empty())
	{
		return;
	}

	auto moveStep = moveMark.back();
	moveMark.pop_back();

	switch (moveStep.dir)
	{
	case UP:
		moveStep.dir = DOWN; break;
	case DOWN:
		moveStep.dir = UP; break;
	case LEFT:
		moveStep.dir = RIGHT; break;
	case RIGHT:
		moveStep.dir = LEFT; break;
	default:
		break;
	}
	moveAction(moveStep.roleSprite, moveStep.dir, false);

}


