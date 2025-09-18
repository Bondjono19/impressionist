//
// MeasureBrush.h
//
// The header file for Measure Brush. 
//

#ifndef MEASUREBRUSH_H
#define MEASUREBRUSH_H

#include "ImpBrush.h"

class MeasureBrush : public ImpBrush
{
public:
	MeasureBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
private:
	Point start;
};

#endif