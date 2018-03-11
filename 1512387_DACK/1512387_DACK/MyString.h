#pragma once

#include "Resource.h"
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
using namespace std;

class MyString
{
private:
	string str;
public:
	MyString();
	MyString(string p);
	MyString(char *s);
	MyString(const MyString &p);

	MyString& operator = (const MyString &p);
	bool operator == (const MyString &p);
	vector<MyString> split(char *p)	const;
	static vector<MyString> Split(char *myStr, char *p);
	float toFloat() const;
	int toInt() const;
};