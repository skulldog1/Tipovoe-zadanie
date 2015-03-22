#include "FileSystemObject.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

FileSystemObject::FileSystemObject(const FileSystemObject* parent, const char *name)
	: ObjectEqual()
{
	this->parent = parent;
	this->name = new ObjectName(name);
};

FileSystemObject::FileSystemObject(const FileSystemObject& object)
	: ObjectEqual()
{
	this->parent = object.parent;
	this->name = new ObjectName(object.GetName());
};

FileSystemObject::FileSystemObject(const FileSystemObject* object)
	: ObjectEqual()
{
	this->parent = object->parent;
	this->name = new ObjectName(object->GetName());
};

FileSystemObject::~FileSystemObject()
{
	delete this->name;
	this->parent = 0;
};

const char* FileSystemObject::GetName() const
{
	return name != 0 ? (name->GetName() != 0 ? name->GetName() : "") : "";
};

void FileSystemObject::GetPath(char* path) const
{
	if (path == 0) return;
	strcpy(path, "");

	if (parent != 0)
	{
		char *parentPath = new char[MAX_PATH_LENGTH];
		parent->GetPath(parentPath);

		strcpy(path, parentPath);
		strcpy(path + strlen(path), "\\");
		strcpy(path + strlen(path), this->GetName());

		delete[]parentPath;
	}
	else
	{
		strcpy(path + strlen(path), this->GetName());
	};
};

const FileSystemObject* FileSystemObject::GetParentObject() const
{
	return 0;
};

void FileSystemObject::SetParentObject(const FileSystemObject* parent)
{
	this->parent = parent;
};


const bool FileSystemObject::Equals(const ObjectEqual* obj) const
{
	if (!ObjectEqual::Equals(obj)) return false;
	if (this->ClassType() != obj->ClassType()) return false;

	char *thisPath = new char[MAX_PATH_LENGTH];
	char *objPath = new char[MAX_PATH_LENGTH];

	this->GetPath(thisPath);
	((FileSystemObject*)obj)->GetPath(objPath);

	bool result = stricmp(thisPath, objPath) == 0 ? true : false;

	delete[]thisPath;
	delete[]objPath;

	return result;
};

const int FileSystemObject::ClassType() const
{
	return (int)(this->GetType());
};

ostream& operator<<(ostream& os, const FileSystemObject& obj)
{
	char *path = new char[MAX_PATH_LENGTH];
	obj.GetPath(path);

	os << (obj.GetType() == FileSystemObjectType::CATALOG
			? "Каталог: " 
			: obj.GetType() == FileSystemObjectType::FILE 
				? "Файл: " : "Объект файловой системы: "
			);
	os << path;

	delete[]path;

	return os;
};