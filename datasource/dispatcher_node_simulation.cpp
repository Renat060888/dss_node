
#include <microservice_common/system/logger.h>
#include <dss_common/common/common_utils.h>

#include "dispatcher_node_simulation.h"

using namespace std;
using namespace common_types;

static constexpr const char * PRINT_HEADER = "DispatcherNodeWorkerSimula:";

DispatcherNodeSimulation::DispatcherNodeSimulation()
{

}

DispatcherNodeSimulation::~DispatcherNodeSimulation()
{

}

bool DispatcherNodeSimulation::init( const SInitSettings & _settings ){





    return true;
}

void DispatcherNodeSimulation::runSystemClock(){

    static constexpr int64_t NODE_WORKER_DISAPPEAR_TIMEOUT_MILLISEC = 30000;

    for( auto iter = m_nodesById.begin(); iter != m_nodesById.end(); ){
        PNodeProxyWorkerSimulation & worker = iter->second;

        if( (common_utils::getCurrentTimeMillisec() - worker->getState().lastPingAtMillisec) > NODE_WORKER_DISAPPEAR_TIMEOUT_MILLISEC ){
            VS_LOG_WARN << PRINT_HEADER << " worker disappeared for context: " << worker->getState().ctxId << endl;

            iter = m_nodesById.erase( iter );
        }
        else{
            ++iter;
        }
    }
}

bool DispatcherNodeSimulation::requestNode( common_types::TContextId _ctxId, common_types::TMissionId _missioinId ){

    // create process or local instance (for tests)



    return true;
}

void DispatcherNodeSimulation::releaseNode( const common_types::TNodeId & _id ){

    PNodeProxyWorkerSimulation node;
    auto iter = m_nodesById.find( _id );
    if( iter != m_nodesById.end() ){
        node = iter->second;
    }

    // send message to process to begin shutdown or destroy local instance (for tests)
}

const vector<PNodeProxyWorkerSimulation> & DispatcherNodeSimulation::getNodes(){
    return m_nodes;
}

PNodeProxyWorkerSimulation DispatcherNodeSimulation::getNode( const TNodeId & _id ){

    auto iter = m_nodesById.find( _id );
    if( iter != m_nodesById.end() ){
        return iter->second;
    }

    return nullptr;
}

void DispatcherNodeSimulation::updateWorker( const SNodeWorkerSimulationState & _workerState ){

    // update existing worker
    auto iterWorker = m_nodesById.find( _workerState.id );
    if( iterWorker != m_nodesById.end() ){
        PNodeProxyWorkerSimulation node = iterWorker->second;
        node->updateState( _workerState );
    }
    // new worker
    else{
        PNodeProxyWorkerSimulation node = std::make_shared<NodeProxyWorkerSimulation>();
        node->updateState( _workerState );
        m_nodes.push_back( node );
        m_nodesById.insert( {_workerState.id, node} );
    }
}



