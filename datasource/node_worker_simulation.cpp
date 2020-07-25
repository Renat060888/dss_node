
#include "node_worker_simulation.h"

using namespace std;

static constexpr const char * PRINT_HEADER = "NodeWorkerSimula:";

NodeWorkerSimulation::NodeWorkerSimulation()
{

}

NodeWorkerSimulation::~NodeWorkerSimulation()
{

}

bool NodeWorkerSimulation::init( const SInitSettings & _settings ){

    m_state.settings = _settings;







    return true;
}
