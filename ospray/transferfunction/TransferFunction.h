//
//                 INTEL CORPORATION PROPRIETARY INFORMATION
//
//    This software is supplied under the terms of a license agreement or
//    nondisclosure agreement with Intel Corporation and may not be copied
//    or disclosed except in accordance with the terms of that agreement.
//    Copyright (C) 2014 Intel Corporation. All Rights Reserved.
//

#pragma once

#include "ospray/common/managed.h"

//! \brief Define a function to create an instance of the InternalClass
//!  associated with ExternalName.
//!
//! \internal The function generated by this macro is used to create an
//!  instance of a concrete subtype of an abstract base class.  This
//!  macro is needed since the subclass type may not be known to OSPRay
//!  at build time.  Rather, the subclass can be defined in an external
//!  module and registered with OSPRay using this macro.
//!
#define OSP_REGISTER_TRANSFER_FUNCTION(InternalClass, ExternalName) \
    extern "C" TransferFunction *ospray_create_transfer_function_##ExternalName() \
        { return(new InternalClass()); }

namespace ospray {

    //! \brief A TransferFunction is an abstraction that maps a value to
    //!  a color and opacity for rendering.
    //!
    //!  The actual mapping is unknown to this class, and is implemented
    //!  in subclasses.  A type string specifies a particular concrete
    //!  implementation to createInstance().  This type string must be
    //!  registered in OSPRay proper, or in a loaded module using
    //!  OSP_REGISTER_TRANSFER_FUNCTION.
    //!
    class TransferFunction : public ManagedObject {
    public:

        //! Constructor.
        TransferFunction() {};

        //! Destructor.
        virtual ~TransferFunction() {};

        //! Allocate storage and populate the transfer function.
        virtual void commit() = 0;

        //! Create a transfer function of the given type.
        static TransferFunction *createInstance(std::string type);

        //! Get the ISPC transfer function.
        void *getEquivalentISPC() const { return(getIE()); }

        //! A string description of this class.
        virtual std::string toString() const { return("ospray::TransferFunction"); }

    protected:

        //! Create the equivalent ISPC transfer function.
        virtual void createEquivalentISPC() = 0;

        //! Print an error message.
        void emitMessage(const std::string &kind, const std::string &message) const
            { std::cerr << "  " + toString() + "  " + kind + ": " + message + "." << std::endl; }

        //! Error checking.
        void exitOnCondition(bool condition, const std::string &message) const
            { if (!condition) return;  emitMessage("ERROR", message);  exit(1); }

        //! Warning condition.
        void warnOnCondition(bool condition, const std::string &message) const
            { if (!condition) return;  emitMessage("WARNING", message); }

    };

} // namespace ospray

