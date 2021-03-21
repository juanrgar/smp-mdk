//
// Title:
//      IDynamicSimulator.h
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
//      This file defines the IDynamicSimulator interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IDYNAMICSIMULATOR_H
#define SMP_IDYNAMICSIMULATOR_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/IFactory.h"
#include "Smp/ISimulator.h"

// ---------------------------------------------------------------------------
// ---------------------- IDynamicSimulator interface ------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    static const Smp::String8 DuplicateUuidTemplate = "Uuid of factory '%s' already used by '%s'";

    /// This interface gives access to a dynamic simulator.
    /// External applications can register component factories with a dynamic
    /// simulator, and can use its CreateInstance() method to create component
    /// instances.
    class IDynamicSimulator : public virtual ISimulator
    {
    public:
        /// Duplicate Uuid.
        /// This exception is raised when trying to register a factory with
        /// an implementation Uuid of an existing factory.
        /// This would lead to duplicate implementation Uuids.
        class DuplicateUuid : public Smp::Exception
        {
        public:
            /// Name of factory that tried to register under this Uuid.
            String8 newName;
            /// Name of factory already registered under this Uuid.
            String8 oldName;

            DuplicateUuid(
                String8 _newName,
                String8 _oldName) throw() :
            Smp::Exception("DuplicateUuid"),
                newName(_newName),
                oldName(_oldName)
            {
                description = new Char8[strlen(DuplicateUuidTemplate) 
                    + strlen(newName)
                    + strlen(oldName)];

                sprintf(description, DuplicateUuidTemplate, 
                    newName,
                    oldName);
            }
            ~DuplicateUuid() throw() {}
        };

        /// Register a global component factory with the simulator.
        /// @param   componentFactory Component factory that creates and deletes
        ///          the component instances.
        virtual void RegisterFactory(IFactory* componentFactory) throw (
            Smp::IDynamicSimulator::DuplicateUuid) = 0;

        /// Create an instance of the given component implementation.
        /// @param   implUuid Identifier of component Implementation.
        /// @return  New component instance of given component implementation,
        ///          or null if no factory is available.
        virtual IComponent* CreateInstance(const Uuid implUuid) = 0;

        /// Get the factory of the given component implementation.
        /// @param   implUuid Identifier of component Implementation.
        /// @return  Component factory of given component implementation,
        ///          or null if no factory is available.
        virtual const IFactory* GetFactory(const Uuid implUuid) = 0;

        /// Get all factories of the given component specification.
        /// @param   specUuid Identifier of component Specification.
        /// @return  Collection of factories of given component specification.
        /// @remarks The collection may be empty if no factories have been
        ///          registered for the given specification identifier.
        virtual FactoryCollection GetFactories(const Uuid specUuid) = 0;
    };
}

#endif // SMP_IDYNAMICSIMULATOR_H

/***********
 * History *
 ***********/

//$Log: IDynamicSimulator.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

