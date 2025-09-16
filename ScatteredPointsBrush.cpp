//
// ScatteredPointsBrush.cpp
//
// The implementation of ScatteredPoints Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointsBrush.h"

extern float frand();
extern int irand(int max);

ScatteredPointsBrush::ScatteredPointsBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredPointsBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	size = pDoc->getSize();



	glPointSize( 1.0f );

	BrushMove( source, target );
}

void ScatteredPointsBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredPointsBrush::BrushMove  document is NULL\n" );
		return;
	}

	glBegin( GL_POINTS );
        for (int i = 0; i < size; i++) {
            Point offset = Point(irand(size)-size/2, irand(size)-size/2);
		    SetColor( offset + source );
            glVertex2d(target.x + offset.x, target.y + offset.y);
        }
		//glVertex2d( target.x, target.y );
	glEnd();
}

void ScatteredPointsBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

