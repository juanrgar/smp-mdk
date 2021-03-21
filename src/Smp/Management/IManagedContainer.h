//
// Title:
//      IManagedContainer.h
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
//      This file defines the IManagedContainer interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IMANAGEDCONTAINER_H
#define SMP_MANAGEMENT_IMANAGEDCONTAINER_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exceptions.h"
#include "Smp/IContainer.h"
#include <sstream>

// ----------------------------------------------------------------------------
// --------------------------- IManagedContainer interface --------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management 
    {
        /// Managed container.
        /// A managed container additionally allows
        /// querying the size limits and adding contained components.
        class IManagedContainer : public virtual IContainer
        {
        public:
            /// Container is full.
            /// This exception is raised when trying to add a component to a
            /// container that is full, i.e. where the Count() has reached the
            /// Upper() limit.
            class ContainerFull : public Smp::Exception
            {
            public:
                /// Name of full container.
                String8 containerName;
                /// Number of components in the container, which is its Upper()
                /// limit when the container is full.
                const Int64  containerSize;

                ContainerFull(
                    String8 _containerName, 
                    const Int64 _containerSize) throw() : 
                Smp::Exception("ContainerFull"),
                    containerName(_containerName),
                    containerSize(_containerSize)
                {
                    std::stringstream ss;
                    
                    ss  << "Container '" 
                        << containerName
                        << "' is full ("
                        << containerSize
                        << " components)";
                    
                    description = new Char8[ss.str().length()+1];

                    strcpy(description, ss.str().c_str());
                }

                ~ContainerFull() throw() {}
            };

            /// Add component.
            /// Add a contained component to the container.
            /// @param  component New contained component.
            /// @remarks This method raises a ContainerFull exception if the 
            /// container is full.
            virtual void AddComponent(IComponent* component) throw (
                Smp::Management::IManagedContainer::ContainerFull, 
                Smp::DuplicateName,
                Smp::InvalidObjectType) = 0;

            /// Get the number of contained components.
            /// Query for the number of components in the container.
            /// @return Current number of components.
            virtual Int64 Count() const = 0;

            /// Get lower bound of multiplicity.
            /// Query the minimum number of components in the container.
            /// @return Minimum number of components.
            virtual Int64 Lower() const = 0;

            /// Get upper bound for number of components.
            /// Query the maximum number of components in the container.
            /// @return  Maximum number of contained components (-1 = unlimited).
            /// @remarks A return value of -1 indicates that the container has
            ///          no upper limit. This is consistent with the use of upper
            ///          bounds in UML, where a value of -1 represents no limit 
            ///          (typically shown as *).
            virtual Int64 Upper() const = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IMANAGEDCONTAINER_H

/***********
 * History *
 ***********/

//$Log: IManagedContainer.h,v $
//Revision 1.3  2006/11/20 13:59:06  nin
//Some message formatting reworked to be portable and without compile-time warnings.
//
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

