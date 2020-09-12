
#include <microservice_common/communication/amqp_controller.h>
#include <microservice_common/communication/amqp_client_c.h>

#include "system/config_reader.h"
#include "system/objrepr_bus_node.h"
#include "node_controller_simulation.h"

using namespace std;

NodeControllerSimulation::NodeControllerSimulation()
{

}

bool NodeControllerSimulation::init( const SInitSettings & _settings ){

    // TODO: also determine which mission is being used

    // objrepr
    if( ! OBJREPR_BUS.openContext(_settings.ctxId) ){
        return false;
    }

    // worker
    NodeWorkerSimulation::SInitSettings workerSettings;
    workerSettings.workerId = _settings.workerId;
    workerSettings.ctxId = _settings.ctxId;
    if( ! m_worker.init(workerSettings) ){
        return false;
    }

    // communication with agent
    m_networkWithAgent = connectToNetwork( _settings.workerId, _settings.agentId );
    if( ! m_networkWithAgent ){
        return false;
    }

    PNetworkProvider provider = std::dynamic_pointer_cast<INetworkProvider>( m_networkWithAgent );
    provider->addObserver( this );
    m_networkProvider = provider;

    // ping entity
    m_pingRequest = m_networkWithAgent->getRequestInstance();

    return true;
}

void NodeControllerSimulation::callbackNetworkRequest( PEnvironmentRequest _request ){



    // ...
    int a = 0;

    switch( a ){
    case 0 : {

        break;
    }
    case 1 : {

        break;
    }
    case 2 : {

        break;
    }
    case 3 : {

        break;
    }
    case 4 : {

        break;
    }
    default : {

    }
    }
}

PNetworkClient NodeControllerSimulation::connectToNetwork( const common_types::TNodeId & _id, const common_types::TNodeId & _agentId ){

    // amqp client
    PAmqpClient client = std::make_shared<AmqpClient>( INetworkEntity::INVALID_CONN_ID );

    AmqpClient::SInitSettings clientSettings;
    clientSettings.serverHost = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_SERVER_HOST;
    clientSettings.amqpVirtualHost = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_VIRTUAL_HOST;
    clientSettings.port = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_SERVER_PORT;
    clientSettings.login = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_LOGIN;
    clientSettings.pass = CONFIG_PARAMS.baseParams.COMMUNICATION_AMQP_PASS;
    clientSettings.deliveredMessageExpirationSec = 60;

    if( ! client->init(clientSettings) ){
        m_state.lastError = client->getState().m_lastError;
        return nullptr;
    }

    // controller for it
    SAmqpRouteParameters routes;
    routes.predatorExchangePointName = "dss_dx_node_workers";
    routes.predatorQueueName = "dss_q_node_worker_mailbox_" + _id;
    routes.predatorRoutingKeyName = "dss_rk_to_node_worker_" + _id;

    routes.targetExchangePointName = "dss_dx_node_agents";
    routes.targetQueueName = "dss_q_node_agent_mailbox_" + _agentId;
    routes.targetRoutingKeyName = "dss_rk_to_node_agent_" + _agentId;

    AmqpController::SInitSettings settings2;
    settings2.client = client;
    settings2.route = routes;

    PAmqpController controller = std::make_shared<AmqpController>( INetworkEntity::INVALID_CONN_ID );
    const bool rt = controller->init( settings2 );
    if( ! rt ){
        m_state.lastError = controller->getState().lastError;
        return nullptr;
    }

    return controller;
}

void NodeControllerSimulation::launch(){

    while( true ){

        m_networkProvider->runNetworkCallbacks();

        // ping agent
        const string serializedWorkerState = "";
        m_pingRequest->setOutcomingMessage( serializedWorkerState );
    }
}

void NodeControllerSimulation::processMessageConfigure(){

    common_types::SConfigSimulation cfg;


    m_worker.configure( cfg );
}

void NodeControllerSimulation::processMessageStart(){

    m_worker.start();
}

void NodeControllerSimulation::processMessagePause(){

    m_worker.pause();
}

void NodeControllerSimulation::processMessageStop(){

    m_worker.stop();
}

void NodeControllerSimulation::processMessageSwitchLiveProcessing(){

    m_worker.switchLivePlaying( true );
}

void NodeControllerSimulation::processMessageUseRTI(){

    m_worker.useRTI( false );
}




