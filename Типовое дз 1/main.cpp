#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "ObjectName.h"

#include "FileSystemObject.h"
#include "FileSystemObjects.h"

#include "File.h"
#include "Catalog.h"

void TestObjectName()
{
	cout << "---------------------" << endl << endl;

	ObjectName obj1 = ObjectName("Объект");
	ObjectName obj2 = ObjectName("Объект");
	ObjectName obj3 = ObjectName("Объект Object");

	cout << obj1.GetName() << endl;
	cout << obj2.GetName() << endl;
	cout << obj3.GetName() << endl;
	cout << "obj1.Equals(&obj2): " << obj1.Equals(&obj2) << endl;
	cout << "obj1.Equals(&obj3): " << obj1.Equals(&obj3) << endl;

	cout << endl << "---------------------" << endl << endl;
};

void FileTest()
{
	cout << "---------------------" << endl << endl;

	File file1 = File(0, "Файл1.txt");

	FileSystemObject **file1Copy = new FileSystemObject*();
	file1.GetCopy("Файл1 копия.txt", file1Copy);

	cout << file1 << endl;
	cout << **file1Copy << endl;

	File *file2 = new File(file1);
	cout << *file2 << endl;

	cout << endl << "---------------------" << endl << endl;

	delete *file1Copy;
	delete file1Copy;
	delete file2;
};

void CatalogTest()
{
	cout << "---------------------" << endl << endl;

	Catalog disk = Catalog(0, "C:");

	Catalog *catalog1 = new Catalog(&disk, "Каталог 1");

	disk.Add((FileSystemObject*)catalog1);

	File file1 = File(0, "File1.txt");
	File file2 = File(0, "File2.dat");

	disk.Add(&file1);
	disk.Add(&file2);

	cout << disk << endl;
	cout << "---" << endl;

	disk.Copy(file1.GetName(), "File1copy.dat");

	cout << disk << endl;
	cout << "---" << endl;

	disk.Copy(file1.GetName(), "file2.dat");

	cout << disk << endl;
	cout << "---" << endl;

	disk.Move("file2.dat", "file3.dat");

	disk.Rename("File1copy.dat", "file4.txt");

	cout << disk << endl;
	cout << "---" << endl;

	disk.Remove("file3.dat");

	File** file  = new File*();
	disk.Find("file4.txt", file);
	disk.Remove((*file)->GetName());
	delete file;

	FileSystemObject** cat  = new FileSystemObject*();
	disk.Find(catalog1->GetName(), cat);
	disk.Remove((*cat)->GetName());
	delete cat;

	cout << disk << endl;
	cout << "---" << endl;

	Catalog diskD = Catalog(0, "D:");
	File fileD1 = File(0, "Файл D1.dat");
	File fileD2 = File(0, "Файл D2.dat");

	diskD.Add(&fileD1);
	diskD.Add(&fileD2);

	Catalog CDSum = Catalog(0, "E:");
	CDSum.Add((FileSystemObjects*)&diskD);
	CDSum.Add((FileSystemObjects*)&disk);
	cout << CDSum << endl;
	cout << "---" << endl;

	cout << endl << "---------------------" << endl << endl;

	CDSum.RemoveAll();
	disk.RemoveAll();
	diskD.RemoveAll();
	delete catalog1;
};


int main()
{
	setlocale(LC_ALL, "Russian");

	TestObjectName();
	getch();

	FileTest();
	getch();

	CatalogTest();
	getch();

	return 0;
};