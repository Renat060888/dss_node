
#include "processing_object_weather.h"

using namespace std;

ProcessingObjectWeather::ProcessingObjectWeather()
{

}

void ProcessingObjectWeather::accept( IVisitorProcessingObject * _visitor ){
    _visitor->visit( this );
}

void ProcessingObjectWeather::makeStep( common_types::TLogicStep _step ){

}
