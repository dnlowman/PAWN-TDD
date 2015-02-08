#define MAX_UNIT_TESTS (200)
#define MAX_UNIT_TEST_ASSERTIONS (20)
#define UNIT_TEST_NAME_LENGTH (128)

enum E_UNIT_TESTS_STRUCT
{
	E_FUNCTION_NAME[UNIT_TEST_NAME_LENGTH]
};
stock UnitTests[MAX_UNIT_TESTS][E_UNIT_TESTS_STRUCT];

stock bool: Results[MAX_UNIT_TEST_ASSERTIONS] = {false, ...};
stock ResultIndex = 0;

/* AreEqual */
stock Assert_IntAreEqual(expected, actual)
{
	new resCache = Results[ResultIndex] = (expected == actual);
	++ResultIndex;
	return resCache;
}

stock Assert_FloatAreEqual(Float: expected, Float: actual)
{
	new resCache = Results[ResultIndex] = (floatcmp(expected, actual) == 0) ? true : false;
	++ResultIndex;
	return resCache;
}

stock Assert_StringAreEqual(const expected[], const actual[])
{
	new resCache = Results[ResultIndex] = strcmp(expected, actual) == 0;
	++ResultIndex;
	return resCache;
}

stock Assert_BoolAreEqual(bool: expected, bool: actual)
{
	new resCache = Results[ResultIndex] = expected == actual;
	++ResultIndex;
	return resCache;
}

/* AreNotEqual */
stock Assert_IntAreNotEqual(expected, actual)
{
	new resCache = Results[ResultIndex] = (expected != actual);
	++ResultIndex;
	return resCache;
}

stock Assert_FloatAreNotEqual(Float: expected, Float: actual)
{
	new resCache = Results[ResultIndex] = (floatcmp(expected, actual) != 0) ? true : false;
	++ResultIndex;
	return resCache;
}

stock Assert_StringAreNotEqual(const expected[], const actual[])
{
	new resCache = Results[ResultIndex] = strcmp(expected, actual) != 0;
	++ResultIndex;
	return resCache;
}

stock Assert_BoolAreNotEqual(bool: expected, bool: actual)
{
	new resCache = Results[ResultIndex] = expected != actual;
	++ResultIndex;
	return resCache;
}

// IsTrue
stock Assert_IntIsTrue(value)
{
	new resCache = Results[ResultIndex] = (expected > 0);
	++ResultIndex;
	return resCache;
}

stock Assert_FloatIsTrue(Float: value)
{
	new resCache = Results[ResultIndex] = (floatcmp(value, 0) == 1);
	++ResultIndex;
	return resCache;
}

stock Assert_StringIsTrue(const str[])
{
	new resCache = Results[ResultIndex] = (strlen(str) > 0);
	++ResultIndex;
	return resCache;
}

stock Assert_BoolIsTrue(bool: value)
{
	new resCache = Results[ResultIndex] = (value == true);
	++ResultIndex;
	return resCache;
}

// IsNotTrue
stock Assert_IntIsNotTrue(value)
{
	new resCache = Results[ResultIndex] = (expected <= 0);
	++ResultIndex;
	return resCache;
}

stock Assert_FloatIsNotTrue(Float: value)
{
	new resCache = Results[ResultIndex] = (floatcmp(value, 0) != 1);
	++ResultIndex;
	return resCache;
}

stock Assert_StringIsNotTrue(const str[])
{
	new resCache = Results[ResultIndex] = (strlen(str) == 0);
	++ResultIndex;
	return resCache;
}

stock Assert_BoolIsNotTrue(bool: value)
{
	new resCache = Results[ResultIndex] = (value != true);
	++ResultIndex;
	return resCache;
}

/* Helpers */
stock RegisterUnitTest(functionName[])
{
	new index = FindEmptyUnitTestArrayIndex(functionName);
	if(index == -1) printf("[Unit Test Error] - Error could not register the function %s, either the test already exists or you have reached the maximum amount of unit tests.", functionName);
	else format(UnitTests[index][E_FUNCTION_NAME], UNIT_TEST_NAME_LENGTH, "%s", functionName);
}

stock ExecuteUnitTests()
{
	for(new i = 0; i < MAX_UNIT_TESTS; ++i)
	{
		if(strlen(UnitTests[i][E_FUNCTION_NAME]) != 0)
		{
			ResetUnitTestCheck();
			CallRemoteFunction(UnitTests[i][E_FUNCTION_NAME], "");
			printf("[Unit Test] - %s - %s", UnitTests[i][E_FUNCTION_NAME], (CheckIfUnitTestPassed(ResultIndex)) ? ("PASSED") : ("\a\t\tFAILED"));
		}
	}
	ResetUnitTestCheck();
}

stock FindEmptyUnitTestArrayIndex(const functionName[])
{
	if(strlen(functionName) == 0) return -1;
	for(new i = 0; i < MAX_UNIT_TESTS; ++i)
	{
		if(strlen(UnitTests[i][E_FUNCTION_NAME]) == 0) return i;
	}
	return -1;
}

stock CheckIfUnitTestPassed(index)
{
	new resultCount = 0;
	for(new i = 0; i <= index; ++i) if(Results[i] == true) ++resultCount;
	return (resultCount == index && resultCount != 0);
}

stock ResetUnitTestCheck()
{
	for(new i = 0; i < MAX_UNIT_TEST_ASSERTIONS; ++i) Results[i] = false;
	ResultIndex = 0;
}