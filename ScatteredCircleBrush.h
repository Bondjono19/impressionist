//
// CircleBrush.h
//
// The header file for Circle Brush. 
//

#ifndef SCATTEREDCIRCLEBRUSH_H
#define SCATTEREDCIRCLEBRUSH_H

#include <vector>
#include "ImpBrush.h"

inline std::vector<float> calculateScatteredCirclePoints(int radius, int segments, const Point target);

class ScatteredCircleBrush : public ImpBrush
{
public:
	ScatteredCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif