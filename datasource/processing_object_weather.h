#ifndef PROCESSING_OBJECT_WEATHER_H
#define PROCESSING_OBJECT_WEATHER_H

#include "i_processing_object.h"

class ProcessingObjectWeather : public IProcessingObject
{
public:
    ProcessingObjectWeather();

    virtual void accept( IVisitorProcessingObject * _visitor ) override;
    virtual void makeStep( common_types::TLogicStep _step ) override;


private:



    // objrepr + plugin-model
};

#endif // PROCESSING_OBJECT_WEATHER_H
