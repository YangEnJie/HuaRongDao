#include "Roles.h"


static Roles* s_Roles = nullptr;
static std::string RolesFileName = "Roles.xml";


Roles::~Roles()
{

	if (s_Roles != nullptr)
	{
		delete s_Roles;
	}
	s_Roles = nullptr;

}


Roles* Roles::getInstance()
{
	if (s_Roles == nullptr)
	{
		s_Roles = new Roles();
		s_Roles->init();
	}
	return s_Roles;
}


bool Roles::init()
{
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(RolesFileName);

	tinyxml2::XMLDocument pDoc;

	FileUtils::getInstance()->setPopupNotify(false);
	ssize_t fileSize = 0;
	std::string data = FileUtils::getInstance()->getStringFromFile(filePath.c_str());
	FileUtils::getInstance()->setPopupNotify(true);
	pDoc.Parse(data.c_str());
	XMLElement * pEle = pDoc.RootElement();
	//auto child = pEle->FirstChildElement();


	for (auto child = pEle->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{

		Role role;
		/*std::string str;*/
		role.id = atoi(child->Attribute("id"));
		role.width = atoi(child->Attribute("width"));
		role.height = atoi(child->Attribute("height"));
		role.type = getTypeByString(child->Attribute("type"));
		role.imageName = __String(child->Attribute("image_name"));

		roles.push_back(role);
	}

	return true;
}

RoleType Roles::getTypeByString(const char *type)
{
	if (strcmp("boss", type) == 0)
	{
		return Type_Boss;
	}
	else if (strcmp("general_ver", type) == 0)
	{
		return Type_General_Vertical;
	}
	else if (strcmp("general_hor", type) == 0)
	{
		return Type_General_horizontal;
	}
	else
	{
		return Type_soldier;
	}
	
}

Role Roles::getRoleById(int id)
{

	for (auto role : roles)
	{
		if (role.id == id)
		{
			return role;
		}
	}
	Role mroles;
	return mroles;
}