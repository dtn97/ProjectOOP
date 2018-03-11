#include "stdafx.h"
#include "Figure.h"

Figure::Figure()
{

}

Figure::Figure(const map<string, Attribute*> &p)
{
	for (auto i : p)
	{
		myAttr[i.first] = i.second->clone();
	}
}

Figure::Figure(const Figure &p)
{
	for (auto i : p.myAttr)
	{
		myAttr[i.first] = i.second->clone();
	}
}

Figure::~Figure()
{
	for (auto i : myAttr)
		delete i.second;
	myAttr.clear();
}

Figure& Figure::operator = (const Figure &p)
{
	if (this != &p)
	{
		for (auto i : myAttr)
			delete i.second;
		myAttr.clear();
		for (auto i : p.myAttr)
		{
			myAttr[i.first] = i.second->clone();
		}
	}
	return *this;
}

void Figure::draw(Graphics &graph)
{
	if ((Attribute*)myAttr["transform"] != NULL)
	{
		vector<float> temp = ((CTransform*)myAttr["transform"])->getValue();
		graph.TranslateTransform(temp[0], temp[1], MatrixOrderAppend);
		graph.RotateTransform(temp[2], MatrixOrderAppend);
		graph.ScaleTransform(temp[3], temp[4]);
	}
}

Figure* Figure::clone() const
{
	return new Figure(*this);
}

void Figure::setAttribute(xml_node<> *node)
{
	AttributeFactory factoryAttr;
	for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
	{
		Attribute *temp = factoryAttr.createAttribute(attr);
		if (temp != NULL)
		{
			temp->setAttribute(attr->value());
			myAttr[attr->name()] = temp;
			temp = NULL;
		}
	}
	factory.setAttribute(myAttr);
}

void Figure::setAttribute(string name, Attribute *p)
{
	if ((void*)myAttr[name] != NULL)
		delete myAttr[name];
	myAttr[name] = p->clone();
}

CLine::CLine() : Figure()
{

}

CLine::CLine(map<string, Attribute*> p) : Figure(p)
{

}
CLine::CLine(const CLine& p) : Figure(p)
{

}

