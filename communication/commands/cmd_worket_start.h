#ifndef CMD_USER_REGISTER_H
#define CMD_USER_REGISTER_H

#include <microservice_common/communication/i_command_external.h>
#include <dss_common/common/common_types.h>

class CommandWorkerStart : public ICommandExternal
{
    friend class CommandFactory;
public:
    CommandWorkerStart( common_types::SIncomingCommandServices * _services );

    virtual bool exec() override;


private:
    std::string m_userIpStr;
    common_types::TPid m_userPid;



};
using PCommandWorkerStart = std::shared_ptr<CommandWorkerStart>;

#endif // CMD_USER_REGISTER_H


