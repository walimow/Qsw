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

#ifndef QSWDATAFORM_H
#define QSWDATAFORM_H

#include <QObject>
#include <QStepWalk.h>

#include <string>
#include <map>
#include <BText.h>

using namespace xsxp;

namespace qstepwork {

///minimalistic data Packet, qt-based, data(types) can be longlong( num) or string  or both (with userdefined meaning)

  
  
class QstwDataForm : public QObject, public IMessageSupport::IDataForm
{
    Q_OBJECT

      
public:
      std::map<std::string,std::string> _mstr;
      std::map<std::string,long long> _mll;
      std::map<std::string,std::string> _minfo;   //additional to an elaboted interpretation (as idea,for future)
   
      DataFormType form(const std::string& s)const override;
      std::string getString(const std::string& s,const std::string& sDefault="")const override;
      long long   getNum(const std::string& s, long long llDefault=0)const override;
      
      
      void setString(const std::string& s,const std::string& v)override;
      void setNum(const std::string& s,long long  v)override;
      
      void clear()override{
	_minfo.clear();
	_mll.clear();
	_minfo.clear();
      }
      int _toDest(IDataForm&)override;
      
       //public IMessageSupport::IDataForm
      ///defaultFormer
      
      
      

};

      
//QstwDataForm  mkFormFromLime(const std::string& s);   //simple interpretation if isNum-> num, else str)

}

#endif // QSWDATAFORM_H
