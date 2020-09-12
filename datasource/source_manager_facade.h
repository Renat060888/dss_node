#ifndef SOURCE_MANAGER_H
#define SOURCE_MANAGER_H

#include <thread>

#include <microservice_common/system/library_loader.h>
#include <dss_common/common/common_types.h>

#include "dispatcher_node_simulation.h"
#include "dispatcher_node_real.h"

class SourceManagerFacade
{
public:
    struct SInitSettings {
        common_types::TNodeId agentId;
        common_types::IServiceInternalCommunication * serviceInternalCommunication;
    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    SourceManagerFacade();
    ~SourceManagerFacade();

    bool init( const SInitSettings & _settings );
    void shutdown();

    // REQUEST FROM CORE
    DispatcherNodeSimulation * getSimulaDispatcher();
    DispatcherNodeReal * getRealDispatcher();


private:
    void threadMaintenance();

    bool initSimulationMode( const SInitSettings & _settings );
    bool initRealMode( const SInitSettings & _settings );
    bool initDumpMode( const SInitSettings & _settings );

    // RESPONSE TO CORE
    inline void pingCore();
    std::string serializeSimulationMode();
    std::string serializeRealMode();
    std::string serializeDumpMode();

    void refreshPluginLibs();


    // data
    SState m_state;
    bool m_shutdownCalled;    

    // service
    PNetworkClient m_networkWithCore;
    LibraryLoader m_libraryLoader;  
    std::thread * m_threadMaintenance;

    common_types::INodeDispatcher * m_dispatcher;
    DispatcherNodeSimulation * m_dispatcherNodeSimulation;
    DispatcherNodeReal * m_dispatcherNodeReal;
};

#endif // SOURCE_MANAGER_H
