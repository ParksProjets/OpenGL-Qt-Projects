#include "rendering/cell.h"

Cell::Cell(double leftX, double bottomY, double sideLength,
		int row, int column) :
	leftX(leftX),
	bottomY(bottomY),
	sideLength(sideLength),
	isVisited(false),
	row(row),
	column(column),
	bounds(leftX, leftX + sideLength, bottomY, bottomY + sideLength)
{
}

void Cell::MarkVisited()
{
	isVisited = true;
}

bool Cell::IsVisited()
{
	return isVisited;
}

int Cell::GetRow()
{
	return row;
}

int Cell::GetColumn()
{
	return column;
}

double Cell::GetLeftX()
{
	return leftX;
}

double Cell::GetBottomY()
{
	return bottomY;
}

double Cell::GetSideLength()
{
	return sideLength;
}

Point2D Cell::GetBottomLeft()
{
	return bounds.GetBottomLeft();
}

Point2D Cell::GetBottomRight()
{
	return bounds.GetBottomRight();
}

Point2D Cell::GetTopLeft()
{
	return bounds.GetTopLeft();
}

Point2D Cell::GetTopRight()
{
	return bounds.GetTopRight();
}

bool Cell::HasIntersectingEdge(Blend *blend)
{
	int insideCorners = 0;

	int numCorners = 4;
	Point2D points[] = {
			GetBottomLeft(),
			GetBottomRight(),
			GetTopLeft(),
			GetTopRight()
	};

	for (int i = 0; i < numCorners; i++) {
		if (blend->ContainsPoint(points[i])) {
			insideCorners++;
		}
	}

	return insideCorners != 0 && insideCorners != 4;
}

std::list<Edge> Cell::GetIntersectingEdges(Blend *blend)
{
	int numCandidates = 4;
	Edge candidates[] = {
		Edge(GetBottomLeft(), GetBottomRight()),
		Edge(GetBottomLeft(), GetTopLeft()),
		Edge(GetTopLeft(), GetTopRight()),
		Edge(GetBottomRight(), GetTopRight())
	};

	std::list<Edge> edges;
	for (int i = 0; i < numCandidates; i++) {
		Edge candidate = candidates[i];

		if (candidate.HasIntersection(blend)) {
			edges.push_back(candidate);
		}
	}

	return edges;
}

