
#include <algorithm>

#include <dss_common/common/common_utils.h>

#include "dispatcher_node_real.h"

using namespace std;
using namespace common_types;

// -----------------------------------------------------------------------
// fake real-worker
// -----------------------------------------------------------------------
class FakeNodeWorkerReal : public INodeWorkerReal {
public:

    virtual void start() override {


    }

    virtual SNodeWorkerRealState & getState() override {
        return m_state;
    }

    void updateState( const common_types::SNodeWorkerRealState & _workerState ){
        m_state = _workerState;
        m_state.lastPingAtMillisec = common_utils::getCurrentTimeMillisec();
    }


private:

    // data
    common_types::SNodeWorkerRealState m_state;
};
using PFakeNodeWorkerReal = std::shared_ptr<FakeNodeWorkerReal>;


// -----------------------------------------------------------------------
// dispatcher
// -----------------------------------------------------------------------
DispatcherNodeReal::DispatcherNodeReal()
{

}

DispatcherNodeReal::~DispatcherNodeReal()
{

}

bool DispatcherNodeReal::init( const SInitSettings & _settings ){

    m_state.settings = _settings;

    // create fake real workers
    for( const string & pluginName : _settings.pluginNames ){

        SNodeWorkerRealState state;
        state.id = common_utils::generateUniqueId();
        state.agentId = _settings.nodeAgentId;
        state.realObjectName = pluginName;
        state.caps = "";

        PFakeNodeWorkerReal fakeWorker = std::make_shared<FakeNodeWorkerReal>();
        fakeWorker->updateState( state );


        m_nodes.push_back( fakeWorker );
        m_nodesById.insert( {state.id, fakeWorker} );
    }




    return true;
}

void DispatcherNodeReal::runSystemClock(){



}

void DispatcherNodeReal::configureNode( void * _cfg ){


    // if context defined - swap fake and new spawned real worker

}

vector<PNodeWorkerReal> DispatcherNodeReal::getNodes(){
    return m_nodes;
}

PNodeWorkerReal DispatcherNodeReal::getNode( const common_types::TNodeId & _id ){

    auto iter = m_nodesById.find( _id );
    if( iter != m_nodesById.end() ){
        return iter->second;
    }
    else{
        return nullptr;
    }
}

void DispatcherNodeReal::addPluginName( const std::string & _pluginName ){

    auto iter = std::find( m_newPluginsNames.begin(), m_newPluginsNames.end(), _pluginName );
    if( iter != m_newPluginsNames.end() ){
        return;
    }
    m_newPluginsNames.push_back( _pluginName );

    // create new fake worker
    SNodeWorkerRealState state;
    state.id = common_utils::generateUniqueId();
    state.agentId = m_state.settings.nodeAgentId;
    state.realObjectName = _pluginName;
    state.caps = "";

    PFakeNodeWorkerReal fakeWorker = std::make_shared<FakeNodeWorkerReal>();
    fakeWorker->updateState( state );

    m_nodes.push_back( fakeWorker );
    m_nodesById.insert( {state.id, fakeWorker} );
}
















