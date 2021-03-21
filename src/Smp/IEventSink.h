//
// Title:
//      IEventSink.h
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
//      This file defines the IEventSink interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IEVENTSINK_H
#define SMP_IEVENTSINK_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ---------------------------- IEventSink interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Event sink that can be subscribed to event source (IEventSource).
    /// Provide notification method (event handler) that 
    /// can be called by event publishers when an event is emitted.
    class IEventSink : public virtual IObject
    {
    public:
        /// Event notification.
        /// This event handler method is called when an event is emitted.
        /// @param sender Object sending the event.
        /// @param arg Event argument.
        virtual void Notify(IObject* sender, AnySimple arg) = 0;
    };
}

namespace Smp
{
    /// Collection of event sinks.
    /// An event sink collection is an ordered collection of event sinks,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IEventSink*> EventSinkCollection;
}

#endif // SMP_IEVENTSINK_H

/***********
 * History *
 ***********/

//$Log: IEventSink.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

