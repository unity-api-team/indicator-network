/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -N -p ofonomodemsimmanager.h -c OfonoModemSimManager ofonomodem.xml org.ofono.SimManager
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "ofonomodemsimmanager.h"

/*
 * Implementation of interface class OfonoModemSimManager
 */

OfonoModemSimManager::OfonoModemSimManager(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OfonoModemSimManager::~OfonoModemSimManager()
{
}
