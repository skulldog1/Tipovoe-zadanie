#ifndef EQUAL_OBJECT_H
#define EQUAL_OBJECT_H

class ObjectEqual
{
	public:
	ObjectEqual();
	virtual ~ObjectEqual();

	virtual const bool Equals(const ObjectEqual& obj) const;
	virtual const bool Equals(const ObjectEqual* obj) const;

	virtual const int ClassType() const;
};

#endif