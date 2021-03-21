//
// Title:
//      IEventManager.h
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
//      This file defines the IEventManager interface for the event manager.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_SERVICES_IEVENTMANAGER_H
#define SMP_SERVICES_IEVENTMANAGER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IService.h"
#include "Smp/IEntryPoint.h"

// ----------------------------------------------------------------------------
// --------------------------- Constant Declarations --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        const String8 SMP_LeaveConnecting    = "Smp_LeaveConnecting";
        const String8 SMP_EnterInitialising  = "Smp_EnterInitialising";
        const String8 SMP_LeaveInitialising  = "Smp_LeaveInitialising";
        const String8 SMP_EnterStandby       = "Smp_EnterStandby";
        const String8 SMP_LeaveStandby       = "Smp_LeaveStandby";
        const String8 SMP_EnterExecuting     = "Smp_EnterExecuting";
        const String8 SMP_LeaveExecuting     = "Smp_LeaveExecuting";
        const String8 SMP_EnterStoring       = "Smp_EnterStoring";
        const String8 SMP_LeaveStoring       = "Smp_LeaveStoring";
        const String8 SMP_EnterRestoring     = "Smp_EnterRestoring";
        const String8 SMP_LeaveRestoring     = "Smp_LeaveRestoring";
        const String8 SMP_EnterExiting       = "Smp_EnterExiting";
        const String8 SMP_EnterAborting      = "Smp_EnterAborting";
             
        const String8 SMP_EpochTimeChanged   = "Smp_EpochTimeChanged";
        const String8 SMP_MissionTimeChanged = "Smp_MissionTimeChanged";
             
        const EventId SMP_LeaveConnectingId    =  1; ///< Leave Connecting state.
        const EventId SMP_EnterInitialisingId  =  2; ///< Enter Initialising state.
        const EventId SMP_LeaveInitialisingId  =  3; ///< Leave Initialising state.
        const EventId SMP_EnterStandbyId       =  4; ///< Enter Standby state.
        const EventId SMP_LeaveStandbyId       =  5; ///< Leave Standby state.
        const EventId SMP_EnterExecutingId     =  6; ///< Enter Executing state.
        const EventId SMP_LeaveExecutingId     =  7; ///< Leave Executing state.
        const EventId SMP_EnterStoringId       =  8; ///< Enter Storing state.
        const EventId SMP_LeaveStoringId       =  9; ///< Leave Storing state.
        const EventId SMP_EnterRestoringId     = 10; ///< Enter Restoring state.
        const EventId SMP_LeaveRestoringId     = 11; ///< Leave Restoring state.
        const EventId SMP_EnterExitingId       = 12; ///< Enter Exiting state.
        const EventId SMP_EnterAbortingId      = 13; ///< Enter Aborting state.
             
        const EventId SMP_EpochTimeChangedId   = 14; ///< Epoch time has changed.
        const EventId SMP_MissionTimeChangedId = 15; ///< Mission time has changed.

        /// Name of Event Manager service.
        const String8 SMP_EventManager = "Smp_EventManager";
    }
}

