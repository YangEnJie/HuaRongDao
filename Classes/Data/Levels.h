#ifndef LEVELS_H_
#define LEVELS_H_


#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "GameStruct.h"

using namespace tinyxml2;
USING_NS_CC;








class Levels
{
public:

	static Levels* getInstance();

	//std::vector<RowColRole> levels;
	std::vector<std::vector<RowColRole>> levels;

private:
	bool init();
	~Levels();

};

#endif