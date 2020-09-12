
#include <boost/property_tree/json_parser.hpp>
#include <microservice_common/system/system_monitor.h>
#include <microservice_common/system/logger.h>
#include <dss_common/common/common_utils.h>

#include "system/args_parser.h"
#include "system/config_reader.h"
#include "source_manager_facade.h"

using namespace std;

static constexpr const char * PRINT_HEADER = "SrcManager:";
static constexpr const char * PLUGIN_SYMBOL_CONSTRUCT = "construct";
static constexpr const char * PLUGIN_SYMBOL_GET_NAME = "get_name";

SourceManagerFacade::SourceManagerFacade()
    : m_shutdownCalled(false)
    , m_threadMaintenance(nullptr)
    , m_dispatcher(nullptr)
    , m_dispatcherNodeSimulation(nullptr)
    , m_dispatcherNodeReal(nullptr)
{

}

SourceManagerFacade::~SourceManagerFacade(){

    shutdown();
}

bool SourceManagerFacade::init( const SInitSettings & _settings ){

    m_state.settings = _settings;

    // agent type
    if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_SIMULATION) ){
        if( ! initSimulationMode(_settings) ){
            return false;
        }
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_REAL) ){
        if( ! initRealMode(_settings) ){
            return false;
        }
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_DUMP) ){
        if( ! initDumpMode(_settings) ){
            return false;
        }
    }
    else{
        VS_LOG_ERROR << PRINT_HEADER << " unknown node-agent type" << endl;
        return false;
    }

    // network
    m_networkWithCore = _settings.serviceInternalCommunication->getCoreCommunicator();

    // maintenance thread
    m_threadMaintenance = new std::thread( & SourceManagerFacade::threadMaintenance, this );

    VS_LOG_INFO << PRINT_HEADER << " init success" << endl;
    return true;
}

bool SourceManagerFacade::initSimulationMode( const SInitSettings & _settings ){

    // available plugin models
    LibraryLoader::SInitSettings settingsLoader;
    settingsLoader.directoryForLibrariesSearch = CONFIG_PARAMS.PLUGINS_SIMULATION_DIR_FULL_PATH;
    settingsLoader.filterLibrariesBySymbols.push_back( PLUGIN_SYMBOL_CONSTRUCT );
    settingsLoader.filterLibrariesBySymbols.push_back( PLUGIN_SYMBOL_GET_NAME );
    if( ! m_libraryLoader.init(settingsLoader) ){
        return false;
    }

    // dispatcher
    DispatcherNodeSimulation::SInitSettings settingsDisp;
    settingsDisp.internalCommunication = _settings.serviceInternalCommunication;
    settingsDisp.nodeAgentId = _settings.agentId;
    m_dispatcherNodeSimulation = new DispatcherNodeSimulation();
    if( m_dispatcherNodeSimulation->init(settingsDisp) ){
        return false;
    }

    m_dispatcher = m_dispatcherNodeSimulation;

    // ...




    return true;
}

bool SourceManagerFacade::initRealMode( const SInitSettings & _settings ){

    // available plugin models
    LibraryLoader::SInitSettings settingsLoader;
    settingsLoader.directoryForLibrariesSearch = CONFIG_PARAMS.PLUGINS_REAL_DIR_FULL_PATH;
    settingsLoader.filterLibrariesBySymbols.push_back( PLUGIN_SYMBOL_CONSTRUCT );
    settingsLoader.filterLibrariesBySymbols.push_back( PLUGIN_SYMBOL_GET_NAME );
    if( ! m_libraryLoader.init(settingsLoader) ){
        return false;
    }

    // dispatcher
    DispatcherNodeReal::SInitSettings settingsDisp;
    settingsDisp.internalCommunication = _settings.serviceInternalCommunication;
    settingsDisp.nodeAgentId = _settings.agentId;
    settingsDisp.pluginNames = m_libraryLoader.getLoadedLibrariesNames();
    m_dispatcherNodeReal = new DispatcherNodeReal();
    if( m_dispatcherNodeReal->init(settingsDisp) ){
        return false;
    }

    m_dispatcher = m_dispatcherNodeReal;

    // ...



    return true;
}

bool SourceManagerFacade::initDumpMode( const SInitSettings & _settings ){






    return true;
}

void SourceManagerFacade::shutdown(){

    if( m_shutdownCalled ){
        return;
    }

    VS_LOG_INFO << PRINT_HEADER << " begin shutdown" << endl;

    m_shutdownCalled = true;
    common_utils::threadShutdown( m_threadMaintenance );






    VS_LOG_INFO << PRINT_HEADER << " shutdown success" << endl;
}

void SourceManagerFacade::threadMaintenance(){

    VS_LOG_INFO << PRINT_HEADER << " start maintenance THREAD" << endl;

    while( ! m_shutdownCalled ){

        pingCore();
        refreshPluginLibs();
        m_dispatcher->runSystemClock();
    }

    VS_LOG_INFO << PRINT_HEADER << " maintenance THREAD stopped" << endl;
}

