//
// Title:
//      IResolver.h
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
//      This file defines the IResolver interface for the resolver service.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_SERVICES_IRESOLVER_H
#define SMP_SERVICES_IRESOLVER_H

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
        /// Name of Resolver service.
        const String8 SMP_Resolver = "Smp_Resolver";
    }
}

// ---------------------------------------------------------------------------
// --------------------------- IResolver interface ---------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// This interface gives access to the Resolver.
        /// Components can use the Resolver to resolve references to other 
        /// components.
        /// @remarks This is an optional service the simulation environment
        ///          may provide via its GetService() method.
        class IResolver : public virtual IService
        {
        public:
            /// Resolve reference to component via absolute path.
            /// @param   absolutePath Absolute path to component in simulation.
            /// @return  Component identified by path, or null for invalid path.
            virtual IComponent* ResolveAbsolute(String8 absolutePath) = 0;

            /// Resolve reference to component via relative path.
            /// @param   relativePath Relative path to component in simulation.
            /// @param   sender Component that asks for resolving the reference.
            /// @return  Component identified by path, or null for invalid path.
            virtual IComponent* ResolveRelative(
                String8 relativePath, 
                IComponent* sender) = 0;
        };
    }
}

#endif // SMP_SERVICES_IRESOLVER_H

/***********
 * History *
 ***********/

//$Log: IResolver.h,v $
//Revision 1.2  2006/09/27 11:43:57  nin
//SMP2 v1.2
// 

