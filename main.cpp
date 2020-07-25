
#include <boost/property_tree/json_parser.hpp>
#include <microservice_common/system/logger.h>
#include <microservice_common/system/daemonizator.h>
#include <microservice_common/communication/shell.h>

#include "system/args_parser.h"
#include "system/config_reader.h"
#include "system/path_locator.h"
#include "communication/unified_command_convertor_node.h"
#include "datasource/node_controller_simulation.h"
#include "datasource/node_controller_real.h"
#include "node_agent.h"

using namespace std;

static string getLoggerName( bool _daemon, bool _clientShell ){

    if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_SIMULATION) ){
        if( _daemon ){ return "NodeAgentSimDaemon"; }
        else if( _clientShell ){ return "NodeAgentSimShellClient"; }
        else{ return "NodeAgentSim"; }
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_REAL) ){
        if( _daemon ){ return "NodeAgentRealDaemon"; }
        else if( _clientShell ){ return "NodeAgentRealShellClient"; }
        else{ return "NodeAgentReal"; }
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_WORKER_SIMULATION) ){
        return "NodeWorkerSim";
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_WORKER_REAL) ){
        return "NodeWorkerReal";
    }
    else{
        assert( false && "unknown node type" );
    }
}

static string getConfigPath(){

    if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_SIMULATION) ){
        return CONFIG_PARAMS.SYSTEM_UNILOG_CONFIG_PATH_FOR_AGENT_SIMULA;
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_AGENT_REAL) ){
        return CONFIG_PARAMS.SYSTEM_UNILOG_CONFIG_PATH_FOR_AGENT_REAL;
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_WORKER_SIMULATION) ){
        return CONFIG_PARAMS.SYSTEM_UNILOG_CONFIG_PATH_FOR_WORKER_SIMULA;
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_WORKER_REAL) ){
        return CONFIG_PARAMS.SYSTEM_UNILOG_CONFIG_PATH_FOR_WORKER_REAL;
    }
    else{
        assert( false && "unknown node type" );
    }
}

static bool initSingletons( int _argc, char ** _argv, char ** _env ){

    // cmd line arguments
    ArgsParser::SInitSettings settings;
    settings.argc = _argc;
    settings.argv = _argv;
    settings.printConfigExample = std::bind( & AConfigReader::getConfigExample, & CONFIG_READER );
    settings.commandConvertor = & UNIFIED_COMMAND_CONVERTOR;
    if( ! ARGS_PARSER.init(settings) ){
        return false;
    }

    // configs
    ConfigReader::SIninSettings settings3;
    settings3.mainConfigPath = ARGS_PARSER.getVal(ENodeArguments::MAIN_CONFIG_PATH_FROM_CONSOLE);
    settings3.commandConvertor = & UNIFIED_COMMAND_CONVERTOR;
    settings3.env = _env;
    settings3.projectName = "dss_node";
    if( ! CONFIG_READER.init(settings3) ){
        return false;
    }

    // logger
    logger_common::SInitSettings settings2;
    settings2.loggerName = getLoggerName( false, false );
    settings2.unilogConfigPath = getConfigPath();

    if( CONFIG_PARAMS.baseParams.SYSTEM_LOG_TO_STDOUT ){
        settings2.logEndpoints = (logger_common::ELogEndpoints)( (int)settings2.logEndpoints | (int)logger_common::ELogEndpoints::Stdout );
    }
    if( CONFIG_PARAMS.baseParams.SYSTEM_LOG_TO_FILE ){
        settings2.logEndpoints = (logger_common::ELogEndpoints)( (int)settings2.logEndpoints | (int)logger_common::ELogEndpoints::File );
        settings2.fileName = CONFIG_PARAMS.baseParams.SYSTEM_LOGFILE_NAME;
        settings2.filePath = CONFIG_PARAMS.baseParams.SYSTEM_REGULAR_LOGFILE_PATH;
        settings2.rotationSizeMb = CONFIG_PARAMS.baseParams.SYSTEM_LOGFILE_ROTATION_SIZE_MB;
    }

    Logger::singleton().initGlobal( settings2 );

    return true;
}

static void parseResponse( const std::string & _msg ){

    // parse base part
    boost::property_tree::ptree parsedRepsonseJson;
    try{
        istringstream contentStream( _msg );
        boost::property_tree::json_parser::read_json( contentStream, parsedRepsonseJson );
    }
    catch( boost::property_tree::json_parser::json_parser_error & _ex ){
        VS_LOG_ERROR    << " parse failed of [" << _msg << "]" << endl
                        << "Reason: [" << _ex.what() << "]" << endl;
        return;
    }

    VS_LOG_INFO << "response from unix-socket-dss [" <<  _msg << "]" << endl;

    // TODO: print values from parsedRepsonseJson ?
}

