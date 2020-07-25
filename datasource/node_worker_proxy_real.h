#ifndef NODE_WORKER_PROXY_REAL_H
#define NODE_WORKER_PROXY_REAL_H

#include <memory>

#include <dss_common/common/common_types.h>

class INodeWorkerReal{
public:
    ~INodeWorkerReal(){}

    virtual common_types::SNodeWorkerRealState & getState() = 0;
    virtual void start() = 0;
};
using PNodeWorkerReal = std::shared_ptr<INodeWorkerReal>;


class NodeWorkerProxyReal : public INodeWorkerReal
{
    friend class DispatcherNodeReal;
public:
    NodeWorkerProxyReal();

    virtual common_types::SNodeWorkerRealState & getState() override;
    virtual void start() override;


private:


    // data
    common_types::SNodeWorkerRealState m_state;


};
using PNodeWorkerProxyReal = std::shared_ptr<NodeWorkerProxyReal>;

#endif // NODE_WORKER_PROXY_REAL_H
