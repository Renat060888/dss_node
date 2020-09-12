
#include <dss_common/communication/protocols/dss_node_agent_simulation.pb.h>
#include <dss_common/common/common_utils.h>

#include "node_proxy_worker_simulation.h"

using namespace std;

NodeProxyWorkerSimulation::NodeProxyWorkerSimulation()
{

}

NodeProxyWorkerSimulation::~NodeProxyWorkerSimulation(){

}

const common_types::SNodeWorkerSimulationState & NodeProxyWorkerSimulation::getState(){
    return m_state;
}

bool NodeProxyWorkerSimulation::configure( const common_types::SConfigSimulation & _cfg ){

    // create request
    google_protobuf_dss_agent_simula::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_simula::MessageRequestConfigure messageRequestConfigure;
    messageRequestConfigure.set_realtime( _cfg.realtime );
    messageRequestConfigure.set_processing_interval_millisec( _cfg.pollIntervalMillisec );

    google_protobuf_dss_agent_simula::MessageAgentSimulaToWorkerRequest messageAgentSimulaToWorkerRequest;
    messageAgentSimulaToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentSimulaToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_simula::EAgentToWorkerRequestType::AWCT_CONFIGURE );
    messageAgentSimulaToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestConfigure );

    google_protobuf_dss_agent_simula::MessageAgentSimula messageAgentSimula;
    messageAgentSimula.set_msg_type( ::google_protobuf_dss_agent_simula::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentSimula.mutable_request_to_worker()->CopyFrom( messageAgentSimulaToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentSimula.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );

    return true;
}

void NodeProxyWorkerSimulation::shutdown(){

}

bool NodeProxyWorkerSimulation::start(){

    // create request
    google_protobuf_dss_agent_simula::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_simula::MessageRequestStart messageRequestStart;

    google_protobuf_dss_agent_simula::MessageAgentSimulaToWorkerRequest messageAgentSimulaToWorkerRequest;
    messageAgentSimulaToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentSimulaToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_simula::EAgentToWorkerRequestType::AWCT_START );
    messageAgentSimulaToWorkerRequest.mutable_msg_start()->CopyFrom( messageRequestStart );

    google_protobuf_dss_agent_simula::MessageAgentSimula messageAgentSimula;
    messageAgentSimula.set_msg_type( ::google_protobuf_dss_agent_simula::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentSimula.mutable_request_to_worker()->CopyFrom( messageAgentSimulaToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentSimula.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );

    return true;
}

bool NodeProxyWorkerSimulation::pause(){

    // create request
    google_protobuf_dss_agent_simula::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_simula::MessageRequestPause messageRequestPause;

    google_protobuf_dss_agent_simula::MessageAgentSimulaToWorkerRequest messageAgentSimulaToWorkerRequest;
    messageAgentSimulaToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentSimulaToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_simula::EAgentToWorkerRequestType::AWCT_PAUSE );
    messageAgentSimulaToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestPause );

    google_protobuf_dss_agent_simula::MessageAgentSimula messageAgentSimula;
    messageAgentSimula.set_msg_type( ::google_protobuf_dss_agent_simula::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentSimula.mutable_request_to_worker()->CopyFrom( messageAgentSimulaToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentSimula.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );

    return true;
}

bool NodeProxyWorkerSimulation::reset(){

    // create request
    google_protobuf_dss_agent_simula::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_simula::MessageRequestStop messageRequestStop;

    google_protobuf_dss_agent_simula::MessageAgentSimulaToWorkerRequest messageAgentSimulaToWorkerRequest;
    messageAgentSimulaToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentSimulaToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_simula::EAgentToWorkerRequestType::AWCT_STOP );
    messageAgentSimulaToWorkerRequest.mutable_msg_start()->CopyFrom( messageRequestStop );

    google_protobuf_dss_agent_simula::MessageAgentSimula messageAgentSimula;
    messageAgentSimula.set_msg_type( ::google_protobuf_dss_agent_simula::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentSimula.mutable_request_to_worker()->CopyFrom( messageAgentSimulaToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentSimula.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );

    return true;
}

void NodeProxyWorkerSimulation::switchLivePlaying( bool _live ){

    // create request
    google_protobuf_dss_agent_simula::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_simula::MessageRequestLiveProcessing messageRequestLiveProcessing;
    messageRequestLiveProcessing.set_live( _live );

    google_protobuf_dss_agent_simula::MessageAgentSimulaToWorkerRequest messageAgentSimulaToWorkerRequest;
    messageAgentSimulaToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentSimulaToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_simula::EAgentToWorkerRequestType::AWCT_LIVE_PROCESSING );
    messageAgentSimulaToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestLiveProcessing );

    google_protobuf_dss_agent_simula::MessageAgentSimula messageAgentSimula;
    messageAgentSimula.set_msg_type( ::google_protobuf_dss_agent_simula::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentSimula.mutable_request_to_worker()->CopyFrom( messageAgentSimulaToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentSimula.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );
}

void NodeProxyWorkerSimulation::useRTI( bool _use ){

    // create request
    google_protobuf_dss_agent_simula::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_simula::MessageRequestUseRTI messageRequestUseRTI;
    messageRequestUseRTI.set_use( _use );

    google_protobuf_dss_agent_simula::MessageAgentSimulaToWorkerRequest messageAgentSimulaToWorkerRequest;
    messageAgentSimulaToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentSimulaToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_simula::EAgentToWorkerRequestType::AWCT_USE_RTI );
    messageAgentSimulaToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestUseRTI );

    google_protobuf_dss_agent_simula::MessageAgentSimula messageAgentSimula;
    messageAgentSimula.set_msg_type( ::google_protobuf_dss_agent_simula::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentSimula.mutable_request_to_worker()->CopyFrom( messageAgentSimulaToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentSimula.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );
}

void NodeProxyWorkerSimulation::updateState( const common_types::SNodeWorkerSimulationState & _workerState ){

    m_state = _workerState;
}
