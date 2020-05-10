#pragma once

#include "cocos2d.h"
#include <iostream>

#include "Specification.h"
#include "Core.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;


class MyTests {
private:
	// attributes
	Core* _core = Core::sharedCore();

	bool TestIsCheck();
	bool TestIsCheckmate();
	bool TestIsDraw();
	bool Test—astling();
	bool TestEnPassant();
	bool TestIsKingInDanger();
public:
	// attributes

	// methods
	void runCoreTests();
};