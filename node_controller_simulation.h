#ifndef NODE_CONTROLLER_SIMULATION_H
#define NODE_CONTROLLER_SIMULATION_H

#include <microservice_common/communication/network_interface.h>
#include <dss_common/common/common_types.h>

#include "datasource/node_worker_simulation.h"

class NodeControllerSimulation : public INetworkObserver
{
public:
    struct SInitSettings {
        common_types::TNodeId workerId;
        common_types::TNodeId agentId;
        common_types::TContextId ctxId;
        common_types::TMissionId missionId;
    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    NodeControllerSimulation();

    bool init( const SInitSettings & _settings );
    void launch();


private:
    virtual void callbackNetworkRequest( PEnvironmentRequest _request ) override;

    PNetworkClient connectToNetwork( const common_types::TNodeId & _id, const common_types::TNodeId & _agentId );

    void processMessageConfigure();

    void processMessageStart();
    void processMessagePause();
    void processMessageStop();

    void processMessageSwitchLiveProcessing();
    void processMessageUseRTI();


    // data
    SState m_state;
    NodeWorkerSimulation m_worker;
    bool m_shutdownCalled;
    int64_t m_lastPingAtMillisec;


    // service
    PNetworkClient m_networkWithAgent;
    PNetworkProvider m_networkProvider;
    PEnvironmentRequest m_pingRequest;

};

#endif // NODE_CONTROLLER_SIMULATION_H
