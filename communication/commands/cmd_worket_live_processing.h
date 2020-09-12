#ifndef CMD_USER_PING_H
#define CMD_USER_PING_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandWorkerLiveProcessing : public ICommandExternal
{
    friend class CommandFactory;
public:
    CommandWorkerLiveProcessing( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:
    common_types::TUserId m_userId;



};
using PCommandWorkerLiveProcessing = std::shared_ptr<CommandWorkerLiveProcessing>;

#endif // CMD_USER_PING_H
