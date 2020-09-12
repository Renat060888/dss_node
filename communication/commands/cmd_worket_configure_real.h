#ifndef CMD_CONTEXT_OPEN_H
#define CMD_CONTEXT_OPEN_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandWorkerConfigureReal : public ICommandExternal
{
    friend class CommandFactory;
public:
    CommandWorkerConfigureReal( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:
    common_types::TUserId m_userId;
    std::string m_contextName;



};
using PCommandWorkerConfigureReal = std::shared_ptr<CommandWorkerConfigureReal>;

#endif // CMD_CONTEXT_OPEN_H
