#pragma once
#include "CFigure.h"

struct PointDouble {
	double x, y;
	PointDouble(Point P) {
		x = P.x;
		y = P.y;
	};
	PointDouble() {
		x = 0; y = 0;
	}
};

class CHexagon : public CFigure
{
private:
	Point center;
	static const int DefaultHexagonSize;
	int hexagonSize;

	double calcTriangleArea(PointDouble, PointDouble, PointDouble);
public:
	CHexagon();
	CHexagon(Point, GfxInfo);
	void Draw(Output* pOut);
	static int GetDefaultHexagonSize();
	bool IsPointInside(Point);
	Point GetCenter() const;
	void SetCenter(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
	bool GetCorner(Point, int&);
	void SetCorner(Point, int);
};


