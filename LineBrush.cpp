//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Linebrush.h"

#define PI 3.14159265

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	line_height = pDoc->getSize();
	line_width = pDoc->getLineWidth();
	angle = pDoc->getLineAngle();

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);

	SetColor( source );

	PrecisionPoint vertices[4] = {
		PrecisionPoint(-line_height/2.0, -line_width/2.0),
		PrecisionPoint( line_height/2.0, -line_width/2.0),
		PrecisionPoint( line_height/2.0,  line_width/2.0),
		PrecisionPoint(-line_height/2.0,  line_width/2.0)
	};

	for (int i = 0; i < 4; i++) {
		PrecisionPoint rotated = PrecisionPoint::rotate(vertices[i], angle * PI / 180.0);
		glVertex2d(target.x + rotated.x, target.y + rotated.y);
	}

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


