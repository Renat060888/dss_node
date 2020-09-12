
#include <microservice_common/system/logger.h>

#include "node_worker_real.h"

using namespace std;

static constexpr const char * PRINT_HEADER = "NodeWorkerReal:";

NodeWorkerReal::NodeWorkerReal()
{

}

NodeWorkerReal::~NodeWorkerReal(){

}

bool NodeWorkerReal::init( const SInitSettings & _settings ){




    return true;
}

bool NodeWorkerReal::configure( const common_types::SConfigReal & _cfg ){

    VS_LOG_INFO << PRINT_HEADER << " call configure" << endl;
    return true;
}

bool NodeWorkerReal::start(){

    VS_LOG_INFO << PRINT_HEADER << " call start" << endl;
    return true;
}

void NodeWorkerReal::pause(){

    VS_LOG_INFO << PRINT_HEADER << " call pause" << endl;
}

void NodeWorkerReal::reset(){

    VS_LOG_INFO << PRINT_HEADER << " call stop" << endl;
}

void NodeWorkerReal::switchLivePlaying( bool _live ){

    VS_LOG_INFO << PRINT_HEADER << " call live playing" << endl;
}







