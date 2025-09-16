//
// ScatteredPointsBrush.h
//
// The header file for ScatteredPoints Brush. 
//

#ifndef SCATTEREDPOINTSBRUSH_H
#define SCATTEREDPOINTSBRUSH_H

#include "ImpBrush.h"
#include <Math.h>

class ScatteredPointsBrush : public ImpBrush
{
private:
    int size;

public:
	ScatteredPointsBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif

