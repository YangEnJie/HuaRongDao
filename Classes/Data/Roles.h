#ifndef ROLES_H_
#define ROLES_H_

#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "GameStruct.h"

using namespace tinyxml2;
USING_NS_CC;







class Roles
{
public:


	static Roles* getInstance();


	Role getRoleById(int id);

	bool init();

	std::vector<Role> roles;


private:
	RoleType getTypeByString(const char *type);
	~Roles();

};

#endif