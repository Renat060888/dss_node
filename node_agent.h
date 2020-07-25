#ifndef NODE_AGENT_H
#define NODE_AGENT_H

#include <string>
#include <future>

#include <boost/signals2.hpp>
#include <microservice_common/system/system_environment_facade.h>
#include <dss_common/common/common_types.h>

#include "communication/communication_gateway_facade_node.h"
#include "datasource/source_manager_facade.h"
#include "storage/storage_engine.h"
#include "analyze/analytic_manager_facade.h"

class NodeAgent
{
    static void callbackUnixInterruptSignal();
    static boost::signals2::signal<void()> m_unixInterruptSignal;
public:
    struct SInitSettings {

    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    NodeAgent();
    ~NodeAgent();

    bool init( const SInitSettings & _settings );
    const SState & getState(){ return m_state; }

    void launch();


private:
    void shutdown();
    void shutdownByUnixInterruptSignal();
    void checkForSelfShutdown();

    // data
    SState m_state;
    common_types::SIncomingCommandServices m_commandServices;
    std::atomic<bool> m_shutdownCalled;
    std::future<void> m_selfShutdownFuture;

    // service
    CommunicationGatewayFacadeNode * m_communicateGateway;
    SourceManagerFacade * m_sourceManager;
    AnalyticManagerFacade * m_analyticManager;
    StorageEngineFacade * m_storageEngine;
    SystemEnvironmentFacade * m_systemEnvironment;
};

#endif // NODE_AGENT_H
