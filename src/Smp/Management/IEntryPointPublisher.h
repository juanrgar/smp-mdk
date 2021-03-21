//
// Title:
//      IEntryPointPublisher.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Mapping
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines the IEntryPointPublisher interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IENTRYPOINTPUBLISHER_H
#define SMP_MANAGEMENT_IENTRYPOINTPUBLISHER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IModel.h"
#include "Smp/IEntryPoint.h"

// ----------------------------------------------------------------------------
// --------------------------- IEntryPointPublisher interface -----------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management
    {
        /// Entry point publisher.
        /// An entry point publisher is a model that holds entry points,
        /// which may be registered,
        /// for example, with the Scheduler or the Event Manager services.
        /// @remarks This is an optional interface.
        ///          It needs to be implemented for managed models only,
        ///          which want to allow access to entry points by name.
        class IEntryPointPublisher : public virtual IModel
        {
        public:
            /// Get all entry points.
            /// Query for the collection of all entry points of the model.
            /// @return Collection of entry points.
            /// @remarks The collection may be empty if no entry points exist.
            virtual const EntryPointCollection* GetEntryPoints() const = 0;

            /// Get an entry point by name.
            /// Query for an entry point of this model by its name.
            /// @param  name Entry point name.
            /// @return  Entry point with given name, or null if no
            ///          entry point with given name could be found.
            /// @remarks The returned entry point may be null if no
            ///          entry point with the given name could be found.
            virtual const IEntryPoint* GetEntryPoint(String8 name) const = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IENTRYPOINTPUBLISHER_H

/***********
 * History *
 ***********/

//$Log: IEntryPointPublisher.h,v $
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

