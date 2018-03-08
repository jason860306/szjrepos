#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include "aes_cppunit.h"

int main(int /*argc*/, char* /*argv*/[])
{
    bool wasSucessful = true;
    /// 1. SimpleTest
    {
        CppUnit::TestResult r;
        CppUnit::TestResultCollector rc;
        r.addListener(&rc);

        AESSimpleTest t;
        t.run(&r);

        CppUnit::TextOutputter o(&rc, std::cout);
        o.write();

        wasSucessful =  rc.wasSuccessful();
    }

    printf("======================================================\n");

    /// 2. Fixture和TestCaller组合
    {
        CppUnit::TestResult r;
        CppUnit::TestResultCollector rc;
        r.addListener(&rc);

        CppUnit::TestRunner runner;
        runner.addTest(new CppUnit::TestCaller<AESTest>(
                           "testEncrypt", &AESTest::testEncrypt));
        runner.addTest(new CppUnit::TestCaller<AESTest>(
                           "testDecrypt", &AESTest::testDecrypt));

        runner.run(r);

        CppUnit::TextOutputter o(&rc, std::cout);
        o.write();

        wasSucessful =  rc.wasSuccessful();
    }

    printf("======================================================\n");

    /// 3. 借助CppUnit定义的一套辅助宏，将测试用命的定义和注册变得自动化
    {
        /// Get the top level suite from the registry
        CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

        /// Adds the test to the list of test to run
        CppUnit::TextUi::TestRunner runner;
        runner.addTest(suite);

        /// Change the default outputter to a compiiler error format outputter
        runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

        /// Run the tests.
        wasSucessful = runner.run();
    }

    /// Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}
