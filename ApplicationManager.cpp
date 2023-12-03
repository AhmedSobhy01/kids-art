#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddHexagonAction.h"
#include "Actions\SelectAction.h"
#include "Actions\MoveAction.h"
#include "Actions\SwitchToDrawAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\ChangeOutlineColorAction.h"
#include "Actions\ChangeFillColorAction.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	SelectedFig = NULL;
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;

	case DRAW_SQUARE:
		pAct = new AddSquareAction(this);
		break;

	case DRAW_TRIANGLE:
		pAct = new AddTriangleAction(this);
		break;

	case DRAW_CIRCLE:
		pAct = new AddCircleAction(this);
		break;

	case DRAW_HEXAGON:
		pAct = new AddHexagonAction(this);
		break;

	case SELECT:
		pAct = new SelectAction(this);
		break;

	case MOVE:
		pAct = new MoveAction(this);
		break;
      
	case TO_PLAY:
		pAct = new SwitchToPlayAction(this);
		break;

	case TO_DRAW:
		pAct = new SwitchToDrawAction(this);
		break;

	case OUTLINE_COLOR:
		pAct = new ChangeOutlineColorAction(this);
		break;

	case FILL_COLOR:
		pAct = new ChangeFillColorAction(this);
		break;

	case EXIT:
		///create ExitAction here

		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}
CFigure* ApplicationManager::GetSelected() {
	return SelectedFig;
}
void ApplicationManager::SetSelected(CFigure* c) {
	SelectedFig = c;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	bool found = false;
	int i = FigCount - 1;
	while (i >= 0 && !found) {
		if (FigList[i]->CheckSelected(x, y)) {
			found = true;
		}
		else i--;
	}

	if (found)return FigList[i];


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;

}
