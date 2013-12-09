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

#include "QstwProcessor.h"
#include <exception>

#include <QstwEnvironment.h>

namespace qstepwork{

QstwProcessor::QstwProcessor(IEnvironment&e):_env(e)
{
    _return=0;
    _oPos= undefined;
    _iPos = before_pos;
    
    _pEnvImmediate=&_env;
}

int QstwProcessor::call_step(IStepSupport&o, QstwDataForm& list ){
    //local attributes als middle-environment
  QstwEnvironment* pqe = dynamic_cast<QstwEnvironment*>(&_env);
    
  _pEnvImmediate =  QstwEnvironment::createEnvironment(list,"@.immedate.env", pqe);
  
  return step(o);
  
}

int QstwProcessor::step(IStepSupport& o){
  _return=0;

  try{
    _oPos= undefined;
    _iPos = before_pos;
    IStepSupport& oInst =  o.enter_instance(*_pEnvImmediate);
    
    _oPos=preq;
    _iPos= on_pos;
    _return = oInst.prequest();
    _iPos= post_pos;
    if (_return<=0)
      return _return;
    
    _oPos= prep;
    _iPos= on_pos;
    
    _return = oInst.prepare();
    _iPos= post_pos;
    if (_return>=0){
      _iPos= on_pos;  
      _return= oInst.perform();
      _iPos= post_pos;	
      if (_return<0){
	_oPos= fail;
	_iPos= on_pos;	
	IFailSupport* pFailSupport = dynamic_cast<IFailSupport*>(&oInst);
	if (pFailSupport){
	  if (pFailSupport->canReset()){
	    _oPos= reset;
	    _iPos= on_pos;
	    _return = pFailSupport->reset();
	    _iPos= post_pos;
	  }
	  
	}
	_oPos=post;
	oInst.post(_return);
      }
      
    }
  }
  catch(std::exception& x){
    //defined exception
  }
  catch(...){
    //undefined
  }
  return _return;
}

}

//#include "QstwProcessor.moc"
