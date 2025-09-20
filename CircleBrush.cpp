// CircleBrush.cpp

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"
#include "math.h"
#include "vector"

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);

	BrushMove(source, target);
}

std::vector<float> calculateCirclePoints(int radius, int segments, const Point target) {
	std::vector<float> circleVertices;
	circleVertices.reserve(segments * 2);
	for (int i = 0;i < segments;i++) {
		float ii = (2 * M_PI) * float(float(i) / segments);
		float x = target.x + cosf(ii) * radius;
		float y = target.y + sinf(ii) * radius;
		circleVertices.push_back(x);
		circleVertices.push_back(y);
	}
	return circleVertices;
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}
	int size = pDoc->getSize();
	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);
	std::vector<float> vertices = calculateCirclePoints(size/2, 100, target);
	for (int i = 0; i < vertices.size(); i=i+2) {
		glVertex2d(vertices[i], vertices[i + 1]);
	}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
