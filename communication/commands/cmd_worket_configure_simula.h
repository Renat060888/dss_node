#ifndef CMD_CONTEXT_CLOSE_H
#define CMD_CONTEXT_CLOSE_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandWorkerConfigureSimula : public ICommandExternal
{
    friend class CommandFactory;
public:
    CommandWorkerConfigureSimula( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:
    common_types::TUserId m_userId;


};
using PCommandWorkerConfigureSimula = std::shared_ptr<CommandWorkerConfigureSimula>;

#endif // CMD_CONTEXT_CLOSE_H
