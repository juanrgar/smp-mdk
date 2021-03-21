//
// Title:
//      IPersist.h
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
//      This file defines the IPersist interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IPERSIST_H
#define SMP_IPERSIST_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/Exceptions.h"

// ----------------------------------------------------------------------------
// ---------------------------- IStorageReader interface ----------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Storage reader.
    /// Provide functionality to read data from a storage.
    /// This interface is provided by a client (typically the simulation
    /// environment) to allow models implementing the IPersist interface 
    /// to restore their state. It is passed to the Restore() method of every
    /// component implementing IPersist.
    /// @remarks This interface is platform specific.
    ///          For details see the SMP Platform Mappings.
    class IStorageReader
    {
    public:
        /// Virtual destructor.
        virtual ~IStorageReader() { }

        /// Restore data from storage.
        /// This method reads a memory block of data from the state vector.
        /// @param   address Memory address of memory block.
        /// @param   size Size of memory block.
        /// @remarks It is the component's responsibility to <code>Store</code>
        ///             a block of the same size to IStorageWrite on Store.
        virtual void Restore(void* address, Int32 size) = 0;
    };
}

// ----------------------------------------------------------------------------
// ---------------------------- IStorageWriter interface ----------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Storage writer.
    /// Provide functionality to write data to a storage.
    /// This interface is provided by a client (typically the simulation
    /// environment) to allow models implementing the IPersist interface 
    /// to store their state. It is passed to the Store() method of every
    /// component implementing IPersist.
    /// @remarks This interface is platform specific.
    ///          For details see the SMP Platform Mappings.
    class IStorageWriter
    {
    public:
        /// Virtual destructor.
        virtual ~IStorageWriter() { }

        /// Store data to storage.
        /// This method writes a memory block of data to the state vector.
        /// @param   address Memory address of memory block.
        /// @param   size Size of memory block.
        /// @remarks It is the component's responsibility to <code>Restore</code>
        ///             a block of the same size from IStorageReader on Restore.
        virtual void Store(void* address, Int32 size) = 0;
    };
}

// ----------------------------------------------------------------------------
// ---------------------------- IPersist interface ----------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    static const Smp::String8 CannotStoreTemplate   = "Cannot store data: %s";
    static const Smp::String8 CannotRestoreTemplate = "Cannot restore data: %s";

    /// Self persistence for components.
    /// A component may implement this interface if it wants to have control
    /// over loading and saving of its state.
    /// @remarks This is an optional interface. It needs to be implemented
    ///          for components with self-persistence only.
    class IPersist : public virtual IComponent
    {    
    public:
        /// Cannot restore from storage reader (IStorageReader).
        /// This exception is raised when the content of the storage reader
        /// passed to the Restore() method contains invalid data.
        /// @remarks This typically happens when a Store() has been created
        /// from a different configuration of components.
        class CannotRestore : public Smp::Exception
        {
        public:
            /// Error message indicating details of the problem.
            String8 message;

            CannotRestore(
                String8 _message) throw() :
            Smp::Exception("CannotRestore"),
                message(_message)
            {
                description = new Char8[strlen(CannotRestoreTemplate) 
                    + strlen(message)];

                sprintf(description, CannotRestoreTemplate, 
                    message);
            }
        };

        /// Cannot store to storage writer (IStorageWriter).
        /// This exception is raised when the component cannot store its data
        /// to the storage writer given to the Store() method.
        /// @remarks This may e.g. be if there is no disk space left.
        class CannotStore : public Smp::Exception
        {
        public:
            /// Error message indicating details of the problem.
            String8 message;

            CannotStore(
                String8 _message) throw() :
            Smp::Exception("CannotStore"),
                message(_message)
            {
                description = new Char8[strlen(CannotStoreTemplate) 
                    + strlen(message)];

                sprintf(description, CannotStoreTemplate, 
                    message);
            }
        };

        /// Restore component state from storage.
        /// @param    reader Interface that allows reading from storage.
        virtual void Restore(IStorageReader* reader) throw (
            Smp::IPersist::CannotRestore) = 0;

        /// Store component state to storage.
        /// @param    writer Interface that allows writing to storage.
        virtual void Store(IStorageWriter* writer) throw (
            Smp::IPersist::CannotStore) = 0;
    };
}

#endif    // SMP_IPERSIST_H

/***********
 * History *
 ***********/

//$Log: IPersist.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

