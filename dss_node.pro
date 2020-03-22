ROOT_DIR=../

TEMPLATE = app
TARGET = node

include($${ROOT_DIR}pri/common.pri)

CONFIG -= qt
#CONFIG += release

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable

DEFINES += \
    SWITCH_LOGGER_SIMPLE \

LIBS += \
    -lrti1516e \ # TODO: wtf?
    -lfedtime1516e \ # TODO: wtf?
    -lFedTime \     # OpenRTI # TODO: wtf?
    -lOpenRTI \     # OpenRTI # TODO: wtf?
    -lRTI-NG \      # OpenRTI # TODO: wtf?
    -lboost_program_options \ # TODO: wtf?
    -lmicroservice_common \
    -ldss_common

# NOTE: paths for dev environment ( all projects sources in one dir )
INCLUDEPATH +=  \
    $${ROOT_DIR}/microservice_common/ \

SOURCES += \
        datasource/source_manager.cpp \
        main.cpp \
        node_agent.cpp \
        datasource/node_controller_dump.cpp \
        datasource/node_controller_real.cpp \
        datasource/node_controller_simulation.cpp \
        datasource/node_worker_dump.cpp \
        datasource/node_worker_real.cpp \
        datasource/node_worker_simulation.cpp \
        storage/storage_engine.cpp

HEADERS += \
    datasource/source_manager.h \
    node_agent.h \
    datasource/node_controller_dump.h \
    datasource/node_controller_real.h \
    datasource/node_controller_simulation.h \
    datasource/node_worker_dump.h \
    datasource/node_worker_real.h \
    datasource/node_worker_simulation.h \
    storage/storage_engine.h
