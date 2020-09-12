#ifndef NODE_WORKER_PROXY_DUMP_H
#define NODE_WORKER_PROXY_DUMP_H

#include <dss_common/common/common_types.h>

class NodeProxyWorkerDump
{
    friend class DispatcherNodeDump;
public:
    NodeProxyWorkerDump();



private:



};
using PNodeProxyWorkerDump = std::shared_ptr<NodeProxyWorkerDump>;

#endif // NODE_WORKER_PROXY_DUMP_H
