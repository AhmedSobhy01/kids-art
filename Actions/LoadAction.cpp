#include "LoadAction.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CTriangle.h"
#include "ClearAllAction.h"

LoadAction::LoadAction(ApplicationManager *pApp) : Action(pApp) {}

void LoadAction::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Loading File: Enter File Name or Press esc to Cancel");
	FileName = pIn->GetString(pOut);
}

bool LoadAction::Execute()
{
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	ifstream FileInputStream;
	FileInputStream.open("Saved Graphs/" + FileName); // save graph to Saved Graphs \ FileName
	if (FileInputStream.is_open())
	{
		Action *pClearAllAction = new ClearAllAction(pManager);
		pClearAllAction->Execute();
		delete pClearAllAction;

		pOut->PrintMessage("Opened Load File Successfully");
		std::string x;
		CFigure *Figure;
		pOut->CreateDrawToolBar(); // To update border width icon
		UI.PenWidth = 3;
		UI.BackgroundColor = BASE;
		while (!FileInputStream.eof())
		{
			FileInputStream >> UI.DrawColor >> UI.FillColor;
			if (FileInputStream.peek() != '\n') FileInputStream >> UI.BackgroundColor;
			if (FileInputStream.peek() != '\n') FileInputStream >> UI.PenWidth;
			int count;
			FileInputStream >> count;
			for (int i = 0; i < count; i++) // load all figures
			{
				FileInputStream >> x;
				if (x == "RECTANGLE" || x == "RECT")
					Figure = new CRectangle();
				else if (x == "SQUARE")
					Figure = new CSquare();
				else if (x == "CIRCLE" || x == "CIRC")
					Figure = new CCircle();
				else if (x == "HEXAGON" || x == "HEXA")
					Figure = new CHexagon();
				else if (x == "TRIANGLE" || x == "TRIANG")
					Figure = new CTriangle();
				Figure->Load(FileInputStream);
				pManager->AddFigure(Figure);
			}
			FileInputStream >> x;
		}
		if (UI.BackgroundColor == TRANSPARENT_COLOR)UI.BackgroundColor = BASE;
		FileInputStream.close();
		return 1;
	}
	pOut->PrintMessage("Please Enter a Valid File Name");
	return 0;
}

bool LoadAction::ShouldRecord() const
{
	return false;
}
