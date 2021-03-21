//
// Title:
//      IEntryPoint.h
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
//      This file defines the IEntryPoint interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IENTRYPOINT_H
#define SMP_IENTRYPOINT_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ---------------------------- IEntryPoint interface -------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Entry point for IScheduler or IEventManager.
    /// Provide a notification method (event handler) that can be called
    /// by the Scheduler or Event Manager when an event is emitted.
    class IEntryPoint : public virtual IObject
    {
    public:
        /// Entry point owner.
        /// This method returns the Component that owns the entry point.
        /// @return  Owner of entry point.
        /// @remarks This is required to be able to store and later restore
        ///          entry points.
        virtual IComponent* GetOwner(void) const = 0;

        /// Entry point execution.
        /// Method that is called when an associated event is emitted.
        /// @remarks Models providing entry points must ensure that these 
        ///          entry points do not throw exceptions.
        virtual void Execute(void) const = 0;
    };
}

namespace Smp
{
    /// Collection of entry points.
    /// An entry point collection is an ordered collection of entry points,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<const IEntryPoint*> EntryPointCollection;
}

#endif // SMP_IENTRYPOINT_H

/***********
 * History *
 ***********/

//$Log: IEntryPoint.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

