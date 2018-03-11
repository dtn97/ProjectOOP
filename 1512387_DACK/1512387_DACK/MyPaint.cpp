#include "stdafx.h"
#include "MyPaint.h"

MyPaint::MyPaint()
{

}

MyPaint::MyPaint(const MyPaint& p)
{
	for (auto i : p.myFigure)
		myFigure.push_back(i->clone());
}

MyPaint::~MyPaint()
{
	for (auto i : myFigure)
		delete i;
	myFigure.clear();
}

MyPaint& MyPaint::operator = (const MyPaint& p)
{
	if (this != &p)
	{
		for (auto i : myFigure)
			delete i;
		myFigure.clear();
		for (auto i : p.myFigure)
			myFigure.push_back(i->clone());
	}
	return *this;
}

int MyPaint::readSVG(string fileName)
{
	string input_xml;
	string line;
	fstream in;
	in.open(fileName, ios_base::in);
	if (!in)
		return 1;
	while (getline(in, line))
		input_xml += line;
	in.close();
	vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');
	xml_document<> doc;
	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);
	xml_node<> *node = doc.first_node("svg");
	node = node->first_node();
	FigureFactory factory;
	do
	{
		Figure *_temp = factory.getFigure(node);
		_temp->setAttribute(node);
		myFigure.push_back(_temp);
		_temp = NULL;
		node = node->next_sibling();
	} while (node);
}

void MyPaint::draw(HDC &hdc)
{
	Graphics graph(hdc);
	for (auto i : myFigure)
		i->draw(graph);
}