#include<iostream>
#include <cstring>

using namespace std;

class CompactDisc
{
private:
	char title[20];
	int capacity;

public:
	CompactDisc(const char* t, int c) 
	{
		strcpy_s(title, t);
		capacity = c;
		cout << "CompactDisc() called" << endl;
	}

	~CompactDisc() {
		cout << "~CompactDisc() called" << endl;
	}

	const char* getTitle()
	{
		return title;
	}
	int getCapacity()
	{
		return this->capacity;
	}
};

class CDDrive 
{
private:
	char manufacturer[20];
	int speed;
	CompactDisc* aCompactDisc;

public:
	CDDrive(const char* m, int s)
	{
		strcpy_s(manufacturer, m);
		speed = s;
		aCompactDisc = nullptr;
		cout << "CDDrive() called" << endl;
	}

	~CDDrive() 
	{
		cout << "~CDDrive() called" << endl;
	}

	void InsertCD(CompactDisc* cd)
	{
		aCompactDisc = cd;
	}

	void Play() {
		if (aCompactDisc == nullptr)
		{
			cout << "Please insert a disc." << endl;
		}
		else {
			cout << "Title: " << aCompactDisc->getTitle() << ", Capacity: " << aCompactDisc->getCapacity() << " MB" << endl;
		}
	}

	CompactDisc* EjectCD()
	{
		CompactDisc* temp = aCompactDisc;
		aCompactDisc = nullptr;
		return temp;
	}
};

int main() {
	CompactDisc cd1("Disc 1", 800);
	CompactDisc cd2("Disc 2", 750);
	CDDrive theCDDrive("Manufacturer", 24);

	theCDDrive.InsertCD(&cd1);
	theCDDrive.Play();
	theCDDrive.EjectCD();
	theCDDrive.Play();
	theCDDrive.InsertCD(&cd2);
	theCDDrive.Play();
	theCDDrive.EjectCD();

	return 0;
}
