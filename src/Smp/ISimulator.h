//
// Title:
//      ISimulator.h
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
//      This file defines the ISimulator interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_ISIMULATOR_H
#define SMP_ISIMULATOR_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/IModel.h"
#include "Smp/IService.h"
#include "Smp/IComposite.h"
#include "Smp/Exceptions.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/ITimeKeeper.h"
#include "Smp/Services/IEventManager.h"
#include "Smp/Management/IManagedContainer.h"

// ---------------------------------------------------------------------------
// --------------------------- Simulator Container ---------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    // ------------------------------------------------------------------------
    // Predefined Simulator Containers
    // ------------------------------------------------------------------------

    const String8 SMP_SimulatorModels   = "Models";
    const String8 SMP_SimulatorServices = "Services";
}

// ---------------------------------------------------------------------------
// --------------------------- SimulatorStateKind ----------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    /// Enumeration of available simulator states.
    /// The Simulator is always in one of these simulator states.
    enum SimulatorStateKind
    {
        /// In Building state, the model hierarchy is created. This
        /// is done by an external component, not by the simulator.
        /// @par
        /// This state is entered automatically after the simulation 
        /// environment has performed its initialisation.
        /// @par
        /// To leave it, call the Connect() state transition method.
        SSK_Building,

        /// In Connecting state, the simulation environment traverses the 
        /// model hierarchy and calls the Connect() method of each model.
        /// @par
        /// This state is entered using the Connect() state transition.
        /// @par
        /// After connecting all models to the simulator, an automatic 
        /// state transition to the Initialising state is performed.
        SSK_Connecting,

        /// In Initialising state, the simulation environment traverses the
        /// model hierarchy and calls the Initialize method of each model.
        /// @par
        /// This state is either entered automatically after the simulation
        /// environment has connected all models to the simulator, or
        /// manually from Standby state using the Initialise() state transition.
        /// @par
        /// After initialising all models, an automatic state transition to
        /// the Standby state is performed.
        SSK_Initialising,

        /// In Standby state, the simulation environment (namely 
        /// the Time Keeper Service) does not progress simulation time.
        /// Only entry points registered relative to Zulu time 
        /// are executed.
        /// @par
        /// This state is entered automatically from the Initialising,
        /// Storing, and Restoring states, or manually from the Running state
        /// using the Hold() state transition.
        /// @par
        /// To leave this state, call one of the Run(), Store(), Restore(), or 
        /// Exit() state transitions.
        SSK_Standby,

        /// In Executing state, the simulation environment (namely 
        /// the Time Keeper Service) does progress simulation time.
        /// Entry points registered with any of the available time kinds 
        /// are executed.
        /// @par
        /// This state is entered using the Run() state transition.
        /// @par
        /// To leave this state, call the Hold() state transition.
        SSK_Executing,

        /// In Storing state, the simulation environment stores the values
        /// of all fields published with the State attribute to disk.
        /// Further, the Store() method of all components implementing the
        /// optional IPersist interface is called, to allow custom
        /// serialisation of additional information.
        /// While in this state, fields published with the State attribute
        /// must not be modified by the models, to ensure a consistent
        /// vector of field values is stored.
        /// @par
        /// This state is entered using the Store() state transition.
        /// @par
        /// After storing the simulator state, an automatic state transition
        /// to the Standby state is performed.
        SSK_Storing,

        /// In Restoring state, the simulation environment restores the values
        /// of all fields published with the State attribute from disk.
        /// Further, the Restore() method of all components implementing the
        /// optional IPersist interface is called, to allow custom
        /// deserialisation of additional information.
        /// While in this state, fields published with the State attribute
        /// must not be modified by the models, to ensure a consistent
        /// vector of field values is stored.
        /// @par
        /// This state is entered using the Restore() state transition.
        /// @par
        /// After restoring the simulator state, an automatic state transition
        /// to the Standby state is performed.
        SSK_Restoring,

        /// In Exiting state, the simulation environment is properly
        /// terminating a running simulation.
        /// @par
        /// This state is entered using the Exit() state transition.
        /// @par
        /// After exiting, the simulator is in an undefined state.
        SSK_Exiting,

        /// In this state, the simulation environment performs an
        /// abnormal simulation shut-down.
        /// @par
        /// This state is entered using the Abort() state transition.
        /// @par
        /// After aborting, the simulator is in an undefined state.
        SSK_Aborting
    };
}

