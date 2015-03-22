#include "File.h"

File::File(const FileSystemObject* parent, const char *name)
	: FileSystemObject(parent, name)
{
};

File::File(const File& object)
	: FileSystemObject(object)
{
};

File::File(const File* object)
	: FileSystemObject(object)
{
};

File::~File()
{
};

FileSystemObjectType File::GetType() const
{
	return FileSystemObjectType::FILE;
};

void File::GetCopy(const char *name, FileSystemObject** copy) const
{
	if (copy == 0) return;

	File *file = new File(this->GetParentObject(), name);
	(*copy) = file;
};