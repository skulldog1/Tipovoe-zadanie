#ifndef FILE_SYSTEM_OBJECT
#define FILE_SYSTEM_OBJECT

#include <iostream>
using namespace std;

#include "EqualObject.h"
#include "ObjectName.h"

const short MAX_PATH_LENGTH = 512;

enum class FileSystemObjectType : int
	{
		FILE = 100,
		CATALOG = 200,
		NONE = 300
	};

class FileSystemObject : public ObjectEqual
{
	private:
		const FileSystemObject *parent;
		ObjectName *name;

	public:
		FileSystemObject(const FileSystemObject* parent, const char *name);
		FileSystemObject(const FileSystemObject& object);
		FileSystemObject(const FileSystemObject* object);

		virtual ~FileSystemObject();

		virtual FileSystemObjectType GetType() const = 0;

		virtual const char* GetName() const;

		virtual void GetPath(char* path) const;

		virtual const FileSystemObject* GetParentObject() const;
		virtual void SetParentObject(const FileSystemObject* parent);

		virtual const bool Equals(const ObjectEqual* obj) const;
		virtual const int ClassType() const;

		virtual void GetCopy(const char *name, FileSystemObject** copy) const = 0;

		friend ostream& operator<<(ostream& os, const FileSystemObject& obj);
};

ostream& operator<<(ostream& os, const FileSystemObject& obj);


#endif