#include "stdafx.h"
#include "Attribute.h"


CColor::CColor()
{
	R = G = B = 0;
}

CColor::CColor(int r, int g, int b)
{
	R = r;
	G = g;
	B = b;
}

CColor::CColor(const CColor &p)
{
	R = p.R;
	G = p.G;
	B = p.B;
}

CColor& CColor::operator = (const CColor& p)
{
	if (this != &p)
	{
		R = p.R;
		G = p.G;
		B = p.B;
	}
	return *this;
}

void CColor::setAttribute(char *s)
{
	char s1[256];
	strcpy_s(s1, strlen(s) + 1, s);
	vector<MyString> temp = MyString::Split(s1, "rgb( ,.)");
	if (temp[0] == (string)"none")
	{
		R = G = B = -1;
		return;
	}
	R = temp[0].toInt();
	G = temp[1].toInt();
	B = temp[2].toInt();
}

Attribute* CColor::clone() const
{
	return new CColor(*this);
}

int* CColor::getValue()
{
	int* temp = new int[3];
	temp[0] = R;
	temp[1] = G;
	temp[2] = B;
	return temp;
}

CFloat::CFloat()
{
	value = 0;
}

CFloat::CFloat(float x)
{
	value = x;
}

CFloat::CFloat(const CFloat &p)
{
	value = p.value;
}

CFloat& CFloat::operator = (const CFloat &p)
{
	if (this != &p)
	{
		value = p.value;
	}
	return *this;
}

void CFloat::setAttribute(char *s)
{
	value = ((MyString)s).toFloat();
}

Attribute* CFloat::clone() const
{
	return new CFloat(*this);
}

float CFloat::getValue()
{
	return value;
}

CPoints::CPoints(){}

CPoints::CPoints(const CPoints& p)
{
	for (auto i : p.value)
		value.push_back(i);
}

CPoints& CPoints::operator = (const CPoints &p)
{
	if (this != &p)
	{
		value.clear();
		for (auto i : p.value)
			value.push_back(i);
	}
	return *this;
}

void CPoints::setAttribute(char *s)
{
	char *s1 = new char[strlen(s) + 1];
	strcpy_s(s1, strlen(s) + 1, s);
	vector<MyString> temp = MyString::Split(s1, ", ");
	for (auto i : temp)
		value.push_back(i.toFloat());
	delete[] s1;
}

Attribute* CPoints::clone() const
{
	return new CPoints(*this);
}

vector<float> CPoints::getValue()
{
	return value;
}

CTransform::CTransform()
{
	dx = dy = rotate = 0;
	sx = sy = 1;
}

CTransform::CTransform(const CTransform &p)
{
	dx = p.dx;
	dy = p.dy;
	rotate = p.rotate;
	sx = p.sx;
	sy = p.sy;
}

CTransform& CTransform::operator = (const CTransform &p)
{
	if (this != &p)
	{
		dx = p.dx;
		dy = p.dy;
		sx = p.sx;
		sy = p.sy;
		rotate = p.rotate;
	}
	return *this;
}

void CTransform::setAttribute(char *s)
{
	char s1[256];
	strcpy_s(s1, strlen(s) + 1, s);
	char *p1 = strstr(s1, "translate");
	char *p2 = strstr(s1, "rotate");
	char *p3 = strstr(s1, "scale");
	vector<MyString> temp;
	if (p1 != NULL)
	{
		*(strstr(p1, ")")) = '\0';
		p1 += 9;
		temp = MyString::Split(p1, "( ,)");
		dx = temp[0].toFloat();
		dy = temp[0].toFloat();
		temp.clear();
	}
	if (p2 != NULL)
	{
		*(strstr(p2, ")")) = '\0';
		p2 += 7;
		rotate = ((MyString)p2).toFloat();
	}
	if (p3 != NULL)
	{
		*(strstr(p3, ")")) = '\0';
		p3 += 6;
		temp = MyString::Split(p3, "( ,)");
		if (temp.size() == 1)
		{
			sx = sy = temp[0].toFloat();
		}
		else
		{
			sx = temp[0].toFloat();
			sy = temp[1].toFloat();
		}
	}
}

