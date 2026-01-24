/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <EnhancedInput/EnhancedInputTypeIds.h>
#include <EnhancedInput/InputAction.h>
#include <EnhancedInput/InputMappingContext.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/std/functional.h>

namespace EnhancedInput
{
    using InputActionCallback = AZStd::function<void(const InputActionInstance&)>;

    class EnhancedInputRequests
    {
    public:
        AZ_RTTI(EnhancedInputRequests, EnhancedInputRequestsTypeId);
        virtual ~EnhancedInputRequests() = default;

        virtual void RegisterAction(const AZStd::string& name, InputValueType valueType = InputValueType::Boolean) = 0;
        virtual void UnregisterAction(const AZStd::string& name) = 0;
        virtual const InputAction* GetAction(const AZStd::string& name) const = 0;

        virtual void AddMappingContext(InputMappingContextPtr context, int priority = 0) = 0;
        virtual void RemoveMappingContext(const AZStd::string& contextName) = 0;
        virtual void ClearMappingContexts() = 0;

        virtual void BindAction(const AZStd::string& actionName, TriggerEvent events, InputActionCallback callback) = 0;
        virtual void UnbindAction(const AZStd::string& actionName) = 0;

        virtual const InputActionInstance* GetActionState(const AZStd::string& actionName) const = 0;
    };

    class EnhancedInputBusTraits
        : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using EnhancedInputRequestBus = AZ::EBus<EnhancedInputRequests, EnhancedInputBusTraits>;
    using EnhancedInputInterface = AZ::Interface<EnhancedInputRequests>;

    class EnhancedInputNotifications
        : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        virtual void OnActionTriggered([[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnActionStarted([[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnActionOngoing([[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnActionCompleted([[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnActionCanceled([[maybe_unused]] const InputActionInstance& instance) {}
    };

    using EnhancedInputNotificationBus = AZ::EBus<EnhancedInputNotifications>;

} // namespace EnhancedInput
