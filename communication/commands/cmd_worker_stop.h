#ifndef CMD_WORKER_STOP_H
#define CMD_WORKER_STOP_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandWorkerStop : public ICommandExternal
{
    friend class CommandFactory;
public:
    CommandWorkerStop( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:



};
using PCommandWorkerStop = std::shared_ptr<CommandWorkerStop>;

#endif // CMD_WORKER_STOP_H
