#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\DEFS.h"
#include "..\GUI\Output.h"
#include <fstream>
#include <string>

// Base class for all figures

class CFigure
{
protected:
	static int LastID;	  // Last ID given to a figure
	int ReferenceCount;	  // Number of references to the figure
	int ID;				  // Each figure has an ID
	bool Selected;		  // true if the figure is selected.
	GfxInfo FigGfxInfo;	  // Figure graphis info
	std::string TypeName; // Figure type name
	bool Hidden;		  // True if the figure is hidden in play mode

public:
	CFigure();
	CFigure(GfxInfo);

	void SetSelected(bool);	 // Set selected status of the figure
	bool IsSelected() const; // Check if the figure is selected

	virtual void Draw(Output *) = 0; // Draw the figure (different drawing techniques for each figure)

	color GetDrawColor() const; // returns the figure's drawing color
	color GetFillColor() const; // returns the figure's filling color
	int GetBorderWidth() const; // returns the figure's border width

	void ChangeDrawColor(color); // changes the figure's drawing color
	void ChangeFillColor(color); // changes the figure's filling color
	void ChangeBorderWidth(int); // changes the figure's Border Width

	///				Play Mode Functions			///
	bool IsHidden();			// Checks if a shape is hidden
	void Hide();				// Hides the shape
	void Unhide();				// Unhides the shape
	std::string Type() const;	// Returns the type of a shape
	bool IsFilled() const;		// Checks if a shape is filled
	bool operator==(CFigure &); // Checks if two shapes are equal
	static void ResetID();		// Resets the ID counter to 0

	virtual bool IsPointInside(Point) = 0;		// Check's if the point is inside the shape or not (ssed in selecting)
	virtual Point GetCenter() const = 0;		// Get the shape's current center (used in moving)
	virtual void SetCenter(Point) = 0;			// Set the Shape's new center (used in moving)
	virtual void Save(ofstream &OutFile) = 0;	// Save the figure parameters to the file (used in saving)
	virtual void Load(ifstream &Infile) = 0;	// Load the figure parameters to the file (used in loading)
	virtual bool GetCorner(Point &, int &) = 0; // Get the shape corner and its index given the point
	virtual void SetCorner(Point, int) = 0;		// Sets the shape Corner given the point and its index (used in resizing)
	virtual void PrintInfo(Output *pOut) = 0;	// Print all figure info on the status bar (used in status bar)

	// Reference Counting Functions
	void IncrementReference() // Increment the reference count by 1
	{
		ReferenceCount++;
	}

	void DecrementReference() // Decrement the reference count by 1
	{
		if (ReferenceCount > 0)
			ReferenceCount--;
	}

	bool CanBeDeleted() const // Returns whether object can be deleted or not
	{
		return ReferenceCount == 0;
	}
};

#endif