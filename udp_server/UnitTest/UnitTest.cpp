#include "pch.h"
#include "CppUnitTest.h"
#include "../udp_server/udp_server.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	void commandOkTest(char command[]) {
		const char* test = parseCommand(command, 0);
		Assert::AreEqual(test, "Command Work!\n");
	}
	void commandNeedTest(char command[]) {
		const char* test = parseCommand(command, 0);
		Assert::AreEqual(test, "Need More Parameters!\n");
	}
	void commandNotTest(char command[]) {
		const char* test = parseCommand(command, 0);
		Assert::AreEqual(test, "Command not found!\n");
	}
	void limitTest(char command[]) {
		const char* test = parseCommand(command, 0);
		Assert::AreEqual(test, "Exceeding limits!\n");
	}
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(ClearCommand)
		{
			commandOkTest("clear display (255 255 255)");
		}
		TEST_METHOD(PixelCommand)
		{
			commandOkTest("draw pixel 1 1 (255 255 255)");
		}
		TEST_METHOD(LineCommand)
		{
			commandOkTest("draw line 1 1 2 2 (255 255 255)");
		}
		TEST_METHOD(drawRectCommand)
		{
			commandOkTest("draw rectangle 1 1 10 10 (255 255 255)");
		}
		TEST_METHOD(fillRectCommand)
		{
			commandOkTest("fill rectangle 1 1 10 10 (255 255 255)");
		}
		TEST_METHOD(drawEllipseCommand)
		{
			commandOkTest("draw ellipse 1 1 10 10 (255 255 255)");
		}
		TEST_METHOD(fillEllipseCommand)
		{
			commandOkTest("fill ellipse 1 1 10 10 (255 255 255)");
		}
		TEST_METHOD(dCircleCommand)
		{
			commandOkTest("draw circle 1 1 10 (255 255 255)");
		}
		TEST_METHOD(fCircleCommand)
		{
			commandOkTest("fill circle 1 1 10 (255 255 255)");
		}
		TEST_METHOD(drawRoundedRectangleCommand)
		{
			commandOkTest("draw rounded rectangle 1 1 20 20 10 (255 255 255)");
		}
		TEST_METHOD(fillRoundedRectangleCommand)
		{
			commandOkTest("fill rounded rectangle 1 1 20 20 10 (255 255 255)");
		}
		TEST_METHOD(drawTextCommand)
		{
			commandOkTest("draw text 1 1 (255 255 255) 10 5 hello");
		}
		TEST_METHOD(drawImageCommand)
		{
			commandOkTest("draw image 1 1 10 10 'image.png'");
		}
		TEST_METHOD(setOrientationCommand)
		{
			commandOkTest("set orientation 90");
		}
		TEST_METHOD(getWidthCommand)
		{
			commandOkTest("get width");
		}
		TEST_METHOD(getHeightCommand)
		{
			commandOkTest("get height");
		}

		TEST_METHOD(NeedMoreParams)
		{
			commandNeedTest("draw pixel 1");
		}
		TEST_METHOD(NotFound)
		{
			commandNotTest("test");
		}
		TEST_METHOD(WrongParams)
		{
			commandNeedTest("draw circle one two thre 4");
		}
		TEST_METHOD(ZeroParams)
		{
			commandNeedTest("draw circle");
		}
		TEST_METHOD(intLimit)
		{
			limitTest("draw circle 101");
		}
		TEST_METHOD(colorLimit)
		{
			limitTest("draw circle (266 265 264)");
		}
	};
}