inline void SourceManagerFacade::pingCore(){

    static constexpr int64_t PING_INTERVAL_MILLISEC = 1000;
    static int64_t lastPingAtMillisec = 0;

    if( (common_utils::getCurrentTimeMillisec() - lastPingAtMillisec) > PING_INTERVAL_MILLISEC ){
        lastPingAtMillisec = common_utils::getCurrentTimeMillisec();

        string serializedMsg;

        // TODO: may be smelly approach
        if( m_dispatcherNodeSimulation ){
            serializedMsg = serializeSimulationMode();
        }
        else if( m_dispatcherNodeReal ){
            serializedMsg = serializeRealMode();
        }

        PEnvironmentRequest netRequest = m_networkWithCore->getRequestInstance();
        netRequest->setOutcomingMessage( serializedMsg );
    }
}

void SourceManagerFacade::refreshPluginLibs(){

    // TODO: really need ?
    return;

    // every N minutes
    static constexpr int64_t REFRESH_INTERVAL_SEC = 60;    
    int64_t lastPluginsRefreshSec = 0;

    if( (common_utils::getCurrentTimeSec() - lastPluginsRefreshSec) < REFRESH_INTERVAL_SEC ){
        return;
    }
    lastPluginsRefreshSec = common_utils::getCurrentTimeSec();

    // get files list
    vector<pair<string, int64_t>> pluginFileNameTimes;



    // compare with loaded plugins
    for( const pair<string, int64_t> & fileNameTime : pluginFileNameTimes ){
        const int64_t loadTimeMillisec = m_libraryLoader.getLibLoadTimeMillisec( fileNameTime.first );

        // reload
        if( fileNameTime.second != loadTimeMillisec ){
            const bool reloadIfExist = true;
            m_libraryLoader.load( fileNameTime.first, reloadIfExist );
        }
        // new one
        else if( 0 == loadTimeMillisec ){
            m_libraryLoader.load( fileNameTime.first );

            if( m_dispatcherNodeReal ){
                m_dispatcherNodeReal->addPluginName( fileNameTime.first );
            }
        }
        // plugin removed from dir
        // TODO:
    }



}

std::string SourceManagerFacade::serializeSimulationMode(){

    // node state
    boost::property_tree::ptree serializedNodeStatesArray;
    const vector<PNodeProxyWorkerSimulation> & simulaNodes = m_dispatcherNodeSimulation->getNodes();
    for( const PNodeProxyWorkerSimulation & simulaNode : simulaNodes ){
        const common_types::SNodeWorkerSimulationState & nodeState = simulaNode->getState();

        boost::property_tree::ptree nodeStateElem;

        nodeStateElem.put( "id", nodeState.id );
        nodeStateElem.put( "ctx_id", nodeState.ctxId );
        nodeStateElem.put( "status", common_utils::convertNodeStatusToStr(nodeState.status) );

        serializedNodeStatesArray.push_back( boost::property_tree::ptree::value_type("", nodeStateElem) );
    }

    // physic models
    boost::property_tree::ptree serializedLibNamesArray;
    const std::vector<std::string> libNames = m_libraryLoader.getLoadedLibrariesNames();
    for( const string & libName : libNames ){
        boost::property_tree::ptree libNameElem;

        libNameElem.put( "lib_name", libName );

        serializedLibNamesArray.push_back( boost::property_tree::ptree::value_type("", libNameElem) );
    }

    // system
    boost::property_tree::ptree serializedSystemState;
    const SystemMonitor::STotalInfo systemSnapshot = SYSTEM_MONITOR.getTotalSnapshot();

    serializedSystemState.add( "cpu_avg_load_percent", systemSnapshot.cpu.totalLoadByAvgFromCoresPercent );
    serializedSystemState.add( "ram_total_mb", systemSnapshot.memory.ramTotalMb );
    serializedSystemState.add( "ram_free_mb", systemSnapshot.memory.ramFreeMb );




    // result
    boost::property_tree::ptree serializedState;
    serializedState.add_child( "node_states", serializedNodeStatesArray );
    serializedState.add_child( "lib_names", serializedLibNamesArray );
    serializedState.add_child( "system_state", serializedSystemState );

    stringstream ss;
    boost::property_tree::json_parser::write_json( ss, serializedState );
    return ss.str();
}

std::string SourceManagerFacade::serializeRealMode(){

    const vector<PNodeWorkerReal> & realNodes = m_dispatcherNodeReal->getNodes();
    const SystemMonitor::STotalInfo systemSnapshot = SYSTEM_MONITOR.getTotalSnapshot();
    const std::vector<std::string> pluginsLibs = m_libraryLoader.getLoadedLibrariesNames();

    // create real node agent protobuf






    boost::property_tree::ptree serializedState;

    stringstream ss;
    boost::property_tree::json_parser::write_json( ss, serializedState );
    return ss.str();
}

std::string SourceManagerFacade::serializeDumpMode(){






    boost::property_tree::ptree serializedState;

    stringstream ss;
    boost::property_tree::json_parser::write_json( ss, serializedState );
    return ss.str();
}

DispatcherNodeSimulation * SourceManagerFacade::getSimulaDispatcher(){
    return m_dispatcherNodeSimulation;
}

DispatcherNodeReal * SourceManagerFacade::getRealDispatcher(){
    return m_dispatcherNodeReal;
}