// ---------------------------------------------------------------------------
// --------------------------- ISimulator interface --------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    /// Interface to the Simulator.
    /// The Simulator is a composite component that manages models and services.
    /// As a service provider, it allows to add services, and to query for them.
    /// As a model container, it allows to add root models, and to query for them.
    /// In addition, the Simulator gives access to the simulator state.
    /// @remarks Typically, this interface is implemented by
    ///          the simulation environment itself.
    class ISimulator : public virtual IComposite
    {
    public:
        /// Get all models.
        /// Query for the collection of all root models.
        /// @return Collection of root model components.
        /// @remarks The collection may be empty if no models exist
        ///          in the Models container.
        virtual const ModelCollection* GetModels() = 0;

        /// Get a root model by name.
        /// Query for a root model by its name.
        /// @param   name Model name.
        /// @return  Root model with the given name, or null if no 
        ///          root model with the given name could be found.
        /// @remarks Users should always check the return value, as null
        ///          is returned when no root model with the given name
        ///          could be found.
        virtual IModel* GetModel(String8 name) = 0;

        /// Add a root model.
        /// Add a new root model to the simulator.
        /// @param   model The root model.
        /// @remarks As root models are identified by their name, the new model
        ///          needs to have a unique name within the root models.
        ///          Otherwise, it will not be added, and an exception of type
        ///          DuplicateName will be raised.
        virtual void AddModel(IModel* model) throw (
            Smp::DuplicateName) = 0;

        /// Get all services.
        /// Query for the collection of all services.
        /// @return Collection of services.
        /// @remarks The collection may be empty if no services exist
        ///          in the Services container.
        virtual const ServiceCollection* GetServices() = 0;

        /// Get a service by name.
        /// Query for a service by its name.
        /// @param   name Service name.
        /// @return  Service with the given name, or null if no 
        ///          service with the given name could be found.
        /// @remarks Users should always check the return value, as null
        ///          is returned when no service with the given name
        ///          could be found.
        virtual IService* GetService(String8 name) = 0;

        /// Add a user-defined service.
        /// Add a new service to the simulator.
        /// @param   service The user-defined service.
        /// @remarks As services are identified by their name, the new service
        ///          needs to have a unique name within the services.
        ///          Otherwise, it will not be added, and an exception of type
        ///          DuplicateName will be raised.
        virtual void AddService(IService* service) throw (
            Smp::DuplicateName) = 0;

        /// Get logger service.
        /// Query for mandatory logger service.
        /// @return  Mandatory logger service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          logger service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        virtual Services::ILogger* GetLogger() const = 0;

        /// Get scheduler service.
        /// Query for mandatory scheduler service.
        /// @return  Mandatory scheduler service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          scheduler service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        virtual Services::IScheduler* GetScheduler() const = 0;

        /// Get time keeper service.
        /// Query for mandatory time keeper service.
        /// @return  Mandatory time keeper service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          time keeper service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        virtual Services::ITimeKeeper* GetTimeKeeper() const = 0;

        /// Get event manager service.
        /// Query for mandatory event manager service.
        /// @return  Mandatory event manager service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          event manager service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        virtual Services::IEventManager* GetEventManager() const = 0;

        /// Get simulator state.
        /// Returns the current simulator state.
        /// @return  Current simulator state.
        virtual SimulatorStateKind GetState() const = 0;

        /// Call Publish() method of models.
        /// This method asks the simulation environment to call the Publish()
        /// method of all model instance in the hierarchy which are still in
        /// <em>Created</em> state.
        /// @remarks This method is typically called by an external component
        ///          after creating new model instances.
        virtual void Publish() = 0;

        /// Call Configure() method of models.
        /// This method asks the simulation environment to call the Configure()
        /// method of all model instance in the hierarchy which are still in
        /// <em>Publishing</em> state.
        /// @remarks This method is typically called by an external component
        ///          after setting field values of new model instances,
        ///          typically using the information in an SMDL Assembly.
        ///          This method can only be called in Building state.
        virtual void Configure() = 0;

        /// Enter Connecting state.
        /// This method informs the simulation environment that the hierarchy
        /// of model instances has been built, and can now be connected
        /// to the simulator. After connecting all models, an automatic state
        /// transition to the Initialising state is performed.
        /// @remarks This method is typically called by an external component
        ///          after creating and configuring all model instances.
        virtual void Connect() = 0;

        /// Enter initialising state.
        /// This method changes from Standby state to Initialising state,
        /// where each initialisation entry point will be executed again.
        /// @remarks The entry points will be called in the order they
        ///          have been added using the AddInitEntryPoint() method.
        virtual void Initialise() = 0;

        /// Enter standby state.
        /// This method changes from executing to standby state.
        /// @remarks This method can only be called when in Executing state.
        virtual void Hold() = 0;

        /// Enter executing state.
        /// This method changes from standby to executing state.
        /// @remarks This method can only be called when in Standby state.
        virtual void Run() = 0;

        /// Enter storing state.
        /// This method is used to store a state vector to file.
        /// @param   filename Name to use for simulation state vector file.
        /// @remarks This method can only be called when in Standby state.
        virtual void Store(String8 filename) = 0;

        /// Enter restoring state.
        /// This method is used to restore a state vector from file.
        /// @param   filename Name of simulation state vector file.
        /// @remarks This method can only be called when in Standby state.
        virtual void Restore(String8 filename) = 0;

        /// Enter exiting state.
        /// This method is used for a normal termination of a simulation.
        /// @remarks This method can only be called when in Standby state.
        virtual void Exit() = 0;

        /// Enter aborting state.
        /// This method is used for an abnormal termination of a simulation.
        /// @remarks This method can be called from any other state.
        virtual void Abort() = 0;

        /// Add initialisation entry point.
        /// This method can be used to add entry points that shall be executed
        /// in the Initialising state.
        /// These entry points will be called in the order they have been
        /// added to the simulator using this method.
        /// @par
        /// The ITask interface (which is derived from IEntryPoint) can be 
        /// used to add several entry points in a well-defined order.
        virtual void AddInitEntryPoint(IEntryPoint* entryPoint) = 0;
    };
}

#endif // SMP_ISIMULATOR_H

/***********
 * History *
 ***********/

//$Log: ISimulator.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

