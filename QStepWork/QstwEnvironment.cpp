/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
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

#include <QstwDataForm.h>
#include "QstwEnvironment.h"
#include <QSharedData>
#include <iostream>



namespace qstepwork{

   QstwEnvironment::Entry    QstwEnvironment::nullEntry;
   
   QstwEnvironment::QstwEnvironment(){
     
  };
  
  QstwEnvironment::~QstwEnvironment(){
    //std::cout<<"QstwEnvironment::~QstwEnvironment()";
  };
   
  QstwEnvironment::QstwEnvironment(QObject* parent):QObject(parent){
    
  };

  bool QstwEnvironment::hasEntry(const QString& name, bool bHier){
  
};

  bool QstwEnvironment::hasEntry(const std::string&, bool bHierarch){
    
  }    
  
  IEnvironment::IEntry& QstwEnvironment::entry(const std::string&, bool bHierarch){
    
  }    
  
  IEnvironment::IEntry& QstwEnvironment::operator[](const std::string&){
    
  };
  
  IEnvironment* QstwEnvironment::superEnvironment(){
    
  }    
  
  //with pSuper as (QObject)Parent
  QstwEnvironment * QstwEnvironment::createEnvironment( QstwDataForm& list, const QString& s, QstwEnvironment *pSuper){
    QstwEnvironment* pReturn = new QstwEnvironment(pSuper);
    
    for(auto s2s: list._mstr){
      pReturn->setEntry<QString>( s2s.first.c_str(), s2s.second.c_str());
      
    }
    for(auto s2ll: list._mll){
      pReturn->setEntry<long long>( s2ll.first.c_str(), s2ll.second);
    }
    
    //pReturn->setParent(pSuper);
    
    return pReturn;
    
  }


  const QstwEnvironment::Entry&	QstwEnvironment::getEntry(const QString& name, bool bHier, const QstwEnvironment::Entry& _default){
  
};


}