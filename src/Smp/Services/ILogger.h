//
// Title:
//      ILogger.h
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
//      This file defines the ILogger interface for the logger service.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_SERVICES_ILOGGER_H
#define SMP_SERVICES_ILOGGER_H

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
        /// Identifier of log message kind.
        typedef Int32 LogMessageKind;

        // Predefined Logger Message Kinds
        const LogMessageKind LMK_Information = 0;  ///< Information message.
        const LogMessageKind LMK_Event       = 1;  ///< Event message.
        const LogMessageKind LMK_Warning     = 2;  ///< Warning message.
        const LogMessageKind LMK_Error       = 3;  ///< Error message.
        const LogMessageKind LMK_Debug       = 4;  ///< Debug message.

        // Names of predefined Log Message Kinds
        const String8 LMK_InformationName = "Information";
        const String8 LMK_EventName       = "Event";
        const String8 LMK_WarningName     = "Warning";
        const String8 LMK_ErrorName       = "Error";
        const String8 LMK_DebugName       = "Debug";

        /// Name of Logger service.
        const String8 SMP_Logger    = "Smp_Logger";
    }
}

// ----------------------------------------------------------------------------
// --------------------------- ILogger interface ------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Services
    {
        /// This interface gives access to the Logger.
        /// All objects in a simulation can log messages using this service.
        /// @remarks This is a mandatory service the simulation environment
        ///          has to provide via its GetService() method.
        class ILogger : public virtual IService
        {
        public:
            /// Return identifier of log message kind by name.
            /// This method can be used for pre-defined log message kinds,
            /// but is especially useful for user-defined log message kinds.
            /// @param   messageKindName Name of log message kind.
            /// @return  Identifier of log message kind.
            /// @remarks It is guaranteed that this method always returns
            ///          the same id for the same messageKindName string.
            virtual Smp::Services::LogMessageKind GetLogMessageKind(
                Smp::String8 messageKindName) = 0;

            /// Mechanism to log a messages.
            /// This function logs a message to the simulation log file.
            /// @param   sender Object that sends the message.
            /// @param   message The message to log.
            /// @param   kind Kind of message.
            virtual void Log(
                const IObject* sender,
                String8 message,
                const LogMessageKind kind = LMK_Information) = 0;
        };
    }
}

#endif // SMP_SERVICES_ILOGGER_H

/***********
 * History *
 ***********/

//$Log: ILogger.h,v $
//Revision 1.2  2006/09/27 11:43:57  nin
//SMP2 v1.2
// 

