
#include <algorithm>

#include <microservice_common/system/logger.h>
#include <dss_common/common/common_utils.h>

#include "system/config_reader.h"
#include "dispatcher_node_real.h"

using namespace std;
using namespace common_types;

static constexpr const char * PRINT_HEADER = "DispatcherNodeWorkerReal:";

// -----------------------------------------------------------------------
// Fake worker
// - actual worker will be created when user will choose context due to:
// 1) worker must be launched in separate process
// 2) there can be quite a lot of real objects ( which are not even used )
// 3) plugin file can be transparently updated "on the fly" after worker reload
// 4) "minimalism of states" ( processing objects like a flightradar ~2000, RTI federate, objrepr objects, see p.3, etc... )
// -----------------------------------------------------------------------
class FakeNodeWorkerReal : public INodeWorkerReal {
public:
    virtual void configure( const common_types::SConfigReal & _cfg ) override {

        // TODO: save fake parameters before potential "flip-flop"

        if( m_state.ctxId != _cfg.ctxId ){
            for( INodeWorkerRealObserver * obs : m_observers ){
                obs->callbackNodeContextChanged( m_state.id, _cfg.ctxId );
            }
        }
    }

    virtual void start() override {
        // dummy
    }

    virtual void pause() override {
        // dummy
    }

    virtual void stop() override {
        // dummy
    }

    virtual void switchLivePlaying( bool _live ) override {
        // dummy
    }

    virtual SNodeWorkerRealState & getState() override {
        return m_state;
    }

    void updateState( const common_types::SNodeWorkerRealState & _workerState ){
        m_state = _workerState;
        m_state.lastPingAtMillisec = common_utils::getCurrentTimeMillisec();
    }

    void addObserver( INodeWorkerRealObserver * _observer ){

        auto iter = std::find( m_observers.begin(), m_observers.end(), _observer );
        if( iter == m_observers.end() ){
            m_observers.push_back( _observer );
        }
    }


private:
    // data
    common_types::SNodeWorkerRealState m_state;
    std::vector<INodeWorkerRealObserver *> m_observers;
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

    // create fake workers
    for( const string & pluginName : _settings.pluginNames ){

        const string pluginCaps = getCaps( pluginName );
        if( ! pluginCaps.empty() ){
            return false;
        }

        SNodeWorkerRealState state;
        state.id = common_utils::generateUniqueId();
        state.agentId = _settings.nodeAgentId;
        state.realObjectName = pluginName;
        state.availableCaps = pluginCaps;
        state.status = common_types::ENodeStatus::ACTIVE;

        PFakeNodeWorkerReal fakeWorker = std::make_shared<FakeNodeWorkerReal>();
        fakeWorker->updateState( state );

        m_nodes.push_back( fakeWorker );
        m_fakeNodesById.insert( {state.id, fakeWorker} );
    }

    // ...



    return true;
}

void DispatcherNodeReal::callbackNodeContextChanged( common_types::TNodeId _nodeId, common_types::TContextId _ctxId ){

    assert( ! (m_nodesById.find(_nodeId) != m_nodesById.end() && m_fakeNodesById.find(_nodeId) != m_fakeNodesById.end()) );

    if( 0 == _ctxId ){
        // real becomes back to fake
        auto iter = m_nodesById.find( _nodeId );
        if( iter != m_nodesById.end() ){
            PNodeWorkerReal node = iter->second;

            const common_types::SNodeWorkerRealState state = node->getState();
            PFakeNodeWorkerReal fakeWorker = std::make_shared<FakeNodeWorkerReal>();
            fakeWorker->updateState( state );

            m_nodes.push_back( fakeWorker );
            m_fakeNodesById.insert( {state.id, fakeWorker} );
        }
    }
    else{
        // fake to real
        auto iterFake = m_fakeNodesById.find( _nodeId );
        if( iterFake != m_fakeNodesById.end() ){
            PNodeWorkerReal fakeNode = iterFake->second;

            const common_types::SNodeWorkerRealState state = fakeNode->getState();
            const bool rt = requestNode( _ctxId, 0, state );

            // NOTE: destroy fake when real will arrive via ping ( for consistency )
        }

        // reload real
        auto iter = m_nodesById.find( _nodeId );
        if( iter != m_nodesById.end() ){
            PNodeWorkerReal node = iterFake->second;

            const common_types::SNodeWorkerRealState state = node->getState();
            const bool rt = requestNode( _ctxId, 0, state );

            // NOTE: destroy current real when new one will arrive via ping ( for consistency )
        }
    }
}

