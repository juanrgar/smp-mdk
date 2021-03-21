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

#ifndef MDK_MANAGEMENT_MANAGEDREFERENCE_H_
#define MDK_MANAGEMENT_MANAGEDREFERENCE_H_

#include "Mdk/Reference.h"
#include "Smp/Management/IManagedReference.h"

namespace Smp
{
    namespace Mdk
    {
        namespace Management
        {
            template< typename T> class ManagedReference :
                    public Smp::Mdk::Reference< T>,
                    public virtual Smp::Management::IManagedReference
            {
                public:
                    ManagedReference(
                            Smp::String8 name,
                            Smp::String8 description,
                            Smp::IComponent* parent,
                            Smp::Int64 lower = 0,
                            Smp::Int64 upper = -1) :
                        Smp::Mdk::Reference< T>(name, description, parent),
                        m_lower(lower),
                        m_upper(upper)
                    {
                    }

                    virtual ~ManagedReference(void)
                    {
                    }

                    virtual void AddComponent(
                            Smp::IComponent* component)
                        throw (Smp::Management::IManagedReference::ReferenceFull, Smp::InvalidObjectType)
                    {
                        if ((this->m_upper >= 0) && (Count() >= this->m_upper)) {
                            throw Smp::Management::IManagedReference::ReferenceFull(GetName(), Count());
                        }

                        Reference< T>::Add(component);
                    }

                    virtual void RemoveComponent(
                            Smp::IComponent* component)
                        throw (Smp::Management::IManagedReference::NotReferenced)
                    {
                        if (component == NULL) {
                            return;
                        }

                        T* provider = dynamic_cast< T*>(component);

                        if (provider == NULL) {
                            return;
                        }

                        if (!Reference< T>::Remove(component)) {
                            throw Smp::Management::IManagedReference::NotReferenced(GetName(), component);
                        }
                    }

                    virtual Smp::Int64 Count(void) const 
                    { 
                        return Reference< T>::Count();
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

#endif  // MDK_MANAGEMENT_MANAGEDREFERENCE_H_
