//
// Title:
//      IEventSource.h
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
//      This file defines the IEventSource interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IEVENTSOURCE_H
#define SMP_IEVENTSOURCE_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exceptions.h"
#include "Smp/IEventSink.h"

// ----------------------------------------------------------------------------
// ---------------------------- IEventSource interface ------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    static const Smp::String8 AlreadySubscribedTemplate = "Sink '%s' already subscribed to source '%s'";
    static const Smp::String8 NotSubscribedTemplate     = "Sink '%s' not subscribed to source '%s'";
    static const Smp::String8 InvalidEventSinkTemplate  = "Sink '%s' is not of valid type for source '%s'";

    /// Event source that event sinks (IEventSink) can subscribe to.
    /// Allow event consumers to subscribe or unsubscribe to/from an event.
    class IEventSource : public virtual IObject
    {
    public:
        /// Event sink is already subscribed.
        /// This exception is raised when trying to subscribe an event sink 
        /// to an event source that is already subscribed.
        class AlreadySubscribed : public Smp::Exception
        {
        public:
            /// Event source the event sink is subscribed to.
            const IEventSource* eventSource;
            /// Event sink that is already subscribed.
            const IEventSink*   eventSink;

            AlreadySubscribed(
                const IEventSource* _eventSource,
                const IEventSink*   _eventSink) throw() :
            Smp::Exception("AlreadySubscribed"),
                eventSource(_eventSource),
                eventSink  (_eventSink)
            {
                Smp::String8 sourceName = "NULL";
                Smp::String8 sinkName = "NULL";

                if (eventSource)
                {
                    sourceName = eventSource->GetName();
                }
                if (eventSink)
                {
                    sinkName = eventSink->GetName();
                }

                description = new Char8[strlen(AlreadySubscribedTemplate) 
                    + strlen(sourceName)
                    + strlen(sinkName)];

                sprintf(description, AlreadySubscribedTemplate, 
                    sinkName, 
                    sourceName);
            }

            ~AlreadySubscribed() throw() {}
        };

        /// Event sink is not subscribed.
        /// This exception is raised when trying to unsubscribe an event sink
        /// from an event source that is not subscribed to it.
        class NotSubscribed : public Smp::Exception
        {
        public:
            /// Event source the event sink is not subscribed to.
            const IEventSource* eventSource;
            /// Event sink that is not subscribed.
            const IEventSink* eventSink;

            NotSubscribed(
                const IEventSource* _eventSource,
                const IEventSink*   _eventSink) throw() :
            Smp::Exception("NotSubscribed"),
                eventSource(_eventSource),
                eventSink  (_eventSink)
            {
                Smp::String8 sourceName = "NULL";
                Smp::String8 sinkName = "NULL";

                if (eventSource)
                {
                    sourceName = eventSource->GetName();
                }
                if (eventSink)
                {
                    sinkName = eventSink->GetName();
                }

                description = new Char8[strlen(NotSubscribedTemplate) 
                    + strlen(sourceName)
                    + strlen(sinkName)];

                sprintf(description, NotSubscribedTemplate, 
                    sinkName, 
                    sourceName);
            }

            ~NotSubscribed() throw() {}
        };

        /// Event sink is not compatible with event source.
        /// This exception is raised when trying to subscribe an event sink
        /// to an event source that has a different event type.
        class InvalidEventSink : public Smp::Exception
        {
        public:
            /// Event source the event sink is subscribed to.
            const IEventSource* eventSource;
            /// Event sink that is not of valid type.
            const IEventSink*   eventSink;

            InvalidEventSink(
                const IEventSource* _eventSource,
                const IEventSink*   _eventSink) throw() :
            Smp::Exception("InvalidEventSink"),
                eventSource(_eventSource),
                eventSink  (_eventSink)
            {
                Smp::String8 sourceName = "NULL";
                Smp::String8 sinkName = "NULL";

                if (eventSource)
                {
                    sourceName = eventSource->GetName();
                }
                if (eventSink)
                {
                    sinkName = eventSink->GetName();
                }

                description = new Char8[strlen(InvalidEventSinkTemplate) 
                    + strlen(sourceName)
                    + strlen(sinkName)];

                sprintf(description, InvalidEventSinkTemplate, 
                    sinkName, 
                    sourceName);
            }

            ~InvalidEventSink() throw() {}
        };

        /// Event subscription.
        /// Subscribe to the event source, i.e. request notifications.
        /// @param eventSink Event sink to subscribe to event source.
        /// @remarks An event sink can only be subscribed once to each
        ///          event source.
        ///          @par
        ///          Implementations may perform type checking on the
        ///          optional event argument of event source and event sink.
        ///          @par
        ///          Event sinks will be called synchronously in the order 
        ///          they have been subscribed to the event source.
        virtual void Subscribe(IEventSink* eventSink) throw (
            Smp::IEventSource::AlreadySubscribed,
            Smp::IEventSource::InvalidEventSink) = 0;

        /// Event unsubscription.
        /// Unsubscribe from the event source, i.e. cancel notifications.
        /// @param eventSink Event sink to unsubscribe from event source.
        /// @remarks An event sink can only be unsubscribed if it has been
        ///          subscribed before.
        virtual void Unsubscribe(IEventSink* eventSink) throw (
            Smp::IEventSource::NotSubscribed) = 0;
    };
}

namespace Smp
{
    /// Collection of event sources.
    /// An event source collection is an ordered collection of event sources,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IEventSource*> EventSourceCollection;
}

#endif // SMP_IEVENTSOURCE_H

/***********
 * History *
 ***********/

//$Log: IEventSource.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

