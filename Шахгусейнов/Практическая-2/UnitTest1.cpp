#include "pch.h"
#include "CppUnitTest.h" 
#include "../deque/Deque.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDeque
{
	deque tD;
	TEST_CLASS(AddElement)
	{
	public:

		TEST_METHOD(TestAdd1) //проверка вставки элемента в начало
		{
			tD.insertFront(5);
			tD.insertFront(37);
			tD.insertFront(-1);
			Assert::AreEqual(-1, tD.front->data);
			Assert::AreEqual(37, tD.front->next->data);
			Assert::AreEqual(5, tD.front->next->next->data);
		}

		TEST_METHOD(TestAdd2) //проверка вставки элемента в конец
		{
			tD.insertLast(0);
			tD.insertLast(7);
			Assert::AreEqual(7, tD.last->data);
			Assert::AreEqual(0, tD.last->prev->data);
		}

		TEST_METHOD(TestAdd3) //проверка вставки элемента в середину перед указанным(по значению)
		{
			tD.insertBefore(14, 5);
			Assert::AreEqual(14, tD.front->next->next->data);
		}

		TEST_METHOD(TestAdd4) //проверка вставки элемента в середину после указанного(по значению)
		{
			tD.insertAfter(37, 5);
			Assert::AreEqual(37, tD.front->next->next->next->next->data);
		}
	};

	TEST_CLASS(DeleteElement)
	{
	public:

		TEST_METHOD(TestDelete1) //проверка удаления элемента из начала
		{
			tD.deleteFront();
			Assert::AreEqual(37, tD.front->data);
		}

		TEST_METHOD(TestDelete2) //проверка удаления элемента из конца
		{
			tD.deleteLast();
			Assert::AreEqual(0, tD.last->data);
		}

		TEST_METHOD(TestDelete3) //проверка удаления первого вхождения элемента
		{
			tD.deleteByData(5);
			Assert::AreEqual(37, tD.front->next->next->data);
		}

		TEST_METHOD(TestDelete4) //проверка удаления всех вхождений элемента
		{
			tD.deleteByDataAll(37);
			Assert::AreEqual(14, tD.front->data);
			Assert::AreEqual(0, tD.front->next->data);
		}
	};

	TEST_CLASS(EraseDeque)
	{
	public:

		TEST_METHOD(TestErase) //проверка удаления дека
		{
			tD.eraseAll();
			Assert::IsFalse(tD.front);
			Assert::IsFalse(tD.last);
		}
	};
}
