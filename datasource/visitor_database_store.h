#ifndef VISITOR_DATABASE_STORE_H
#define VISITOR_DATABASE_STORE_H

#include <microservice_common/storage/database_manager_base.h>

#include "processing_object_trajectory.h"
#include "processing_object_weather.h"

class VisitorDatabaseStore : public IVisitorProcessingObject
{
public:
    VisitorDatabaseStore( DatabaseManagerBase * _database );

    void batchStore();

private:
    virtual void visit( ProcessingObjectTrajectory * _obj ) override;
    virtual void visit( ProcessingObjectWeather * _obj ) override;

    DatabaseManagerBase * m_database;
};

#endif // VISITOR_DATABASE_STORE_H
