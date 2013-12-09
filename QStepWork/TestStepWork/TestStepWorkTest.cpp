#include "TestStepWorkTest.h"
#include <QtTest/QTest>

#include <QstwEnvironment.h>

#include <BText.h>

using namespace qstepwork;

void TestStepWorkTest::initTestCase()
{}

void TestStepWorkTest::init()
{}

void TestStepWorkTest::cleanup()
{}

void TestStepWorkTest::cleanupTestCase()
{}


void TestStepWorkTest::testCreateEnvironment(){
  m_pEnvironment = new QstwEnvironment(this);
}


void TestStepWorkTest::testSetData2Environment1(){
  m_pEnvironment->clearEnvironment();
  m_pEnvironment->setEntry<int>("a",99);
  m_pEnvironment->setEntry<QString>("b","Hallo");
  int test= m_pEnvironment->size();
  QCOMPARE(test,2);
  m_pEnvironment->clearEnvironment();
  test =m_pEnvironment->size();
  QCOMPARE(test,0);
  
};

void TestStepWorkTest::testCreateXsxpSupport(){
  m_pXsxp = new QswXSxprSupport(this);
  
  std::string sForm= R"(create(*(a (1))b(68.5) c(hallo) d(\" das ist wtext  \")))";
  std::cout <<sForm<<"\n==================================================================\n";
  auto v = m_pXsxp->document(sForm);
  v.Trace("--Bt1--");
  std::cout <<"\n****************************************************************************************\n";
  BText::IdType  ch1=  v._id;
  std::cout <<"\nRoot: "<<ch1;
  
  auto vc1 = m_pXsxp->child_ids(ch1) ;
  std::cout <<"  coc:"<<vc1.size();
  for( auto c1: vc1)
    std::cout <<"\nLevel 1: "<<c1<<"  \n";
  
  auto * pElm = m_pXsxp->element(4,v);
  if (!pElm)
    QFAIL("selection(m_pXsxp->element(4,v) )failed!");
  std::cout <<"\nE: "<<pElm->_id << " (pre:"<<pElm->_sPre<< ") (post:"<<pElm->_sPost<< ") szInner:"<< pElm->_inner.size()<<"\n\n";
  
  ///Kopierkonstruktor
  BText::Sxpr x2(*pElm);
  std::cout <<"\nECopy: "<<x2._id << " (pre:"<<x2._sPre<< ") (post:"<<x2._sPost<< ") szInner:"<< x2._inner.size()<<"\n\n";
  if (x2._inner.size()){
    BText::Sxpr x3(x2._inner.front());
    std::cout <<"\nESub: "<<x3._id << " (pre:"<<x3._sPre<< ") (post:"<<x3._sPost<< ") szInner:"<< x3._inner.size()<<"\n\n";
  }
  
  
  
  
  
};





QTEST_MAIN(TestStepWorkTest)
//#include "TestStepWorkTest.moc"
