QT += network websockets

RESOURCES += \
    $$PWD/com_indeema_QPredix.qrc

include(./QPredixCore/QPredixCore.pri)
include(./QUaa/QUaa.pri)
include(./QTimeSeries/QTimeSeries.pri)
