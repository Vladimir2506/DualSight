/*
 Name:		DualSightBlocks.ino
 Created:	2017/7/8 16:15:11
 Author:	dell1
*/


#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include <MsTimer2.h>
#include "MainLogic.h"

#define _PIN_X A2
#define _PIN_Y A3
#define _PIN_SW 7
#define _PIN_IO 12
#define _PIN_CS 11
#define _PIN_CLK 10

CMainLogic Instance(_PIN_X, _PIN_Y, _PIN_SW, _PIN_IO, _PIN_CS, _PIN_CLK, 2);

void setup()
{
	Instance.Init();
}

void loop()
{
	Instance.Run();
}
