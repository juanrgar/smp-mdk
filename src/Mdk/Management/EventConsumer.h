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

#ifndef MDK_MANAGEMENT_EVENTCONSUMER_H_
#define MDK_MANAGEMENT_EVENTCONSUMER_H_

#include "Smp/Management/IEventConsumer.h"

namespace Smp
{
    namespace Mdk
    {
        namespace Management
        {
            class EventConsumer :
                public virtual Smp::Management::IEventConsumer
            {
                public:
                    EventConsumer(void);

                    virtual ~EventConsumer(void);

                    virtual const Smp::EventSinkCollection* GetEventSinks(void) const;

                    virtual Smp::IEventSink* GetEventSink(
                            Smp::String8 name) const;

                protected:
                    void AddEventSink(
                            Smp::IEventSink* eventSink);

                    void Clear(void);

                private:
                    Smp::EventSinkCollection mm_eventSinks;
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_EVENTCONSUMER_H_
