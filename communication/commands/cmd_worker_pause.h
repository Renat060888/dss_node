#ifndef CMD_WORKER_PAUSE_H
#define CMD_WORKER_PAUSE_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandWorkerPause : public ICommandExternal
{
    friend class CommandFactory;
public:
    CommandWorkerPause( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:


};
using PCommandWorkerPause = std::shared_ptr<CommandWorkerPause>;

#endif // CMD_WORKER_PAUSE_H