CLine& CLine::operator = (const CLine &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CLine::draw(Graphics &graph)
{
	Pen *pen = factory.getPen();
	PointF p1 = factory.getPoint(myAttr["x1"], myAttr["y1"]);
	PointF p2 = factory.getPoint(myAttr["x2"], myAttr["y2"]);
	Figure::draw(graph);
	graph.DrawLine(pen, p1, p2);
	delete pen;
}

Figure* CLine::clone() const
{
	return new CLine(*this);
}

CCircle::CCircle() : Figure(){}
CCircle::CCircle(map<string, Attribute*> p) : Figure(p){}
CCircle::CCircle(const CCircle& p) : Figure(p){}

CCircle& CCircle::operator = (const CCircle &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CCircle::draw(Graphics &graph)
{
	Pen *pen = factory.getPen();
	SolidBrush *brush = factory.getBrush();
	PointF p = factory.getPoint(myAttr["cx"], myAttr["cy"]);
	float radius = factory.toFloat(myAttr["r"]);
	Figure::draw(graph);
	graph.DrawEllipse(pen, p.X - radius, p.Y - radius, radius * 2, radius * 2);
	graph.FillEllipse(brush, p.X - radius, p.Y - radius, radius * 2, radius * 2);
	graph.ResetTransform();
	delete pen;
	delete brush;
}

Figure* CCircle::clone() const
{
	return new CCircle(*this);
}

CEllipse::CEllipse() : Figure(){}
CEllipse::CEllipse(map<string, Attribute*> p) : Figure(p){}
CEllipse::CEllipse(const CEllipse& p) : Figure(p){}

CEllipse& CEllipse::operator = (const CEllipse &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CEllipse::draw(Graphics &graph)
{
	Pen *pen = factory.getPen();
	SolidBrush *brush = factory.getBrush();
	PointF p = factory.getPoint(myAttr["cx"], myAttr["cy"]);
	float radius1 = factory.toFloat(myAttr["rx"]);
	float radius2 = factory.toFloat(myAttr["ry"]);
	Figure::draw(graph);
	graph.DrawEllipse(pen, p.X - radius1, p.Y - radius2, radius1 * 2, radius2 * 2);
	graph.FillEllipse(brush, p.X - radius1, p.Y - radius2, radius1 * 2, radius2 * 2);
	graph.ResetTransform();
	delete pen;
	delete brush;
}

Figure* CEllipse::clone() const
{
	return new CEllipse(*this);
}

CRectangle::CRectangle() : Figure(){}
CRectangle::CRectangle(map<string, Attribute*> p) : Figure(p){}
CRectangle::CRectangle(const CRectangle& p) : Figure(p){}

CRectangle& CRectangle::operator = (const CRectangle &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CRectangle::draw(Graphics &graph)
{
	Pen *pen = factory.getPen();
	SolidBrush *brush = factory.getBrush();
	PointF p = factory.getPoint(myAttr["x"], myAttr["y"]);
	float width = factory.toFloat(myAttr["width"]);
	float height = factory.toFloat(myAttr["height"]);
	Figure::draw(graph);
	graph.DrawRectangle(pen, p.X, p.Y, width, height);
	graph.FillRectangle(brush, p.X, p.Y, width, height);
	graph.ResetTransform();
	delete pen;
	delete brush;
}

Figure* CRectangle::clone() const
{
	return new CRectangle(*this);
}

CPolyline::CPolyline() : Figure(){}
CPolyline::CPolyline(map<string, Attribute*> p) : Figure(p){}
CPolyline::CPolyline(const CPolyline& p) : Figure(p){}

CPolyline& CPolyline::operator = (const CPolyline &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CPolyline::draw(Graphics &graph)
{
	Pen *pen = factory.getPen();
	SolidBrush *brush = factory.getBrush();
	PointF *p = factory.getPoint(myAttr["points"]);
	int n = ((CPoints*)myAttr["points"])->getValue().size() / 2;
	Figure::draw(graph);
	graph.FillPolygon(brush, p, n);
	graph.DrawLines(pen, p, n);
	graph.ResetTransform();
	delete pen;
	delete brush;
}

CPolygon::CPolygon() : Figure(){}
CPolygon::CPolygon(map<string, Attribute*> p) : Figure(p){}
CPolygon::CPolygon(const CPolygon& p) : Figure(p){}

CPolygon& CPolygon::operator = (const CPolygon &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CPolygon::draw(Graphics &graph)
{
	Pen *pen = factory.getPen();
	SolidBrush *brush = factory.getBrush();
	PointF *p = factory.getPoint(myAttr["points"]);
	int n = ((CPoints*)myAttr["points"])->getValue().size() / 2;
	Figure::draw(graph);
	graph.FillPolygon(brush, p, n);
	graph.DrawPolygon(pen, p, n);
	graph.ResetTransform();
	delete pen;
	delete brush;
}

Figure* CPolygon::clone() const
{
	return new CPolygon(*this);
}

Figure* CPolyline::clone() const
{
	return new CPolyline(*this);
}

CText::CText() : Figure(){}
CText::CText(map<string, Attribute*> p) : Figure(p){}
CText::CText(const CText& p) : Figure(p){}

CText& CText::operator = (const CText &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CText::draw(Graphics &graph)
{
	SolidBrush *brush = factory.getBrush();
	int size = (int)(3.0 * (((CFloat*)myAttr["font-size"])->getValue()) / 4);
	PointF p1 = factory.getPoint(myAttr["x"], myAttr["y"]);
	PointF p(p1.X - size, p1.Y - size);
	Font f(&FontFamily(L"Times New Roman"), size);
	wchar_t *s = factory.getText(value);
	Figure::draw(graph);
	graph.DrawString(s, value.length(), &f, p, brush);
	delete brush;
	delete[] s;
}

Figure* CText::clone() const
{
	return new CText(*this);
}

void CText::setAttribute(xml_node<> *node)
{
	value = node->value();
	Figure::setAttribute(node);
}

CPath::CPath() : Figure(){}
CPath::CPath(map<string, Attribute*> p) : Figure(p){}
CPath::CPath(const CPath& p) : Figure(p){}

CPath& CPath::operator = (const CPath &p)
{
	if (this != &p)
	{
		Figure::operator=(p);
	}
	return *this;
}

void CPath::draw(Graphics &graph)
{
	SolidBrush *brush = factory.getBrush();
	Pen *pen = factory.getPen();
	GraphicsPath *path = ((CMyPath*)myAttr["d"])->getPath();
	Figure::draw(graph);
	graph.DrawPath(pen, path);
	graph.FillPath(brush, path);
	delete path;
	delete pen;
	delete brush;

}

Figure* CPath::clone() const
{
	return new CPath(*this);
}

CGroup::CGroup() : Figure(){}
CGroup::CGroup(map<string, Attribute*> p, vector<Figure*> a) : Figure(p)
{
	for (auto i : a)
		figure.push_back(i->clone());
}
CGroup::CGroup(const CGroup& p) : Figure(p){}

CGroup& CGroup::operator = (const CGroup &p)
{
	if (this != &p)
	{
		for (auto i : figure)
			delete i;
		figure.clear();
		for (auto i : p.figure)
			figure.push_back(i->clone());
		Figure::operator=(p);
	}
	return *this;
}

void CGroup::draw(Graphics &graph)
{
	for (auto i : figure)
	{
		i->draw(graph);
	}
}

Figure* CGroup::clone() const
{
	return new CGroup(*this);
}

void CGroup::setAttribute(xml_node<> *node)
{
	Figure::setAttribute(node);

	xml_node<> *node1 = node->first_node();
	if (node1 == NULL)
		return;
	
	FigureFactory factory;
	do
	{
		Figure *_temp = factory.getFigure(node1);
		for (auto i : myAttr)
		{
			_temp->setAttribute(i.first, i.second);
		}
		_temp->setAttribute(node1);
		figure.push_back(_temp);
		_temp = NULL;
		node1 = node1->next_sibling();
	} while (node1);
}

FigureFactory::FigureFactory(){
	myFigure["line"] = []{return new CLine; };
	myFigure["circle"] = []{return new CCircle; };
	myFigure["ellipse"] = []{return new CEllipse; };
	myFigure["rect"] = []{return new CRectangle; };
	myFigure["polyline"] = []{return new CPolyline; };
	myFigure["polygon"] = []{return new CPolygon; };
	myFigure["path"] = []{return new CPath; };
	myFigure["text"] = []{return new CText; };
	myFigure["g"] = []{return new CGroup; };
}

Figure* FigureFactory::getFigure(xml_node<> *node)
{
	return ((void*)myFigure[(string)node->name()]() == NULL ? NULL : myFigure[(string)node->name()]());
}