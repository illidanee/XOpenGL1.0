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

void XHero::SetName(const char* name)
{
	strcpy(_Name, name);
}

void XHero::SetAge(int age)
{ 
	_Age = age; 
}