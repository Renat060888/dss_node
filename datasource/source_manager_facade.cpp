
#include <microservice_common/system/system_monitor.h>
#include <microservice_common/system/logger.h>

#include "system/args_parser.h"
#include "system/config_reader.h"
#include "source_manager_facade.h"

using namespace std;

static constexpr const char * PRINT_HEADER = "SrcManager:";

static constexpr const char * PLUGIN_SYMBOL_CONSTRUCT = "construct";
static constexpr const char * PLUGIN_SYMBOL_GET_NAME = "getName";

SourceManagerFacade::SourceManagerFacade()
    : m_shutdownCalled(false)
    , m_lastPluginsRefreshSec(0)
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

    // choose agent type
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

    m_dispatcherNodeSimulation = new DispatcherNodeSimulation();
    m_dispatcher = m_dispatcherNodeSimulation;





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

    m_dispatcherNodeReal = new DispatcherNodeReal();
    m_dispatcher = m_dispatcherNodeReal;




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

        m_dispatcher->runSystemClock();
        pingCore();
        refreshPluginLibs();
    }

    VS_LOG_INFO << PRINT_HEADER << " maintenance THREAD stopped" << endl;
}

void SourceManagerFacade::pingCore(){

    // ping core ( workers, available physic models, system info, etc... )

    const string serializedMsg = "";




    PEnvironmentRequest netRequest = m_networkWithCore->getRequestInstance();
    netRequest->setOutcomingMessage( serializedMsg );
}

void SourceManagerFacade::refreshPluginLibs(){

    // every N minutes
    static constexpr int64_t REFRESH_INTERVAL_SEC = 60;    

    if( (common_utils::getCurrentTimeSec() - m_lastPluginsRefreshSec) < REFRESH_INTERVAL_SEC ){
        return;
    }
    m_lastPluginsRefreshSec = common_utils::getCurrentTimeSec();

    // get files list
    vector<pair<string, int64_t>> pluginFileNameTimes;




    // compare with loaded plugins
    for( const pair<string, int64_t> & fileNameTime : pluginFileNameTimes ){
        const int64_t loadTimeMillisec = m_libraryLoader.getLibLoadTimeMillisec( fileNameTime.first );

        // reload
        if( fileNameTime.second != loadTimeMillisec ){
            m_libraryLoader.load( fileNameTime.first, true );
        }
        // new one
        else if( 0 == loadTimeMillisec ){
            m_libraryLoader.load( fileNameTime.first );

            if( m_dispatcherNodeReal ){
                m_dispatcherNodeReal->addPluginName( fileNameTime.first );
            }
        }
    }



}











