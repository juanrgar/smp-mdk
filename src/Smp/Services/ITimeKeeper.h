//
// Title:
//      ITimeKeeper.h
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
//      This file defines the ITimeKeeper interface for the time keeper service.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_SERVICES_ITIMEKEEPER_H
#define SMP_SERVICES_ITIMEKEEPER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IService.h"

// ----------------------------------------------------------------------------
// --------------------------- Constant Declarations --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// Name of Time Keeper service.
        const String8 SMP_TimeKeeper = "Smp_TimeKeeper";
    }
}

// ----------------------------------------------------------------------------
// --------------------------- ITimeKeeper interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// This interface gives access to the Time Keeper.
        /// Components can query for the time, and set epoch and mission time.
        /// @remarks This is a mandatory service the simulation environment
        ///          has to provide via its GetService() method.
        class ITimeKeeper : public virtual IService
        {
        public:
            /// Return simulation time.
            /// Simulation time is a relative time that starts at 0.
            /// @return  Current simulation time.
            virtual Duration GetSimulationTime() = 0;

            /// Return Epoch time.
            /// Epoch time is an absolute time with a fixed offset to simulation 
            /// time.
            /// @return  Current epoch time.
            /// @remarks Epoch time typically progresses with simulation
            ///          time, but can be changed with SetEpochTime().
            virtual DateTime GetEpochTime() = 0;

            /// Return Mission time.
            /// Mission time is a relative time with a fixed offset to epoch
            /// time.
            /// @return  Current mission time.
            /// @remarks Mission time typically progresses with epoch
            ///          time, but can be changed with SetMissionTime().
            virtual Duration GetMissionTime() = 0;

            /// Return Zulu time.
            /// Zulu time is a system dependent time and not related to simulation
            /// time.
            /// @return  Current Zulu time.
            /// @remarks Zulu time is typically related to the system clock of the
            ///          computer.
            virtual DateTime GetZuluTime() = 0;

            /// Set Epoch time.
            /// Changes the offset between simulation time and epoch time.
            /// @param     epochTime New epoch time.
            /// @remarks This shall raise an SMP_EpochTimeChanged event.
            ///          As mission time is relative to epoch time, this will 
            ///          change the mission time as well.
            virtual void SetEpochTime(const DateTime epochTime) = 0;

            /// Set Mission start.
            /// Changes the offset between mission time and epoch time.
            /// The mission time itself will be calculated as the offset
            /// between the current epoch time and the given mission start.
            /// @param      missionStart New mission start date and time.
            /// @remarks This shall raise an SMP_MissionTimeChanged event.
            virtual void SetMissionStart(const DateTime missionStart) = 0;

            /// Set Mission time.
            /// Changes the offset between mission time and epoch time.
            /// @param      missionTime New mission time.
            /// @remarks This shall raise an SMP_MissionTimeChanged event.
            virtual void SetMissionTime(const Duration missionTime) = 0;
        };
    }
}

#endif // SMP_SERVICES_ITIMEKEEPER_H

/***********
 * History *
 ***********/

//$Log: ITimeKeeper.h,v $
//Revision 1.2  2006/09/27 11:43:57  nin
//SMP2 v1.2
// 

