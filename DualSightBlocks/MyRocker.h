/*
	MyRocker.h
	Wrapped Rocker get direction
*/
#ifndef _MY_ROCKER_H
#define _MY_ROCKER_H

#define _MID 511
#define _POSI 1
#define _NEGA -1
#define _NEUT 0
#define _UP 1
#define _DOWN 0
#define _THRESHOLD 100

typedef struct __ROCKER_STATUS 
{
  unsigned int _x;
  unsigned int _y;
  int _sw;
} _rocker;

class CRocker 
{
  protected:
    int xPin;
    int yPin;
    int swPin;
    _rocker rockerState;
  public:
    CRocker(int _x_pin, int _y_pin, int _sw_pin) 
	{
      rockerState._sw = _UP;
      rockerState._x = _MID;
      rockerState._y = _MID;
      xPin = _x_pin;
      yPin = _y_pin;
      swPin = _sw_pin;
    }
	void Init()
	{
		pinMode(xPin, INPUT);
		pinMode(yPin, INPUT);
		pinMode(swPin, INPUT_PULLUP);
	}
    void UpdateData() 
	{
      rockerState._x = analogRead(xPin);
      rockerState._y = analogRead(yPin);
      rockerState._sw = digitalRead(swPin);
    }
    void GetStatusByDir(int *_array, int _len) 
	{
      if (_len != 3) 
	  {
        return;
      }
      if (rockerState._x > _MID + _THRESHOLD) 
	  {
        _array[0] = _POSI;
      }
      else if (rockerState._x < _MID - _THRESHOLD) 
	  {
        _array[0] = _NEGA;
      }
      else {
        _array[0] = _NEUT;
      }
      if (rockerState._y > _MID + _THRESHOLD) 
	  {
        _array[1] = _POSI;
      }
      else if (rockerState._y < _MID - _THRESHOLD) 
	  {
        _array[1] = _NEGA;
      }
      else 
	  {
        _array[1] = _NEUT;
      }
      _array[2] = rockerState._sw;
    }
};

#endif

