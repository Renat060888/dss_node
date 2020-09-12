#ifndef NODE_WORKER_PROXY_REAL_H
#define NODE_WORKER_PROXY_REAL_H

#include <dss_common/common/common_types.h>

// abstraction
class INodeWorkerReal{
public:
    ~INodeWorkerReal(){}

    virtual void configure( const common_types::SConfigReal & _cfg ) = 0;
    virtual common_types::SNodeWorkerRealState & getState() = 0;

    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    virtual void switchLivePlaying( bool _live ) = 0;
};
using PNodeWorkerReal = std::shared_ptr<INodeWorkerReal>;

// observer
class INodeWorkerRealObserver {
public:
    virtual ~INodeWorkerRealObserver(){}

    virtual void callbackNodeContextChanged( common_types::TNodeId _nodeId, common_types::TContextId _ctxId ) = 0;
};

// proxy
class NodeProxyWorkerReal : public INodeWorkerReal
{
    friend class DispatcherNodeReal;
public:
    NodeProxyWorkerReal();

    virtual void configure( const common_types::SConfigReal & _cfg ) override;
    virtual common_types::SNodeWorkerRealState & getState() override;

    virtual void start() override;
    virtual void pause() override;
    virtual void stop() override;

    virtual void switchLivePlaying( bool _live ) override;

    void addObserver( INodeWorkerRealObserver * _observer );


private:


    // data
    common_types::SNodeWorkerRealState m_state;
    std::vector<INodeWorkerRealObserver *> m_observers;


};
using PNodeProxyWorkerReal = std::shared_ptr<NodeProxyWorkerReal>;

#endif // NODE_WORKER_PROXY_REAL_H
