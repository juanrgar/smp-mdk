//
// Title:
//      IEventConsumer.h
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
//      This file defines the IEventConsumer interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IEVENTCONSUMER_H
#define SMP_MANAGEMENT_IEVENTCONSUMER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/IEventSink.h"

// ----------------------------------------------------------------------------
// --------------------------- IEventConsumer interface -----------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management
    {
        /// Event consumer.
        /// Component that holds event sinks, which may
        /// be subscribed to other component's event sources.
        /// @remarks This is an optional interface.
        ///          It needs to be implemented for managed components only, 
        ///          which want to allow access to event sinks by name.
        class IEventConsumer : public virtual IComponent
        {
        public:
            /// Get all event sinks.
            /// Query for the collection of all event sinks of the component.
            /// @return Collection of event sinks.
            /// @remarks The collection may be empty if no event sinks exist.
            virtual const EventSinkCollection* GetEventSinks() const = 0;

            /// Get an event sink by name.
            /// Query for an event sink of this component by its name.
            /// @param   name Event sink name.
            /// @return  Event sink with the given name, or null if no
            ///          event sink with the given name could be found.
            /// @remarks The returned event sink may be null if no
            ///          event sink with the given name could be found.
            virtual IEventSink* GetEventSink(String8 name) const = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IEVENTCONSUMER_H

/***********
 * History *
 ***********/

//$Log: IEventConsumer.h,v $
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

