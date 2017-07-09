/*
	MainLogic.h
	Russian Blocks Game Procedure
*/
#ifndef _MAINLOGIC_H
#define _MAINLOGIC_H

#include "MyRocker.h"
#include "Monitor.h"
#include "Object.h"

typedef uint8_t TPIN;

class CMainLogic
{
private:
	CRocker Rocker;	//Rocker for input
	CMonitor Monitor;	//LED for output
	bool **MapData;	//Logistic Map
	Object* pBlock;
	void ClearMap()
	{
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 16; ++j)
			{
				MapData[i][j] = false;
			}
		}
	}
	void GameStart()
	{
		ClearMap();
	}
	bool IsValid(Object next)
	{
		bool bResult = true;
		Coord<int> pointCentre = next.get_center();
		for (auto &p : next)
		{
			if (p.x + pointCentre.x >= 8 || p.x + pointCentre.x < 0)
			{
				bResult = false;
				break;
			}
			else if (p.y + pointCentre.y < 0)
			{
				bResult = false;
				break;
			}
			if (MapData[p.x + pointCentre.x][p.y + pointCentre.y])
			{
				bResult = false;
				break;
			}
		}
		return bResult;
	}
	void RoundStart()
	{
		Coord<int> pointBorn(5, 14);
		CCreator CreateBlock;
		pBlock = new Object(CreateBlock(pointBorn));
	}
	void TestMap()
	{
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Serial.print((unsigned)MapData[7 - j][15 - i]);
				Serial.print(" ");
			}
			Serial.println();
		}
		Serial.println();
	}
	bool Round(int *con)
	{
		Coord<int> pointCentre = pBlock->get_center();
		for (auto &p : *pBlock)
		{
			if (p.y + pointCentre.y >= 0 && p.y + pointCentre.y < 16 && p.x + pointCentre.x < 8 && p.x + pointCentre.x >= 0)
			{
				MapData[p.x + pointCentre.x][p.y + pointCentre.y] = false;
			}
		}
		Object nextStep = *pBlock, origState = *pBlock;
		int nDown = 1;
		switch (con[0])
		{
		case _NEUT:
			break;
		case _POSI:
			nextStep.moveLeft();
			break;
		case _NEGA:
			nextStep.moveRight();
			break;
		default:
			break;
		}
		switch (con[1])
		{
		case _NEUT:
			break;
		case _POSI:
			nextStep.rotateRight();
			break;
		case _NEGA:
			nextStep.rotateLeft();
			break;
		default:
			break;
		}
		switch (con[2])
		{
		case _UP:
			break;
		case _DOWN:
			++nDown;
			break;
		default:
			break;
		}
		if (IsValid(nextStep))
		{
			*pBlock = nextStep;
		}
		for (int i = 0; i < nDown; ++i)
		{
			nextStep.moveDown();
			if (IsValid(nextStep))
			{
				*pBlock = nextStep;
			}
		}
		origState.moveDown();
		return !IsValid(origState);
	}
	bool RoundEnd()
	{
		delete pBlock;
		pBlock = NULL;
		bool bGameOver = false;
		bool bFlag = false;
		for (int y = 0; y < 16; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				if (!MapData[x][y])
				{
					break;
				}
				else if(MapData[7][y])
				{
					bFlag = true;
				}
			}
			if (bFlag)
			{
				for (int k = y; k < 16; ++k)
				{
					for (int x = 0; x < 8; ++x)
					{
						if (k == 15)
						{
							MapData[x][k] = false;
						}
						else
						{
							MapData[x][k] = MapData[x][k + 1];
						}
					}
				}
			}
		}
		for (int x = 0; x < 8; ++x)
		{
			if (MapData[x][15])
			{
				return true;
			}
		}
		return false;
	}
public:
	int nIter;
	void Show()
	{
		bool ShowMat[16][8];
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				ShowMat[i][j] = MapData[7-j][15-i];
			}
		}
		Monitor.Paint((bool*)ShowMat);
	}
	//Constructor  
	CMainLogic(TPIN pinX, TPIN pinY, TPIN pinSW, TPIN pinIO, TPIN pinCS, TPIN pinCLK, int nDevices)
		:Rocker(pinX, pinY, pinSW), Monitor(pinIO, pinCS, pinCLK, nDevices)
	{
		MapData = new bool*[8];
		for (int i = 0; i < 8; ++i)
		{
			MapData[i] = new bool[16];
		}
		nIter = 0;;
		pBlock = NULL;
	}
	//Destructor
	~CMainLogic()
	{
		for (int i = 0; i < 8; ++i)
		{
			delete[] MapData[i];
		}
		delete[] MapData;
		Serial.end();
	}
	//Initialization in setup()
	void Init()
	{
		Rocker.Init();
		Monitor.InitScreen(1);
		std::srand(std::time(NULL));
		Serial.begin(9600);
	}
	//GameProcedure in loop()
	void Run()
	{
		int Controller[3];
		bool bGameOver = false;
		if (nIter == 0)
		{
			GameStart();
		}
		if (pBlock == NULL)
		{
			RoundStart();
		}
		Coord<int> pointCentre = pBlock->get_center();
		for (auto &p : *pBlock)
		{
			if (p.y + pointCentre.y >= 0 && p.y + pointCentre.y < 16 && p.x + pointCentre.x < 8 && p.x + pointCentre.x >= 0)
			{
				MapData[p.x + pointCentre.x][p.y + pointCentre.y] = true;
			}
		}
		Rocker.UpdateData();
		Rocker.GetStatusByDir(Controller, 3);
		bool bRoundOver = Round(Controller);
		pointCentre = pBlock->get_center();
		for (auto &p : *pBlock)
		{
			if (p.y + pointCentre.y >= 0 && p.y + pointCentre.y < 16 && p.x + pointCentre.x < 8 && p.x + pointCentre.x >= 0)
			{
				MapData[p.x + pointCentre.x][p.y + pointCentre.y] = true;
			}
		}
		Show();
		if (bRoundOver)
		{
			bGameOver = RoundEnd();
		}
		if (bGameOver)
		{
			nIter = 0;
			Monitor.ClearAll();
		}
		else
		{
			++nIter;
		}
		delay(300);
	}
};

#endif 
