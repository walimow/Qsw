#ifndef TestStepWorkTEST_H
#define TestStepWorkTEST_H

#include <QObject>
#include <QstwEnvironment.h>
#include <QswXSxprSupport.h>

using namespace qstepwork;

class TestStepWorkTest : public QObject
{
Q_OBJECT
  QstwEnvironment * m_pEnvironment=nullptr;;
  QswXSxprSupport * m_pXsxp=nullptr;
private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCreateEnvironment();
    void testSetData2Environment1();
    void testCreateXsxpSupport();
    
};

#endif // TestStepWorkTEST_H
