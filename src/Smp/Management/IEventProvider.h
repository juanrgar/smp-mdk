//
// Title:
//      IEventProvider.h
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
//      This file defines the IEventProvider interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IEVENTPUBLISHER_H
#define SMP_MANAGEMENT_IEVENTPUBLISHER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/IEventSource.h"

// ----------------------------------------------------------------------------
// --------------------------- IEventProvider interface -----------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management
    {
        /// Event publisher.
        /// Component that holds event sources, which allow
        /// other components to subscribe their event sinks.
        /// @remarks This is an optional interface.
        ///          It needs to be implemented for managed components only, 
        ///          which want to allow access to event sources by name.
        class IEventProvider : public virtual IComponent
        {
        public:
            /// Get all event sources.
            /// Query for the collection of all event sources of the component.
            /// @return  Collection of event sources.
            /// @remarks The collection may be empty if no event sources exist.
            virtual const EventSourceCollection* GetEventSources() const = 0;

            /// Get an event source by name.
            /// Query for an event source of this component by its name.
            /// @param   name Event source name.
            /// @return  Event source with the given name, or null if no
            ///          event source with the given name could be found.
            /// @remarks The returned event source may be null if no
            ///          event source with the given name could be found.
            virtual IEventSource* GetEventSource(String8 name) const = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IEVENTPUBLISHER_H

/***********
 * History *
 ***********/

//$Log: IEventProvider.h,v $
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

