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

#ifndef QSTWBTEXTPARSER_H
#define QSTWBTEXTPARSER_H

#include <QObject>

namespace qstepwork {

  typedef unsigned long long Siid;
  
class QstwBTextParser : public QObject
{
    Q_OBJECT

public:
  class Cell
  {
    Siid _siid;
    //Status (FValue, 
  public:
    
  };
  QstwBTextParser();
   ~QstwBTextParser();

private:

};

}

#endif // QSTWBTEXTPARSER_H
