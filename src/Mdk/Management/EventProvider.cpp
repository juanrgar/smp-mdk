/** This file is part of smp-mdk
 *
 * Copyright (C) 2018 Juan R. Garcia Blanco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Mdk/Management/EventProvider.h"

#include <cstring>

using namespace Smp::Mdk::Management;

EventProvider::EventProvider(void)
{
}

EventProvider::~EventProvider(void)
{
    Clear();
}

const Smp::EventSourceCollection* EventProvider::GetEventSources(void) const
{
    return &(this->m_eventSources);
}

Smp::IEventSource* EventProvider::GetEventSource(
        Smp::String8 name) const
{
    if (name == NULL) {
        return NULL;
    }

    Smp::EventSourceCollection::const_iterator it(this->m_eventSources.begin());
    Smp::EventSourceCollection::const_iterator endIt(this->m_eventSources.end());

    Smp::IEventSource* es = NULL;

    while ((es == NULL) && (it != endIt)) {
        if (::strcmp(name, (*it)->GetName()) == 0) {
            es = *it;
        }

        ++it;
    }

    return es;
}

void EventProvider::AddEventSource(
        Smp::IEventSource* eventSource)
{
    if (eventSource == NULL) {
        return;
    }

    Smp::IEventSource* dup = GetEventSource(eventSource->GetName());

    if (dup != NULL) {
        return;
    }

    this->m_eventSources.push_back(eventSource);
}

void EventProvider::Clear(void)
{
    this->m_eventSources.clear();
}
