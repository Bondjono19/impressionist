#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <math.h>
#include <stdlib.h>

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	NUM_BRUSH_TYPE // Make sure this stays at the end!
};

enum
{
	SLIDER_OR_RIGHT_MOUSE = 0,
	GRADIENT,
	BRUSH_STROKE_DIRECTION,
	NUM_BRUSH_STOKE_TYPE // Make sure this stays at the end!
};


class ImpressionistDoc; // Pre-declaring class

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;

	double distance(const Point& other) {
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}

	Point operator+(const Point& other) {
        return Point(x + other.x, y + other.y);
    }
};

class PrecisionPoint 
{
public:
	PrecisionPoint() {};
	PrecisionPoint(double xx, double yy) { x = xx; y = yy; };

	double x, y;

	static PrecisionPoint rotate(PrecisionPoint p, double angle);
};

class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target ) = 0;
	virtual void BrushMove( const Point source, const Point target ) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	Point prev = Point(-1, -1);

	int ImpBrush::GetLuminance(const GLubyte color[3]);
	int ImpBrush::convolve(const Point source, const int kernel[3][3]);
	Point ImpBrush::GetGradient(Point target);

	// according to the source image and the position, determine the draw color
	void SetColor( const Point source );

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;
};

#endif