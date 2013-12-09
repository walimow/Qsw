/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  kh <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef QSTEPOBJECTBASE_H
#define QSTEPOBJECTBASE_H
#include <QObject>
#include <QStepWalk.h>
#include <QstwEnvironment.h>

namespace qstepwork{


/**
 * Baseobject to all 'operating' Objects with Qt, stw-DummyFinctionality
 */



class QstwStepObjectBase : public QObject, 
      public IStepSupport, public IFailSupport
{
    Q_OBJECT
    Q_PROPERTY(QString objectName READ objectName WRITE setObjectName)

    Q_PROPERTY(QString typeName READ typeName)
public:
    QstwStepObjectBase();
    ~QstwStepObjectBase();

    QString objectName() const;
    QString typeName() const{
      return _typeName;
    };
    
    
protected:
    QString _typeName="?noTypename.defined";
    QPointer<QstwEnvironment>  _oEnvironment;
public Q_SLOTS:
  
public:
  
    void setObjectName(const QString& sObjectName);
//----------------Stepwalk----------------
    StepState stepState() override  			{ return _stepState; };
    StepSuccessState stepSuccessState()override  	{ return _stepSuccessState; };;
    
///@  InstanceSupport
    IStepSupport& enter_instance(IEnvironment&)override;
    void leave_instance()override;
///@  StepSupport
    int prequest()override;
    int prepare()override;
    int perform()override;
    void post(int)override;
//-------------- FailSupport
    int onStepFailed()override;
    bool canReset()override;
    int reset()override;    
    //int fail  (int);
    
    ///for qt-property-handling
    
  //enum EStepState{sts_noState= qstepwork::StepState::noState, sts_initialized, sts_prepared, sts_performed, sts_postperf, sts_invalidated };
  Q_ENUMS(StepState);       //funktioniert das im PropertyBrowser??
  Q_PROPERTY( StepState stepState READ stepState )
  
  
  StepState stepState()const {    
    //return reinterpret_cast<EStepState> (_stepState);
    return _stepState;
  }
  
  //enum EStepSuccessState{scs_noSuccessState= noSuccessState, scs_ok, scs_failed=-1};
  Q_ENUMS(StepSuccessState);
  Q_PROPERTY( StepSuccessState stepSuccessState READ stepSuccessState )
  
  StepSuccessState stepSuccessState()const {
    return  _stepSuccessState;
  }
private:
  int _ret=0;
  StepState  _stepState= noState;
  StepSuccessState _stepSuccessState = noSuccessState; 
    QString m_sObjectName ;

};

}

#endif // QSTEPOBJECTBASE_H
