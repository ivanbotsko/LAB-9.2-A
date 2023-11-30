#include "pch.h"
#include "CppUnitTest.h"
#include "../PR 9.2 A/PR 9.2 A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YourProjectNamespace
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestCreateFunction)
        {
            const int N = 2;
            Student* s = new Student[N];

            std::stringstream input;
            input << "Прізвище1\n1\n0\n5\n4\n3\n\t Прізвище2\n2\n1\n3\n3\n4\n";

            std::streambuf* originalCin = std::cin.rdbuf();
            std::cin.rdbuf(input.rdbuf());

            Create(s, N);

            std::cin.rdbuf(originalCin);

            Assert::AreEqual(std::string("Прізвище1"), s[0].surname);
            Assert::AreEqual(5, s[0].physics);
            Assert::AreEqual(4, s[0].math);
            Assert::AreEqual(3, s[0].informatics);

            Assert::AreEqual(std::string("Прізвище2"), s[1].surname);
            Assert::AreEqual(3, s[1].physics);
            Assert::AreEqual(3, s[1].math);
            Assert::AreEqual(4, s[1].informatics);

            delete[] s;
        }
    };
}
