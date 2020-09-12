#ifndef I_PROCESSING_OBJECT_H
#define I_PROCESSING_OBJECT_H

#include <dss_common/common/common_types.h>

// visitor
class IVisitorProcessingObject {
public:
    virtual void visit( class ProcessingObjectTrajectory * _obj ) = 0;
    virtual void visit( class ProcessingObjectWeather * _obj ) = 0;
};


// interface
class IProcessingObject
{
public:
    IProcessingObject();

    virtual void accept( IVisitorProcessingObject * _visitor ) = 0;
    virtual void makeStep( common_types::TLogicStep _step ) = 0;
};

#endif // I_PROCESSING_OBJECT_H
