#include "stdafx.h"
#include "Factory.h"

GraphphicsFactory::GraphphicsFactory()
{

}

void GraphphicsFactory::setAttribute(map<string, Attribute*> p)
{
	attr["fill"] = ((Attribute*)p["fill"] == NULL ? new CColor(-1, -1, -1) : p["fill"]->clone());
	attr["fill-opacity"] = ((Attribute*)p["fill-opacity"] == NULL ? new CFloat(1) : p["fill-opacity"]->clone());
	attr["stroke"] = ((Attribute*)p["stroke"] == NULL ? new CColor(-1, -1, -1) : p["stroke"]->clone());
	attr["stroke-opacity"] = ((Attribute*)p["stroke-opacity"] == NULL ? new CFloat(1) : p["stroke-opacity"]->clone());
	attr["stroke-width"] = ((Attribute*)p["stroke-width"] == NULL ? new CFloat : p["stroke-width"]->clone());
}

Color GraphphicsFactory::getColor(Attribute* color, Attribute *opac)
{
	int *c = ((CColor*)color)->getValue();
	float opacity = ((CFloat*)opac)->getValue();
	if (c[0] == -1)
	{
		c[0] = c[1] = c[2] = 0;
		opacity = 0;
	}
	Color result((int)(opacity * 255), c[0], c[1], c[2]);
	delete c;
	return result;
}

Pen* GraphphicsFactory::getPen()
{
	float width = ((CFloat*)attr["stroke-width"])->getValue();
	Pen *pen = new Pen(getColor(attr["stroke"], attr["stroke-opacity"]), width);
	return pen;
}

SolidBrush* GraphphicsFactory::getBrush()
{
	SolidBrush *brush = new SolidBrush(getColor(attr["fill"], attr["fill-opacity"]));
	return brush;
}

float GraphphicsFactory::toFloat(Attribute *p)
{
	return ((CFloat*)p)->getValue();
}

PointF GraphphicsFactory::getPoint(Attribute *p1, Attribute *p2)
{
	float a = toFloat(p1);
	float b = toFloat(p2);
	PointF result(a, b);
	return result;
}

PointF* GraphphicsFactory::getPoint(Attribute* p)
{
	vector<float> temp = ((CPoints*)p)->getValue();
	PointF *points = new PointF[temp.size() / 2];
	for (int i = 0; i < temp.size() / 2; ++i)
	{
		points[i].X = temp[2 * i];
		points[i].Y = temp[2 * i + 1];
	}
	return points;
}

wchar_t* GraphphicsFactory::getText(string str)
{
	int size = str.length();
	wchar_t *s = new wchar_t[size];
	for (int i = 0; i < size; ++i)
	{
		s[i] = (wchar_t)str[i];
	}
	return s;
}