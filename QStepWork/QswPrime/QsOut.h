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

#ifndef QSOUT_H
#define QSOUT_H

#include <QObject>
//#include </part/b7/opt/boost_1_52_0/boost/concept_check.hpp>
#include <QstwEnvironment.h>
#include <QstwStepObjectBase.h>

using namespace qstepwork;

namespace qswPrim{

//Outpot event with state to Environment
class QsOut: public QstwStepObjectBase
{
  Q_OBJECT
  Q_PROPERTY(int opt READ option   WRITE setOption )
  
  int		_opt=0;
  
  Q_PROPERTY(QString text READ text   WRITE setText )
  QString	_text="";
public:
    QsOut();
    ~QsOut();
    
    inline int option()const{ return _opt;}
    inline void setOption(int v){ _text=v;} 
    
    inline QString text()const{ return _text;}
    inline void setText(const QString& v){ _text=v;} 

    ///pppp
    int prequest()override;
    int prepare()override;
    int perform()override;
    void post(int)override;
    
};
}

#endif // QSOUT_H
