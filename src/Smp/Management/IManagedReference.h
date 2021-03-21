//
// Title:
//      IManagedReference.h
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
//      This file defines the IManagedReference interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IMANAGEDREFERENCE_H
#define SMP_MANAGEMENT_IMANAGEDREFERENCE_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IReference.h"
#include "Smp/Exceptions.h"
#include <sstream>

// ----------------------------------------------------------------------------
// --------------------------- IManagedReference interface --------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management 
    {
        static const Smp::String8 NotReferencedTemplate = "Reference '%s' does not reference component '%s'";

        /// Managed reference.
        /// A managed reference additionally allows
        /// querying the size limits and adding referenced components.
        class IManagedReference : public virtual IReference
        {
        public:
            /// Reference is full.
            /// This exception is raised when trying to add a component to a
            /// reference that is full, i.e. where the Count() has reached the
            /// Upper() limit.
            class ReferenceFull : public Smp::Exception
            {
            public:
                /// Name of full reference.
                String8 referenceName;
                /// Number of components in the reference, which is its Upper()
                /// limit when the reference is full.
                const Int64  referenceSize;

                ReferenceFull(
                    String8 _referenceName,
                    const Int64  _referenceSize) throw() :
                Smp::Exception("ReferenceFull"),
                    referenceName(_referenceName), 
                    referenceSize(_referenceSize)
                {
                    std::stringstream ss;
                    
                    ss  << "Reference '"
                        << referenceName
                        << "' is full ("
                        << referenceSize
                        << "components)";

                    description = new Char8[ss.str().length()+1];

                    strcpy(description, ss.str().c_str());
                }
                ~ReferenceFull() throw() {}
            };

            /// Component was not referenced.
            /// This exception is thrown when trying to remove a component
            /// from a reference which was not referenced before.
            class NotReferenced : public Smp::Exception
            {
            public:
                /// Name of reference.
                String8 referenceName;
                /// Component that is not referenced.
                const IComponent* component;

                NotReferenced(
                    String8 _referenceName,
                    const IComponent* _component) throw() :
                Smp::Exception("NotReferenced"),
                    referenceName(_referenceName), 
                    component(_component)
                {
                    Smp::String8 componentName = "NULL";

                    if (component)
                    {
                        componentName = component->GetName();
                    }

                    description = new Char8[strlen(NotReferencedTemplate) 
                        + strlen(referenceName) 
                        + strlen(componentName)];

                    sprintf(description, NotReferencedTemplate, 
                        referenceName, 
                        componentName);
                }
                ~NotReferenced() throw() {}
            };

            /// Add component.
            /// Add a referenced component.
            /// @param   component New referenced component.
            /// @remarks This method raises a ReferenceFull exception if the 
            /// reference is full.
            virtual void AddComponent(IComponent* component) throw (
                Smp::Management::IManagedReference::ReferenceFull,
                Smp::InvalidObjectType) = 0;

            /// Get the number of referenced components.
            /// Query for the number of referenced components.
            /// @return Current number of referenced components.
            virtual Int64 Count() const = 0;

            /// Get lower bound of multiplicity.
            /// Query the minimum number of components in the collection of references.
            /// @return Minimum number of referenced components.
            virtual Int64 Lower() const = 0;

            /// Get upper bound for number of components.
            /// Query the maximum number of components in the collection of references.
            /// @return  Maximum number of referenced components (-1 = unlimited).
            /// @remarks A return value of -1 indicates that the reference has
            ///          no upper limit. This is consistent with the use of upper
            ///          bounds in UML, where a value of -1 represents no limit 
            ///          (typically shown as *).
            virtual Int64 Upper() const = 0;

            /// Remove component.
            /// Remove a referenced component.
            /// @param   component Referenced component to remove.
            /// @remarks This method raises a NotReferenced exception if the 
            ///          given component is not referenced.
            virtual void RemoveComponent(IComponent* component) throw (
                Smp::Management::IManagedReference::NotReferenced) = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IMANAGEDREFERENCE_H

/***********
 * History *
 ***********/

//$Log: IManagedReference.h,v $
//Revision 1.3  2006/11/20 13:59:22  nin
//Some message formatting reworked to be portable and without compile-time warnings.
//
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

