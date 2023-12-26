#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"
#include <cmath>

class Output // The application manager should have a pointer to this class
{
	window *pWind;				 // Pointer to the Graphics Window
	window *pColorMenuWind;		 // Pointer to the Color Menu Window
	std::string LastMessage;	 // Last message printed on the status bar
	bool UpdateToolBar;			 // Indicates whether the tool bar should be updated or not
	bool UpdateStatusBar;		 // Indicates whether the status bar should be updated or not
	bool IsPlayingRecording;	 // Indicates whether the program is playing a recording or not
	bool PlayActionSoundEnabled; // Indicates whether the program should play an action sound or not

	void CreateColorMenuWind(int, bool); // Creates the color menu window
	void DrawColorMenuItems(bool) const; // Draws color images to color menu window
public:
	Output();

	window *CreateWind(int, int, int, int) const; // Creates the application window
	Input *CreateInput() const;					  // Creates a pointer to the Input object

	void OpenColorMenuWind(int = 0, bool = true); // Creates the color menu window and draws color images
	void CloseColorMenuWind();					  // Closes the color menu window
	window *GetColorMenuWind() const;			  // Returns pointer to the color menu window object

	// Toolbar functions
	void CreateDrawToolBar() const; // Creates Draw mode toolbar & menu
	void CreatePlayToolBar() const; // Creates Play mode toolbar & menu

	// Status bar functions
	void CreateStatusBar() const;				 // Creates the status bar
	void PrintMessage(std::string, bool = true); // Print a message on status bar
	void ClearStatusBar();

	void ClearDrawArea() const; // Clears the drawing area

	void UpdateInterface(); // Redraws all the drawing window if UpdateToolBar or UpdateStatusBar are true

	void SetRecordingState(bool);		// Changes start recording icon
	void SetPlayActionSoundState(bool); // Changes play sound icon

	// Figures drawing functions
	void DrawRect(Point, Point, GfxInfo, bool = false);			   // Draw a rectangle
	void DrawSquare(Point, int, GfxInfo, bool = false);			   // Draw a square
	void DrawTriangle(Point, Point, Point, GfxInfo, bool = false); // Draw a triangle
	void DrawHexagon(Point, int, GfxInfo, bool = false);		   // Draw a hexagon
	void DrawCircle(Point, Point, GfxInfo, bool = false);		   // Draw a circle

	color GetCurrentDrawColor() const; // Get current drawing color
	color GetCurrentFillColor() const; // Get current filling color
	int GetCurrentPenWidth() const;	   // Get current pen width

	~Output();
};

#endif