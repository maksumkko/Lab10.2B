#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10.2B/Lab10.2B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102B
{
	TEST_CLASS(UnitTest102B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Students S[5] = {
				{ "Student1", 1, ITIS, 4, 5, 4 },
				{ "Student2", 2, RE, 5, 4, 3 },
				{ "Student3", 3, KN, 4, 4, 5 },
				{ "Student4", 1, KI, 5, 5, 4 },
				{ "Student5", 2, PZ, 3, 4, 4 }
			};

			int count_math = 0;
			int count_physics = 0;
			int count_info = 0;
			int count_physics_5 = 0;

			count_good_grades(S, 5, count_math, count_physics, count_info, count_physics_5);

			Assert::AreEqual(count_math, 3);
		}
	};
}