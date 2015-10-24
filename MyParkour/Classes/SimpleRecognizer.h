#ifndef __SIMPLERECOGNIZER_H__
#define __SIMPLERECOGNIZER_H__
#include <limits>
#include <iostream>
#include <vector>
#include <cmath>
#include "cocos2d.h"


using namespace std;

typedef enum {
	SimpleGesturesRight,
	SimpleGesturesLeft,
	SimpleGesturesUp,
	SimpleGesturesDown,
	SimpleGesturesError,
	SimpleGesturesNotSupport

} SimpleGestures;


class SimpleRecognizer
{
protected:
	//--- These are variables because C++ doesn't (easily) allow
	//---  constants to be floating point numbers
	double X;
	double Y;
	SimpleGestures result;
	std::vector<cocos2d::CCPoint> points;

public:
	SimpleRecognizer();

	void beginPoint(double x, double y);
	void movePoint(double x, double y);
	SimpleGestures endPoint();

	std::vector<cocos2d::CCPoint>& getPoints();
};

#endif // __SIMPLERECOGNIZER_H__
