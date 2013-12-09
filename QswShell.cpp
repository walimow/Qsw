#include "QswShell.h"
#include <iostream>

#include "ui_QswShellForm.h"

  
/*
 #include "ui_QswShellApp.h"

QswShellApp::QswShellApp()
{
    ui = new Ui::QswShellApp;
    ui->setupUi(this);
}
 */

namespace qstepwork {

QswShell::QswShell()
{
    ui = new Ui::QswShellForm;
    ui->setupUi(this);
    
    //connect( ui->plainTextEdit, SIGNAL( keyPressEvent(QKeyEvent*)) , this,  SIGNAL( ioKeyPressEvent(QKeyEvent*) ) );
    connect(ui->consoleEdit, SIGNAL(onCommand(QString)), this, SLOT(onConsoleInputText(QString)) );
    
}

void 	QswShell::onConsoleInputText(const QString&s){
  ui->consoleEdit->output("==!!!==");
  std::cout<< "QswShell::onConsoleInputText: "<< s.toLocal8Bit().data();
  
}

/*
 void QswShell::ioKeyPressEvent(QKeyEvent* e){
   auto k=  e->key();
   auto s = e->text();
   std::cout<<  s.toLocal8Bit().data();
};*/

QswShell::~QswShell()
{}

/*void 	QswShell::setIOText(const QString& s){
  
};*/

}

//#include "QswShell.moc"
