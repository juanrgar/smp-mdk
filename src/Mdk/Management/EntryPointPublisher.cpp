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

#include "Mdk/Management/EntryPointPublisher.h"

#include <cstring>

using namespace Smp::Mdk::Management;

EntryPointPublisher::EntryPointPublisher(void)
{
}

EntryPointPublisher::~EntryPointPublisher(void)
{
    Clear();
}

const Smp::EntryPointCollection* EntryPointPublisher::GetEntryPoints(void) const
{
    return &(this->m_entryPoints);
}

const Smp::IEntryPoint* EntryPointPublisher::GetEntryPoint(
        Smp::String8 name) const
{
    if (name == NULL) {
        return NULL;
    }

    Smp::EntryPointCollection::const_iterator it(this->m_entryPoints.begin());
    Smp::EntryPointCollection::const_iterator endIt(this->m_entryPoints.end());

    const Smp::IEntryPoint* ei = NULL;

    while ((ei == NULL) && (it != endIt)) {
        if (::strcmp(name, (*it)->GetName()) == 0) {
            ei = *it;
        }

        ++it;
    }

    return ei;
}

void EntryPointPublisher::AddEntryPoint(
        Smp::IEntryPoint* entryPoint)
{
    if (entryPoint == NULL) {
        return;
    }

    const Smp::IEntryPoint* dup = GetEntryPoint(entryPoint->GetName());

    if (dup != NULL) {
        return;
    }

    this->m_entryPoints.push_back(entryPoint);
}

void EntryPointPublisher::Clear(void)
{
    this->m_entryPoints.clear();
}
