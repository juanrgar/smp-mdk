//
// Title:
//      IComposite.h
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
//      This file defines the IComposite interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_ICOMPOSITE_H
#define SMP_ICOMPOSITE_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IContainer.h"

// ----------------------------------------------------------------------------
// ---------------------------- IComposite interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Composite component.
    /// A component with contained components implements this interface.
    /// Child components are held in named containers.
    /// @remarks Together with the IContainer interface, this interface 
    ///          represents the composition mechanism (Container) of the SMP 
    ///          Metamodel (SMDL).
    ///          In UML 2.0, this maps to a composite required interface.
    class IComposite : public virtual IComponent
    {
    public:
        /// Get all containers.
        /// Query for the collection of all containers of the component.
        /// @return Collection of containers.
        /// @remarks The collection may be empty if no containers exist.
        virtual const ContainerCollection* GetContainers() const = 0;

        /// Get a container by name.
        /// Query for a container of this component by its name.
        /// @param   name Container name.
        /// @return  Container queried for by name, or undefined if
        ///             no container with this name exists.
        /// @remarks The returned container may be undefined if no
        ///          container with the given name could be found.
        virtual IContainer* GetContainer(String8 name) const = 0;
    };
}

#endif // SMP_ICOMPOSITE_H

/***********
 * History *
 ***********/

//$Log: IComposite.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

