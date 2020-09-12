
#include <microservice_common/system/logger.h>

#include "system/config_reader.h"
#include "node_worker_simulation.h"

using namespace std;

static constexpr const char * PRINT_HEADER = "NodeWorkerSimula:";

NodeWorkerSimulation::NodeWorkerSimulation()
    : m_federate(nullptr)
    , m_visitorDatabaseStore(nullptr)
    , m_visitorNetworkNotify(nullptr)
    , m_database(nullptr)
    , m_trObjectsProcessing(nullptr)
    , m_shutdownCalled(false)
    , m_stepToSimulateCount(0)
    , m_livePlaying(false)
    , m_useRTI(false)
{

}

NodeWorkerSimulation::~NodeWorkerSimulation()
{

}

bool NodeWorkerSimulation::init( const SInitSettings & _settings ){

    m_state.state.status = common_types::ENodeStatus::PREPARING;
    m_state.settings = _settings;

    // database
    DatabaseManagerBase::SInitSettings dbSettings;
    dbSettings.host = CONFIG_PARAMS.STORAGE_DATABASE_HOST;
    dbSettings.databaseName = CONFIG_PARAMS.STORAGE_DATABASE_NAME;
    m_database = DatabaseManagerBase::getInstance();
    if( ! m_database->init(dbSettings) ){
        m_state.state.status = common_types::ENodeStatus::CRASHED;
        return false;
    }

    // RTI
    if( ! initRTI() ){
        m_state.state.status = common_types::ENodeStatus::CRASHED;
        return false;
    }

    // visitor
    m_visitorDatabaseStore = new VisitorDatabaseStore( m_database );
    m_visitorNetworkNotify = new VisitorNetworkNotify();

    // objects
    if( ! prepareObjects() ){
        m_state.state.status = common_types::ENodeStatus::CRASHED;
        return false;
    }

    m_trObjectsProcessing = new std::thread( & NodeWorkerSimulation::threadObjectsProcessing, this );

    m_state.state.status = common_types::ENodeStatus::READY;
    return true;
}

bool NodeWorkerSimulation::prepareObjects(){

    IProcessingObject * testObj = new ProcessingObjectTrajectory();





    return true;
}

void NodeWorkerSimulation::threadObjectsProcessing(){

    VS_LOG_INFO << PRINT_HEADER << " enter in objects processing THREAD" << endl;

    std::mutex lockMutex;

    while( ! m_shutdownCalled ){

        // wait start event
        std::unique_lock<std::mutex> cvLock( lockMutex );
        m_cvObjectsProcessing.wait( cvLock, [this](){ return m_shutdownCalled
                || (common_types::ENodeStatus::ACTIVE == m_state.state.status
                && m_stepToSimulateCount != 0);
                } );

        // processing
        while( common_types::ENodeStatus::ACTIVE == m_state.state.status && m_stepToSimulateCount != 0 ){

            for( IProcessingObject * object : m_processingObjects ){
                // produce data
                object->makeStep( 0LL );

                // process data
                object->accept( m_visitorDatabaseStore );

                if( m_livePlaying ){
                    object->accept( m_visitorNetworkNotify );
                }

                m_visitorDatabaseStore->batchStore();
                m_visitorNetworkNotify->batchNotify();
            }

            m_stepToSimulateCount--;

            if( m_useRTI ){
                // advance RTI time
            }

            VS_LOG_INFO << PRINT_HEADER << " processing step " << m_stepToSimulateCount << endl;
        }

        m_state.state.status = common_types::ENodeStatus::READY;
    }

    VS_LOG_INFO << PRINT_HEADER << " quit from objects processing THREAD" << endl;
}

bool NodeWorkerSimulation::configure( const common_types::SConfigSimulation & _cfg ){

    VS_LOG_INFO << PRINT_HEADER
                << " call configure -"
                << " poll interval millisec: " << _cfg.pollIntervalMillisec
                << endl;

    return true;
}

bool NodeWorkerSimulation::start(){

    VS_LOG_INFO << PRINT_HEADER << " call start" << endl;

    m_stepToSimulateCount = 10;
    m_state.state.status = common_types::ENodeStatus::ACTIVE;
    m_cvObjectsProcessing.notify_one();

    return true;
}

void NodeWorkerSimulation::pause(){

    VS_LOG_INFO << PRINT_HEADER << " call pause" << endl;

    m_state.state.status = common_types::ENodeStatus::IDLE;
}

void NodeWorkerSimulation::stop(){

    VS_LOG_INFO << PRINT_HEADER << " call reset" << endl;

    m_stepToSimulateCount = 10;
    m_state.state.status = common_types::ENodeStatus::READY;


}

void NodeWorkerSimulation::switchLivePlaying( bool _live ){

    VS_LOG_INFO << PRINT_HEADER << " call live playing: " << _live << endl;

    m_livePlaying = _live;
}

void NodeWorkerSimulation::useRTI( bool _use ){

    VS_LOG_INFO << PRINT_HEADER << " call use RTI: " << _use << endl;

    m_useRTI = _use;
}

bool NodeWorkerSimulation::initRTI(){

    m_federate = new rti_client_vega::RTIFederate();








    return true;
}



