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

int ImpBrush::GetLuminance(const GLubyte color[3]) {
	return (int)(0.2126 * color[0] + 0.7152 * color[1] + 0.0722 * color[2]);
}

int ImpBrush::convolve(const Point source, const int kernel[3][3]) {
	int r = 0, g = 0, b = 0;
	ImpressionistDoc* pDoc = GetDocument();
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			GLubyte* color = pDoc->GetOriginalPixel(Point(source.x + dx, source.y + dy));
			r += color[0] * kernel[dy + 1][dx + 1];
			g += color[1] * kernel[dy + 1][dx + 1];
			b += color[2] * kernel[dy + 1][dx + 1];
		}
	}
	return (int)(0.2126 * r + 0.7152 * g + 0.0722 * b);
}

Point ImpBrush::GetGradient(Point target) {
	int gx = 0, gy = 0;
	const int sobel_x[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};

	const int sobel_y[3][3] = {
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};

	gx = convolve(target, sobel_x);
	gy = convolve(target, sobel_y);

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