
#include "processing_object_trajectory.h"

using namespace std;

ProcessingObjectTrajectory::ProcessingObjectTrajectory()
{

}

void ProcessingObjectTrajectory::accept( IVisitorProcessingObject * _visitor ){
    _visitor->visit( this );
}

void ProcessingObjectTrajectory::makeStep( common_types::TLogicStep _step ){

}



