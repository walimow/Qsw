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

#ifndef QSWXSXPSUPPORT_H
#define QSWXSXPSUPPORT_H

#include <BText.h>
#include <map>
#include <deque>
#include <QObject>
#include <QStepWalk.h>

using namespace xsxp;

namespace qstepwork{
  
class IDataFormer
      {
      public:
	virtual int formData(IMessageSupport::IDataForm& dest , const BText::Sxpr& )=0;
      };  

///Support to an extended s-expression (with itemid and stored attributes/links in this registrylike supportobject  
class QswXSxprSupport: public QObject
{
  
public:
  Q_OBJECT
  ///non qt-dataform (copyable):
class DataForm :  public IMessageSupport::IDataForm
{
      
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

};

  static BText::Sxpr		_sxspNull;
private:  
  BText  _btext;
    
  std::map<BText::IdType,BText::IdType> 	_child2super;
  typedef std::multimap<BText::IdType,BText::IdType>	Super2ChildType;
  Super2ChildType	_super2child;
  std::map<BText::IdType,DataForm>		 _m2dataFormIndex;   //additional to an elaboted interpretation (as idea,for future)
  int registerParentChild(BText::IdType idParent, BText::Sxpr& child);
  
public:
  std::pair<bool, std::deque<BText::IdType>>  selectPath( BText::IdType id,  const BText::Sxpr& src);
   BText::Sxpr*  selectElement(const BText::Sxpr& src,const std::deque<BText::IdType>&);
   BText::Sxpr*  selectChildElement(const BText::Sxpr& src,const BText::IdType);
   BText::Sxpr*  element(const BText::IdType,const BText::Sxpr& src);  
   std::vector<BText::IdType>	child_ids(BText::IdType);
   BText::IdType		super_id(BText::IdType id){ return _child2super[id];}
   
   
   
  class BaseForm:  public IDataFormer
  {
  public:
     
      bool str2num(long long& dest ,const std::string&, std::ios_base::fmtflags flags= std::ios::dec);
      void applyNum(IMessageSupport::IDataForm& dest ,const std::string& sKey, long long v);
      void applyString(IMessageSupport::IDataForm& dest ,const std::string& sKey, const std::string& v, bool bAutoRemoveDElimiter=true);
      int formData(IMessageSupport::IDataForm& dest , const BText::Sxpr& ) override;
      static BaseForm _defaultDataForm;
  };
    QswXSxprSupport( QObject*pParent=nullptr);
    QswXSxprSupport(const QswXSxprSupport& other);
    ~QswXSxprSupport();
    QswXSxprSupport& operator=(const QswXSxprSupport& other);
    
    BText::Sxpr document(const std::string& );

    
      inline void clear(){
	_child2super.clear();
	_super2child.clear();
	_m2dataFormIndex.clear();
      }
    int loadDataForm(IMessageSupport::IDataForm& f , const BText::Sxpr& sxpr, IDataFormer& former=BaseForm::_defaultDataForm);
};

}

#endif // QSWXSXPSUPPORT_H
