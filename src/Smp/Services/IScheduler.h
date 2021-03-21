//
// Title:
//      IScheduler.h
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
//      This file defines the IScheduler interface for the scheduler service.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_SERVICES_ISCHEDULER_H
#define SMP_SERVICES_ISCHEDULER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IService.h"
#include "Smp/IEntryPoint.h"
#include "Smp/SimpleTypes.h"

// ----------------------------------------------------------------------------
// --------------------------- Constant Declarations --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// Name of Scheduler service.
        const String8 SMP_Scheduler = "Smp_Scheduler";
    }
}

// ----------------------------------------------------------------------------
// --------------------------- TimeKind enumeration ---------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// Enumeration of supported time kinds.
        enum TimeKind
        {
            TK_SimulationTime,  ///< Simulation time.
            TK_EpochTime,       ///< Epoch time.
            TK_MissionTime,     ///< Mission time.
            TK_ZuluTime         ///< Zulu time.
        };
    }
}

// ----------------------------------------------------------------------------
// --------------------------- ITask interface --------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// Interface for Scheduler task.
        /// This interface extends IEntryPoint to allow scheduling tasks.
        /// A Task is an ordered collection of entry points.
        class ITask : public virtual IEntryPoint
        {
        public:
            /// Get all entry points.
            /// Query for the collection of all entry points of the task.
            /// @return  Collection of entry points in the order they have been
            ///          added using the AddEntryPoint() method.
            /// @remarks The collection may be empty if no entry points exist.
            virtual EntryPointCollection GetEntryPoints() = 0;

            /// Add entry point.
            /// Add an entry point to the task.
            /// @param   entryPoint Entry point to add to task.
            virtual void AddEntryPoint(const IEntryPoint* entryPoint) = 0;
        };
    }
}

