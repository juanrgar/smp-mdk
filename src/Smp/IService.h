//
// Title:
//      IService.h
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
//      This file defines the IService interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_ISERVICE_H
#define SMP_ISERVICE_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/Exceptions.h"
#include <sstream>

// ----------------------------------------------------------------------------
// ---------------------------- IService interface ----------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Base interface for simulation services.
    /// All SMDL services implement this interface.
    /// @remarks Currently, this interface does not add any functionality.
    class IService : public virtual IComponent
    {
    };
}

namespace Smp
{
    /// Collection of services.
    /// A service collection is an ordered collection of services,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IService*> ServiceCollection;
}

// ----------------------------------------------------------------------------
// ---------------------------- InvalidEventId exception ----------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Simulation Services interfaces.
    /// This namespace defines the available simulation services of SMP.
    /// For each pre-defined service, a constant name is defined as well.
    namespace Services
    {
        /// Identifier of global event of scheduler or event manager service.
        typedef Int64 EventId;

        /// Invalid event identifier.
        /// This exception is raised when calling Subscribe(), Unsubscribe()
        /// or Emit() of the event manager using an invalid global event.
        /// This exception is raised when calling SetEventSimulationTime(),
        /// SetEventMissionTime(), SetEventEpochTime(), SetEventZuluTime(),
        /// SetEventCycleTime(), SetEventCount() or RemoveEvent() of the
        /// Scheduler using an invalid scheduler event identifier.
        class InvalidEventId : public Smp::Exception
        {
        public:
            /// Invalid event identifier.
            const EventId event;

            InvalidEventId(
                const EventId _event) throw() :
            Smp::Exception("InvalidEventId"),
                event(_event)
            {
                std::stringstream ss;
                
                ss  << "Invalid event id "
                    << event;
                
                description = new Char8[ss.str().length()+1];

                strcpy(description, ss.str().c_str());
            }

            ~InvalidEventId() throw() {}
        };
    }
}

#endif // SMP_ISERVICE_H

/***********
 * History *
 ***********/

//$Log: IService.h,v $
//Revision 1.3  2006/11/20 13:59:17  nin
//Some message formatting reworked to be portable and without compile-time warnings.
//
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

