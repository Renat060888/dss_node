#ifndef NODE_WORKER_SIMULATION_H
#define NODE_WORKER_SIMULATION_H

#include <microservice_common/system/library_loader.h>

class NodeWorkerSimulation
{
public:
    struct SInitSettings {

    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    NodeWorkerSimulation();
    ~NodeWorkerSimulation();

    bool init( const SInitSettings & _settings );
    const SState & getState(){ return m_state; }




private:


    // data
    SState m_state;

    // service
    LibraryLoader m_libraryLoader;


};

#endif // NODE_WORKER_SIMULATION_H
