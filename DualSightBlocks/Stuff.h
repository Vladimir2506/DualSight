/* 
	Stuff.h
	Describe a stuff in a Coordinate System
*/
#ifndef _STUFF_H
#define _STUFF_H

#include "Coord.h"
#include <vector>

class CStick
{
private:
	Coord<int> cCentre;
	bool IsMoveValid(int dx, int dy)
	{
		return ((cCentre + Coord<int>(1 + dx, dy)).isInSquare(mLimit.nXMax, mLimit.nYMax, mLimit.nXMin, mLimit.nYMin)
			&& (cCentre + Coord<int>(-1 + dx, dy)).isInSquare(mLimit.nXMax, mLimit.nYMax, mLimit.nXMin, mLimit.nYMin)
			&& (cCentre + Coord<int>(dx,1 + dy)).isInSquare(mLimit.nXMax, mLimit.nYMax, mLimit.nXMin, mLimit.nYMin)
			&& (cCentre + Coord<int>(dx,-1 + dy)).isInSquare(mLimit.nXMax, mLimit.nYMax, mLimit.nXMin, mLimit.nYMin));
	}
public:
	Limits mLimit;
	CStick(int xInit, int yInit, const Limits & lt) : mLimit(lt)
	{
		cCentre.x = xInit;
		cCentre.y = yInit;
	}
	void Move(int dx, int dy)
	{
		if (IsMoveValid(dx, dy))
		{
			cCentre += Coord<int>(dx, dy);
		}
	}
	void Show(bool * Map)
	{
		for (int i = mLimit.nXMin; i < mLimit.nXMax; ++i)
		{
			for (int j = mLimit.nYMin; j < mLimit.nYMax; ++j)
			{
				Coord<int> CurPoint(i, j);
				if (CurPoint == cCentre
					|| CurPoint == cCentre + Coord<int>(1, 0)
					|| CurPoint == cCentre + Coord<int>(-1, 0))
				{
					*(Map + j * mLimit.nXMax + i) = true;
				}
				else
				{
					*(Map + j * mLimit.nXMax + i) = false;
				}
			}
		}
	}
};
class CCross
{
private:
	Coord<int> cCentre;
	bool IsMoveValid(int dx, int dy)
	{
		return ((cCentre + Coord<int>(1 + dx, 1 + dy)).isInSquare(mLimit.nXMax, mLimit.nYMax, mLimit.nXMin, mLimit.nYMin)
			&& (cCentre + Coord<int>(-1 + dx, -1 + dy)).isInSquare(mLimit.nXMax, mLimit.nYMax, mLimit.nXMin, mLimit.nYMin));
	}
public:
	Limits mLimit;
	CCross(int xInit, int yInit, const Limits & lt) : mLimit(lt)
	{
		cCentre.x = xInit;
		cCentre.y = yInit;
	}
	void Move(int dx, int dy)
	{
		if (IsMoveValid(dx, dy))
		{
			cCentre += Coord<int>(dx, dy);
		}
	}
	void Show(bool * Map)
	{
		for (int i = mLimit.nXMin; i < mLimit.nXMax; ++i)
		{
			for (int j = mLimit.nYMin; j < mLimit.nYMax; ++j)
			{
				Coord<int> CurPoint(i, j);
				if (CurPoint == cCentre
					|| CurPoint == cCentre + Coord<int>(0, 1)
					|| CurPoint == cCentre + Coord<int>(0, -1)
					|| CurPoint == cCentre + Coord<int>(1, 0)
					|| CurPoint == cCentre + Coord<int>(-1, 0))
				{
					*(Map + j * mLimit.nXMax + i) = true;
				}
				else
				{
					*(Map + j * mLimit.nXMax + i) = false;
				}
			}
		}
	}
};

#endif
