/** This file is part of smp-mdk
 *
 * Copyright (C) 2017 Juan R. Garcia Blanco
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

#ifndef MDK_MANAGEMENT_MANAGEDOBJECT_H_
#define MDK_MANAGEMENT_MANAGEDOBJECT_H_

#include "Mdk/Object.h"
#include "Smp/Management/IManagedObject.h"

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management 
        {
            class ManagedObject :
                public Smp::Mdk::Object,
                public virtual Smp::Management::IManagedObject
            {
                public:
                    ManagedObject(void);
                    ManagedObject(
                            Smp::String8 name,
                            Smp::String8 description)
                        throw (Smp::InvalidObjectName);
                    virtual ~ManagedObject(void);

                    virtual void SetName(
                            Smp::String8 name)
                        throw (Smp::InvalidObjectName);
                    virtual void SetDescription(
                            Smp::String8 description);
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_MANAGEDOBJECT_H_
