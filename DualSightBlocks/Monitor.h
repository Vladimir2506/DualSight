/*
	Monitor.h
	Control of LED Matrices and Coordinate System
*/
#ifndef _MONITOR_H
#define _MONITOR_H
#include "Coord.h"
#include <LedControl.h>

class CMonitor
{
private:
	LedControl lcCore;
	void UpdateData(byte * Matrix)
	{
		for (int i = mLimit.nYMin; i < mLimit.nYMax; ++i)
		{
			int nDev = i / mLimit.nXMax;
			int nRow = i % mLimit.nXMax;
			lcCore.setRow(nDev, nRow, Matrix[i]);
		}
	}
public:
	Limits mLimit;
	CMonitor(int pinIO, int pinCS, int pinCLK, int nDev) :lcCore(pinIO, pinCLK, pinCS, nDev)
	{
		mLimit.nXMax = 8;
		mLimit.nXMin = 0;
		mLimit.nYMin = 0;
		mLimit.nYMax = 8 * nDev;
	}
	void InitScreen(int nIntensity)
	{
		for (int i = 0; i < lcCore.getDeviceCount(); ++i)
		{
			lcCore.shutdown(i, false);
		}
		for (int i = 0; i < lcCore.getDeviceCount(); ++i)
		{
			lcCore.setIntensity(i, nIntensity);
		}
		for (int i = 0; i < lcCore.getDeviceCount(); ++i)
		{
			lcCore.clearDisplay(i);
		}
	}
	void Paint(bool* Map)
	{
		byte * Mask = new byte[mLimit.nYMax];
		memset(Mask, 0, mLimit.nYMax * sizeof(byte));
		for (int i = mLimit.nYMin; i < mLimit.nYMax; ++i)
		{
			for (int j = mLimit.nXMin; j < mLimit.nXMax; ++j)
			{
				Mask[i] |= (*(Map + i * mLimit.nXMax + j) << (mLimit.nXMax - 1 - j));
			}
		}
		UpdateData(Mask);
		delete[] Mask;
	}
	void ClearAll()
	{
		for (int i = 0; i < lcCore.getDeviceCount(); ++i)
		{
			lcCore.clearDisplay(i);
		}
	}
};

#endif 
