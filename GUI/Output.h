#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include <cmath>

class Output // The application manager should have a pointer to this class
{
private:
	window *pWind;			// Pointer to the Graphics Window
	window *pColorMenuWind; // Pointer to the Color Menu Window
	string LastMessage;
	bool UpdateToolBar;
	bool UpdateStatusBar;
	bool IsPlayingRecording;
	bool PlayActionSoundEnabled;

public:
	Output();

	window *CreateWind(int, int, int, int) const; // creates the application window

	void CreateColorMenuWind(int, bool);		  // Creates color menu window
	void DrawColorMenuItems(bool) const;		  // Draws color images to color menu window
	void OpenColorMenuWind(int = 0, bool = true); // Creates the color menu window and draws color images
	void CloseColorMenuWind();					  // Closes the color menu window
	window *GetColorMenuWind() const;			  // Returns pointer to the color menu window or NULL if it doesn't exist

	void CreateDrawToolBar() const; // Creates Draw mode toolbar & menu
	void CreatePlayToolBar() const; // Creates Play mode toolbar & menu
	void CreateStatusBar() const;	// Create the status bar

	void SetRecordingState(bool);  // Changes toggle sound icon
	void SetPlayActionState(bool); // Changes start recording icon

	Input *CreateInput() const; // Creates a pointer to the Input object
	void ClearStatusBar();		// Clears the status bar
	void ClearDrawArea() const; // Clears the drawing area

	// Figures drawing functions
	void DrawRect(Point, Point, GfxInfo, bool = false);			   // Draw a rectangle
	void DrawSquare(Point, int, GfxInfo, bool = false);			   // Draw a square
	void DrawTriangle(Point, Point, Point, GfxInfo, bool = false); // Draw a triangle
	void DrawHexagon(Point, int, GfxInfo, bool = false);		   // Draw a hexagon
	void DrawCircle(Point, Point, GfxInfo, bool = false);		   // Draw a circle

	void PrintMessage(string, bool = true); // Print a message on status bar

	color GetCurrentDrawColor() const; // Get current drawing color
	color GetCurrentFillColor() const; // Get current filling color
	int GetCurrentPenWidth() const;	   // Get current pen width
	void UpdateInterface();

	~Output();
};

#endif