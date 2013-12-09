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

#include "QstwMessageAutomat.h"

namespace qstepwork{
//#include </part/b7/opt/boost_1_52_0/boost/concept_check.hpp>

QstwMessageAutomat::QstwMessageAutomat()
{
}

QstwMessageAutomat::~QstwMessageAutomat()
{
}

/*
 
 */

int QstwMessageAutomat::onMessage(const IMessageSupport::IPacket& oPacket, int type){
  int rc=0;
  auto key = type!=-1 ? type : oPacket.mtype();
  if (_pre){
    rc= _pre->onMessage(oPacket,key);
    if (rc>=rOkFinal || (rc>=rCritical && rc<= rFail ))
      return rc;
  }
  
  auto it  =  _mRecs.find(  key );
  while (it != _mRecs.end() && it->first==key){
    if (it->second){
      rc= _pre->onMessage(oPacket,key);
      if (rc>=rOkFinal || (rc>=rCritical && rc<= rFail ))
	return rc;
    }
  }
  
  auto itP  =  _mProcs.find(  key );
  while (itP != _mProcs.end() && it->first==key){
    if (itP->second){
      rc= _pre->onMessage(oPacket,key);
      if (rc>=rOkFinal || (rc>=rCritical && rc<= rFail ))
	return rc;
    }
  }
  if (_post){
    rc= _post->onMessage(oPacket,key);
    if (rc>=rOkFinal || (rc>=rCritical && rc<= rFail ))
      return rc;
  }
  
  return rc;
}

int QstwMessageAutomat::registerReceptor(QstwMessageAutomat::QReceptor* p, int type){
    _mRecs.insert( RECS::value_type( type, QPointer<QstwMessageAutomat::QReceptor>(p) ));
    return 1;
}
  
int QstwMessageAutomat::registerProcessor(QstwMessageAutomat::QProcessor* p, int type){
  _mProcs.insert( PROCS::value_type(type, p ));
    return 1;
}

}
