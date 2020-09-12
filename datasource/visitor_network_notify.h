#ifndef VISITOR_NETWORK_NOTIFY_H
#define VISITOR_NETWORK_NOTIFY_H

#include "processing_object_trajectory.h"
#include "processing_object_weather.h"

class VisitorNetworkNotify : public IVisitorProcessingObject
{
public:
    VisitorNetworkNotify();

    void batchNotify();

private:
    virtual void visit( ProcessingObjectTrajectory * _obj ) override;
    virtual void visit( ProcessingObjectWeather * _obj ) override;
};

#endif // VISITOR_NETWORK_NOTIFY_H
