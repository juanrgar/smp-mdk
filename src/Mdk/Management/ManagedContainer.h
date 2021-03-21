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

#ifndef MDK_MANAGEMENT_MANAGEDCONTAINER_H_
#define MDK_MANAGEMENT_MANAGEDCONTAINER_H_

#include "Mdk/Container.h"
#include "Smp/Management/IManagedContainer.h"
#include "Smp/Management/IManagedComponent.h"

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management
        {
            template < typename T> class ManagedContainer :
                public Smp::Mdk::Container< T>,
                public virtual Smp::Management::IManagedContainer
            {
                public:
                    ManagedContainer(
                            Smp::String8 name, 
                            Smp::String8 description, 
                            Smp::IComposite* parent, 
                            Smp::Int64 lower = 0, 
                            Smp::Int64 upper = -1) :
                        Smp::Mdk::Container< T>(name, description, parent),
                        m_lower(lower),
                        m_upper(upper)
                    {
                    }

                    virtual ~ManagedContainer(void)
                    {
                    }

                    virtual void AddComponent(
                            Smp::IComponent* component)
                        throw (Smp::Management::IManagedContainer::ContainerFull, Smp::DuplicateName, Smp::InvalidObjectType)
                    {
                        if ((this->m_upper >= 0) && (Count() >= this->m_upper)) {
                            throw Smp::Management::IManagedContainer::ContainerFull(GetName(), Count());
                        }

                        Container< T>::Add(component);

                        Smp::Management::IManagedComponent* mcomp =
                            dynamic_cast< Smp::Management::IManagedComponent*>(component);

                        if (mcomp != NULL) {
                            mcomp->SetParent(this->m_parent);
                        }
                    }

                    virtual Smp::Int64 Count(void) const 
                    { 
                        return Container< T>::Count();
                    }

                    virtual Smp::Int64 Lower(void) const
                    {
                        return this->m_lower;
                    }

                    virtual Smp::Int64 Upper(void) const
                    {
                        return this->m_upper;
                    }

                private:
                    Smp::Int64 m_lower;
                    Smp::Int64 m_upper;
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_MANAGEDCONTAINER_H_
