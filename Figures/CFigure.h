#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>
#include <string>
using namespace std;

// Base class for all figures

class CFigure
{
protected:
	static int LastID;
	int ReferenceCount;
	int ID;				// Each figure has an ID
	bool Selected;		// true if the figure is selected.
	GfxInfo FigGfxInfo; // Figure graphis info
	string TypeName;
	bool Hidden;

	/// Add more parameters if needed.

public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);

	void SetSelected(bool s); // select/unselect the figure
	bool IsSelected() const;  // check whether fig is selected

	virtual void Draw(Output *pOut) = 0; // Draw the figure

	color GetDrawClr() const;	// returns the figure's drawing color
	color GetFillClr() const;	// returns the figure's filling color
	int GetBorderWidth() const; // returns the figure's Border Width

	void ChngDrawClr(color Dclr);	  // changes the figure's drawing color
	void ChngFillClr(color Fclr);	  // changes the figure's filling color
	void ChngBorderWidth(int BWidth); // changes the figure's Border Width

	///				Play Mode Functions			///
	bool isHidden(); // Checks if a shape is hidden
	void Hide();	 // Hides the shape
	void UnHide();	 // Unhides the shape
	string Type();	 // Returns the type of a shape
	bool IsFilled();
	bool operator==(CFigure &);
	static void ResetID();

	virtual bool IsPointInside(Point) = 0;		//Check's if the point is inside the shape
	virtual Point GetCenter() const = 0;		//Get the shape's current center
	virtual void SetCenter(Point) = 0;			//Set the Shape's new center
	virtual void Save(ofstream& OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	virtual bool GetCorner(Point&, int&) = 0;	//Get the shape sorner and its index
	virtual void SetCorner(Point, int) = 0;		//Sets the shape Corner given the point and its index
	virtual void PrintInfo(Output* pOut) = 0;	//Print all figure info on the status bar

	// Reference
	void IncrementReference()
	{
		ReferenceCount++;
	}

	void DecrementReference()
	{
		if (ReferenceCount > 0)
			ReferenceCount--;
	}

	bool CanBeDeleted() const
	{
		return ReferenceCount == 0;
	}
};

#endif