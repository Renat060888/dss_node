#ifndef DISPATCHER_NODE_SIMULATION_H
#define DISPATCHER_NODE_SIMULATION_H

#include <dss_common/common/common_types.h>

class DispatcherNodeSimulation : public common_types::INodeDispatcher
{
public:
    DispatcherNodeSimulation();

    virtual void runSystemClock() override;


private:




};

#endif // DISPATCHER_NODE_SIMULATION_H
