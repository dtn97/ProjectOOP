#pragma once

#include "Resource.h"
#include "Attribute.h"
#include <wchar.h>

class GraphphicsFactory
{
private:
	map<string, Attribute*> attr;
public:
	GraphphicsFactory();
	void setAttribute(map<string, Attribute*> p);
	Color getColor(Attribute* color, Attribute *opac);
	Pen* getPen();
	SolidBrush* getBrush();
	float toFloat(Attribute *p);
	PointF getPoint(Attribute *p1, Attribute *p2);
	PointF* getPoint(Attribute* p);
	wchar_t* getText(string str);
};