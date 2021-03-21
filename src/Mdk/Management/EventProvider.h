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

#ifndef MDK_MANAGEMENT_EVENTPROVIDER_H_
#define MDK_MANAGEMENT_EVENTPROVIDER_H_

#include "Smp/Management/IEventProvider.h"

namespace Smp 
{
    namespace Mdk
    {
        namespace Management
        {
            class EventProvider :
                public virtual Smp::Management::IEventProvider
            {
                public:
                    EventProvider(void);

                    virtual ~EventProvider(void);

                    virtual const Smp::EventSourceCollection* GetEventSources(void) const;

                    virtual Smp::IEventSource* GetEventSource(
                            Smp::String8 name) const;

                protected:
                    void AddEventSource(
                            Smp::IEventSource* eventSource);

                    void Clear(void);

                private:
                    Smp::EventSourceCollection m_eventSources;
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_EVENTPROVIDER_H_
