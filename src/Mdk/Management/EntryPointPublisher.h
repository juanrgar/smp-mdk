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

#ifndef MDK_MANAGEMENT_ENTRYPOINTPUBLISHER_H_
#define MDK_MANAGEMENT_ENTRYPOINTPUBLISHER_H_

#include "Smp/Management/IEntryPointPublisher.h"

namespace Smp
{
    namespace Mdk
    {
        namespace Management
        {
            class EntryPointPublisher :
                public virtual Smp::Management::IEntryPointPublisher
            {
                public:
                    EntryPointPublisher(void);

                    virtual ~EntryPointPublisher(void);

                    virtual const Smp::EntryPointCollection* GetEntryPoints(void) const;

                    virtual const Smp::IEntryPoint* GetEntryPoint(
                            Smp::String8 name) const;

                protected:
                    void AddEntryPoint(
                            Smp::IEntryPoint* entryPoint);

                    void Clear(void);
                private:
                    Smp::EntryPointCollection m_entryPoints;
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_ENTRYPOINTPUBLISHER_H_
