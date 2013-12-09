#ifndef QSTEP_WORK_ABSTRACT__H_
#define QSTEP_WORK_ABSTRACT__H_		1

#include <QObject>
#include <QPointer>

namespace qstepwork{
  
  typedef enum StepState{noState=0, initialized, prepared, performed, postperf, invalidated }StepState;
  typedef enum StepSuccessState{noSuccessState=0, ok, failed=-1}StepSuccessState;
  
  typedef enum { rNoError=0, rOk=1, rModified=2,
      rHandled=-1, 
      rOkFinal=1000, rCritical=-2000 , rFail=-1000   //Break
    } Defines;
  
  class IEnvironment;
  
  class IStepSupport
  {
  public:
    virtual StepState stepState()=0;
    virtual StepSuccessState stepSuccessState()=0;
    virtual ~IStepSupport(){}
   
    
    virtual IStepSupport& enter_instance(IEnvironment&)=0;
    virtual void leave_instance()=0;
    
    virtual int prequest()=0;
    virtual int prepare()=0;
    virtual int perform()=0;
    virtual void post(int)=0;
  };
  
  
  class IStwProcessor
  {
  public:
    typedef enum OuterPosition { undefined, preq, prep,perf,post, fail, reset,off} OuterPosition;
    typedef enum InnerPosition { before_pos, on_pos,post_pos} InnerPosition;    
    
    virtual OuterPosition oPos()=0;
    virtual InnerPosition iPos()=0;
    virtual operator int()=0;   
    virtual int step(IStepSupport&o)=0;
  };

  class IFailSupport
  {
    public:
    virtual ~IFailSupport(){}
    virtual int onStepFailed()=0;
    virtual bool canReset()=0;
    virtual int reset()=0;
  };
  
  class IEnvironment
  {
  public:
    
     class IEntry
     {
     public:
       typedef enum{ et_empty, et_data, et_obj, et_passiv, et_activ} Type;
       virtual ~IEntry(){}
       
       virtual const QString& name()const=0;
       
       virtual void assignData(const QVariant&v)=0;
       virtual QVariant&  data()=0;
       virtual QObject* obj()=0;
       virtual void setObj(QObject*)=0;
        
     };
     virtual ~IEnvironment(){}
     virtual bool hasEntry(const std::string&, bool bHierarch=false)=0;
     virtual IEntry& entry(const std::string&, bool bHierarch=false)=0;
     virtual IEntry& operator[](const std::string&)=0;
     virtual IEnvironment* superEnvironment()=0;
     virtual unsigned int  size()=0;
     virtual void  clearEnvironment()=0;
  };
  
  class IMessageSupport
  {
  public:
    
    
    class IDataForm
    {
    public:
      
      virtual ~IDataForm(){}
      typedef enum {none,  num, str, combi} DataFormType;
      virtual DataFormType form(const std::string& s)const=0;
      virtual std::string getString(const std::string& s,const std::string& sDefault="")const=0;      
      virtual long long   getNum(const std::string& s, long long llDefault=0)const=0;

      virtual void setString(const std::string& s,const std::string& v)=0;
      virtual void setNum(const std::string& s,long long  v)=0;
      virtual int _toDest(IDataForm&)=0;
      
      virtual void clear()=0;
    };
    ///Datenpaket (+ Info?)
    class IPacket
    {
    public:
      virtual const IDataForm& dataForm()=0;
      virtual const int mtype() const=0;
      virtual const unsigned long long curr() const=0;
      virtual ~IPacket(){}
    };
    ///
    class IReceptor
    {
    public:
      virtual ~IReceptor(){}
      virtual int onMessage(const IPacket&, int type)=0;  //Packeges should be copied
    };
    class IProcessor
    {
    public:
      virtual ~IProcessor(){}
      virtual int procMessage(IPacket&,  int type)=0;  //Packeges can be consumed/changed
    };
    
  };
}

#endif