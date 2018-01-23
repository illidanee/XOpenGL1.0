#include "XHero.h"

#include <string>

XHero::XHero(int id, const char* name)
{
	_ID = id;
	strcpy(_Name, name);
}

XHero::~XHero()
{

}

const char* XHero::GetName()
{
	return _Name;
}

void XHero::SetName(const char* name)
{
	strcpy(_Name, name);
}

int XHero::GetAge()
{
	return _Age;
}

void XHero::SetAge(int age)
{ 
	_Age = age; 
}