//
// MeasureBrush.cpp
//
// The implementation of Measure Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include <math.h>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "MeasureBrush.h"

extern float frand();
#define PI 3.14159265

MeasureBrush::MeasureBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void MeasureBrush::BrushBegin( const Point source, const Point target )
{
	glPointSize( (float)20 );

	start = target;
	BrushMove( source, target );
}

void MeasureBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();

	if ( pDoc == NULL ) {
		printf( "MeasureBrush::BrushMove  document is NULL\n" );
		return;
	}

	glBegin( GL_LINES );
        GLubyte color[4] = { 255, 0, 0, 255 };
		glColor4ubv( color );

		glVertex2d( start.x, start.y );
		glVertex2d( target.x, target.y );

	glEnd();
}

void MeasureBrush::BrushEnd( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (pDoc->m_nCurrentStrokeDirection == SLIDER_OR_RIGHT_MOUSE && (pDoc->m_pCurrentBrush == ImpBrush::c_pBrushes[BRUSH_LINES] || pDoc->m_pCurrentBrush == ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]))
	{
		dlg->setSize( (int) sqrt( (target.x - start.x)*(target.x - start.x) + (target.y - start.y)*(target.y - start.y) ) );
		dlg->setAngle( (360 + (int) (atan2(target.y - start.y, target.x - start.x)*180/PI))%360 );
	}
}
