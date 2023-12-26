#include "PlayMode.h"

PlayMode::PlayMode(ApplicationManager *pApp) : Action(pApp)
{
	if (pManager->FiguresCount() != 0)
		RandomFigure = pManager->GetRandomFigure(); // Getting random figure
}

void PlayMode::ReadActionParameters() // Initializes the data members
{
	CorrectPicks = 0;
	Counter = 0;
}

void PlayMode::FinalMessage(bool &ChangedAction) // Displays the final message
{
	Output *pOut = pManager->GetOutput();
	if ((Counter == CorrectPicks) && !ChangedAction)
		pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else
		pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");
}

void PlayMode::SetCorrectCondition() // Sets the correct condition depending on which mode is chosen
{
	if (ClickedFigure != NULL)
		switch (Mode)
		{
		case PICK_BY_COLOR:
			CorrectCondition = ClickedFigure->GetFillColor() == RandomFigure->GetFillColor();
			break;
		case PICK_BY_SHAPE:
			CorrectCondition = ClickedFigure->Type() == RandomFigure->Type();
			break;
		case PICK_BY_SHAPE_COLOR:
			CorrectCondition = *ClickedFigure == *RandomFigure;
			break;
		}
}

void PlayMode::GetClickedAction(bool &ChangedAction, bool &EmptyClick)
{
	ChangedAction = false;
	EmptyClick = false;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	ActionType Act = pIn->GetAction(P);
	if (Act == TO_DRAW || (Act >= PICK_BY_COLOR && Act <= PICK_BY_SHAPE_COLOR) || Act == EXIT)
		ChangedAction = true;
	else
	{
		ClickedFigure = pManager->GetFigure(P.x, P.y);
		SetCorrectCondition();
		if (ClickedFigure == NULL || ClickedFigure->IsHidden())
		{
			EmptyClick = true;
			return;
		}
		else if (CorrectCondition)
		{
			CorrectPicks++;
			pOut->PrintMessage("Correct.");
		}
		else
			pOut->PrintMessage("Incorrect.");
		ClickedFigure->Hide();
	}
}

bool PlayMode::Execute()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	bool ChangedAction, EmptyClick;
	int FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0)
	{
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with.");
		return false;
	}
	ReadActionParameters();
	StartingMessage();

	while (CorrectPicks < Target && Counter != FiguresNumber) // Main loop
	{
		pIn->GetPointClicked(P.x, P.y);
		GetClickedAction(ChangedAction, EmptyClick);
		if (EmptyClick)
			continue;
		else if (ChangedAction)
			break;

		pManager->UpdateInterface();
		Counter++;
	}
	FinalMessage(ChangedAction);
	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}