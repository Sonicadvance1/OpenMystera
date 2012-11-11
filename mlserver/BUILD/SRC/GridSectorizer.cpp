#include "RakAssert.h"
#include "GridSectorizer.h"
#include <stdlib.h>
#include <math.h>

GridSectorizer::GridSectorizer()
{
	grid=0;
}
GridSectorizer::~GridSectorizer()
{
	if (grid)
		delete [] grid;
}
void GridSectorizer::Init(const float _maxCellWidth, const float _maxCellHeight, const float minX, const float minY, const float maxX, const float maxY)
{
	RakAssert(_maxCellWidth > 0.0f && _maxCellHeight > 0.0f);
	if (grid)
		delete [] grid;

	cellOriginX=minX;
	cellOriginY=minY;
	gridWidth=maxX-minX;
	gridHeight=maxY-minY;
	gridCellWidthCount=(int) ceil(gridWidth/_maxCellWidth);
	gridCellHeightCount=(int) ceil(gridHeight/_maxCellHeight);
	// Make the cells slightly smaller, so we allocate an extra unneeded cell if on the edge.  This way we don't go outside the array on rounding errors.
	cellWidth=gridWidth/gridCellWidthCount;
	cellHeight=gridHeight/gridCellHeightCount;
	invCellWidth = 1.0f / cellWidth;
	invCellHeight = 1.0f / cellHeight;

#ifdef _USE_ORDERED_LIST
	grid = new DataStructures::OrderedList<void*, void*>[gridCellWidthCount*gridCellHeightCount];
	DataStructures::OrderedList<void*,void*>::IMPLEMENT_DEFAULT_COMPARISON();
#else
	grid = new DataStructures::List<void*>[gridCellWidthCount*gridCellHeightCount];
#endif
}
void GridSectorizer::AddEntry(void *entry, const float minX, const float minY, const float maxX, const float maxY)
{
	RakAssert(cellWidth>0.0f);
	RakAssert(minX < maxX && minY < maxY);

	int xStart, yStart, xEnd, yEnd, xCur, yCur;
	xStart=WorldToCellXOffsetAndClamped(minX);
	yStart=WorldToCellYOffsetAndClamped(minY);
	xEnd=WorldToCellXOffsetAndClamped(maxX);
	yEnd=WorldToCellYOffsetAndClamped(maxY);

	for (xCur=xStart; xCur <= xEnd; ++xCur)
	{
		for (yCur=yStart; yCur <= yEnd; ++yCur)
		{
#ifdef _USE_ORDERED_LIST
			grid[yCur*gridCellWidthCount+xCur].Insert(entry,entry, true);
#else
			grid[yCur*gridCellWidthCount+xCur].Insert(entry);
#endif
		}
	}
}
#ifdef _USE_ORDERED_LIST
void GridSectorizer::RemoveEntry(void *entry, const float minX, const float minY, const float maxX, const float maxY)
{
	RakAssert(cellWidth>0.0f);
	RakAssert(minX <= maxX && minY <= maxY);

	int xStart, yStart, xEnd, yEnd, xCur, yCur;
	xStart=WorldToCellXOffsetAndClamped(minX);
	yStart=WorldToCellYOffsetAndClamped(minY);
	xEnd=WorldToCellXOffsetAndClamped(maxX);
	yEnd=WorldToCellYOffsetAndClamped(maxY);

	for (xCur=xStart; xCur <= xEnd; ++xCur)
	{
		for (yCur=yStart; yCur <= yEnd; ++yCur)
		{
			grid[yCur*gridCellWidthCount+xCur].RemoveIfExists(entry);
		}
	}
}
void GridSectorizer::MoveEntry(void *entry, const float sourceMinX, const float sourceMinY, const float sourceMaxX, const float sourceMaxY,
			   const float destMinX, const float destMinY, const float destMaxX, const float destMaxY)
{
	RakAssert(cellWidth>0.0f);
	RakAssert(sourceMinX < sourceMaxX && sourceMinY < sourceMaxY);
	RakAssert(destMinX < destMaxX && destMinY < destMaxY);

	if (PositionCrossesCells(sourceMinX, sourceMinY, destMinX, destMinY)==false &&
		PositionCrossesCells(destMinX, destMinY, destMinX, destMinY)==false)
		return;

	int xStartSource, yStartSource, xEndSource, yEndSource;
	int xStartDest, yStartDest, xEndDest, yEndDest;
	int xCur, yCur;
	xStartSource=WorldToCellXOffsetAndClamped(sourceMinX);
	yStartSource=WorldToCellYOffsetAndClamped(sourceMinY);
	xEndSource=WorldToCellXOffsetAndClamped(sourceMaxX);
	yEndSource=WorldToCellYOffsetAndClamped(sourceMaxY);

	xStartDest=WorldToCellXOffsetAndClamped(destMinX);
	yStartDest=WorldToCellYOffsetAndClamped(destMinY);
	xEndDest=WorldToCellXOffsetAndClamped(destMaxX);
	yEndDest=WorldToCellYOffsetAndClamped(destMaxY);

	// Remove source that is not in dest
	for (xCur=xStartSource; xCur <= xEndSource; ++xCur)
	{
		for (yCur=yStartSource; yCur <= yEndSource; ++yCur)
		{
			if (xCur < xStartDest || xCur > xEndDest ||
				yCur < yStartDest || yCur > yEndDest)
			{
				grid[yCur*gridCellWidthCount+xCur].RemoveIfExists(entry);
			}
		}
	}

	// Add dest that is not in source
	for (xCur=xStartDest; xCur <= xEndDest; ++xCur)
	{
		for (yCur=yStartDest; yCur <= yEndDest; ++yCur)
		{
			if (xCur < xStartSource || xCur > xEndSource ||
				yCur < yStartSource || yCur > yEndSource)
			{
				grid[yCur*gridCellWidthCount+xCur].Insert(entry,entry, true);
			}
		}
	}
}
#endif
void GridSectorizer::GetEntries(DataStructures::List<void*>& intersectionList, const float minX, const float minY, const float maxX, const float maxY)
{
#ifdef _USE_ORDERED_LIST
	DataStructures::OrderedList<void*, void*>* cell;
#else
	DataStructures::List<void*>* cell;
#endif
	int xStart, yStart, xEnd, yEnd, xCur, yCur;
	unsigned index;
	xStart=WorldToCellXOffsetAndClamped(minX);
	yStart=WorldToCellYOffsetAndClamped(minY);
	xEnd=WorldToCellXOffsetAndClamped(maxX);
	yEnd=WorldToCellYOffsetAndClamped(maxY);

	intersectionList.Clear(true);
	for (xCur=xStart; xCur <= xEnd; ++xCur)
	{
		for (yCur=yStart; yCur <= yEnd; ++yCur)
		{
			cell = grid+yCur*gridCellWidthCount+xCur;
			for (index=0; index < cell->Size(); ++index)
				intersectionList.Insert(cell->operator [](index));
		}
	}
}
bool GridSectorizer::PositionCrossesCells(const float originX, const float originY, const float destinationX, const float destinationY) const
{
	return originX/cellWidth!=destinationX/cellWidth || originY/cellHeight!=destinationY/cellHeight;
}
int GridSectorizer::WorldToCellX(const float input) const
{
	return (int)((input-cellOriginX)*invCellWidth);
}
int GridSectorizer::WorldToCellY(const float input) const
{
	return (int)((input-cellOriginY)*invCellHeight);
}
int GridSectorizer::WorldToCellXOffsetAndClamped(const float input) const
{
	int cell=WorldToCellX(input);
	cell = cell > 0 ? cell : 0; // __max(cell,0);
	cell = gridCellWidthCount-1 < cell ? gridCellWidthCount-1 : cell; // __min(gridCellWidthCount-1, cell);
	return cell;
}
int GridSectorizer::WorldToCellYOffsetAndClamped(const float input) const
{
	int cell=WorldToCellY(input);
	cell = cell > 0 ? cell : 0; // __max(cell,0);
	cell = gridCellHeightCount-1 < cell ? gridCellHeightCount-1 : cell; // __min(gridCellHeightCount-1, cell);
	return cell;
}
void GridSectorizer::Clear(void)
{
	int cur;
	int count = gridCellWidthCount*gridCellHeightCount;
	for (cur=0; cur<count;cur++)
		grid[cur].Clear(true);
}