void DispatcherNodeReal::runSystemClock(){

    static constexpr int64_t NODE_WORKER_DISAPPEAR_TIMEOUT_MILLISEC = 30000;

    // watch for disappeared workers
    for( auto iter = m_nodesById.begin(); iter != m_nodesById.end(); ){
        PNodeWorkerReal & worker = iter->second;

        if( (common_utils::getCurrentTimeMillisec() - worker->getState().lastPingAtMillisec) > NODE_WORKER_DISAPPEAR_TIMEOUT_MILLISEC ){
            VS_LOG_WARN << PRINT_HEADER << " worker disappeared with id: " << worker->getState().id << endl;

            iter = m_nodesById.erase( iter );
        }
        else{
            ++iter;
        }
    }
}

bool DispatcherNodeReal::requestNode( common_types::TContextId _ctxId,
                                      common_types::TMissionId _missioinId,
                                      const common_types::SNodeWorkerRealState & _initialState ){

    // create process or local instance (for tests)



    return true;
}

void DispatcherNodeReal::releaseNode( const common_types::TNodeId & _id ){

    PNodeWorkerReal node;
    auto iter = m_nodesById.find( _id );
    if( iter != m_nodesById.end() ){
        node = iter->second;
    }

    // send message to process to begin shutdown or destroy local instance (for tests)
}

const vector<PNodeWorkerReal> & DispatcherNodeReal::getNodes(){
    return m_nodes;
}

PNodeWorkerReal DispatcherNodeReal::getNode( const common_types::TNodeId & _id ){

    auto iter = m_nodesById.find( _id );
    if( iter != m_nodesById.end() ){
        return iter->second;
    }

    auto iter2 = m_fakeNodesById.find( _id );
    if( iter2 != m_fakeNodesById.end() ){
        return iter2->second;
    }

    return nullptr;
}

void DispatcherNodeReal::addPluginName( const std::string & _pluginName ){

    auto iter = std::find( m_newPluginsNames.begin(), m_newPluginsNames.end(), _pluginName );
    if( iter != m_newPluginsNames.end() ){
        return;
    }
    m_newPluginsNames.push_back( _pluginName );

    // create new initial fake worker
    const string pluginCaps = getCaps( _pluginName );
    if( ! pluginCaps.empty() ){
        return;
    }

    SNodeWorkerRealState state;
    state.id = common_utils::generateUniqueId();
    state.agentId = m_state.settings.nodeAgentId;
    state.realObjectName = _pluginName;
    state.availableCaps = pluginCaps;

    PFakeNodeWorkerReal fakeWorker = std::make_shared<FakeNodeWorkerReal>();
    fakeWorker->updateState( state );

    m_nodes.push_back( fakeWorker );
    m_fakeNodesById.insert( {state.id, fakeWorker} );
}

std::string DispatcherNodeReal::getCaps( const std::string & _pluginName ){

    // search file
    const string pluginCapsFilePath = CONFIG_READER.getConfigFileLocationPath() + "/" + _pluginName + "_plugin_caps.json";

    ifstream capsFile( pluginCapsFilePath );
    if( ! capsFile.is_open() ){
        VS_LOG_ERROR << PRINT_HEADER
                     << " caps file for [" << _pluginName << "] not found,"
                     << " by following path [" << pluginCapsFilePath << "]"
                     << endl;
        return string();
    }

    // read
    return string( std::istreambuf_iterator<char>(capsFile), std::istreambuf_iterator<char>() );
}














