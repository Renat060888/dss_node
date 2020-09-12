#ifndef DISPATCHER_NODE_SIMULATION_H
#define DISPATCHER_NODE_SIMULATION_H

#include <map>

#include <dss_common/common/common_types.h>

#include "node_proxy_worker_simulation.h"

class DispatcherNodeSimulation : public common_types::INodeDispatcher
{
    friend class CommandNodeWorkerPing;
public:
    struct SInitSettings {
        common_types::TNodeId nodeAgentId;
        common_types::IServiceInternalCommunication * internalCommunication;
    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    DispatcherNodeSimulation();
    ~DispatcherNodeSimulation();

    bool init( const SInitSettings & _settings );
    const SState & getState(){ return m_state; }
    virtual void runSystemClock() override;

    // simulation nodes initiated from client -> system
    bool requestNode( common_types::TContextId _ctxId, common_types::TMissionId _missioinId );
    void releaseNode( const common_types::TNodeId & _id );

    const std::vector<PNodeProxyWorkerSimulation> & getNodes();
    PNodeProxyWorkerSimulation getNode( const common_types::TNodeId & _id );


private:
    void updateWorker( const common_types::SNodeWorkerSimulationState & _workerState );



    // data
    SState m_state;
    std::vector<PNodeProxyWorkerSimulation> m_nodes;
    std::map<common_types::TNodeId, PNodeProxyWorkerSimulation> m_nodesById;
    std::map<common_types::TContextId, PNodeProxyWorkerSimulation> m_nodesByContextId;


};

#endif // DISPATCHER_NODE_SIMULATION_H
