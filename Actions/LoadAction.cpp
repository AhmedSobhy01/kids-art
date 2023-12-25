#include "LoadAction.h"
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
	pOut->PrintMessage("Loading File: Enter File Name or Press esc to Cancel");
	fName = pIn->GetString(pOut);
}

bool LoadAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	ifstream fin;
	fin.open("Saved Graphs/" + fName);			// save graph to Saved Graphs \ fName
	if (fin.is_open())
	{
		Action* pAct;
		pAct = new ClearAllAction(pManager);
		pAct->Execute();
		delete pAct;
		pAct = NULL;

		pOut->PrintMessage("Opened Load File Successfully");
		string x;
		CFigure* Figure;
		UI.PenWidth = 3;
		pOut->CreateDrawToolBar(); // To update border width icon
		while (!fin.eof())
		{
			fin >> UI.DrawColor >> UI.FillColor >> UI.BkGrndColor;
			int count;
			fin >> count;
			for (int i = 0; i <= count; i++)		// load all figures
			{
				fin >> x;
				if (x == "RECTANGLE")
					Figure = new CRectangle();
				else if (x == "SQUARE")
					Figure = new CSquare();
				else if (x == "CIRCLE")
					Figure = new CCircle();
				else if (x == "HEXAGON")
					Figure = new CHexagon();
				else if (x == "TRIANGLE")
					Figure = new CTriangle();
				Figure->Load(fin);
				Figure->Draw(pOut);
				pManager->AddFigure(Figure);
			}
		}
		fin.close();
		return 1;
	}
	pOut->PrintMessage("Please Enter a Valid File Name");
	return 0;
}

bool LoadAction::ShouldRecord() const
{
	return false;
}
