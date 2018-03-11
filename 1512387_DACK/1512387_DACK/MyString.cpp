#include "stdafx.h"
#include "MyString.h"

MyString::MyString()
{

}

MyString::MyString(string p)
{
	str = p;
}

MyString::MyString(char *s)
{
	str = (string)s;
}

MyString::MyString(const MyString &p)
{
	str = p.str;
}

MyString& MyString::operator = (const MyString &p)
{
	if (this != &p)
	{
		str.clear();
		str = p.str;
	}
	return *this;
}

bool MyString::operator == (const MyString &p)
{
	return str == p.str;
}

vector<MyString> MyString::split(char *p)	const
{
	char *temp = new char[str.length() + 1];
	strcpy_s(temp, str.length() + 1, str.c_str());
	char *s = new char[256];
	vector<MyString> result;
	char *i = NULL;
	s = strtok_s(temp, p, &i);
	if (s != NULL)
		result.push_back((MyString)s);
	while (s = strtok_s(NULL, p, &i))
	{

		result.push_back((MyString)s);
	}
	delete[] temp;
	delete[] s;
	return result;
}

vector<MyString> MyString::Split(char *myStr, char *p)
{
	MyString temp(myStr);
	return temp.split(p);
}

float MyString::toFloat() const
{
	return atof(str.c_str());
}

int MyString::toInt() const
{
	return atoi(str.c_str());
}