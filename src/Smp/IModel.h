//
// Title:
//      IModel.h
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
//      This file defines the IModel interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IMODEL_H
#define SMP_IMODEL_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exceptions.h"
#include "Smp/IComponent.h"
#include "Smp/IComposite.h"
#include "Smp/Services/ILogger.h"

// ----------------------------------------------------------------------------
// ---------------------------- IModel interface ------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    static const String8 InvalidModelStateTemplate       = "Invalid state: Expected '%s', but is '%s'";
    static const String8 ModelStateName[] =
    {
        "Created",      ///< Initial state of a model.
        "Publishing",   ///< Model can publish features.
        "Configured",   ///< Model has been configured.
        "Connected"     ///< Model has been connected.
    };


    // Forward declarations because of circular references.
    class IPublication;
    class ISimulator;

    /// Enumeration of available model states.
    /// Each model is always in one of these four model states.
    /// @par
    /// Before going into <em>Initialising</em> state, the simulator has to
    /// ensure that every model is in <em>Connected</em> state.
    enum ModelStateKind
    {
        /// The <em>Created</em> state is the initial state of a model.
        /// Model creation is done by an external mechanism, e.g. by Factories.
        /// @par
        /// This state is entered automatically after the model
        /// has been created.
        /// @par
        /// To leave it, call the Publish() state transition method.
        MSK_Created,

        /// In <em>Publishing</em> state, the model is allowed to publish features.
        /// This includes publication of fields, operations and properties.
        /// In addition, the model is allowed to create other models.
        /// @par
        /// This state is entered using the Publish() state transition.
        /// @par
        /// To leave it, call the Configure() state transition method.
        MSK_Publishing,

        /// In <em>Configured</em> state, the model has been fully configured.
        /// This configuration may be done by external components, e.g. based
        /// on information stored in an SMDL Assembly, or internally by the
        /// model itself, e.g. by reading data from an external source.
        /// @par
        /// This state is entered using the Configure() state transition.
        /// @par
        /// To leave it, call the Connect() state transition method.
        MSK_Configured,

        /// In <em>Connected</em> state, the model is connected to the simulator.
        /// In this state, neither publication nor creation of other models
        /// is allowed anymore.
        /// @par
        /// This state is entered using the Connect() state transition.
        MSK_Connected
    };

    /// Model base interface.
    /// All SMDL models implement this interface.
    /// @remarks This is the only mandatory interface models have to implement.
    ///             All other functionality derived from it is optional.
    class IModel : public virtual IComponent
    {
    public:
        /// Invalid model state.
        /// This exception is raised by a model when one of the
        /// state transition methods is called in an invalid state.
        class InvalidModelState : public Smp::Exception
        {
        public:
            /// Name of the state that is not valid.
            Smp::ModelStateKind invalidState;
            /// Name of the state that was expected.
            Smp::ModelStateKind expectedState;

            /// Constructor for new exception.
            InvalidModelState(
                Smp::ModelStateKind _invalidState,
                Smp::ModelStateKind _expectedState) throw() :
            Smp::Exception("InvalidModelState"),
                invalidState(_invalidState),
                expectedState(_expectedState)
            {
                description = new Char8[strlen(InvalidModelStateTemplate) 
                        + strlen(ModelStateName[expectedState]) 
                        + strlen(ModelStateName[invalidState])];

                sprintf(description, InvalidModelStateTemplate, 
                    ModelStateName[expectedState], 
                    ModelStateName[invalidState]);
            }
            ~InvalidModelState() throw() {}
        };

        /// Return model state.
        /// Return the state the model is currently in.
        /// @return  Current model state.
        /// @remarks The model state can be changed using the Publish(), 
        ///          Configure() and Connect() state transition methods.
        virtual ModelStateKind GetState() const = 0;

        /// Request for publication.
        /// Request the model to publish its fields and operations
        /// against the provided IPublication interface.
        /// @par
        /// This method can only be called once for each model, and only
        /// when the model is in the <em>Created</em> state.
        /// When this operation is called, the model immediately enters
        /// the <em>Publishing</em> state, before it publishes any of its
        /// features.
        /// @param   receiver Publication receiver.
        /// @remarks The simulation environment typically calls this
        ///          method in the <em>Building</em> state.
        virtual void Publish(IPublication* receiver) throw (
            Smp::IModel::InvalidModelState) = 0;

        /// Request for configuration.
        /// Request the model to perform any custom configuration.
        /// The model can create and configure other models using
        /// the field values of its published fields.
        /// @par
        /// This method can only be called once for each model, and only
        /// when the model is in <em>Publishing</em> state. The model can still
        /// publish further features in this call, and can even create other
        /// models, but at the end of this call, it needs to enter the
        /// <em>Configured</em> state.
        /// @param   logger Logger.
        /// @remarks The simulation environment typically calls this
        ///          method in the <em>Building</em> state.
        virtual void Configure(Smp::Services::ILogger* logger) throw (
            Smp::IModel::InvalidModelState) = 0;

        /// Connect model to simulator.
        /// Allow the model to connect to the simulator (ISimulator).
        /// @par
        /// This method can only be called once for each model, and only
        /// when the model is in the <em>Configured</em> state.
        /// When this operation is called, the model immediately enters
        /// the <em>Connected</em> state, before it uses any of the simulator
        /// methods and services.
        /// @par
        /// In this method, the model may query for and use any of the 
        /// available simulation services, as they are all guaranteed to be 
        /// fully functional at that time. It may as well
        /// connect to other models' functionality (e.g. to event sources),
        /// as it is guaranteed that all models have been created and
        /// configured before the Connect() method of any model is called.
        /// @param   simulator Simulation Environment that hosts the model.
        /// @remarks The simulation environment typically calls this
        ///          method in the <em>Connecting</em> state.
        virtual void Connect(ISimulator* simulator) throw (
            Smp::IModel::InvalidModelState) = 0;
    };
}

namespace Smp
{
    /// Collection of models.
    /// A model collection is an ordered collection of models,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings.
    typedef std::vector<IModel*> ModelCollection;
}

#endif // SMP_IMODEL_H

/***********
 * History *
 ***********/

//$Log: IModel.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

