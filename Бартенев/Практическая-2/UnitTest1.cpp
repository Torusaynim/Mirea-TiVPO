#include "pch.h"
#include "CppUnitTest.h"
#include "LDS.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(TestinsertFront)
	{
	public:
		TEST_METHOD(TestinsertFront1)
		{
			Lds lds;
			lds.insertFront(1);

			Assert::AreEqual(lds.front->data, 1);
			Assert::AreEqual(lds.rear->data, 1);
		}
		TEST_METHOD(TestinsertFront2)
		{
			Lds lds;

			Assert::IsNull(lds.front);
			Assert::IsNull(lds.rear);
		}
		TEST_METHOD(TestinsertFront3)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);
			Assert::AreEqual(lds.front->data, 101);
			Assert::AreEqual(lds.front->next->data, 1);
		}
		TEST_METHOD(TestinsertFront4)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);

			Assert::AreEqual(lds.rear->prev->next->data, 1);
			Assert::AreEqual(lds.front->next->prev->data, 66);

			Assert::AreEqual(lds.front->data, 66);
			Assert::AreEqual(lds.front->next->data, 101);
		}
		TEST_METHOD(TestinsertFront5)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);
			lds.insertFront(9125);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);

			Assert::AreEqual(lds.rear->prev->next->data, 1);
			Assert::AreEqual(lds.rear->prev->prev->data, 66);

			Assert::AreEqual(lds.front->next->next->data, 101);
			Assert::AreEqual(lds.front->next->prev->data, 9125);

			Assert::AreEqual(lds.front->data, 9125);
			Assert::AreEqual(lds.front->next->data, 66);

		}
	};


	TEST_CLASS(TestrearFront)
	{
	public:
		TEST_METHOD(TestinsertRear1)
		{
			Lds lds;
			lds.insertRear(1, 0);

			Assert::AreEqual(lds.front->data, 1);
			Assert::AreEqual(lds.rear->data, 1);
		}
		TEST_METHOD(TestinsertRear2)
		{
			Lds lds;
			lds.insertRear(101, 0);
			lds.insertRear(1, 0);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);
			Assert::AreEqual(lds.front->data, 101);
			Assert::AreEqual(lds.front->next->data, 1);
		}
		TEST_METHOD(TestinsertRear3)
		{
			Lds lds;
			lds.insertRear(66, 0);
			lds.insertRear(101, 0);
			lds.insertRear(1, 0);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);

			Assert::AreEqual(lds.rear->prev->next->data, 1);
			Assert::AreEqual(lds.front->next->prev->data, 66);

			Assert::AreEqual(lds.front->data, 66);
			Assert::AreEqual(lds.front->next->data, 101);
		}
		TEST_METHOD(TestinsertRear4)
		{
			Lds lds;
			lds.insertRear(9125, 0);
			lds.insertRear(66, 0);
			lds.insertRear(101, 0);
			lds.insertRear(1, 0);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);

			Assert::AreEqual(lds.rear->prev->next->data, 1);
			Assert::AreEqual(lds.rear->prev->prev->data, 66);

			Assert::AreEqual(lds.front->next->next->data, 101);
			Assert::AreEqual(lds.front->next->prev->data, 9125);

			Assert::AreEqual(lds.front->data, 9125);
			Assert::AreEqual(lds.front->next->data, 66);

		}
	};


	TEST_CLASS(Testinsert)
	{
	public:
		TEST_METHOD(Testinsert1)
		{
			Lds lds;
			Assert::AreEqual(lds.insert(1, 1, 1), -1);
		}
		TEST_METHOD(Testinsert2)
		{
			Lds lds;
			lds.insertRear(101, 0);
			lds.insert(101, 1, 1);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);
			Assert::AreEqual(lds.front->data, 101);
			Assert::AreEqual(lds.front->next->data, 1);
		}
		TEST_METHOD(Testinsert3)
		{
			Lds lds;
			lds.insertRear(66, 0);
			lds.insertRear(1, 0);
			lds.insert(66, 101, 1);

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);

			Assert::AreEqual(lds.rear->prev->next->data, 1);
			Assert::AreEqual(lds.front->next->prev->data, 66);

			Assert::AreEqual(lds.front->data, 66);
			Assert::AreEqual(lds.front->next->data, 101);
		}
		TEST_METHOD(Testinsert4)
		{
			Lds lds;
			lds.insertRear(101, 0);
			lds.insert(101, 1, 0);

			Assert::AreEqual(lds.rear->data, 101);
			Assert::AreEqual(lds.rear->prev->data, 1);
			Assert::AreEqual(lds.front->data, 1);
			Assert::AreEqual(lds.front->next->data, 101);
		}
	};

	TEST_CLASS(DeleteFront)
	{
	public:
		TEST_METHOD(DeleteFront1)
		{
			Lds lds;
			Assert::AreEqual(lds.deleteFront(), 0);
		}
		TEST_METHOD(DeleteFront2)
		{
			Lds lds;
			lds.insertFront(1);
			lds.deleteFront();

			Assert::IsNull(lds.front);
			Assert::IsNull(lds.rear);
		}
		TEST_METHOD(DeleteFront3)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.deleteFront();

			Assert::AreEqual(lds.front->data, 1);
			Assert::AreEqual(lds.rear->data, 1);
		}
		TEST_METHOD(DeleteFront4)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);
			lds.deleteFront();

			Assert::AreEqual(lds.rear->data, 1);
			Assert::AreEqual(lds.rear->prev->data, 101);
			Assert::AreEqual(lds.front->data, 101);
			Assert::AreEqual(lds.front->next->data, 1);
		}
	};
	TEST_CLASS(DeleteRear)
	{
	public:
		TEST_METHOD(DeleteRear1)
		{
			Lds lds;
			Assert::AreEqual(lds.deleteRear(), 0);
		}
		TEST_METHOD(DeleteRear2)
		{
			Lds lds;
			lds.insertFront(1);
			lds.deleteRear();

			Assert::IsNull(lds.front);
			Assert::IsNull(lds.rear);
		}
		TEST_METHOD(DeleteRear3)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.deleteRear();

			Assert::AreEqual(lds.front->data, 101);
			Assert::AreEqual(lds.rear->data, 101);
		}
		TEST_METHOD(DeleteRear4)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);
			lds.deleteRear();

			Assert::AreEqual(lds.rear->data, 101);
			Assert::AreEqual(lds.rear->prev->data, 66);
			Assert::AreEqual(lds.front->data, 66);
			Assert::AreEqual(lds.front->next->data, 101);
		}
	};
	TEST_CLASS(Erase)
	{
	public:
		TEST_METHOD(Erase1)
		{
			Lds lds;
			Assert::AreEqual(lds.erase(), 0);
		}
		TEST_METHOD(Erase2)
		{
			Lds lds;
			lds.insertFront(1);
			lds.erase();

			Assert::IsNull(lds.front);
			Assert::IsNull(lds.rear);
		}
		TEST_METHOD(Erase3)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);
			lds.erase();

			Assert::IsNull(lds.front);
			Assert::IsNull(lds.rear);
		}
	};
	TEST_CLASS(findAll)
	{
	public:
		TEST_METHOD(findAll1)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);

			Node* testNode = lds.front->next;

			vector<Node*> testResult;
			testResult.push_back(testNode);

			Assert::AreEqual(lds.findAll(101, 0)[0]->data, testResult[0]->data);
		}
		TEST_METHOD(findAll2)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);

			Node* testNode = lds.front;

			vector<Node*> testResult;
			testResult.push_back(testNode);

			Assert::AreEqual(lds.findAll(66, 0)[0]->data, testResult[0]->data);
		}
		TEST_METHOD(findAll3)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(66);

			Node* testNode = lds.rear;

			vector<Node*> testResult;
			testResult.push_back(testNode);

			Assert::AreEqual(lds.findAll(1, 0)[0]->data, testResult[0]->data);
		}
		TEST_METHOD(findAll4)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(1);
			lds.insertFront(66);
			lds.insertFront(1);

			Node* testNode = lds.rear;

			vector<Node*> testResult;
			testResult.push_back(testNode);
			testNode = lds.front;
			testResult.push_back(testNode);
			testNode = lds.front->next->next;
			testResult.push_back(testNode);

			Assert::AreEqual(lds.findAll(1, 0)[0]->data, testResult[0]->data);
			Assert::AreEqual(lds.findAll(1, 0)[2]->data, testResult[0]->data);
			Assert::AreEqual(lds.findAll(1, 0)[1]->data, testResult[0]->data);
		}
		TEST_METHOD(findAll5)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(1);
			lds.insertFront(1);

			Node* testNode = lds.rear;

			vector<Node*> testResult;
			testResult.push_back(testNode);
			testNode = lds.front;
			testResult.push_back(testNode);
			testNode = lds.front->next;
			testResult.push_back(testNode);

			Assert::AreEqual(lds.findAll(1, 0)[0]->data, testResult[0]->data);
			Assert::AreEqual(lds.findAll(1, 0)[2]->data, testResult[0]->data);
			Assert::AreEqual(lds.findAll(1, 0)[1]->data, testResult[0]->data);
		}
	};
	TEST_CLASS(changeAll)
	{
	public:
		TEST_METHOD(changeAll1)
		{
			Lds lds;
			Assert::AreEqual(lds.changeAll(1, 10), -1);
		}
		TEST_METHOD(changeAll2)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(1);
			lds.insertFront(66);
			lds.insertFront(1);

			Assert::AreEqual(lds.changeAll(2, 20), 0);
		}
		TEST_METHOD(changeAll3)
		{
			Lds lds;
			lds.insertFront(1);
			lds.insertFront(101);
			lds.insertFront(1);
			lds.insertFront(66);
			lds.insertFront(1);

			Assert::AreEqual(lds.changeAll(1, 20), 1);
			Assert::AreEqual(lds.rear->data, 20);
			Assert::AreEqual(lds.front->data, 20);
			Assert::AreEqual(lds.front->next->next->data, 20);
		}
	};
}