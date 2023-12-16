#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>

//Base class for all figures

class CFigure
{
protected:
	static int last_ID;
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	ShapeType type;
	bool Hidden;
	
	/// Add more parameters if needed.

public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure

	color GetDrawClr() const;	//returns the figure's drawing color
	color GetFillClr() const;	//returns the figure's filling color

	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color


	///				Play Mode Functions			///
	bool isHidden();				// Checks if a shape is hidden
	void Hide();					// Hides the shape
	void UnHide();					// Unhides the shape
	ShapeType Type();				// Returns the type of a shape
	bool isFilled();


	virtual bool CheckSelected(int x, int y) = 0;
	virtual Point GetCenter() const = 0;
	virtual void SetCenter(Point) = 0;
	virtual bool Validate(Point) = 0;
	virtual void Save(ofstream& OutFile) = 0; //Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	



	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif