#pragma once

#include "resource.h"
#include "Factory.h"

#include <iostream>
#include <fstream>
#include <wchar.h>
#include <map>
#include <wchar.h>
#include "rapidxml.hpp"	

using namespace std;
using namespace rapidxml;
#include "Attribute.h"

class Figure
{
protected:
	map<string, Attribute*> myAttr;
	GraphphicsFactory factory;
public:
	Figure();
	Figure(const map<string, Attribute*> &p);
	Figure(const Figure &p);
	virtual ~Figure();
	Figure& operator = (const Figure &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
	virtual void setAttribute(xml_node<> *node);
	virtual void setAttribute(string name, Attribute *p);
};

class CLine : public Figure
{
public:
	CLine();
	CLine(map<string, Attribute*> p);
	CLine(const CLine& p);
	CLine& operator = (const CLine &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CCircle : public Figure
{
public:
	CCircle();
	CCircle(map<string, Attribute*> p);
	CCircle(const CCircle& p);
	CCircle& operator = (const CCircle &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CEllipse : public Figure
{
public:
	CEllipse();
	CEllipse(map<string, Attribute*> p);
	CEllipse(const CEllipse& p);
	CEllipse& operator = (const CEllipse &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CRectangle : public Figure
{
public:
	CRectangle();
	CRectangle(map<string, Attribute*> p);
	CRectangle(const CRectangle& p);
	CRectangle& operator = (const CRectangle &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CPolyline : public Figure
{
public:
	CPolyline();
	CPolyline(map<string, Attribute*> p);
	CPolyline(const CPolyline& p);
	CPolyline& operator = (const CPolyline &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CPolygon : public Figure
{
public:
	CPolygon();
	CPolygon(map<string, Attribute*> p);
	CPolygon(const CPolygon& p);
	CPolygon& operator = (const CPolygon &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CText : public Figure
{
private:
	string value;
public:
	CText();
	CText(map<string, Attribute*> p);
	CText(const CText& p);
	CText& operator = (const CText &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
	virtual void setAttribute(xml_node<> *node);
};

class CPath : public Figure
{
public:
	CPath();
	CPath(map<string, Attribute*> p);
	CPath(const CPath& p);
	CPath& operator = (const CPath &p);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class CGroup : public Figure
{
private:
	vector<Figure*> figure;
public:
	CGroup();
	CGroup(map<string, Attribute*> p, vector<Figure*> a);
	CGroup(const CGroup& p);
	CGroup& operator = (const CGroup &p);
	virtual void setAttribute(xml_node<> *node);
	virtual void draw(Graphics &graph);
	virtual Figure* clone() const;
};

class FigureFactory
{
private:
	map<string, function<Figure*()>> myFigure;
public:
	FigureFactory();
	Figure* getFigure(xml_node<> *node);
};