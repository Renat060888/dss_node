
#include "visitor_network_notify.h"

using namespace std;

VisitorNetworkNotify::VisitorNetworkNotify()
{
    // as interface in CommunicationGateway ?
}

void VisitorNetworkNotify::visit( ProcessingObjectTrajectory * _obj ){

    // emit via objrepr->push
}

void VisitorNetworkNotify::visit( ProcessingObjectWeather * _obj ){

    // emit via objrepr->push
}

void VisitorNetworkNotify::batchNotify(){

}

