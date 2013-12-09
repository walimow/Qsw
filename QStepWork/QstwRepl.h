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

#ifndef QSTWREPL_H
#define QSTWREPL_H

#include <QObject>
#include <BText.h>

#include <deque>
#include <functional>

using namespace xsxp;

namespace qstepwork {

class QstwRepl : public QObject
{				
    Q_OBJECT

public:
    QstwRepl(QObject* parent=nullptr);
    
    struct Cursor;
    
    struct EnvironmentMapping
    {
       EnvironmentMapping* _pSuper=nullptr;
       Cursor&  _cursor;
       
       EnvironmentMapping(Cursor&  cursor_, EnvironmentMapping* pSuper_)
       :_cursor(cursor_),
       _pSuper(pSuper_){}
    };
    

    struct Result
    {
      int           _value=0;
      BText::IdType _id=0;
    };
    
    struct Position
    {
      int _irStatus=0;  //result
      BText::IdType  _idConnected=0;   //none, strMap, QVarMap, 
      //QVariant	_data;  //pure qvariant
      int _iiStatus=0;  //internal info about connected/linked/stored type
      
    };
    
    
    typedef Result (Fnc) (const BText::Sxpr& text, EnvironmentMapping& e);
    
    
    struct Cursor
    {
      
      Result  			_result;
      
      EnvironmentMapping*  _pEnvironment=nullptr;
      Cursor*  _Super=nullptr;
      
      std::function<int(void)> _pfPrequest;
      std::function<int(void)> _pfPrepare;
      std::function<int(void)> _pfPerform;
      std::function<int(void)> _pfPost;
      
      std::function<int(void)> _pfFail;
      std::function<int(void)> _pfContinuation;
       
      int apply(BText::Sxpr& text);
    };
    
    struct Corpus
    {
      
      std::vector<Position> 	_signatur;  
      EnvironmentMapping _env;
    };

    
private:
      std::deque<std::pair<int, Result >> _stack;
    std::vector<Cursor> _cursorStack;
};

}

#endif // QSTWREPL_H
