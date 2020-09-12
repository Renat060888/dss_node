#ifndef DISPATCHER_NODE_REAL_H
#define DISPATCHER_NODE_REAL_H

#include <map>

#include <dss_common/common/common_types.h>

#include "node_proxy_worker_real.h"

class DispatcherNodeReal : public common_types::INodeDispatcher
                         , public INodeWorkerRealObserver
{
public:
    struct SInitSettings {
        SInitSettings()
            : internalCommunication(nullptr)
        {}
        common_types::TNodeId nodeAgentId;
        common_types::IServiceInternalCommunication * internalCommunication;
        std::vector<std::string> pluginNames;
    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    DispatcherNodeReal();
    ~DispatcherNodeReal();

    bool init( const SInitSettings & _settings );
    const SState & getState(){ return m_state; }
    virtual void runSystemClock() override;

    void addPluginName( const std::string & _pluginName );

    const std::vector<PNodeWorkerReal> & getNodes();
    PNodeWorkerReal getNode( const common_types::TNodeId & _id );



private:
    virtual void callbackNodeContextChanged( common_types::TNodeId _nodeId, common_types::TContextId _ctxId ) override;

    // real nodes initiated from system -> client
    bool requestNode( common_types::TContextId _ctxId,
                      common_types::TMissionId _missioinId,
                      const common_types::SNodeWorkerRealState & _initialState );
    void releaseNode( const common_types::TNodeId & _id );

    std::string getCaps( const std::string & _pluginName );


    // data
    SState m_state;
    std::vector<PNodeWorkerReal> m_nodes;
    std::map<common_types::TNodeId, PNodeWorkerReal> m_nodesById;
    std::map<common_types::TNodeId, PNodeWorkerReal> m_fakeNodesById;
    std::vector<std::string> m_newPluginsNames;



};

#endif // DISPATCHER_NODE_REAL_H
