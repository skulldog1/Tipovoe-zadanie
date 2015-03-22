#include "FileSystemObjects.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

FileSystemObjects::FileSystemObjects(const FileSystemObject* parent)
	: vector<FileSystemObject*>()
{
	this->parent = parent;
};

FileSystemObjects::FileSystemObjects(const FileSystemObjects& objects)
	: vector<FileSystemObject*>(objects)
{
	this->parent = objects.parent;
};

FileSystemObjects::FileSystemObjects(const FileSystemObjects* objects)
	: vector<FileSystemObject*>(*objects)
{
	this->parent = objects->parent;
};

FileSystemObjects::~FileSystemObjects()
{
	this->RemoveAll();
};

void FileSystemObjects::Add(FileSystemObject *object, bool rewrite)
{
	if (Contains(object))
	{
		this->Remove(object);
		object->SetParentObject(this->parent);
		this->Add(object, rewrite);
	}
	else
	{
		object->SetParentObject(this->parent);
		this->push_back(object);
	};
};

void FileSystemObjects::Add(const FileSystemObjects *objects, bool rewrite)
{
	std::for_each(objects->begin(), objects->end(), 
		[this, rewrite](FileSystemObject* obj)
			{ 
				this->Add(obj, rewrite);
			});
};

void FileSystemObjects::Remove(FileSystemObject *object)
{
	if (!this->Contains(object)) return;

	std::vector<FileSystemObject*>::iterator it = GetIteratorByObject(object);
	this->erase(it);
};

void FileSystemObjects::Remove(const FileSystemObjects *objects)
{
	std::for_each(objects->begin(), objects->end(), 
		[this](FileSystemObject* obj)
			{ 
				this->Remove(obj);
			});
};

void FileSystemObjects::RemoveAll()
{
	this->Remove(this);
};

std::vector<FileSystemObject*>::iterator 
	FileSystemObjects::GetIteratorByObject(FileSystemObject *object)
{
	std::vector<FileSystemObject*>::iterator result = std::find_if(this->begin(), this->end(),
		[object](FileSystemObject* obj) -> bool
			{ 
				return obj->Equals(object);
			});

	return result;
};

const bool FileSystemObjects::Contains(FileSystemObject *object)
{
	return this->GetIteratorByObject(object) != std::end(*this);
};

ostream& operator<<(ostream& os, const FileSystemObjects& obj)
{
	os << "Объекты каталога: " << endl;
	ostream *pos = &os;

	std::for_each(obj.begin(), obj.end(), 
		[pos](const FileSystemObject* obj)
			{ 
				(*pos) << *obj << endl;
			});

	return os;
};

FileSystemObjects operator+(const FileSystemObjects& left, const FileSystemObjects& right)
{
	FileSystemObjects result = FileSystemObjects(left);
	result.Add(new FileSystemObjects(right));

	return result;
};