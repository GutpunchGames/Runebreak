// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameOrchestrator/Test/InputBufferTest.h"
#include "CoreTypes.h"
#include "Containers/UnrealString.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInputBufferTest, "InputBufferTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FInputBufferTest::RunTest(const FString& Parameters)
{
	//// This is an example test.
	//{

	//	FInput Input1;
	//	Input1.MoveDirection = 1;

	//	TestEqual(TEXT("This is an example test."), Input1.MoveDirection, 1);
	//}

	//// All tests successful.
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
