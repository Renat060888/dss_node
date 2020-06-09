
#include <microservice_common/system/logger.h>
#include <microservice_common/system/daemonizator.h>
#include <microservice_common/communication/shell.h>
#include <dss_common/system/args_parser.h>
#include <dss_common/system/config_reader.h>

//#include <dss_common/system/path_locator.h>

using namespace std;

static bool initSingletons( int _argc, char ** _argv, char ** _env ){

    // cmd line arguments
    ArgsParser::SInitSettings settings;
    settings.argc = _argc;
    settings.argv = _argv;
    settings.printConfigExample = std::bind( & AConfigReader::getConfigExample, & CONFIG_READER );
    settings.commandConvertor = nullptr; // & UNIFIED_COMMAND_CONVERTOR;
    if( ! ARGS_PARSER.init(settings) ){
        return false;
    }

    // configs
    ConfigReader::SIninSettings settings3;
    settings3.mainConfigPath = ARGS_PARSER.getVal(EPlayerArguments::MAIN_CONFIG_PATH_FROM_CONSOLE);
    settings3.commandConvertor = nullptr; // & UNIFIED_COMMAND_CONVERTOR;
    settings3.env = _env;
    settings3.projectName = "dss";
    if( ! CONFIG_READER.init(settings3) ){
        return false;
    }

    // logger
    logger_common::SInitSettings settings2;
    settings2.loggerName = "DssNode";
    settings2.unilogConfigPath = CONFIG_PARAMS.SYSTEM_UNILOG_CONFIG_PATH;

    if( CONFIG_PARAMS.SYSTEM_LOG_TO_STDOUT ){
        settings2.logEndpoints = (logger_common::ELogEndpoints)( (int)settings2.logEndpoints | (int)logger_common::ELogEndpoints::Stdout );
    }
    if( CONFIG_PARAMS.SYSTEM_LOG_TO_FILE ){
        settings2.logEndpoints = (logger_common::ELogEndpoints)( (int)settings2.logEndpoints | (int)logger_common::ELogEndpoints::File );
        settings2.fileName = CONFIG_PARAMS.SYSTEM_LOGFILE_NAME;
        settings2.filePath = CONFIG_PARAMS.SYSTEM_REGULAR_LOGFILE_PATH;
        settings2.rotationSizeMb = CONFIG_PARAMS.SYSTEM_LOGFILE_ROTATION_SIZE_MB;
    }

    Logger::singleton().initGlobal( settings2 );

    return true;
}

static bool executeShellCommand(){

    // TODO: do

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







