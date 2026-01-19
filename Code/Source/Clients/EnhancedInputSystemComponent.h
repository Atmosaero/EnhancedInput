/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/std/containers/map.h>
#include <AzCore/std/containers/set.h>
#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/Math/Crc.h>
#include <AzFramework/Input/Events/InputChannelEventListener.h>
#include <EnhancedInput/EnhancedInputBus.h>

namespace EnhancedInput
{
    struct ActionBindingData
    {
        TriggerEvent m_events = TriggerEvent::None;
        InputActionCallback m_callback;
    };

    struct ActionRuntimeState
    {
        InputActionInstance m_instance;
        AZStd::vector<InputTriggerPtr> m_activeTriggers;
        InputValue m_accumulatedValue;
    };

    class EnhancedInputSystemComponent
        : public AZ::Component
        , protected EnhancedInputRequestBus::Handler
        , public AZ::TickBus::Handler
        , public AzFramework::InputChannelEventListener
    {
    public:
        AZ_COMPONENT_DECL(EnhancedInputSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        EnhancedInputSystemComponent();
        ~EnhancedInputSystemComponent();

    protected:
        void RegisterAction(const AZStd::string& name, InputValueType valueType = InputValueType::Boolean) override;
        void UnregisterAction(const AZStd::string& name) override;
        const InputAction* GetAction(const AZStd::string& name) const override;

        void AddMappingContext(InputMappingContextPtr context, int priority = 0) override;
        void RemoveMappingContext(const AZStd::string& contextName) override;
        void ClearMappingContexts() override;

        void BindAction(const AZStd::string& actionName, TriggerEvent events, InputActionCallback callback) override;
        void UnbindAction(const AZStd::string& actionName) override;

        const InputActionInstance* GetActionState(const AZStd::string& actionName) const override;

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;

        bool OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel) override;

    private:
        void ProcessInputForAction(const AZStd::string& actionName, const InputValue& rawValue, float deltaTime);
        void NotifyActionState(const AZStd::string& actionName, const InputActionInstance& instance);
        InputValue ApplyModifiers(const InputValue& value, const AZStd::vector<InputModifierPtr>& modifiers) const;
        TriggerState EvaluateTriggers(const InputValue& value, AZStd::vector<InputTriggerPtr>& triggers, float deltaTime) const;

        AZStd::map<AZStd::string, InputAction> m_registeredActions;
        AZStd::set<ActiveMappingContext> m_activeContexts;
        AZStd::map<AZStd::string, ActionBindingData> m_actionBindings;
        AZStd::map<AZStd::string, ActionRuntimeState> m_actionStates;
        AZStd::unordered_map<AZ::Crc32, InputValue> m_pendingInputs;
    };

} // namespace EnhancedInput
