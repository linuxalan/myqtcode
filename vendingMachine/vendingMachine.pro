#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T15:30:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vendingMachine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        vm_mainwidget.cpp \
    modules/sale_module/vm_salegoods.cpp \
    modules/sale_module/vm_addgoods.cpp \
    modules/sale_module/vm_storagegoods.cpp \
    modules/find_module/vm_findgoods.cpp \
    modules/set_module/vm_setting.cpp

HEADERS += \
        vm_mainwidget.h \
    modules/sale_module/vm_salegoods.h \
    modules/sale_module/vm_addgoods.h \
    modules/sale_module/vm_storagegoods.h \
    modules/find_module/vm_findgoods.h \
    modules/set_module/vm_setting.h

FORMS += \
        vm_mainwidget.ui \
    modules/sale_module/vm_salegoods.ui \
    modules/sale_module/vm_addgoods.ui \
    modules/sale_module/vm_storagegoods.ui \
    modules/find_module/vm_findgoods.ui \
    modules/set_module/vm_setting.ui
