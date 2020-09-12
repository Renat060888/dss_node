
#include "cmd_worket_live_processing.h"

using namespace std;

CommandWorkerLiveProcessing::CommandWorkerLiveProcessing( common_types::SIncomingCommandServices * _services )
    : ICommandExternal(_services)
{

}

bool CommandWorkerLiveProcessing::exec(){

    const string resp = "{ \"bla\" : \"ble\" }";
    sendResponse( resp  );

    return true;
}

