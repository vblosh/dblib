#ifndef UNITTEST_TESTREPORTERSTDOUTEX_H
#define UNITTEST_TESTREPORTERSTDOUTEX_H

#include "TestReporter.h"

namespace UnitTest {

class UNITTEST_LINKAGE TestReporterStdoutEx : public TestReporter
{
public:
    TestReporterStdoutEx(
    bool verbose = false
    , bool color = true
    );

private:
    virtual void ReportTestStart(TestDetails const& test);
    virtual void ReportFailure(TestDetails const& test, char const* failure);
    virtual void ReportTestFinish(TestDetails const& test, float secondsElapsed);
    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);
  
    bool m_verbose;
    bool m_color;
    
    bool m_hadErrors;
};

} // namespace UnitTest

#endif // !UNITTEST_TESTREPORTERSTDOUTEX_H
