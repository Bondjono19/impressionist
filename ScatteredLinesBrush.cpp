//
// ScatteredLinesBrush.cpp
//
// The implementation of ScatteredLines Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include <math.h>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLinesbrush.h"

#define PI 3.14159265

extern float frand();
extern int irand(int max);

ScatteredLinesBrush::ScatteredLinesBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLinesBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	line_height = pDoc->getSize();
	line_width = pDoc->getLineWidth();
	angle = pDoc->getLineAngle();

	BrushMove(source, target);
}

void ScatteredLinesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredLinesBrush::BrushMove  document is NULL\n");
		return;
	}

	if (pDoc->m_nCurrentStrokeDirection == BRUSH_STROKE_DIRECTION)
	{
		if (prev.x != -1 && prev.y != -1 && !(prev.x == target.x && prev.y == target.y))
		{
			angle = 360 + (int)(atan2(target.y - prev.y, target.x - prev.x) * 180 / PI) % 360;

		}
	}	

	PrecisionPoint vertices[4] = {
		PrecisionPoint(-line_height/2.0, -line_width/2.0),
		PrecisionPoint( line_height/2.0, -line_width/2.0),
		PrecisionPoint( line_height/2.0,  line_width/2.0),
		PrecisionPoint(-line_height/2.0,  line_width/2.0)
	};

    for (int i = 0; i < 4; i++) {
        int rand_area = line_height;
        Point offset = Point(irand(rand_area)-rand_area/2, irand(rand_area)-rand_area/2);

	    glBegin(GL_POLYGON);

            SetColor( offset + source );
			if (pDoc->m_nCurrentStrokeDirection == GRADIENT)
			{
				Point g = GetGradient(offset + target);
				if (!(g.x == 0 && g.y == 0)) {
					angle = (90 + 360 + (int)(atan2(g.y, g.x) * 180 / PI)) % 360; //perpendicular to gradient
				}
			}

            for (int j = 0; j < 4; j++) {
                PrecisionPoint rotated = PrecisionPoint::rotate(vertices[j], angle * PI / 180.0);
                glVertex2d(target.x + rotated.x + offset.x, target.y + rotated.y + offset.y);
            }

	    glEnd();
    }
}

void ScatteredLinesBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}



