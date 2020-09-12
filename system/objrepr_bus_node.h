#ifndef OBJREPR_BUS_PLAYER_H
#define OBJREPR_BUS_PLAYER_H

#include <microservice_common/system/objrepr_bus.h>

class ObjreprBusNode : public ObjreprBus
{
public:
    ObjreprBusNode();

    // NOTE: stuff for derived classes ( video-server-object, player-object, etc... )



private:





};
#define OBJREPR_BUS ObjreprBusNode::singleton()

#endif // OBJREPR_BUS_PLAYER_H