// ----------------------------------------------------------------------------
// --------------------------- IScheduler interface ---------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// This interface gives access to the Scheduler.
        /// Components can register and unregister entry points for scheduling.
        /// In addition, tasks can be created, which can contain an ordered
        /// collection of entry points. This allows scheduling several entry
        /// points in one call to the scheduler.
        /// @remarks This is a mandatory service the simulation environment
        ///          has to provide via its GetService() method.
        class IScheduler : public virtual IService
        {
        public:
            /// Add immediate event.
            /// Add an immediate event to the scheduler.
            /// @param   entryPoint Entry point to call from event.
            virtual void AddImmediateEvent(
                const IEntryPoint* entryPoint) = 0;

            /// Add event relative to simulation time.
            /// Add event to scheduler that is called based on simulation time.
            /// @param   entryPoint Entry point to call from event.
            /// @param   simulationTime Duration from now when to trigger event.
            /// @param   cycleTime Duration between two triggers of the event.
            /// @param   count Number of times the event shall be repeated, 
            ///                or 0 for a single event, or -1 for no limit.
            /// @return  Identifier that can be used to change or remove event.
            /// @remarks An event with <code>count=0</code> is not cyclic.
            ///          It will be removed automatically after it has been
            ///          triggered.
            ///          @par
            ///          An event with <code>count>0</code> is cyclic, and will
            ///          be repeated <code>count</code> times. Therefore, it
            ///          will be called <code>count+1</code> times, and then it
            ///          will be removed automatically.
            ///          @par
            ///          An event with <code>count=-1</code> is cyclic as well,
            ///          but it will be triggered forever, unless it is removed
            ///          from the scheduler using the RemoveEvent() method.
            ///          @par
            ///          For a cyclic event, the cycleTime needs to be positive.
            ///          For non-cyclic events, it is ignored.
            ///          @par
            ///          The simulationTime must not be negative. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual EventId AddSimulationTimeEvent(
                const IEntryPoint* entryPoint,
                const Duration simulationTime,
                const Duration cycleTime = 0,
                const Int64 count = 0) = 0;

            /// Add event relative to mission time.
            /// Add event to scheduler that is called based on mission time.
            /// @param   entryPoint Entry point to call from event.
            /// @param   missionTime Absolute mission time when to trigger event.
            /// @param   cycleTime Duration between two triggers of the event.
            /// @param   count Number of times the event shall be repeated, 
            ///                or 0 for a single event, or -1 for no limit.
            /// @return  Identifier that can be used to change or remove event.
            /// @remarks An event with <code>count=0</code> is not cyclic.
            ///          It will be removed automatically after it has been
            ///          triggered.
            ///          @par
            ///          An event with <code>count>0</code> is cyclic, and will
            ///          be repeated <code>count</code> times. Therefore, it
            ///          will be called <code>count+1</code> times, and then it
            ///          will be removed automatically.
            ///          @par
            ///          An event with <code>count=-1</code> is cyclic as well,
            ///          but it will be triggered forever, unless it is removed
            ///          from the scheduler using the RemoveEvent() method.
            ///          @par
            ///          For a cyclic event, the cycleTime needs to be positive.
            ///          For non-cyclic events, it is ignored.
            ///          @par
            ///          The missionTime must not be before the current mission 
            ///          time of the ITimeKeeper service. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual EventId AddMissionTimeEvent(
                const IEntryPoint* entryPoint,
                const Duration missionTime,
                const Duration cycleTime = 0,
                const Int64 count = 0) = 0;

            /// Add event relative to epoch time.
            /// Add event to scheduler that is called based on epoch time.
            /// @param   entryPoint Entry point to call from event.
            /// @param   epochTime Epoch time when to trigger event.
            /// @param   cycleTime Duration between two triggers of the event.
            /// @param   count Number of times the event shall be repeated, 
            ///                or 0 for a single event, or -1 for no limit.
            /// @return  Identifier that can be used to change or remove event.
            /// @remarks An event with <code>count=0</code> is not cyclic.
            ///          It will be removed automatically after it has been
            ///          triggered.
            ///          @par
            ///          An event with <code>count>0</code> is cyclic, and will
            ///          be repeated <code>count</code> times. Therefore, it
            ///          will be called <code>count+1</code> times, and then it
            ///          will be removed automatically.
            ///          @par
            ///          An event with <code>count=-1</code> is cyclic as well,
            ///          but it will be triggered forever, unless it is removed
            ///          from the scheduler using the RemoveEvent() method.
            ///          @par
            ///          For a cyclic event, the cycleTime needs to be positive.
            ///          For non-cyclic events, it is ignored.
            ///          @par
            ///          The epochTime must not be before the current epoch
            ///          time of the ITimeKeeper service. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual EventId AddEpochTimeEvent(
                const IEntryPoint* entryPoint,
                const DateTime epochTime,
                const Duration cycleTime = 0,
                const Int64 count = 0) = 0;

            /// Add event relative to Zulu time.
            /// Add event to scheduler that is called based on Zulu time.
            /// @param   entryPoint Entry point to call from event.
            /// @param   zuluTime Absolute (Zulu) time when to trigger event.
            /// @param   cycleTime Duration between two triggers of the event.
            /// @param   count Number of times the event shall be repeated, 
            ///                or 0 for a single event, or -1 for no limit.
            /// @return  Identifier that can be used to change or remove event.
            /// @remarks An event with <code>count=0</code> is not cyclic.
            ///          It will be removed automatically after it has been
            ///          triggered.
            ///          @par
            ///          An event with <code>count>0</code> is cyclic, and will
            ///          be repeated <code>count</code> times. Therefore, it
            ///          will be called <code>count+1</code> times, and then it
            ///          will be removed automatically.
            ///          @par
            ///          An event with <code>count=-1</code> is cyclic as well,
            ///          but it will be triggered forever, unless it is removed
            ///          from the scheduler using the RemoveEvent() method.
            ///          @par
            ///          For a cyclic event, the cycleTime needs to be positive.
            ///          For non-cyclic events, it is ignored.
            ///          @par
            ///          The zuluTime must not be before the current Zulu
            ///          time of the ITimeKeeper service. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual EventId AddZuluTimeEvent(
                const IEntryPoint* entryPoint,
                const DateTime zuluTime,
                const Duration cycleTime = 0,
                const Int64 count = 0) = 0;

            /// Set event execution time using simulation time.
            /// Update when an existing event on the scheduler shall be called.
            /// @param   event Identifier of event to modify.
            /// @param   simulationTime Duration from now when to trigger event.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          @par
            ///          The simulationTime must not be negative. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual void SetEventSimulationTime(
                const EventId event, 
                const Duration simulationTime) throw (
                Smp::Services::InvalidEventId) = 0;

            /// Set event execution time using mission time.
            /// Update when an existing event on the scheduler shall be called.
            /// @param   event Identifier of event to modify.
            /// @param   missionTime Absolute mission time when to trigger event.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          @par
            ///          The missionTime must not be before the current mission 
            ///          time of the ITimeKeeper service. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual void SetEventMissionTime(
                const EventId event, 
                const Duration missionTime) throw (
                Smp::Services::InvalidEventId) = 0;

            /// Set event execution time using epoch time.
            /// Update when an existing event on the scheduler shall be called.
            /// @param   event Identifier of event to modify.
            /// @param   epochTime Epoch time when to trigger event.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          @par
            ///          The epochTime must not be before the current epoch
            ///          time of the ITimeKeeper service. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual void SetEventEpochTime(
                const EventId event, 
                const DateTime epochTime) throw (
                Smp::Services::InvalidEventId) = 0;

            /// Set event execution time using Zulu time.
            /// Update when an existing event on the scheduler shall be called.
            /// @param   event Identifier of event to modify.
            /// @param   zuluTime Absolute (Zulu) time when to trigger event.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          @par
            ///          The zuluTime must not be before the current Zulu
            ///          time of the ITimeKeeper service. Otherwise, the
            ///          event will never be executed, but immediately removed.
            virtual void SetEventZuluTime(
                const EventId event, 
                const DateTime zuluTime) throw (
                Smp::Services::InvalidEventId) = 0;

            /// Set event cycle time.
            /// Update cycle time of an existing event on the scheduler.
            /// @param   event Identifier of event to modify.
            /// @param   cycleTime Duration between two triggers of the event.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          @par
            ///          For a cyclic event, the cycleTime needs to be positive.
            ///          For non-cyclic events, it is ignored.
            virtual void SetEventCycleTime(
                const EventId event, 
                const Duration cycleTime) throw (
                Smp::Services::InvalidEventId) = 0;

            /// Set event count.
            /// Update the count of an existing event on the scheduler.
            /// @param   event Identifier of event to modify.
            /// @param   count Number of times the event shall be repeated, 
            ///                or 0 for a single event, or -1 for no limit.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          @par
            ///          An event with <code>count=0</code> is not cyclic.
            ///          It will be removed automatically after it has been
            ///          triggered.
            ///          @par
            ///          An event with <code>count>0</code> is cyclic, and will
            ///          be repeated <code>count</code> times. Therefore, it
            ///          will be called <code>count+1</code> times, and then it
            ///          will be removed automatically.
            ///          @par
            ///          An event with <code>count=-1</code> is cyclic as well,
            ///          but it will be triggered forever, unless it is removed
            ///          from the scheduler using the RemoveEvent() method.
            ///          @par
            ///          For a cyclic event, the cycleTime needs to be positive.
            ///          For non-cyclic events, it is ignored.
            virtual void SetEventCount(
                const EventId event, 
                const Int64 count) throw (
                Smp::Services::InvalidEventId) = 0;

            /// Remove an event from the scheduler.
            /// @param   event Event identifier of the event to remove.
            /// @remarks The event identifier must be valid, i.e. an identifier
            ///          of a scheduler event that has not yet been removed.
            ///          An event with <code>count>=0</code> is removed 
            ///          automatically after it has been triggered
            ///          <code>count+1</code> times, and is no longer accessable.
            virtual void RemoveEvent(const EventId event)  throw (
                Smp::Services::InvalidEventId) = 0;
        };
    }
}

#endif // SMP_SERVICES_ISCHEDULER_H

/***********
 * History *
 ***********/

//$Log: IScheduler.h,v $
//Revision 1.2  2006/09/27 11:43:57  nin
//SMP2 v1.2
// 

