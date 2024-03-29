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

#ifndef QSTWPROCESSOR_H
#define QSTWPROCESSOR_H

#include <QtCore/QObject>
#include <QStepWalk.h>
#include <QstwForward.h>

namespace qstepwork{

  
class QstwProcessor : public QObject, public IStwProcessor
{
    Q_OBJECT
    IEnvironment& _env;
    IEnvironment*  _pEnvImmediate;
    int 	_return;
    OuterPosition _oPos;
    InnerPosition _iPos;    
public:
    QstwProcessor(IEnvironment&);
    operator int()override{ return _return;}
    OuterPosition oPos()override  { return  _oPos;}
    InnerPosition iPos() override { return _iPos;}
    int step(IStepSupport&o)override;
    int call_step(IStepSupport&o, QstwDataForm& list );
private:
    

};

}

#endif // QSTWPROCESSOR_H
