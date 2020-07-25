ROOT_DIR=../

TEMPLATE = app
TARGET = dss_node

include($${ROOT_DIR}pri/common.pri)

CONFIG -= qt
#CONFIG += release

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable

# TODO: add defines to logger, system monitor, restbed webserver, database, etc...
DEFINES += \
    SWITCH_LOGGER_SIMPLE \
#    SWITCH_LOGGER_ASTRA \
#    OBJREPR_LIBRARY_EXIST \
#    UNIT_TESTS_GOOGLE \

LIBS += \
    -lpthread \
    -lrti1516e \ # TODO: wtf?
    -lfedtime1516e \ # TODO: wtf?
    -lFedTime \     # OpenRTI # TODO: wtf?
    -lOpenRTI \     # OpenRTI # TODO: wtf?
    -lRTI-NG \      # OpenRTI # TODO: wtf?
    -lboost_system \ # TODO: wtf?
    -lboost_program_options \ # TODO: wtf?
    -lboost_filesystem \
    -lboost_regex \
    -ljsoncpp \
    -lmicroservice_common \
    -ldss_common

contains( DEFINES, OBJREPR_LIBRARY_EXIST ){
    message("connect 'unilog' and 'objrepr' libraries")
LIBS += \
    -lunilog \
    -lobjrepr
}

contains( DEFINES, UNIT_TESTS_GOOGLE ){
    message("connect 'gtests' library")
LIBS += \
    -lgtest
}

# NOTE: paths for dev environment ( all projects sources in one dir )
INCLUDEPATH +=  \
    /usr/include/libmongoc-1.0 \
    /usr/include/libbson-1.0 \
    $${ROOT_DIR}/microservice_common/ \ # TODO: avoidance of ugly traverse "../" for this lib's headers
    $${ROOT_DIR}/dss_common/ \ # TODO: avoidance of ugly traverse "../" for this lib's headers

SOURCES += \
        datasource/dispatcher_node_simulation.cpp \
        datasource/node_worker_proxy_simulation.cpp \
        datasource/source_manager_facade.cpp \
        main.cpp \
        node_agent.cpp \
        datasource/node_controller_dump.cpp \
        datasource/node_controller_real.cpp \
        datasource/node_controller_simulation.cpp \
        datasource/node_worker_dump.cpp \
        datasource/node_worker_real.cpp \
        datasource/node_worker_simulation.cpp \
        storage/storage_engine.cpp \
    system/args_parser.cpp \
    system/config_reader.cpp \
    system/path_locator.cpp \
    communication/commands/cmd_context_close.cpp \
    communication/commands/cmd_context_open.cpp \
    communication/commands/cmd_node_agent_ping.cpp \
    communication/commands/cmd_user_ping.cpp \
    communication/commands/cmd_user_register.cpp \
    communication/command_factory.cpp \
    communication/communication_gateway_facade_node.cpp \
    communication/unified_command_convertor_node.cpp \
    datasource/dispatcher_node_real.cpp \
    analyze/analytic_manager_facade.cpp \
    datasource/node_worker_proxy_real.cpp

HEADERS += \
    datasource/dispatcher_node_simulation.h \
    datasource/node_worker_proxy_simulation.h \
    datasource/source_manager_facade.h \
    node_agent.h \
    datasource/node_controller_dump.h \
    datasource/node_controller_real.h \
    datasource/node_controller_simulation.h \
    datasource/node_worker_dump.h \
    datasource/node_worker_real.h \
    datasource/node_worker_simulation.h \
    storage/storage_engine.h \
    system/args_parser.h \
    system/config_reader.h \
    system/path_locator.h \
    communication/commands/cmd_context_close.h \
    communication/commands/cmd_context_open.h \
    communication/commands/cmd_node_agent_ping.h \
    communication/commands/cmd_user_ping.h \
    communication/commands/cmd_user_register.h \
    communication/command_factory.h \
    communication/communication_gateway_facade_node.h \
    communication/unified_command_convertor_node.h \
    datasource/dispatcher_node_real.h \
    analyze/analytic_manager_facade.h \
    datasource/node_worker_proxy_real.h