// ----------------------------------------------------------------------------
// --------------------------- IEventManager interface ------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        static const Smp::String8 AlreadySubscribedTemplate = "Entry point '%s' of owner '%s' is already subscribed to event '%s'";
        static const Smp::String8 NotSubscribedTemplate     = "Entry point '%s' of owner '%s' is not subscribed to event '%s'";

        /// This interface gives access to the Event Manager.
        /// Components can register entry points with events, define their own
        /// global events, and emit events.
        class IEventManager : public virtual IService
        {
        public:
            /// Entry point is already subscribed.
            /// This exception is raised when trying to subscribe an entry point
            /// to an event that is already subscribed.
            class AlreadySubscribed : public Smp::Exception
            {
            public:
                /// Name of event the entry point is already subscribed to.
                String8 eventName;
                /// Entry point that is already subscribed.
                const IEntryPoint* entryPoint;

                AlreadySubscribed(
                    String8 _eventName,
                    const IEntryPoint* _entryPoint) throw() :
                Smp::Exception("AlreadySubscribed"),
                    eventName(_eventName),
                    entryPoint(_entryPoint)
                {
                    Smp::String8 entryPointName = "";
                    Smp::String8 ownerName = "";

                    if (entryPoint)
                    {
                        entryPointName = entryPoint->GetName();

                        if (entryPoint->GetOwner())
                        {
                            ownerName = entryPoint->GetOwner()->GetName();
                        }
                    }

                    description = new Char8[strlen(AlreadySubscribedTemplate) 
                        + strlen(entryPointName) 
                        + strlen(ownerName) 
                        + strlen(eventName)];

                    sprintf(description, AlreadySubscribedTemplate, 
                        entryPointName, 
                        ownerName, 
                        eventName);
                }

                ~AlreadySubscribed() throw() {}
            };

            /// Entry point is not subscribed.
            /// This exception is raised when trying to unsubscribe an entry
            /// point from an event that is not subscribed to it.
            class NotSubscribed : public Smp::Exception
            {
            public:
                /// Name of event the entry point is not subscribed to.
                String8 eventName;
                /// Entry point that is not subscribed.
                const IEntryPoint* entryPoint;

                NotSubscribed(
                    String8 _eventName,
                    const IEntryPoint* _entryPoint) throw() :
                Smp::Exception("NotSubscribed"),
                    eventName(_eventName),
                    entryPoint(_entryPoint)
                {
                    Smp::String8 entryPointName = "";
                    Smp::String8 ownerName = "";

                    if (entryPoint)
                    {
                        entryPointName = entryPoint->GetName();

                        if (entryPoint->GetOwner())
                        {
                            ownerName = entryPoint->GetOwner()->GetName();
                        }
                    }

                    description = new Char8[strlen(NotSubscribedTemplate) 
                        + strlen(entryPointName) 
                        + strlen(ownerName) 
                        + strlen(eventName)];

                    sprintf(description, NotSubscribedTemplate, 
                        entryPointName, 
                        ownerName, 
                        eventName);
                }

                ~NotSubscribed() throw() {}
            };

            /// Get event identifier.
            /// Get unique event identifier for an event name.
            /// @param   eventName Name of the global event.
            /// @return  Event identifier for global event with given name.
            /// @remarks It is guaranteed that this method will always return
            ///          the same value when called with the same event name.
            virtual EventId GetEventId(String8 eventName) = 0;

            /// Subscribe entry point.
            /// Subscribe an entry point to a global event.
            /// @param   event Event identifier of global event to subscribe to.
            /// @param   entryPoint Entry point to subscribe to global event.
            /// @remarks An entry point can only be subscribed once to an event.
            ///          If trying to subscribe it again, an exception of type
            ///          AlreadySubscribed is raised.
            virtual void Subscribe(
                const EventId event, 
                const IEntryPoint* entryPoint) throw (
                Smp::Services::InvalidEventId, 
                Smp::Services::IEventManager::AlreadySubscribed) = 0;

            /// Unsubscribe entry point.
            /// Unsubscribe an entry point from a global event.
            /// @param   event Event identifier of global event to unsubscribe from.
            /// @param   entryPoint Entry point to unsubscribe from global event.
            /// @remarks An entry point can only be unsubscribed from an event 
            ///          after it has been subscribed before using Subscribe().
            ///          If trying to unsubscribe an entry point without subscribing
            ///          it before, a NotSubscribed exception is raised.
            virtual void Unsubscribe(
                const EventId event, 
                const IEntryPoint* entryPoint) throw (
                Smp::Services::InvalidEventId, 
                Smp::Services::IEventManager::NotSubscribed) = 0;

            /// Emit a global event.
            /// @param   event Event identifier of global event to emit.
            /// @remarks This will call all entry points that are subscribed to the
            ///          global event with the given identifier.
            ///          @par
            ///          Entry points will be called synchronously in the order 
            ///          they have been subscribed to the global event.
            virtual void Emit(const EventId event) throw (
                Smp::Services::InvalidEventId) = 0;
        };
    }
}

#endif // SMP_SERVICES_IEVENTMANAGER_H

/***********
 * History *
 ***********/

//$Log: IEventManager.h,v $
//Revision 1.2  2006/09/27 11:43:57  nin
//SMP2 v1.2
// 

