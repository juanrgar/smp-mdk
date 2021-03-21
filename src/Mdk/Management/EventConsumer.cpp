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

#include "Mdk/Management/EventConsumer.h"

#include <cstring>

using namespace Smp::Mdk::Management;

EventConsumer::EventConsumer(void)
{
}

EventConsumer::~EventConsumer(void)
{
    Clear();
}

const Smp::EventSinkCollection* EventConsumer::GetEventSinks(void) const
{
    return &(this->mm_eventSinks);
}

Smp::IEventSink* EventConsumer::GetEventSink(
        Smp::String8 name) const
{
    if (name == NULL) {
        return NULL;
    }

    Smp::EventSinkCollection::const_iterator it(this->mm_eventSinks.begin());
    Smp::EventSinkCollection::const_iterator endIt(this->mm_eventSinks.end());

    Smp::IEventSink* es = NULL;

    while ((es == NULL) && (it != endIt)) {
        if (::strcmp(name, (*it)->GetName()) == 0) {
            es = *it;
        }

        ++it;
    }

    return es;
}

void EventConsumer::AddEventSink(
        Smp::IEventSink* eventSink)
{
    if (eventSink == NULL) {
        return;
    }

    Smp::IEventSink* dup = GetEventSink(eventSink->GetName());

    if (dup != NULL) {
        return;
    }

    this->mm_eventSinks.push_back(eventSink);
}

void EventConsumer::Clear(void)
{
    this->mm_eventSinks.clear();
}
