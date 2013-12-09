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

#include "QstwDataForm.h"
//#include </part/b7/opt/boost_1_52_0/boost/concept_check.hpp>

namespace qstepwork {

  IMessageSupport::IDataForm::DataFormType QstwDataForm::form(const std::string& s)const {
    bool bNum = _mll.find(s) != _mll.end();
    bool bStr = _mstr.find(s) != _mstr.end();
    if (bNum)
      return bStr ? combi : num;
    else
      return bStr ? str : none;
  }
      
  std::string QstwDataForm::getString(const std::string& s,const std::string& sDefault)const {
    auto v = _mstr.find(s);
    return  v!= _mstr.end() ? (*v).second : sDefault;
  }
      
      
  long long   QstwDataForm::getNum(const std::string& s, long long llDefault)const {
    auto v = _mll.find(s);
    return  v!= _mll.end() ? (*v).second : llDefault;
  }
  
  
      
      void QstwDataForm::setString(const std::string& s,const std::string& v){
    _mstr[s]=v;
  }
      
      void QstwDataForm::setNum(const std::string& s,long long  v){
    _mll[s]=v;
  }
      
      int QstwDataForm::_toDest(IDataForm& dest){
	int rc=0;
	for(auto it: _mstr){
	  dest.setString(it.first,it.second);
	  rc++;
	}
	 
	for(auto itLL: _mll){
	  dest.setNum(itLL.first,itLL.second);
	  rc++;
	}
    return rc;
  }
  
  
     
  
  
  
  /*
  QstwDataForm  mkFormFromLime(const std::string& s)   //simple interpretation if isNum-> num, else str)
  {
    //qt
    QstwDataForm  oReturn;
    
    return oReturn;
    
  }*/

}
//#include "QstwDataForm.moc"
