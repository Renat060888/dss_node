#ifndef CMD_NODE_PING_H
#define CMD_NODE_PING_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandNodeWorkerPing : public ICommandExternal
{
public:
    CommandNodeWorkerPing( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:



};
using PCommandNodeWorkerPing = std::shared_ptr<CommandNodeWorkerPing>;

#endif // CMD_NODE_PING_H
