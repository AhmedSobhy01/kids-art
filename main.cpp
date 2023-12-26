#include "ApplicationManager.h"

int main()
{
	ActionType ActType;			   // Type of the action selected by the user
	ApplicationManager AppManager; // Create an object of ApplicationManager

	do
	{
		ActType = AppManager.GetUserAction(); // Read the user action from the user

		AppManager.ExecuteAction(ActType); // Execute the action (code depends on action type)

		AppManager.UpdateInterface(); // Update the user interface after executing the action

	} while (ActType != EXIT); // If user selects exit, then exit the loop

	return 0;
}
