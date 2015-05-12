/*
 * Copyright © 2012-2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Voß <thomas.voss@canonical.com>
 */
#ifndef LOCATION_SERVICE_LOCATION_CONNECTIVITY_OFONO_H
#define LOCATION_SERVICE_LOCATION_CONNECTIVITY_OFONO_H

#include <core/dbus/bus.h>
#include <core/dbus/object.h>
#include <core/dbus/property.h>
#include <core/dbus/service.h>
#include <core/dbus/types/object_path.h>
#include <core/dbus/types/struct.h>
#include <core/dbus/types/stl/map.h>
#include <core/dbus/types/stl/string.h>
#include <core/dbus/types/stl/tuple.h>
#include <core/dbus/types/stl/vector.h>
#include<com/ubuntu/connectivity/util.h>

namespace org
{
struct Ofono
{
static const std::string& name()
{
    static const std::string s{"org.ofono"};
    return s;
}
struct Manager
{
    static const std::string& name()
    {
        static const std::string s{"org.ofono.Manager"};
        return s;
    }

    struct GetModems
    {
        static const std::string& name()
        {
            static const std::string s{"GetModems"};
            return s;
        }

        typedef Manager Interface;
        typedef std::vector<
            core::dbus::types::Struct<
                core::dbus::types::ObjectPath
            >
        > ResultType;

        static std::chrono::milliseconds default_timeout()
        {
            return std::chrono::seconds{1};
        }
    };

    struct ModemAdded
    {
        static const std::string& name()
        {
            static const std::string s{"ModemAdded"};
            return s;
        }

        typedef Manager Interface;
        typedef std::tuple<core::dbus::types::ObjectPath, std::map<std::string, std::string>> ArgumentType;
    };

    struct ModemRemoved
    {
        static const std::string& name()
        {
            static const std::string s{"ModemRemoved"};
            return s;
        }

        typedef Manager Interface;
        typedef core::dbus::types::ObjectPath ArgumentType;
    };

    struct Modem
    {
        struct NetworkRegistration
        {
            static const std::string& name()
            {
                static const std::string s{"org.ofono.NetworkRegistration"};
                return s;
            }

            struct GetProperties
            {
                static const std::string& name()
                {
                    static const std::string s{"GetProperties"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::map<std::string, core::dbus::types::Variant<>> ValueType;

                static std::chrono::milliseconds default_timeout()
                {
                    return std::chrono::seconds{1};
                }
            };

            struct Mode
            {
                static const char* unregistered() { return "unregistered"; }
                static const char* registered() { return "registered"; }
                static const char* searching() { return "searching"; }
                static const char* denied() { return "denied"; }
                static const char* unknown() { return "unknown"; }
                static const char* roaming() { return "roaming"; }

                static const std::string& name()
                {
                    static const std::string s{"Mode"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::string ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            struct LocationAreaCode
            {
                static const std::string& name()
                {
                    static const std::string s{"LocationAreaCode"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::uint16_t ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            struct CellId
            {
                static const std::string& name()
                {
                    static const std::string s{"CellId"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::uint32_t ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            struct MobileCountryCode
            {
                static const std::string& name()
                {
                    static const std::string s{"MobileCountryCode"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::string ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            struct MobileNetworkCode
            {
                static const std::string& name()
                {
                    static const std::string s{"MobileNetworkCode"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::string ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            struct Technology
            {
                static const char* gsm() { return "gsm"; }
                static const char* edge() { return "edge"; }
                static const char* umts() { return "umts"; }
                static const char* hspa() { return "hspa"; }
                static const char* lte() { return "lte"; }

                static const std::string& name()
                {
                    static const std::string s{"Technology"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::string ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            struct Strength
            {
                static const std::string& name()
                {
                    static const std::string s{"Strength"};
                    return s;
                }

                typedef NetworkRegistration Interface;
                typedef std::int8_t ValueType;
                static const bool readable = true;
                static const bool writable = false;
            };

            NetworkRegistration(const std::shared_ptr<core::dbus::Object>& object)
                : object(object),
                  properties{}
            {
                auto result = object->invoke_method_synchronously<GetProperties, GetProperties::ValueType>();
                if (result.is_error())
                    connectivity::throw_dbus_exception(result.error());

                properties = result.value();
            }

            template<typename Property>
            typename Property::ValueType get(
                    const typename Property::ValueType& default_value = typename Property::ValueType{}) const
            {
                try
                {
                    core::dbus::types::Any value = properties.at(Property::name()).get();
                    typename Property::ValueType result; value.reader() >> result;

                    return result;
                } catch(...)
                {
                }

                return default_value;
            }

            std::shared_ptr<core::dbus::Object> object;
            GetProperties::ValueType properties;
        };

        Modem(const std::shared_ptr<core::dbus::Service>& service,
              const std::shared_ptr<core::dbus::Object>& object)
            : service(service),
              object(object),
              network_registration{object}
        {
        }

        std::shared_ptr<core::dbus::Service> service;
        std::shared_ptr<core::dbus::Object> object;
        NetworkRegistration network_registration;
    };

    Manager(const core::dbus::Bus::Ptr& bus)
        : service(core::dbus::Service::use_service<org::Ofono>(bus)),
          object(service->object_for_path(core::dbus::types::ObjectPath("/"))),
          modem_added(object->get_signal<ModemAdded>()),
          modem_removed(object->get_signal<ModemRemoved>())
    {
        auto result = object->invoke_method_synchronously<GetModems, GetModems::ResultType>();

        if (result.is_error())
            connectivity::throw_dbus_exception(result.error());

        for (const auto& element : result.value())
        {
            modems.insert(
                        std::make_pair(
                            element.value,
                            Modem
                            {
                                service,
                                service->object_for_path(element.value)
                            }));
        }

        modem_added->connect([this](const ModemAdded::ArgumentType& arg)
        {
            std::lock_guard<std::mutex> lg(guard);
            modems.insert(
                        std::make_pair(
                            std::get<0>(arg),
                            Modem{
                                service,
                                service->object_for_path(std::get<0>(arg))
                            }));
        });

        modem_removed->connect([this](const ModemRemoved::ArgumentType& arg)
        {
            std::lock_guard<std::mutex> lg(guard);
            modems.erase(arg);
        });
    }

    void for_each_modem(const std::function<void(const Modem&)>& functor) const
    {
        std::lock_guard<std::mutex> lg(guard);
        for (const auto& modem : modems)
        {
            functor(modem.second);
        }
    }

    std::shared_ptr<core::dbus::Service> service;
    std::shared_ptr<core::dbus::Object> object;
    std::shared_ptr<core::dbus::Signal<ModemAdded, ModemAdded::ArgumentType>> modem_added;
    std::shared_ptr<core::dbus::Signal<ModemRemoved, ModemRemoved::ArgumentType>> modem_removed;
    mutable std::mutex guard;
    std::map<core::dbus::types::ObjectPath, Modem> modems;
};
};
}

#endif // LOCATION_SERVICE_LOCATION_CONNECTIVITY_OFONO_H