static bool executeShellCommand(){

    if( ARGS_PARSER.isKeyExist(ENodeArguments::SHELL_COMMAND_START_AGENT) ){

        // deamonize
        if( ARGS_PARSER.isKeyExist(ENodeArguments::AS_DAEMON) ){
            if( ! Daemonizator::turnIntoDaemon() ){
                return false;
            }

            // reinit logger for daemon
            logger_common::SInitSettings settings2;
            settings2.loggerName = getLoggerName( true, false );
            settings2.unilogConfigPath = CONFIG_PARAMS.baseParams.SYSTEM_UNILOG_CONFIG_PATH;
            settings2.logEndpoints = logger_common::ELogEndpoints::File;
            settings2.fileName = CONFIG_PARAMS.baseParams.SYSTEM_LOGFILE_NAME;
            settings2.filePath = CONFIG_PARAMS.baseParams.SYSTEM_REGULAR_LOGFILE_PATH;
            settings2.rotationSizeMb = CONFIG_PARAMS.baseParams.SYSTEM_LOGFILE_ROTATION_SIZE_MB;

            Logger::singleton().initGlobal( settings2 );

            VS_LOG_INFO << "============================ DSS NODE AS DAEMON ========================" << endl;
        }

        // launch
        {
            NodeAgent::SInitSettings settings;
            NodeAgent agent;
            if( agent.init(settings) ){
                agent.launch();
            }
            else{
                return false;
            }
        }
    }
    else if( ARGS_PARSER.isKeyExist(ENodeArguments::SHELL_COMMAND_TO_AGENT) ){

        // reinit logger for client side
        logger_common::SInitSettings settings;
        settings.loggerName = getLoggerName( false, true );
        settings.unilogConfigPath = CONFIG_PARAMS.baseParams.SYSTEM_UNILOG_CONFIG_PATH;
        Logger::singleton().initGlobal( settings );

        // shell client
        Shell::SInitSettings settings2;
        settings2.shellMode = Shell::EShellMode::CLIENT;
        settings2.messageMode = Shell::EMessageMode::WITHOUT_SIZE;
        settings2.socketFileName = PATH_LOCATOR.getShellImitationDomainSocket();
        Shell shell( INetworkEntity::INVALID_CONN_ID );
        if( ! shell.init(settings2) ){
            return false;
        }

        // send message to agent
        const string message =  ARGS_PARSER.getVal(ENodeArguments::SHELL_COMMAND_TO_AGENT);
        const string response = shell.makeBlockedRequest( message );
        parseResponse( response );
    }
    if( ARGS_PARSER.isKeyExist(ENodeArguments::SHELL_COMMAND_START_WORKER) ){

        if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_WORKER_SIMULATION) ){
            NodeControllerSimulation::SInitSettings settings;
            settings.ctxId = std::stoi( ARGS_PARSER.getVal(ENodeArguments::CONTEXT_ID) );
            settings.missionId = std::stoi( ARGS_PARSER.getVal(ENodeArguments::MISSION_ID) );
            NodeControllerSimulation controller;
            if( controller.init(settings) ){
                controller.launch();
            }
            else{
                return false;
            }
        }
        else if( ARGS_PARSER.isKeyExist(ENodeArguments::NODE_WORKER_REAL) ){
            NodeControllerReal::SInitSettings settings;
            settings.ctxId = std::stoi( ARGS_PARSER.getVal(ENodeArguments::CONTEXT_ID) );
            settings.missionId = std::stoi( ARGS_PARSER.getVal(ENodeArguments::MISSION_ID) );
            NodeControllerReal controller;
            if( controller.init(settings) ){
                controller.launch();
            }
            else{
                return false;
            }
        }
        else{
            // TODO: dump node
        }
    }
    else{
        assert( false );
    }

    return true;
}

int main( int argc, char ** argv, char ** env ){

    if( ! initSingletons(argc, argv, env) ){
        PRELOG_ERR << "============================ DSS NODE START FAILED (singletons area) ============================" << endl;
        return -1;
    }

#if 1
    VS_LOG_INFO << endl;
    VS_LOG_INFO << endl;
    if( ! executeShellCommand() ){
        VS_LOG_ERROR << "============================ DSS NODE START FAILED ============================" << endl;
        return -1;
    }
#else
    UnitTests tests;
    tests.run();
#endif

    VS_LOG_INFO << endl;
    VS_LOG_INFO << endl;
    VS_LOG_INFO << "============================ DSS NODE PROCESS RETURNS '0' ============================" << endl;
    return 0;
}







