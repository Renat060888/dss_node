#ifndef NODE_WORKER_PROXY_SIMULATION_H
#define NODE_WORKER_PROXY_SIMULATION_H

#include <dss_common/common/common_types.h>

class NodeProxyWorkerSimulation
{
    friend class DispatcherNodeSimulation;
public:
    NodeProxyWorkerSimulation();
    ~NodeProxyWorkerSimulation();

    const common_types::SNodeWorkerSimulationState & getState();

    bool configure( const common_types::SConfigSimulation & _cfg );
    void shutdown();

    bool start();
    bool pause();
    bool reset();

    void switchLivePlaying( bool _live );
    void useRTI( bool _use );


private:
    void updateState( const common_types::SNodeWorkerSimulationState & _workerState );


    // data
    common_types::SNodeWorkerSimulationState m_state;


};
using PNodeProxyWorkerSimulation = std::shared_ptr<NodeProxyWorkerSimulation>;

#endif // NODE_WORKER_PROXY_SIMULATION_H
