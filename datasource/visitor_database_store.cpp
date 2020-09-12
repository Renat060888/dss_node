
#include "visitor_database_store.h"

using namespace std;

VisitorDatabaseStore::VisitorDatabaseStore( DatabaseManagerBase * _database )
    : m_database(_database)
{
    // TODO: as interface in StorageEngine ?
}

void VisitorDatabaseStore::visit( ProcessingObjectTrajectory * _obj ){

    common_types::SPersistenceTrajectory traj;
    traj.objId = 0;


    const bool rt = m_database->writeTrajectoryData( 0, {traj} );
}

void VisitorDatabaseStore::visit( ProcessingObjectWeather * _obj ){

}

void VisitorDatabaseStore::batchStore(){

}
