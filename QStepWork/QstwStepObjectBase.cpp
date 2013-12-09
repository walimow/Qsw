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

#include "QstwStepObjectBase.h"

namespace qstepwork {

QstwStepObjectBase::QstwStepObjectBase()
{
}

QstwStepObjectBase::~QstwStepObjectBase()
{
}

QString QstwStepObjectBase::objectName() const
{
    return m_sObjectName;
}

void QstwStepObjectBase::setObjectName(const QString& sObjectName)
{
    m_sObjectName = sObjectName;
}


///should be called as parent, if an object enters the instsance (and has to express ist prototype
///concrete Objects may call the environments onEnterInstance finishing its instanciation
IStepSupport& QstwStepObjectBase::enter_instance(IEnvironment& oEnv) {
  //gültiges Objekt
  QstwEnvironment*pQEnv = dynamic_cast<QstwEnvironment*>(&oEnv);
  if (pQEnv){
      _oEnvironment= pQEnv;
      
      emit pQEnv->beforeEnterInstance(this);
      
  }
  return *this;

};

void QstwStepObjectBase::leave_instance() {
  if (_oEnvironment)
    emit _oEnvironment->beforeLeaveInstance(this);
};

int QstwStepObjectBase::prequest() {
    return rNoError;
};

int QstwStepObjectBase::prepare() {
    return rNoError;
};

int QstwStepObjectBase::perform() {
  return rNoError;
};

void QstwStepObjectBase::post(int) {

};
//-------------- FailSupport

int QstwStepObjectBase::onStepFailed() {
  return rNoError;
};

bool QstwStepObjectBase::canReset() {
  return rHandled;
};

int QstwStepObjectBase::reset() {
  return rNoError;
};

}


