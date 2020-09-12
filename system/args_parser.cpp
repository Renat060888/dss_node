
#include <dss_common/common/common_types.h>

#include "args_parser.h"

using namespace std;

bpo::options_description ArgsParser::getArgumentsDescrTemplateMethodPart() {

    bpo::options_description desc("Available options");

    desc.add_options()
            ("help,h","show this help")
            ("version,V", "version of program")
            ("about,A", "description")
            ("main-config,C", bpo::value<std::string>(), "main config file")
            ("main-config-sample,P", "print main config sample")
            ("daemon,D", "start as daemon")
            ("start-agent", "start node agent")
            ("stop-agent", "stop node agent")
            ("start-worker", "start node worker")
            ("agent-type", bpo::value<std::string>(), "type of node agent ( simulation | real | dump )")
            ("worker-type", bpo::value<std::string>(), "type of node worker ( simulation | real | dump )")
            ("worker-id", bpo::value<common_types::TNodeId>(), "id of launched worker")
            ("context-id", bpo::value<common_types::TContextId>(), "launch in context id")
            ("mission-id", bpo::value<common_types::TMissionId>(), "launch in mission id")
            ;

    return desc;
}

void ArgsParser::checkArgumentsTemplateMethodPart( const bpo::variables_map & _varMap ) {

    if( _varMap.find("main-config") != _varMap.end() ){
        m_commmandLineArgs[ENodeArguments::MAIN_CONFIG_PATH_FROM_CONSOLE] = _varMap["main-config"].as<std::string>();
    }

    if( _varMap.find("daemon") != _varMap.end() ){
        m_commmandLineArgs[ENodeArguments::AS_DAEMON] = "bla-bla";
    }

    if( _varMap.find("start-agent") != _varMap.end() ){
        m_commmandLineArgs[ENodeArguments::SHELL_COMMAND_START_AGENT] = "bla-bla";
    }

    if( _varMap.find("stop-agent") != _varMap.end() ){
        m_commmandLineArgs[ENodeArguments::SHELL_COMMAND_TO_AGENT]
            = AArgsParser::getSettings().commandConvertor->getCommandFromProgramArgs( { {"", ""} } );
    }

    if( _varMap.find("start-worker") != _varMap.end() ){
        m_commmandLineArgs[ENodeArguments::SHELL_COMMAND_START_WORKER] = "bla-bla";

        if( _varMap.find("worker-id") != _varMap.end() ){
            m_commmandLineArgs[ENodeArguments::NODE_WORKER_ID] = _varMap["worker-id"].as<std::string>();
        }
        else{
            // TODO: return false
            return;
        }
    }

    if( _varMap.find("agent-type") != _varMap.end() ){
        const string agentType = _varMap["agent-type"].as<std::string>();

        if( "simulation" == agentType ){
            m_commmandLineArgs[ENodeArguments::NODE_AGENT_SIMULATION] = "bla-bla";
        }
        else if( "real" == agentType ){
            m_commmandLineArgs[ENodeArguments::NODE_AGENT_REAL] = "bla-bla";
        }
        else if( "dump" == agentType ){
            m_commmandLineArgs[ENodeArguments::NODE_AGENT_DUMP] = "bla-bla";
        }
        else{

        }
    }

    if( _varMap.find("worker-type") != _varMap.end() ){
        const string workerType = _varMap["worker-type"].as<std::string>();

        if( "simulation" == workerType ){
            m_commmandLineArgs[ENodeArguments::NODE_WORKER_SIMULATION] = "bla-bla";
        }
        else if( "real" == workerType ){
            m_commmandLineArgs[ENodeArguments::NODE_WORKER_REAL] = "bla-bla";
        }
        else if( "dump" == workerType ){
            m_commmandLineArgs[ENodeArguments::NODE_WORKER_DUMP] = "bla-bla";
        }
        else{

        }
    }
}

void ArgsParser::version() {

    // TODO: do
}

void ArgsParser::about() {

    // TODO: do
}
