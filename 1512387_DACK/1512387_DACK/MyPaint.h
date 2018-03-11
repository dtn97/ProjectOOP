#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "Figure.h"


class MyPaint
{
private:
	vector<Figure*> myFigure;
public:
	MyPaint();
	MyPaint(const MyPaint& p);
	~MyPaint();
	MyPaint& operator = (const MyPaint& p);
	int readSVG(string fileName);
	void draw(HDC &hdc);
};