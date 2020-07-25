
#include <microservice_common/communication/amqp_client_c.h>
#include <dss_common/common/common_utils.h>

#include "system/config_reader.h"
#include "command_factory.h"
#include "communication_gateway_facade_node.h"

using namespace std;

CommunicationGatewayFacadeNode::CommunicationGatewayFacadeNode()
    : CommunicationGatewayFacade()
{

}

CommunicationGatewayFacadeNode::~CommunicationGatewayFacadeNode(){

}

bool CommunicationGatewayFacadeNode::init( const SInitSettings & _settings ){

    const string nodeAgentName = string("simula_ip") + common_utils::getIpAddressStr() + string("_pid") + std::to_string( ::getpid() );
    // TODO: or simply generate uuid ?

    SAmqpRouteParameters initialRoute;
    initialRoute.predatorExchangePointName = "dss_dx_node_agents";
    initialRoute.predatorQueueName = "dss_q_node_agent_mailbox_" + nodeAgentName;
    initialRoute.predatorRoutingKeyName = "dss_rk_to_node_agent_" + nodeAgentName;
    initialRoute.targetExchangePointName = "dss_dx_core";
    initialRoute.targetRoutingKeyName = "dss_rk_to_core";


    m_settings = _settings;
    m_settings.paramsForInitialAmqp.route = initialRoute;
    m_settings.paramsForInitialAmqp.enable = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_ENABLE;
    m_settings.paramsForInitialAmqp.host = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_SERVER_HOST;
    m_settings.paramsForInitialAmqp.virtHost = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_VIRTUAL_HOST;
    m_settings.paramsForInitialAmqp.port = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_SERVER_PORT;
    m_settings.paramsForInitialAmqp.login = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_LOGIN;
    m_settings.paramsForInitialAmqp.pass = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_PASS;
    m_settings.specParams.factory = new CommandFactory( m_settings.services );

    if( ! CommunicationGatewayFacade::init(m_settings) ){
        return false;
    }

    // configure communicators by amqp controllers





    const string nodeWorkerName = "simula_ctx0_mis0";

    // player agent & workers...




    // node worker -> core
    SAmqpRouteParameters routes6;
    routes6.predatorExchangePointName = "dss_dx_node_workers";
    routes6.predatorQueueName = "dss_q_node_worker_mailbox_" + nodeWorkerName;
    routes6.predatorRoutingKeyName = "dss_rk_to_node_worker_" + nodeWorkerName;
    routes6.targetExchangePointName = "dss_dx_core";
    routes6.targetRoutingKeyName = "dss_rk_to_core";






    return true;
}

common_types::IServiceInternalCommunication * CommunicationGatewayFacadeNode::serviceForInternalCommunication(){
    return this;
}

PNetworkClient CommunicationGatewayFacadeNode::getCoreCommunicator(){

    if( m_coreCommunicator ){
        return m_coreCommunicator;
    }

    // node agent -> core
    SAmqpRouteParameters route;
    route.predatorExchangePointName = "dss_dx_node_agents";
    route.predatorRoutingKeyName = "dss_rk_to_node_agent_" + m_settings.nodeAgentId;
    route.predatorQueueName = "dss_q_node_agent_mailbox_" + m_settings.nodeAgentId;
    route.targetExchangePointName = "dss_dx_core";
    route.targetRoutingKeyName = "dss_rk_to_core";

    PNetworkClient connection = CommunicationGatewayFacade::getInitialAmqpConnection();
    PAmqpClient amqpClient = std::dynamic_pointer_cast<AmqpClient>( connection );

    AmqpController::SInitSettings settings;
    settings.client = amqpClient;
    settings.route = route;

    PAmqpController controller = std::make_shared<AmqpController>( CommunicationGatewayFacade::getConnectionId() );
    if( ! controller->init( settings ) ){
        m_lastError = controller->getState().lastError;
        return nullptr;
    }

    m_coreCommunicator = controller;
    return controller;
}

PNetworkClient CommunicationGatewayFacadeNode::getNodeWorkerCommunicator( const std::string & _uniqueId ){

    auto iter = m_nodeWorkerCommunicatorsById.find( _uniqueId );
    if( iter != m_nodeWorkerCommunicatorsById.end() ){
        return iter->second;
    }

    // node agent -> node worker
    SAmqpRouteParameters route;
    route.predatorExchangePointName = "dss_dx_node_agents";
    route.predatorRoutingKeyName = "dss_rk_to_node_agent_" + m_settings.nodeAgentId;
    route.predatorQueueName = "dss_q_node_agent_mailbox_" + m_settings.nodeAgentId;
    route.targetExchangePointName = "dss_dx_node_workers";
    route.targetRoutingKeyName = "dss_rk_to_node_worker_" + _uniqueId;

    PNetworkClient connection = CommunicationGatewayFacade::getInitialAmqpConnection();
    PAmqpClient amqpClient = std::dynamic_pointer_cast<AmqpClient>( connection );

    AmqpController::SInitSettings settings;
    settings.client = amqpClient;
    settings.route = route;

    PAmqpController controller = std::make_shared<AmqpController>( CommunicationGatewayFacade::getConnectionId() );
    if( ! controller->init( settings ) ){
        m_lastError = controller->getState().lastError;
        return nullptr;
    }

    m_nodeWorkerCommunicatorsById.insert( {_uniqueId, controller} );
    return controller;
}





















