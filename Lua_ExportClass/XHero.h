#pragma once


class XHero
{
public:
	XHero(int id, char* name);
	~XHero();

	void SetName(char* name);
	void SetAge(int age);

private:
	int _ID;
	char _Name[32];
	int _Age;
};