#include "ObjectName.h"

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

ObjectName::ObjectName() 
	: ObjectEqual()
{
	this->name = 0;
};

ObjectName::ObjectName(const char *name)
	: ObjectEqual()
{
	this->name = 0;
	this->SetName(name);
};

ObjectName::ObjectName(const ObjectName& name)
	: ObjectEqual()
{
	this->name = 0;
	this->SetName(name.GetName());
};

ObjectName::ObjectName(const ObjectName* name)
	: ObjectEqual()
{
	this->name = 0;
	this->SetName(name->GetName());
};

ObjectName::~ObjectName()
{
	this->SetName(0);
};

const char* ObjectName::GetName() const
{
	return this->name;
};

void ObjectName::SetName(const char *name)
{
	if (this->name != 0)
	{
		delete[]this->name;
		this->name = 0;
	};

	if (name != 0)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	};
};

const bool ObjectName::Equals(const ObjectEqual* obj) const
{
	if (!ObjectEqual::Equals(obj)) return false;
	if (this->ClassType() != obj->ClassType()) return false;
	return stricmp(this->GetName(), ((ObjectName*)obj)->GetName()) == 0 ? true : false;
};

const int ObjectName::ClassType() const
{
	return 1;
};
