#ifndef NODE_CONTROLLER_REAL_H
#define NODE_CONTROLLER_REAL_H

#include <dss_common/common/common_types.h>

class NodeControllerReal
{
public:
    struct SInitSettings {
        common_types::TNodeId agentId;
        common_types::TNodeId workerId;
        common_types::TContextId ctxId;
        common_types::TMissionId missionId;
    };

    struct SState {
        SInitSettings settings;
        std::string lastError;
    };

    NodeControllerReal();

    bool init( const SInitSettings & _settings );
    void launch();


private:
    void processMessageConfigure();
    void processMessageStart();
    void processMessagePause();
    void processMessageStop();
    void processMessageSwitchLiveProcessing();




};

#endif // NODE_CONTROLLER_REAL_H
