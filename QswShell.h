#ifndef QswShell_H
#define QswShell_H

#include <QtWidgets/QDialog>

#include <QtWidgets/QPlainTextEdit>
#include <QKeyEvent>

namespace Ui
{
class QswShellForm;
}
  
namespace qstepwork{
  
class QswShell : public QDialog
{
Q_OBJECT
public:
    QswShell();
    virtual ~QswShell();
private:
    Ui::QswShellForm* ui;

private slots:
      //void ioKeyPressEvent(QKeyEvent * e);
public slots:
  void 	onConsoleInputText(const QString&);
signals:
 // void ioTextChanged();
};

}

#endif // QswShell_H
