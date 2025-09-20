// ScatteredCircleBrush.cpp

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "math.h"
#include <cmath>
#include "vector"
#include "ScatteredCircleBrush.h"

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);

	BrushMove(source, target);
}

std::vector<float> calculateScatteredCirclePoints(int radius, int segments, const Point target) {
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

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	for (int i = 0; i < 4; i++) {
		int offsetX = static_cast<int>(std::round(((frand() - 0.5) * size*2)));
		int offsetY = static_cast<int>(std::round(((frand() - 0.5) * size*2)));
		Point pSource(source.x + offsetX, source.y + offsetY);
		Point pTarget(target.x + offsetX, target.y + offsetY);
		glBegin(GL_TRIANGLE_FAN);
		SetColor(pSource);
		std::vector<float> vertices = calculateScatteredCirclePoints(size/2, 100, pTarget);
		for (int i = 0; i < vertices.size(); i = i + 2) {
			glVertex2d(vertices[i], vertices[i + 1]);
		}
		glEnd();
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
