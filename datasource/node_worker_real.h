#ifndef NODE_WORKER_REAL_H
#define NODE_WORKER_REAL_H

#include <microservice_common/system/library_loader.h>
#include <dss_common/communication/rti/federate.h>
#include <dss_common/common/common_types.h>

#include "visitor_database_store.h"
#include "visitor_network_notify.h"

class NodeWorkerReal
{
public:
    struct SInitSettings {
        common_types::TNodeId workerId;
        common_types::TContextId ctxId;
        common_types::TMissionId missionId;
    };

    struct SState {
        common_types::SNodeWorkerRealState state;
        SInitSettings settings;
        std::string lastError;
    };

    NodeWorkerReal();
    ~NodeWorkerReal();

    bool init( const SInitSettings & _settings );
    const SState & getState(){ return m_state; }

    bool configure( const common_types::SConfigReal & _cfg );

    bool start();
    void pause();
    void reset();

    void switchLivePlaying( bool _live );


private:



    // data
    SState m_state;
    std::vector<IProcessingObject *> m_processingObjects;


    // service
    LibraryLoader m_libraryLoader;
    VisitorDatabaseStore * m_visitorDatabaseStore;
    VisitorNetworkNotify * m_visitorNetworkNotify;
    rti_client_vega::RTIFederate * m_federate;
};

#endif // NODE_WORKER_REAL_H
