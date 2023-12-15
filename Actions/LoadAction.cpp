#include "LoadAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CTriangle.h"
#include "ClearAllAction.h"

LoadAction::LoadAction(ApplicationManager* pApp) : Action(pApp) {}

void LoadAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Loading File: Enter File Name");
	fName = pIn->GetString(pOut);
	ifstream fin;
	fin.open(fName);
}

bool LoadAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	ifstream fin;
	fin.open(fName);
	if (fin.is_open())
	{
		Action* pAct;
		pAct = new ClearAllAction(pManager);
		pAct->Execute();
		delete pAct;
		pAct = NULL;
		pOut->PrintMessage("Opened Load File Successfully");
		string x;
		Point P1;
		Point P2;
		Point P3;
		Point center;
		Point radius;
		int size;
		GfxInfo GfxInfo;
		bool selected;
		while (!fin.eof())
		{
			char y;
			fin >> x >> y;
			switch (y)
			{
			case 48:
				pOut->PrintMessage("Drew rect");
				fin >> P1.x >> P1.y >> P2.x >> P2.y >> GfxInfo.DrawClr >> GfxInfo.FillClr >> selected;
				pOut->DrawRect(P1, P2, GfxInfo, selected);
				getline(fin, x, '\n');
				if (fin.eof())
					return 1;
				break;
			case 49:
				pOut->PrintMessage("Drew square");
				fin >> center.x >> center.y >> size >> GfxInfo.DrawClr >> GfxInfo.FillClr >> selected;
				pOut->DrawSquare(center, size, GfxInfo, selected);
				getline(fin, x, '\n');
				if (fin.eof())
					return 1;
				break;
			case 50:
				pOut->PrintMessage("Drew tri");
				fin >> P1.x >> P1.y >> P2.x >> P2.y >> P3.x >> P3.y >> GfxInfo.DrawClr >> GfxInfo.FillClr >> selected;
				pOut->DrawTriangle(P1, P2, P3, GfxInfo, selected);
				getline(fin, x, '\n');
				if (fin.eof())
					return 1;
				break;
			case 51:
				pOut->PrintMessage("Drew circ");
				fin >> center.x >> center.y >> radius.x >> radius.y >> GfxInfo.DrawClr >> GfxInfo.FillClr >> selected;
				pOut->DrawCircle(center, radius, GfxInfo, selected);
				getline(fin, x, '\n');
				if (fin.eof())
					return 1;
				break;
			case 52:
				pOut->PrintMessage("Drew hex");
				fin >> center.x >> center.y >> size >> GfxInfo.DrawClr >> GfxInfo.FillClr >> selected;
				pOut->DrawSquare(center, size, GfxInfo, selected);
				getline(fin, x, '\n');
				if (fin.eof())
					return 1;
				break;
			default:
				pOut->PrintMessage("Didn't draw");
				if (fin.eof())
					return 1;
				break;
			}
		}
		fin.close();
		return 1;
	}
	return 0;
}
