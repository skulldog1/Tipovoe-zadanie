#include "EqualObject.h"

ObjectEqual::ObjectEqual() 
{
};

ObjectEqual::~ObjectEqual() 
{
};

const bool ObjectEqual::Equals(const ObjectEqual& obj) const
{
	return this->Equals(&obj);
};

const bool ObjectEqual::Equals(const ObjectEqual* obj) const
{
	return (obj != 0) && (this->ClassType() == obj->ClassType());
};

const int ObjectEqual::ClassType() const
{
	return 0;
};