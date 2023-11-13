#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output // The application manager should have a pointer to this class
{
private:
	window *pWind;		   // Pointer to the Graphics Window
	window *colorMenuWind; // Pointer to the Color Menu Window
public:
	Output();

	window *CreateWind(int, int, int, int) const; // creates the application window

	void CreateColorMenuWind(int);	  // creates color menu window
	void DrawColorMenuItems() const;  // draws color images to color menu window
	void OpenColorMenuWind(int);	  // creates the color menu window and draws color images
	void CloseColorMenuWind();		  // closes the color menu window
	window *GetColorMenuWind() const; // returns pointer to the color menu window or nullptr if it doesn't exist

	void CreateDrawToolBar() const; // creates Draw mode toolbar & menu
	void CreatePlayToolBar() const; // creates Play mode toolbar & menu
	void CreateStatusBar() const;	// create the status bar

	Input *CreateInput() const;	 // creates a pointer to the Input object
	void ClearStatusBar() const; // Clears the status bar
	void ClearDrawArea() const;	 // Clears the drawing area

	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;				   // Draw a rectangle
	void DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected = false) const;						   // Draw a square
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected = false) const; // Draw a triangle
	void DrawHexagon(Point P1, GfxInfo HexagonGfxInfo, bool selected = false) const;					   // Draw a hexagon
	void DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected = false) const;			   // Draw a Circle

	void PrintMessage(string msg) const; // Print a message on Status bar

	color getCrntDrawColor() const; // get current drwawing color
	color getCrntFillColor() const; // get current filling color
	int getCrntPenWidth() const;	// get current pen width

	~Output();
};

#endif