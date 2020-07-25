#ifndef COMMUNICATION_GAREWAY_FACADE_DSS_H
#define COMMUNICATION_GAREWAY_FACADE_DSS_H

#include <microservice_common/communication/communication_gateway_facade.h>
#include <dss_common/common/common_types.h>

class CommunicationGatewayFacadeNode    : public CommunicationGatewayFacade
                                        , public common_types::IServiceInternalCommunication
{
public:
    struct SInitSettings : CommunicationGatewayFacade::SInitSettings {
        common_types::SIncomingCommandServices services;
        common_types::TNodeId nodeAgentId;
    };

    CommunicationGatewayFacadeNode();
    ~CommunicationGatewayFacadeNode();

    bool init( const SInitSettings & _settings );

    common_types::IServiceInternalCommunication * serviceForInternalCommunication();


private:
    // internal
    virtual PNetworkClient getCoreCommunicator() override;
    virtual PNetworkClient getNodeWorkerCommunicator( const std::string & _uniqueId ) override;

    // data
    SInitSettings m_settings;
    std::string m_lastError;

    // service
    PNetworkClient m_coreCommunicator;
    std::map<std::string, PNetworkClient> m_nodeWorkerCommunicatorsById;

};

#endif // COMMUNICATION_GAREWAY_FACADE_DSS_H
