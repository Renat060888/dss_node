#ifndef NODE_CONTROLLER_SIMULATION_H
#define NODE_CONTROLLER_SIMULATION_H

#include <dss_common/common/common_types.h>

class NodeControllerSimulation
{
public:
    struct SInitSettings {
        common_types::TContextId ctxId;
        common_types::TMissionId missionId;
    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    NodeControllerSimulation();

    bool init( const SInitSettings & _settings );
    void launch();


private:



};

#endif // NODE_CONTROLLER_SIMULATION_H
