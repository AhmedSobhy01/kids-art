#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include <cmath>

class Output // The application manager should have a pointer to this class
{
private:
	window *pWind;		   // Pointer to the Graphics Window
	window *colorMenuWind; // Pointer to the Color Menu Window
	string lastMessage;

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

	void CreateDrawToolBar() const;	   // Creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	   // Creates Play mode toolbar & menu
	void CreateStatusBar() const;	   // Create the status bar

	void SetRecordingState(bool);			// Changes toggle sound icon
	void SetPlayActionState(bool);			// Changes start recording icon

	Input *CreateInput() const;	 // Creates a pointer to the Input object
	void ClearStatusBar(); // Clears the status bar
	void ClearDrawArea() const;	 // Clears the drawing area

	// Figures drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false);					   // Draw a rectangle
	void DrawSquare(Point P1, int DefaultSquareSize, GfxInfo SquareGfxInfo, bool selected = false);	   // Draw a square
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected = false);   // Draw a triangle
	void DrawHexagon(Point P1, int DefaultHexagonSize, GfxInfo HexagonGfxInfo, bool selected = false); // Draw a hexagon
	void DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected = false);				   // Draw a circle

	void PrintMessage(string msg, bool update = true); // Print a message on status bar

	color GetCurrentDrawColor() const; // Get current drawing color
	color GetCurrentFillColor() const; // Get current filling color
	int GetCurrentPenWidth() const;	   // Get current pen width
	void UpdateBuffer();

	void UpdateStatusBar();
	void UpdateToolBar();

	~Output();
};

#endif