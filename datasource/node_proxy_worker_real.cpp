
#include <algorithm>

#include <dss_common/communication/protocols/dss_node_agent_real.pb.h>
#include <dss_common/common/common_utils.h>

#include "node_proxy_worker_real.h"

using namespace std;

NodeProxyWorkerReal::NodeProxyWorkerReal()
{

}

void NodeProxyWorkerReal::configure( const common_types::SConfigReal & _cfg ){

    // create request
    google_protobuf_dss_agent_real::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_real::MessageRequestConfigure messageRequestConfigure;
    messageRequestConfigure.set_ctx_id( _cfg.ctxId );
    messageRequestConfigure.set_capability( _cfg.targetCaps );
    messageRequestConfigure.set_processing_interval_millisec( _cfg.pollIntervalMillisec );

    google_protobuf_dss_agent_real::MessageAgentRealToWorkerRequest messageAgentRealToWorkerRequest;
    messageAgentRealToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentRealToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_real::EAgentToWorkerRequestType::AWCT_CONFIGURE );
    messageAgentRealToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestConfigure );

    google_protobuf_dss_agent_real::MessageAgentReal messageAgentReal;
    messageAgentReal.set_msg_type( ::google_protobuf_dss_agent_real::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentReal.mutable_request_to_worker()->CopyFrom( messageAgentRealToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentReal.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );

    return;
}

void NodeProxyWorkerReal::start(){

    // create request
    google_protobuf_dss_agent_real::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_real::MessageRequestStart messageRequestStart;

    google_protobuf_dss_agent_real::MessageAgentRealToWorkerRequest messageAgentRealToWorkerRequest;
    messageAgentRealToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentRealToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_real::EAgentToWorkerRequestType::AWCT_START );
    messageAgentRealToWorkerRequest.mutable_msg_start()->CopyFrom( messageRequestStart );

    google_protobuf_dss_agent_real::MessageAgentReal messageAgentReal;
    messageAgentReal.set_msg_type( ::google_protobuf_dss_agent_real::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentReal.mutable_request_to_worker()->CopyFrom( messageAgentRealToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentReal.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );
}

void NodeProxyWorkerReal::pause(){

    // create request
    google_protobuf_dss_agent_real::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_real::MessageRequestPause messageRequestPause;

    google_protobuf_dss_agent_real::MessageAgentRealToWorkerRequest messageAgentRealToWorkerRequest;
    messageAgentRealToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentRealToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_real::EAgentToWorkerRequestType::AWCT_PAUSE );
    messageAgentRealToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestPause );

    google_protobuf_dss_agent_real::MessageAgentReal messageAgentReal;
    messageAgentReal.set_msg_type( ::google_protobuf_dss_agent_real::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentReal.mutable_request_to_worker()->CopyFrom( messageAgentRealToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentReal.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );
}

void NodeProxyWorkerReal::stop(){

    // create request
    google_protobuf_dss_agent_real::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_real::MessageRequestStop messageRequestStop;

    google_protobuf_dss_agent_real::MessageAgentRealToWorkerRequest messageAgentRealToWorkerRequest;
    messageAgentRealToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentRealToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_real::EAgentToWorkerRequestType::AWCT_STOP );
    messageAgentRealToWorkerRequest.mutable_msg_start()->CopyFrom( messageRequestStop );

    google_protobuf_dss_agent_real::MessageAgentReal messageAgentReal;
    messageAgentReal.set_msg_type( ::google_protobuf_dss_agent_real::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentReal.mutable_request_to_worker()->CopyFrom( messageAgentRealToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentReal.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );
}

void NodeProxyWorkerReal::switchLivePlaying( bool _live ){

    // create request
    google_protobuf_dss_agent_real::MessageHeader header;
    header.set_agent_id( 0 );
    header.set_pid( ::getpid() );
    header.set_ip_octets( common_utils::ipAddressToOctets(common_utils::getIpAddressStr()) );
    header.set_last_error( "no_errors" );

    google_protobuf_dss_agent_real::MessageRequestLiveProcessing messageRequestLiveProcessing;
    messageRequestLiveProcessing.set_live( _live );

    google_protobuf_dss_agent_real::MessageAgentRealToWorkerRequest messageAgentRealToWorkerRequest;
    messageAgentRealToWorkerRequest.mutable_header()->CopyFrom( header );
    messageAgentRealToWorkerRequest.set_cmd_type( ::google_protobuf_dss_agent_real::EAgentToWorkerRequestType::AWCT_LIVE_PROCESSING );
    messageAgentRealToWorkerRequest.mutable_msg_configure()->CopyFrom( messageRequestLiveProcessing );

    google_protobuf_dss_agent_real::MessageAgentReal messageAgentReal;
    messageAgentReal.set_msg_type( ::google_protobuf_dss_agent_real::EAgentMessageType::AMT_REQUEST_TO_WORKER );
    messageAgentReal.mutable_request_to_worker()->CopyFrom( messageAgentRealToWorkerRequest );

    // forward
    const string & requestToWorkerStr = messageAgentReal.SerializeAsString();
//    m_nodeAgentFacility->forwardNodeWorkerRequest( requestToWorkerStr );
}

common_types::SNodeWorkerRealState & NodeProxyWorkerReal::getState(){

    return m_state;
}

void NodeProxyWorkerReal::addObserver( INodeWorkerRealObserver * _observer ){

    auto iter = std::find( m_observers.begin(), m_observers.end(), _observer );
    if( iter == m_observers.end() ){
        m_observers.push_back( _observer );
    }
}
