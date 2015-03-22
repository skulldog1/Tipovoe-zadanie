#ifndef FILE_SYSTEM_OBJECTS
#define FILE_SYSTEM_OBJECTS

#include <vector>
using namespace std;

#include "FileSystemObject.h"

class FileSystemObjects : public vector<FileSystemObject*>
{
	protected:
		const FileSystemObject *parent;
		std::vector<FileSystemObject*>::iterator GetIteratorByObject(FileSystemObject *object);

	public:
		FileSystemObjects(const FileSystemObject* parent);
		FileSystemObjects(const FileSystemObjects& objects);
		FileSystemObjects(const FileSystemObjects* objects);

		virtual ~FileSystemObjects();

		void Add(FileSystemObject *object, bool rewrite = false);
		void Add(const FileSystemObjects *objects, bool rewrite = false);

		void Remove(FileSystemObject *object);
		void Remove(const FileSystemObjects *objects);

		void RemoveAll();

		const bool Contains(FileSystemObject *object);

		friend ostream& operator<<(ostream& os, const FileSystemObjects& obj);

		friend FileSystemObjects operator+(const FileSystemObjects& left, const FileSystemObjects& right);
};

ostream& operator<<(ostream& os, const FileSystemObjects& obj);

FileSystemObjects operator+(const FileSystemObjects& left, const FileSystemObjects& right);

#endif