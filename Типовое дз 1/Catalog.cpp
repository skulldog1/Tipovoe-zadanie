#include "Catalog.h"

#include <string>
#include <algorithm>
using namespace std;

Catalog::Catalog(const FileSystemObject* parent, const char *name)
	: FileSystemObject(parent, name), FileSystemObjects((FileSystemObject*)this)
{
};

Catalog::Catalog(const Catalog& object)
	: FileSystemObject(object), FileSystemObjects((FileSystemObjects&)object)
{
};

Catalog::Catalog(const Catalog* object)
	: FileSystemObject(object), FileSystemObjects((FileSystemObjects*)object)
{
};

Catalog::~Catalog()
{
};

FileSystemObjectType Catalog::GetType() const
{
	return FileSystemObjectType::CATALOG;
};

bool Catalog::Copy(const char *name, const char *copyName, bool rewrite)
{
	FileSystemObject** object = new FileSystemObject*();

	this->Find(name, object);

	if (object == 0 || (*object) == 0) return false;

	if (rewrite)
	{
		FileSystemObject** objectNew = new FileSystemObject*();
		this->Find(name, object);

		if (objectNew != 0 || (*objectNew) != 0) return false;

		delete objectNew;
	};

	FileSystemObject** copy = new FileSystemObject*();
	(*object)->GetCopy(copyName, copy);
	FileSystemObjects::Add(*copy, rewrite);
	delete copy;

	delete object;

	return true;
};

bool Catalog::Move(const char *oldName, const char *newName, bool rewrite)
{
	if (Copy(oldName, newName, rewrite))
	{
		this->Remove(oldName);
		return true;
	};

	return false;
};

bool Catalog::Rename(const char *oldName, const char *newName, bool rewrite)
{
	return this->Move(oldName, newName, rewrite);
};

void Catalog::Remove(const char *name)
{
	FileSystemObject** object = new FileSystemObject*();

	this->Find(name, object);
	if (object != 0 && (*object) != 0)
		FileSystemObjects::Remove(*object);

	delete object;
};

void Catalog::Find(const char *name, FileSystemObject** object)
{
	if (object == 0) return;
	(*object) = 0;

	std::for_each(this->begin(), this->end(), 
		[this, name, object](FileSystemObject*& obj)
			{ 
				if (stricmp(obj->GetName(), name) == 0) (*object) = obj;
			});
};
		
void Catalog::Find(const char *name, File** file)
{
	if (file == 0) return;
	(*file) = 0;

	FileSystemObject** object = new FileSystemObject*();

	this->Find(name, object);
	if (object == 0 
		|| (*object) == 0 
		|| (*object)->GetType() != FileSystemObjectType::FILE) return;

	(*file) = (File*)(*object);

	delete object;
};

void Catalog::GetCopy(const char *name, FileSystemObject** copy) const
{
	if (copy == 0) return;

	Catalog *catalog = new Catalog(this->GetParentObject(), name);
	catalog->Add(this);
	(*copy) = catalog;
};

ostream& operator<<(ostream& os, const Catalog& obj)
{
	os << (FileSystemObject&)obj << endl;
	os << (FileSystemObjects&)obj << endl;
	return os;
};

Catalog operator+(const Catalog& left, const Catalog& right)
{
	Catalog catalog = Catalog(left.GetParentObject(), left.GetName());
	catalog.Add(&(((FileSystemObjects&)left) + ((FileSystemObjects&)right)));
	return catalog;
};