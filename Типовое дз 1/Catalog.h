#ifndef CATALOG_H
#define CATALOG_H

#include "FileSystemObject.h"
#include "FileSystemObjects.h"

#include "File.h"

class Catalog : public FileSystemObject, public FileSystemObjects
{
	public:
		Catalog(const FileSystemObject* parent, const char *name);
		Catalog(const Catalog& object);
		Catalog(const Catalog* object);

		virtual ~Catalog();

		virtual FileSystemObjectType GetType() const;

		bool Copy(const char *name, const char *copyName, bool rewrite = false);
		bool Move(const char *oldName, const char *newName, bool rewrite = false);
		bool Rename(const char *oldName, const char *newName, bool rewrite = false); 
		void Remove(const char *name); 
		
		void Find(const char *name, FileSystemObject** object);
		void Find(const char *name, File** file);

		virtual void GetCopy(const char *name, FileSystemObject** copy) const;

		friend ostream& operator<<(ostream& os, const Catalog& obj);

		friend Catalog operator+(const Catalog& left, const Catalog& right);
};

ostream& operator<<(ostream& os, const Catalog& obj);
Catalog operator+(const Catalog& left, const Catalog& right);

#endif