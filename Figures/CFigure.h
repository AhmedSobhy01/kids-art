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
	CFigure(GfxInfo);

	void SetSelected(bool);	 // select/unselect the figure
	bool IsSelected() const; // check whether fig is selected

	virtual void Draw(Output *) = 0; // Draw the figure

	color GetDrawColor() const; // returns the figure's drawing color
	color GetFillColor() const; // returns the figure's filling color
	int GetBorderWidth() const; // returns the figure's Border Width

	void ChangeDrawColor(color); // changes the figure's drawing color
	void ChangeFillColor(color); // changes the figure's filling color
	void ChangeBorderWidth(int); // changes the figure's Border Width

	///				Play Mode Functions			///
	bool IsHidden(); // Checks if a shape is hidden
	void Hide();	 // Hides the shape
	void Unhide();	 // Unhides the shape
	string Type();	 // Returns the type of a shape
	bool IsFilled();
	bool operator==(CFigure &);
	static void ResetID();

	virtual bool IsPointInside(Point) = 0;
	virtual Point GetCenter() const = 0;
	virtual void SetCenter(Point) = 0;
	virtual void Save(ofstream &) = 0; // Save the figure parameters to the file
	virtual void Load(ifstream &) = 0; // Load the figure parameters to the file
	virtual bool GetCorner(Point &, int &) = 0;
	virtual void SetCorner(Point, int) = 0;
	/// The following functions should be supported by the figure class
	/// It should be overridden by each inherited figure

	/// Decide the parameters that you should pass to each function

	virtual void PrintInfo(Output *) = 0; // print all figure info on the status bar

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