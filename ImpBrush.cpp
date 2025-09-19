//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include <math.h>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

PrecisionPoint PrecisionPoint::rotate(PrecisionPoint p, double angle) {
	PrecisionPoint rotated;
	rotated.x = cos(angle) * p.x - sin(angle) * p.y;
	rotated.y = sin(angle) * p.x + cos(angle) * p.y;
	return rotated;
}

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

int ImpBrush::GetLuminance(const Point source) {
	ImpressionistDoc* pDoc = GetDocument();
	GLubyte* color = pDoc->GetOriginalPixel(source);
	return (int)(0.2126 * color[0] + 0.7152 * color[1] + 0.0722 * color[2]);
}

Point ImpBrush::GetGradient(Point target) {
	int gx = 0, gy = 0;
	int lum_center = GetLuminance(target);
	int lum_left = GetLuminance(Point(target.x - 1, target.y));
	int lum_right = GetLuminance(Point(target.x + 1, target.y));
	int lum_up = GetLuminance(Point(target.x, target.y - 1));
	int lum_down = GetLuminance(Point(target.x, target.y + 1));
	gx = lum_right - lum_left;
	gy = lum_down - lum_up;
	return Point(gx, gy);
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[4] = { 0, 0, 0, (GLubyte)(pDoc->getAlpha() * 255.0f) };

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
 
	glColor4ubv( color );

}