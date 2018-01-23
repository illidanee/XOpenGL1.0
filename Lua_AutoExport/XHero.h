#pragma once


class XHero
{
public:
	XHero(int id, const char* name);
	~XHero();

	void SetName(const char* name);
	void SetAge(int age);

private:
	int _ID;
	char _Name[32];
	int _Age;
};