#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FileSystemObject
{
	public:
		File(const FileSystemObject* parent, const char *name);
		File(const File& object);
		File(const File* object);

		virtual ~File();

		virtual FileSystemObjectType GetType() const;

		virtual void GetCopy(const char *name, FileSystemObject** copy) const;
};


#endif