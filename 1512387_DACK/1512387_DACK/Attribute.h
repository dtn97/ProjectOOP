#pragma once

#include "MyString.h"
#include "Resource.h"
#include "rapidxml.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")
using namespace rapidxml;

class Attribute
{
public:
	virtual void setAttribute(char *s) = 0;
	virtual Attribute* clone() const = 0;
};

class CColor : public Attribute
{
private:
	int R;
	int G;
	int B;
public:
	CColor();
	CColor(int r, int g, int b);
	CColor(const CColor &p);
	CColor& operator = (const CColor& p);
	void setAttribute(char *s);
	Attribute* clone() const;
	int* getValue();
};

class CFloat : public Attribute
{
private:
	float value;
public:
	CFloat();
	CFloat(float x);
	CFloat(const CFloat &p);
	CFloat& operator = (const CFloat &p);
	void setAttribute(char *s);
	Attribute* clone() const;
	float getValue();
};

class CPoints : public Attribute
{
private:
	vector<float> value;
public:
	CPoints();
	CPoints(const CPoints& p);
	CPoints& operator = (const CPoints &p);
	void setAttribute(char *s);
	Attribute* clone() const;
	vector<float> getValue();
};

class CTransform : public Attribute
{
private:
	float dx;
	float dy;
	float rotate;
	float sx;
	float sy;
public:
	CTransform();
	CTransform(const CTransform &p);
	CTransform& operator = (const CTransform &p);
	void setAttribute(char *s);
	Attribute* clone() const;
	vector<float> getValue();
};

class CMyPath : public Attribute
{
private:
	vector<MyString> value;
public:
	CMyPath();
	CMyPath(const CMyPath &p);
	CMyPath& operator = (const CMyPath &p);
	virtual void setAttribute(char *s);
	virtual Attribute* clone() const;
	GraphicsPath* getPath();
};

class AttributeFactory
{
public:
	map<string, function<Attribute*() >> myAttr;
public:
	AttributeFactory();
	Attribute* createAttribute(xml_attribute<> *attr);
};