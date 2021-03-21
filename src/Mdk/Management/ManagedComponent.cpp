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

#include "Mdk/Management/ManagedComponent.h"

#include <stdlib.h>
#include <string.h>

using namespace Smp::Mdk::Management;

ManagedComponent::ManagedComponent(void)
{
}

ManagedComponent::ManagedComponent(
        Smp::String8 name, 
        Smp::String8 description, 
        Smp::IComposite* parent)
    throw (Smp::InvalidObjectName) :
        Component(name, description, parent)
{
}

ManagedComponent::~ManagedComponent(void)
{
}

void ManagedComponent::SetName(
        Smp::String8 name)
throw (Smp::InvalidObjectName)
{
    if (Object::ValidateName(name)) {
        if (this->m_name != NULL) {
            free(this->m_name);
        }
        this->m_name = strdup(name);
    } else {
        throw new Smp::InvalidObjectName(name);
    }
}

void ManagedComponent::SetDescription(
        Smp::String8 description)
{
    if (description != NULL) {
        if (this->m_description != NULL) {
            free(this->m_description);
        }
        this->m_description = strdup(description);
    }
}

void ManagedComponent::SetParent(
        Smp::IComposite* parent)
{
    this->m_parent = parent;
}
