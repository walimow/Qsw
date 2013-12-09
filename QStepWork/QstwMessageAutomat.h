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

#ifndef QSWMESSAGEAUTOMAT_H
#define QSWMESSAGEAUTOMAT_H

#include <QObject>

#include <QstwMessage.h>

namespace qstepwork{

//simple association msgid : receptor with ability to add pre / post-objects
//Convention  receptors will be called before processors : return >1000 breaks 
class QstwMessageAutomat : public QObject, public IMessageSupport::IReceptor
{
    Q_OBJECT
    
public:
  /*Qt-based Form (???)
   
   */
    class QReceptor: public QObject, public IMessageSupport::IReceptor
    {
    public:  
      /*virtual*/ int onMessage(const IMessageSupport::IPacket&, int type);
    };
    class QProcessor: public QObject, public IMessageSupport::IReceptor
    {
    public:
      virtual int procMessage(IMessageSupport::IPacket&, int type);  
    };
    
    QstwMessageAutomat();
    ~QstwMessageAutomat();
  int onMessage(const IMessageSupport::IPacket&, int) override;
  int registerReceptor(QReceptor* p, int type);
  int registerProcessor(QProcessor* p, int type);
private:
  
  QPointer<QstwMessageAutomat>	_pre;
  QPointer<QstwMessageAutomat>	_post;
  typedef std::multimap<int, QPointer< QReceptor >> RECS;
  RECS  _mRecs;
  typedef std::multimap<int, QPointer< QProcessor >> PROCS;
  PROCS _mProcs; 
  
};

}

#endif // QSWMESSAGEAUTOMAT_H
