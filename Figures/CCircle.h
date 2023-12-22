#ifndef CCIRCLE_H
#define CCIRCLE_H
#include "CFigure.h"
class CCircle : public CFigure
{
private:
	Point center;
	Point radius;
public:
	CCircle();
	CCircle(Point, Point, GfxInfo);
	void Draw(Output* pOut)const;
	bool CheckSelected(int x, int y);
	Point GetCenter() const;
	bool SetCenter(Point);
	bool Validate(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
};
#endif

