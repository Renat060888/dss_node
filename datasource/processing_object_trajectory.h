#ifndef PROCESSING_OBJECT_TRAJECTORY_H
#define PROCESSING_OBJECT_TRAJECTORY_H

#include "i_processing_object.h"

class ProcessingObjectTrajectory : public IProcessingObject
{
public:
    ProcessingObjectTrajectory();

    virtual void accept( IVisitorProcessingObject * _visitor ) override;
    virtual void makeStep( common_types::TLogicStep _step ) override;


private:



    // objrepr + plugin-model
};

#endif // PROCESSING_OBJECT_TRAJECTORY_H