Attribute* CTransform::clone() const
{
	return new CTransform(*this);
}

vector<float> CTransform::getValue()
{
	vector<float> temp;
	temp.push_back(dx);
	temp.push_back(dy);
	temp.push_back(rotate);
	temp.push_back(sx);
	temp.push_back(sy);
	return temp;
}

CMyPath::CMyPath()
{

}

CMyPath::CMyPath(const CMyPath &p)
{
	for (auto i : p.value)
		value.push_back(i);
}

CMyPath& CMyPath::operator = (const CMyPath &p)
{
	if (this != &p)
	{
		value.clear();
		for (auto i : p.value)
			value.push_back(i);
	}
	return *this;
}

void CMyPath::setAttribute(char *s)
{
	char *s1 = new char[strlen(s) + 1];
	strcpy_s(s1, strlen(s) + 1, s);
	_strlwr_s(s1, strlen(s1) + 1);
	string str = (string)s1;
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == 'c' || str[i] == 'm' || str[i] == 'l' || str[i] == 'z')
		{
			if (i > 0 && str[i - 1] != ' ')
				str.insert(i++, 1, ' ');
			if (i < str.length() - 1 && str[i + 1] != ' ')
				str.insert(i++ + 1, 1, ' ');
		}
	}
	char *temp = new char[str.length() + 1];
	strcpy_s(temp, str.length() + 1, str.c_str());
	value = MyString::Split(temp, " ,-");
	delete[] temp;
	delete[] s1;
}

Attribute* CMyPath::clone() const
{
	return new CMyPath(*this);
}

GraphicsPath* CMyPath::getPath()
{
	GraphicsPath *path = new GraphicsPath;
	for (int i = 0; i < value.size(); ++i)
	{
		if (value[i] == (string)"c")
		{
			PointF a(value[i - 2].toFloat(), value[i - 1].toFloat());
			PointF b(value[i + 1].toFloat(), value[i + 2].toFloat());
			PointF c(value[i + 3].toFloat(), value[i + 4].toFloat());
			PointF d(value[i + 5].toFloat(), value[i + 6].toFloat());
			i += 6;
			path->AddBezier(a, b, c, d);

		}
		if (value[i] == (string)"l")
		{
			PointF a(value[i - 2].toFloat(), value[i - 1].toFloat());
			PointF b(value[i + 1].toFloat(), value[i + 2].toFloat());
			i += 2;
			path->AddLine(b, a);
		}
	}
	return path;
}

AttributeFactory::AttributeFactory()
{
	myAttr["x"] = []{return new CFloat; };
	myAttr["y"] = []{return new CFloat; };
	myAttr["cx"] = []{return new CFloat; };
	myAttr["cy"] = []{return new CFloat; };
	myAttr["x1"] = []{return new CFloat; };
	myAttr["x2"] = []{return new CFloat; };
	myAttr["y1"] = []{return new CFloat; };
	myAttr["y2"] = []{return new CFloat; };
	myAttr["r"] = []{return new CFloat; };
	myAttr["rx"] = []{return new CFloat; };
	myAttr["ry"] = []{return new CFloat; };
	myAttr["points"] = []{return new CPoints; };
	myAttr["fill"] = []{return new CColor; };
	myAttr["fill-opacity"] = []{return new CFloat; };
	myAttr["stroke"] = []{return new CColor; };
	myAttr["stroke-opacity"] = []{return new CFloat; };
	myAttr["stroke-width"] = []{return new CFloat; };
	myAttr["transform"] = []{return new CTransform; };
	myAttr["width"] = []{return new CFloat; };
	myAttr["height"] = []{return new CFloat; };
	myAttr["font-size"] = []{return new CFloat; };
	myAttr["d"] = []{return new CMyPath; };
}

Attribute* AttributeFactory::createAttribute(xml_attribute<> *attr)
{
	return  ((Attribute*)myAttr[(string)(attr->name())]() == NULL ? NULL : myAttr[(string)(attr->name())]());
}