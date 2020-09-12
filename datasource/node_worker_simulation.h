#ifndef NODE_WORKER_SIMULATION_H
#define NODE_WORKER_SIMULATION_H

#include <thread>

#include <microservice_common/system/library_loader.h>
#include <dss_common/communication/rti/federate.h>
#include <dss_common/common/common_types.h>

#include "visitor_database_store.h"
#include "visitor_network_notify.h"

class NodeWorkerSimulation
{
public:
    struct SInitSettings {
        common_types::TNodeId workerId;
        common_types::TContextId ctxId;
        common_types::TMissionId missionId;
    };

    struct SState {
        common_types::SNodeWorkerSimulationState state;
        SInitSettings settings;
        std::string lastError;
    };

    NodeWorkerSimulation();
    ~NodeWorkerSimulation();

    bool init( const SInitSettings & _settings );
    const SState & getState(){ return m_state; }

    bool configure( const common_types::SConfigSimulation & _cfg );

    bool start();
    void pause();
    void stop();

    void switchLivePlaying( bool _live );
    void useRTI( bool _use );


private:
    void threadObjectsProcessing();

    bool prepareObjects();
    bool initRTI();


    // data
    SState m_state;
    int64_t m_stepToSimulateCount;
    bool m_livePlaying;
    bool m_useRTI;
    std::vector<IProcessingObject *> m_processingObjects;
    bool m_shutdownCalled;

    // service
    LibraryLoader m_libraryLoader;
    rti_client_vega::RTIFederate * m_federate;
    VisitorDatabaseStore * m_visitorDatabaseStore;
    VisitorNetworkNotify * m_visitorNetworkNotify;
    DatabaseManagerBase * m_database;
    std::thread * m_trObjectsProcessing;
    std::condition_variable m_cvObjectsProcessing;
};

#endif // NODE_WORKER_SIMULATION_H
