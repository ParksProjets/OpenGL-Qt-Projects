#ifndef CELL_H_
#define CELL_H_

#include <list>

#include "rendering/blending.h"
#include "rendering/edge.h"
#include "util/geometry.h"

class Cell
{
public:
	Cell(double leftX, double bottomY, double sideLength,
			int row, int column);

	void MarkVisited();
	bool IsVisited();
	int GetRow();
	int GetColumn();
	double GetLeftX();
	double GetBottomY();
	double GetSideLength();
	Point2D GetBottomLeft();
	Point2D GetBottomRight();
	Point2D GetTopLeft();
	Point2D GetTopRight();
	bool HasIntersectingEdge(Blend *blend);
	std::list<Edge> GetIntersectingEdges(Blend *blend);

private:
	double leftX;
	double bottomY;
	double sideLength;
	bool isVisited;
	int row;
	int column;
	Rectangle bounds;
};

#endif
