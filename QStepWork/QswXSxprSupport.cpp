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

#include "QswXSxprSupport.h"
#include <QstwDataForm.h>

#include <sstream>
#include <stdexcept>

namespace qstepwork {

QswXSxprSupport::QswXSxprSupport(QObject*pParent):QObject(pParent)
{

}

QswXSxprSupport::QswXSxprSupport(const QswXSxprSupport& other)
{

}

QswXSxprSupport::~QswXSxprSupport()
{

}

BText::Sxpr		QswXSxprSupport::_sxspNull;

QswXSxprSupport& QswXSxprSupport::operator=(const QswXSxprSupport& other)
{

    return *this;
}
 std::pair<bool, std::deque<BText::IdType>>  QswXSxprSupport::selectPath( BText::IdType id,  const BText::Sxpr& src){
  //bottom->src
  std::deque<BText::IdType> v;
  bool bSelect=false;
  BText::IdType i= id;
  do{
    v.push_front(i);
    i= this->_child2super[i];
    if (i==src._id)
      bSelect=true;
    if (bSelect || !i)
      break;
    
  } while(1);
  return std::pair<bool, std::deque<BText::IdType>> (bSelect , v);
};

std::vector<BText::IdType>	QswXSxprSupport::child_ids(BText::IdType id){
  std::vector<BText::IdType>	ret;
   auto ic =  _super2child.find(id);
   while (ic != _super2child.end() && (*ic).first ==id)
     ret.push_back((*ic++).second);
   return ret;
};

BText::Sxpr*  QswXSxprSupport::element(const BText::IdType id,const BText::Sxpr& src){
  auto ret_path = selectPath(  id,   src);
  if (ret_path.first){
    return selectElement( src, ret_path.second);
  }
  else
    return nullptr;
  
}

BText::Sxpr*  QswXSxprSupport::selectChildElement(const BText::Sxpr& src,const BText::IdType id){
  for (auto& e: src._inner){
    if (e._id== id)
      return (BText::Sxpr*) &e;
  }
  return nullptr;
};

BText::Sxpr*  QswXSxprSupport::selectElement(const BText::Sxpr& src,const std::deque<BText::IdType>&v){
  BText::Sxpr*  pcurr=(BText::Sxpr*)&src;
  for (auto i: v){
      pcurr=  selectChildElement(*pcurr, i);
      if (!pcurr)
	return nullptr;
  }
  return pcurr;
};

BText::Sxpr QswXSxprSupport::document (const std::string& s) {

    //_btext.setText(s);
    auto lst =  _btext.GetHeadTailList(s);
    if (lst._inner.size()) {
        for (auto c: lst._inner) {
            registerParentChild( lst._id,c);
        }
        return lst;
    }

    return _sxspNull;

};

QswXSxprSupport::BaseForm  _defaultDataForm;

int QswXSxprSupport::BaseForm::formData(IMessageSupport::IDataForm& dest , const BText::Sxpr& xpr) {
  //name
  std::string sName = xpr._sPre;
  std::string sValue = "";
  std::string sExtra = "";
  int sz=xpr._inner.size();
  if (sz){
    BText::Sxpr::Inner::const_iterator it = xpr._inner.begin();
    sValue =  it->_sPre;
    if (sz>1){
      sExtra= (++it)->_sPre;
    }
    ///
    if (sValue.size()){
      switch (sValue[0]){
	case '"':
	  //string
	  applyString(dest,sName,sValue);
	  break;
	case '\\':
	  //esc weglassen
	  applyString(dest,sName,sValue,false);
	  break;
	case '0':
	{
	  long long v=0;
	  if (str2num( v, sValue, std::ios::hex))
	    applyNum( dest, sName,  v);
	  else
	    throw std::runtime_error ("cannot convert to (hex)num: "+sValue+" in  QswXSxprSupport::BaseForm::formData");
	}
	  break;  
	default:
	  if (isdigit(sValue[0])){
	    long long v=0;
	    if (str2num( v, sValue ))
	      applyNum( dest, sName,  v);
	    else
	      throw std::runtime_error ("cannot convert to num: "+sValue+ " in QswXSxprSupport::BaseForm::formData");
	    
	  }
	  else
	  {
	    applyString(dest,sName,sValue);
	  }
	
      }
    }
  }
    
  return 1;
}


bool QswXSxprSupport::BaseForm::str2num(long long& dest ,const std::string& s, std::ios_base::fmtflags flags_){
  std::istringstream ist(s);
  long long v =0;
  ist.flags(flags_)  ;
  return ist>>v;
 
};

void QswXSxprSupport::BaseForm::applyNum(IMessageSupport::IDataForm& dest ,const std::string& sKey, long long v){
  dest.setNum(sKey,v);
}

void QswXSxprSupport::BaseForm::applyString(IMessageSupport::IDataForm& dest ,const std::string& sKey, const std::string& s, bool bAutoRemoveDelimiter){
  if (bAutoRemoveDelimiter){
    if (s.size()>1 && s[0]=='"'&& s[s.size()-1]=='"')
      dest.setString(sKey, s.substr(1,s.size()-2));

  }
    else
      dest.setString(sKey, s);
      
}


int QswXSxprSupport::loadDataForm(IMessageSupport::IDataForm& f, const BText::Sxpr& sxpr,IDataFormer& former) {
    return former.formData(f, sxpr);
};

int QswXSxprSupport::registerParentChild(BText::IdType idParent, BText::Sxpr& child) {
    int rc=1;
    auto id = child._id;
    _child2super[id] = idParent;
    _super2child.insert( Super2ChildType::value_type(  idParent,id));
    for (auto c: child._inner) {
        rc+=registerParentChild(id,c);
    }
    return rc;
};



IMessageSupport::IDataForm::DataFormType QswXSxprSupport::DataForm::form(const std::string& s)const {
    bool bNum = _mll.find(s) != _mll.end();
    bool bStr = _mstr.find(s) != _mstr.end();
    if (bNum)
        return bStr ? combi : num;
    else
        return bStr ? str : none;
}

std::string QswXSxprSupport::DataForm::getString(const std::string& s,const std::string& sDefault)const {
    auto v = _mstr.find(s);
    return  v!= _mstr.end() ? (*v).second : sDefault;
}


long long   QswXSxprSupport::DataForm::getNum(const std::string& s, long long llDefault)const {
    auto v = _mll.find(s);
    return  v!= _mll.end() ? (*v).second : llDefault;
}



void QswXSxprSupport::DataForm::setString(const std::string& s,const std::string& v) {
    _mstr[s]=v;
}

void QswXSxprSupport::DataForm::setNum(const std::string& s,long long  v) {
    _mll[s]=v;
}

int QswXSxprSupport::DataForm::_toDest(IDataForm& dest) {
    int rc=0;
    for(auto it: _mstr) {
        dest.setString(it.first,it.second);
        rc++;
    }

    for(auto itLL: _mll) {
        dest.setNum(itLL.first,itLL.second);
        rc++;
    }
    return rc;
}


}
