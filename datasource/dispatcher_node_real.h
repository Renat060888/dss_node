#ifndef DISPATCHER_NODE_REAL_H
#define DISPATCHER_NODE_REAL_H

#include <map>

#include <dss_common/common/common_types.h>

#include "node_worker_proxy_real.h"

class DispatcherNodeReal : public common_types::INodeDispatcher
{
public:
    struct SInitSettings {
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

    void configureNode( void * _cfg );
    std::vector<PNodeWorkerReal> getNodes();
    PNodeWorkerReal getNode( const common_types::TNodeId & _id );



private:



    // data
    SState m_state;
    std::vector<PNodeWorkerReal> m_nodes;
    std::map<common_types::TNodeId, PNodeWorkerReal> m_nodesById;
    std::vector<std::string> m_newPluginsNames;



};

#endif // DISPATCHER_NODE_REAL_H
