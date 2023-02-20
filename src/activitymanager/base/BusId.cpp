// Copyright (c) 2009-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include <regex>

#include "BusId.h"
#include "Subscriber.h"

BusId::BusId()
    : m_type(BusNull)
{
}

BusId::BusId(const std::string& id, BusIdType type)
    : m_id(id)
    , m_type(type)
{
}

BusId::BusId(const char *id, BusIdType type)
    : m_id(id)
    , m_type(type)
{
}

BusId::BusId(const Subscriber& subscriber)
    : m_id(subscriber.m_id.m_id)
    , m_type(subscriber.m_id.m_type)
{
}

BusIdType BusId::getType() const
{
    return m_type;
}

std::string BusId::getId() const
{
    return m_id;
}

std::string BusId::getString() const
{
    return getString(m_id.c_str(), m_type);
}

std::string BusId::getString(const std::string& id, BusIdType type)
{
    return getString(id.c_str(), type);
}

std::string BusId::getString(const char *id, BusIdType type)
{
    if (id == nullptr || type == BusNull)
        return std::string("invalid");
    else if (type == BusApp)
        return std::string("appId:") + id;
    else if (type == BusService)
        return std::string("serviceId:") + id;
    else
        return std::string("anonId:") + id;
}

MojErr BusId::toJson(MojObject& rep) const
{
    MojErr err = MojErrNone;

    if (m_type == BusApp) {
        err = rep.putString(_T("appId"), m_id.c_str());
        MojErrCheck(err);
    } else if (m_type == BusService) {
        err = rep.putString(_T("serviceId"), m_id.c_str());
        MojErrCheck(err);
    } else {
        err = rep.putString(_T("anonId"), m_id.c_str());
    }

    return MojErrNone;
}

BusId& BusId::operator=(const Subscriber& rhs)
{
    m_id = rhs.m_id.m_id;
    m_type = rhs.m_id.m_type;

    return *this;
}

bool BusId::operator<(const BusId& rhs) const
{
    if (m_type != rhs.m_type)
        return (m_type < rhs.m_type);
    else
        return (m_id < rhs.m_id);
}

bool BusId::operator!=(const BusId& rhs) const
{
    return ((m_id != rhs.m_id) || (m_type != rhs.m_type));
}

bool BusId::operator==(const BusId& rhs) const
{
    return ((m_id == rhs.m_id) && (m_type == rhs.m_type));
}

bool BusId::operator!=(const Subscriber& rhs) const
{
    return (*this != rhs.m_id);
}

bool BusId::operator==(const Subscriber& rhs) const
{
    return (*this == rhs.m_id);
}

bool BusId::operator!=(const std::string& rhs) const
{
    return (getString() != rhs);
}

bool BusId::operator==(const std::string& rhs) const
{
    return (getString() == rhs);
}

bool BusId::isLunaSend() const
{
    return m_type == BusService && std::regex_match(m_id, std::regex("com.webos.lunasend-[0-9]+"));
}
