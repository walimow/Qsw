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

#ifndef QSTWMESSAGE_H
#define QSTWMESSAGE_H

#include <QObject>
#include <QStepWalk.h>
#include <QstwDataForm.h>

using namespace qstepwork;



class QstwMessage : public QObject, public IMessageSupport::IPacket
{
    Q_OBJECT
public:
  const int mtype() const override{ return _mType;};	///for specify first recepting	
  const unsigned long long curr() const { return curr();}  ///counter on msgCreate, unspecified (will be copied, can be anachronistic when msg is createt in foreign countings, subjectiv meaning
private:
  int _mType=0;
  long long _curr;
  const IMessageSupport::IDataForm& dataForm()override{ return _dataForm;	};
  QstwDataForm  _dataForm;
};

#endif // QSTWMESSAGE_H
