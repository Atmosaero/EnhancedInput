/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/string/string.h>
#include <EnhancedInput/EnhancedInputBus.h>

namespace EnhancedInput
{
    class PlayerInputComponent
        : public AZ::Component
        , public EnhancedInputNotificationBus::Handler
    {
    public:
        AZ_COMPONENT(PlayerInputComponent, "{A9BACBDC-DEF0-1234-5678-90ABCDEF0123}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        PlayerInputComponent() = default;
        ~PlayerInputComponent() override = default;

        void SubscribeToAction(const AZStd::string& actionName);
        void UnsubscribeFromAction(const AZStd::string& actionName);
        void UnsubscribeFromAllActions();

    protected:
        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void OnActionTriggered(const InputActionInstance& instance) override;
        void OnActionStarted(const InputActionInstance& instance) override;
        void OnActionOngoing(const InputActionInstance& instance) override;
        void OnActionCompleted(const InputActionInstance& instance) override;
        void OnActionCanceled(const InputActionInstance& instance) override;

    private:
        AZStd::vector<AZStd::string> m_subscribedActions;
    };

    class PlayerInputNotifications
        : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
        using BusIdType = AZ::EntityId;

        virtual void OnInputActionTriggered([[maybe_unused]] const AZStd::string& actionName, [[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnInputActionStarted([[maybe_unused]] const AZStd::string& actionName, [[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnInputActionOngoing([[maybe_unused]] const AZStd::string& actionName, [[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnInputActionCompleted([[maybe_unused]] const AZStd::string& actionName, [[maybe_unused]] const InputActionInstance& instance) {}
        virtual void OnInputActionCanceled([[maybe_unused]] const AZStd::string& actionName, [[maybe_unused]] const InputActionInstance& instance) {}
    };

    using PlayerInputNotificationBus = AZ::EBus<PlayerInputNotifications>;

} // namespace EnhancedInput
