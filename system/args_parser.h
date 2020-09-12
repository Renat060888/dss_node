#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <microservice_common/system/a_args_parser.h>

enum class ENodeArguments {
    SHELL_COMMAND_START_AGENT       = 1 << 0,
    SHELL_COMMAND_TO_AGENT          = 1 << 1,
    SHELL_COMMAND_START_WORKER      = 1 << 2,
    AS_DAEMON                       = 1 << 3,
    MAIN_CONFIG_PATH_FROM_CONSOLE   = 1 << 4,
    NODE_AGENT_SIMULATION           = 1 << 5,
    NODE_AGENT_REAL                 = 1 << 6,
    NODE_AGENT_DUMP                 = 1 << 7,
    NODE_WORKER_SIMULATION          = 1 << 8,
    NODE_WORKER_REAL                = 1 << 9,
    NODE_WORKER_DUMP                = 1 << 10,
    NODE_WORKER_ID                  = 1 << 11,
    NODE_AGENT_ID                   = 1 << 12,
    CONTEXT_ID                      = 1 << 13,
    MISSION_ID                      = 1 << 14,
    UNDEFINED                       = 1 << 31
};

class ArgsParser : public AArgsParser<ENodeArguments>
{
public:
    static ArgsParser & singleton(){
        static ArgsParser instance;
        return instance;
    }


private:
    ArgsParser(){}
    ~ArgsParser(){}

    ArgsParser( const ArgsParser & _inst ) = delete;
    ArgsParser & operator=( const ArgsParser & _inst ) = delete;

    virtual bpo::options_description getArgumentsDescrTemplateMethodPart() override;
    virtual void checkArgumentsTemplateMethodPart( const bpo::variables_map & _varMap ) override;
    virtual void version() override;
    virtual void about() override;

};
#define ARGS_PARSER ArgsParser::singleton()

#endif // ARGS_PARSER_H
