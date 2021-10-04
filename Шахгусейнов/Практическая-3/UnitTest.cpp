#include "pch.h"
#include "CppUnitTest.h"
#include "../MatrixCalc/MatrixCalc.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(MatrixConstructorTest)
	{
	public:
		TEST_METHOD(MatrixConstructorTest1)
		{
			MatrixCalc* testMatrix = new MatrixCalc(-1, -1);

			Assert::IsNull(testMatrix->object->matrix);
		}
		TEST_METHOD(MatrixConstructorTest2)
		{
			MatrixCalc* testMatrix = new MatrixCalc(3, 6);

			Assert::IsNotNull(testMatrix->object->matrix);
			Assert::AreEqual(testMatrix->object->n, 3);
			Assert::AreEqual(testMatrix->object->m, 6);
		}
		TEST_METHOD(MatrixConstructorTest3)
		{
			int** testCostMatrix = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix = new MatrixCalc(3, 6, testCostMatrix);

			for (int i=0; i<3; i++)
				for (int j=0; j<6; j++)
					Assert::AreEqual(testMatrix->object->matrix[i][j], testCostMatrix[i][j]);
			Assert::AreEqual(testMatrix->object->n, 3);
			Assert::AreEqual(testMatrix->object->m, 6);
		}
	};


	TEST_CLASS(AddMatrixTest)
	{
	public:
		TEST_METHOD(AddMatrixTest1)
		{
			MatrixCalc* testMatrix1 = new MatrixCalc(-1, -1);
			MatrixCalc* testMatrix2 = new MatrixCalc(-1, -1);
			Assert::IsNull(testMatrix1->addMatrix(testMatrix1, testMatrix2));
		}
		TEST_METHOD(AddMatrixTest2)
		{
			int** testCostMatrix1 = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(3, 6, testCostMatrix1);

			int** testCostMatrix2 = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(3, 6, testCostMatrix2);

			int** costResult = new int* [3]{		new int[6]{ 2, 4, 6, 8, 10, 12 },
													new int[6]{ 14, 16, 18, 20, 22, 24 },
													new int[6]{ 26, 28, 30, 32, 34, 36 }
			};

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 6; j++)
					Assert::AreEqual(testMatrix1->addMatrix(testMatrix1, testMatrix2)->object->matrix[i][j], costResult[i][j]);
		}
		TEST_METHOD(AddMatrixTest3)
		{
			int** testCostMatrix1 = new int* [2]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(2, 6, testCostMatrix1);

			int** testCostMatrix2 = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(3, 6, testCostMatrix2);

			Assert::IsNull(testMatrix1->addMatrix(testMatrix1, testMatrix2));
		}
	};


	TEST_CLASS(SubstractMatrixTest)
	{
	public:
		TEST_METHOD(SubstractMatrixTest1)
		{
			MatrixCalc* testMatrix1 = new MatrixCalc(-1, -1);
			MatrixCalc* testMatrix2 = new MatrixCalc(-1, -1);
			Assert::IsNull(testMatrix1->subMatrix(testMatrix1, testMatrix2));
		}
		TEST_METHOD(SubstractMatrixTest2)
		{
			int** testCostMatrix1 = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(3, 6, testCostMatrix1);

			int** testCostMatrix2 = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(3, 6, testCostMatrix2);

			int** costResult = new int* [3]{		new int[6]{ 0, 0, 0, 0, 0, 0 },
													new int[6]{ 0, 0, 0, 0, 0, 0 },
													new int[6]{ 0, 0, 0, 0, 0, 0 }
			};

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 6; j++)
					Assert::AreEqual(testMatrix1->subMatrix(testMatrix1, testMatrix2)->object->matrix[i][j], costResult[i][j]);
		}
		TEST_METHOD(SubstractMatrixTest3)
		{
			int** testCostMatrix1 = new int* [2]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(2, 6, testCostMatrix1);

			int** testCostMatrix2 = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(3, 6, testCostMatrix2);

			Assert::IsNull(testMatrix1->subMatrix(testMatrix1, testMatrix2));
		}
	};


	TEST_CLASS(NumberMultiplyMatrixTest)
	{
	public:
		TEST_METHOD(NumberMultiplyMatrixTest1)
		{
			MatrixCalc* testMatrix = new MatrixCalc(-1, -1);
			Assert::IsNull(testMatrix->numberMultMatrix(testMatrix, 3));
		}
		TEST_METHOD(NumberMultiplyMatrixTest2)
		{
			int** testCostMatrix = new int* [3]{	new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(3, 6, testCostMatrix);

			int** costResult = new int* [3]{		new int[6]{ 3, 6, 9, 12, 15, 18 },
													new int[6]{ 21, 24, 27, 30, 33, 36 },
													new int[6]{ 39, 42, 45, 48, 51, 54 }
			};

			testMatrix1->numberMultMatrix(testMatrix1, 3);

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 6; j++)
					Assert::AreEqual(testMatrix1->object->matrix[i][j], costResult[i][j]);
		}
	};


	TEST_CLASS(NumberDivisionMatrixTest)
	{
	public:
		TEST_METHOD(NumberDivisionMatrixTest1)
		{
			MatrixCalc* testMatrix = new MatrixCalc(-1, -1);
			Assert::IsNull(testMatrix->numberDivMatrix(testMatrix, 3));
		}
		TEST_METHOD(NumberDivisionMatrixTest2)
		{
			int** testCostMatrix = new int* [3]{	new int[6]{ 3, 6, 9, 12, 15, 18 },
													new int[6]{ 21, 24, 27, 30, 33, 36 },
													new int[6]{ 39, 42, 45, 48, 51, 54 }
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(3, 6, testCostMatrix);

			int** costResult = new int* [3]{		new int[6]{ 1, 2, 3, 4, 5, 6 },
													new int[6]{ 7, 8, 9, 10, 11, 12 },
													new int[6]{ 13, 14, 15, 16, 17, 18 }
			};

			testMatrix1->numberDivMatrix(testMatrix1, 3);

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 6; j++)
					Assert::AreEqual(testMatrix1->object->matrix[i][j], costResult[i][j]);
		}
	};


	TEST_CLASS(MultiplyMatrixTest)
	{
	public:
		TEST_METHOD(MultiplyMatrixTest1)
		{
			MatrixCalc* testMatrix1 = new MatrixCalc(-1, -1);
			MatrixCalc* testMatrix2 = new MatrixCalc(-1, -1);

			Assert::IsNull(testMatrix1->multMatrix(testMatrix1, testMatrix2));
		}
		TEST_METHOD(MultiplyMatrixTest2)
		{
			int** testCostMatrix1 = new int* [2]{	new int[2]{ 2, 4 },
													new int[2]{ 6, 8 },
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(2, 2, testCostMatrix1);

			int** testCostMatrix2 = new int* [2]{	new int[2]{ 1, 3 },
													new int[2]{ 5, 7 },
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(2, 2, testCostMatrix2);

			int** costResult = new int* [2]{		new int[2]{ 22, 34 },
													new int[2]{ 46, 74 },
			};

			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					Assert::AreEqual(testMatrix1->multMatrix(testMatrix1, testMatrix2)->object->matrix[i][j], costResult[i][j]);
		}
		TEST_METHOD(MultiplyMatrixTest3)
		{
			int** testCostMatrix1 = new int* [2]{	new int[2]{ 2, 4 },
													new int[2]{ 6, 8 },
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(2, 2, testCostMatrix1);

			int** testCostMatrix2 = new int* [2]{	new int[2]{ 1, 3 },
													new int[2]{ 5, 7 },
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(2, 2, testCostMatrix2);

			int** costResult = new int* [2]{		new int[2]{ 20, 28 },
													new int[2]{ 52, 76 },
			};

			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					Assert::AreEqual(testMatrix1->multMatrix(testMatrix2, testMatrix1)->object->matrix[i][j], costResult[i][j]);
		}
		TEST_METHOD(MultiplyMatrixTest4)
		{
			MatrixCalc* testMatrix1 = new MatrixCalc(2, 4);
			MatrixCalc* testMatrix2 = new MatrixCalc(2, 4);

			Assert::IsNull(testMatrix1->multMatrix(testMatrix1, testMatrix2));
		}
		TEST_METHOD(MultiplyMatrixTest5)
		{
			int** testCostMatrix1 = new int* [2]{	new int[3]{ 1, 2, 0 },
													new int[3]{ 3, 1, -1 },
			};
			MatrixCalc* testMatrix1 = new MatrixCalc(2, 3, testCostMatrix1);

			int** testCostMatrix2 = new int* [3]{	new int[1]{ 1 },
													new int[1]{ 2 },
													new int[1]{ 3 },
			};
			MatrixCalc* testMatrix2 = new MatrixCalc(3, 1, testCostMatrix2);

			int** costResult = new int* [2]{		new int[1]{ 5 },
													new int[1]{ 2 },
			};

			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 1; j++)
					Assert::AreEqual(testMatrix1->multMatrix(testMatrix1, testMatrix2)->object->matrix[i][j], costResult[i][j]);
		}
	};

	TEST_CLASS(TranspositionMatrixTest)
	{
		TEST_METHOD(TranspositionMatrixTest1)
		{
			MatrixCalc* testMatrix = new MatrixCalc(-1, -1);
			Assert::IsNull(testMatrix->transMatrix(testMatrix));
		}
		TEST_METHOD(TranspositionMatrixTest2)
		{
			int** testCostMatrix = new int* [3]{ new int[6]{ 3, 6, 9, 12, 15, 18 },
														new int[6]{ 21, 24, 27, 30, 33, 36 },
														new int[6]{ 39, 42, 45, 48, 51, 54 }
			};
			MatrixCalc* testMatrix = new MatrixCalc(3, 6, testCostMatrix);

			int** costResult = new int* [6]{		new int[3]{ 3, 21, 39 },
													new int[3]{ 6, 24, 42},
													new int[3]{ 9, 27, 45},
													new int[3]{ 12, 30, 48},
													new int[3]{ 15, 33, 51},
													new int[3]{ 18, 36, 54}
			};

			MatrixCalc* result = testMatrix->transMatrix(testMatrix);

			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 3; j++)
					Assert::AreEqual(result->object->matrix[i][j], costResult[i][j]);
		}
	};
}