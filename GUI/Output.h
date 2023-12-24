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

	Input *CreateInput() const;	 // Creates a pointer to the Input object
	void ClearStatusBar(); // Clears the status bar
	void ClearDrawArea() const;	 // Clears the drawing area

	// Figures drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;				   // Draw a rectangle
	void DrawSquare(Point P1,int DefaultSquareSize ,GfxInfo SquareGfxInfo, bool selected = false) const;						   // Draw a square
	void DrawTriangle(Point P1 ,Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected = false) const; // Draw a triangle
	void DrawHexagon(Point P1, int DefaultHexagonSize, GfxInfo HexagonGfxInfo, bool selected = false) const;					   // Draw a hexagon
	void DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected = false) const;			   // Draw a circle

	void PrintMessage(string msg); // Print a message on status bar

	color getCrntDrawColor() const; // Get current drawing color
	color getCrntFillColor() const; // Get current filling color
	int getCurrentPenWidth() const;	   // Get current pen width
	void updateBuffer();

	void updateStatusBar();
	void updateToolBar();

	~Output();
};

#endif