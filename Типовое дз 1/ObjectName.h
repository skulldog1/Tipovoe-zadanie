#ifndef OBJECT_NAME_H
#define OBJECT_NAME_H

#include "EqualObject.h"

const int OBJECT_NAME_TYPE = 1;

class ObjectName : public ObjectEqual
{
	private:
		char *name;

	public:
		ObjectName();
		ObjectName(const char *name);
		ObjectName(const ObjectName& name);
		ObjectName(const ObjectName* name);

		virtual ~ObjectName();

		const char* GetName() const;
		void SetName(const char *name);

		virtual const bool Equals(const ObjectEqual* obj) const;
		virtual const int ClassType() const;
};

#endif