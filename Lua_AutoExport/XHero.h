#pragma once


class XHero
{
public:
	XHero(int id, const char* name);
	~XHero();

	const char* GetName();
	void SetName(const char* name);
	int GetAge();
	void SetAge(int age);

public:
	int _ID;
	char _Name[32];
	int _Age;
};