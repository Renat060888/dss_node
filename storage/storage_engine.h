#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H


class StorageEngineFacade
{
public:
    struct SServiceLocator {

    };

    struct SInitSettings {
        SServiceLocator services;
    };

    StorageEngineFacade();
    ~StorageEngineFacade();

    bool init( const SInitSettings & _settings );

    void shutdown();

};

#endif // STORAGE_ENGINE_H
