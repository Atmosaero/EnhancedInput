/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "EnhancedInputSystemComponent.h"

#include <EnhancedInput/EnhancedInputTypeIds.h>
#include <EnhancedInput/InputTrigger.h>
#include <EnhancedInput/InputModifier.h>
#include <EnhancedInput/InputMappingContext.h>
#include <EnhancedInput/EnhancedInputLuaHelper.h>
#include <EnhancedInput/InputTypes.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzFramework/Input/Devices/Keyboard/InputDeviceKeyboard.h>
#include <AzFramework/Input/Devices/Mouse/InputDeviceMouse.h>
#include <AzFramework/Input/Devices/Gamepad/InputDeviceGamepad.h>

namespace EnhancedInput
{
    class EnhancedInputNotificationBusHandler
        : public EnhancedInputNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(EnhancedInputNotificationBusHandler, "{CBDCDEF0-1234-5678-9ABC-DEF012345678}", AZ::SystemAllocator,
            OnActionTriggered,
            OnActionStarted,
            OnActionOngoing,
            OnActionCompleted,
            OnActionCanceled);

        void OnActionTriggered(const InputActionInstance& instance) override
        {
            Call(FN_OnActionTriggered, instance);
        }

        void OnActionStarted(const InputActionInstance& instance) override
        {
            Call(FN_OnActionStarted, instance);
        }

        void OnActionOngoing(const InputActionInstance& instance) override
        {
            Call(FN_OnActionOngoing, instance);
        }

        void OnActionCompleted(const InputActionInstance& instance) override
        {
            Call(FN_OnActionCompleted, instance);
        }

        void OnActionCanceled(const InputActionInstance& instance) override
        {
            Call(FN_OnActionCanceled, instance);
        }
    };

    AZ_COMPONENT_IMPL(EnhancedInputSystemComponent, "EnhancedInputSystemComponent",
        EnhancedInputSystemComponentTypeId);

    void EnhancedInputSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        InputValue::Reflect(context);
        InputAction::Reflect(context);
        InputTrigger::Reflect(context);
        InputTriggerPressed::Reflect(context);
        InputTriggerReleased::Reflect(context);
        InputTriggerDown::Reflect(context);
        InputTriggerHold::Reflect(context);
        InputTriggerTap::Reflect(context);
        InputTriggerPulse::Reflect(context);
        InputModifier::Reflect(context);
        InputModifierDeadZone::Reflect(context);
        InputModifierNegate::Reflect(context);
        InputModifierScale::Reflect(context);
        InputModifierSwizzle::Reflect(context);
        InputModifierClamp::Reflect(context);
        InputModifierNormalize::Reflect(context);
        InputMappingContext::Reflect(context);
        ReflectInputTypes(context);

        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<EnhancedInputSystemComponent, AZ::Component>()
                ->Version(1);
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->EnumProperty<static_cast<int>(InputValueType::Boolean)>("InputValueType_Boolean");
            behaviorContext->EnumProperty<static_cast<int>(InputValueType::Axis1D)>("InputValueType_Axis1D");
            behaviorContext->EnumProperty<static_cast<int>(InputValueType::Axis2D)>("InputValueType_Axis2D");
            behaviorContext->EnumProperty<static_cast<int>(InputValueType::Axis3D)>("InputValueType_Axis3D");

            behaviorContext->EnumProperty<static_cast<int>(TriggerState::None)>("TriggerState_None");
            behaviorContext->EnumProperty<static_cast<int>(TriggerState::Started)>("TriggerState_Started");
            behaviorContext->EnumProperty<static_cast<int>(TriggerState::Ongoing)>("TriggerState_Ongoing");
            behaviorContext->EnumProperty<static_cast<int>(TriggerState::Triggered)>("TriggerState_Triggered");
            behaviorContext->EnumProperty<static_cast<int>(TriggerState::Completed)>("TriggerState_Completed");
            behaviorContext->EnumProperty<static_cast<int>(TriggerState::Canceled)>("TriggerState_Canceled");

            behaviorContext->EnumProperty<0>("Trigger_Pressed");
            behaviorContext->EnumProperty<1>("Trigger_Released");
            behaviorContext->EnumProperty<2>("Trigger_Down");
            behaviorContext->EnumProperty<3>("Trigger_Hold");
            behaviorContext->EnumProperty<4>("Trigger_Tap");
            behaviorContext->EnumProperty<5>("Trigger_Pulse");

            behaviorContext->EnumProperty<0>("Key_A");
            behaviorContext->EnumProperty<1>("Key_B");
            behaviorContext->EnumProperty<2>("Key_C");
            behaviorContext->EnumProperty<3>("Key_D");
            behaviorContext->EnumProperty<4>("Key_E");
            behaviorContext->EnumProperty<5>("Key_F");
            behaviorContext->EnumProperty<6>("Key_G");
            behaviorContext->EnumProperty<7>("Key_H");
            behaviorContext->EnumProperty<8>("Key_I");
            behaviorContext->EnumProperty<9>("Key_J");
            behaviorContext->EnumProperty<10>("Key_K");
            behaviorContext->EnumProperty<11>("Key_L");
            behaviorContext->EnumProperty<12>("Key_M");
            behaviorContext->EnumProperty<13>("Key_N");
            behaviorContext->EnumProperty<14>("Key_O");
            behaviorContext->EnumProperty<15>("Key_P");
            behaviorContext->EnumProperty<16>("Key_Q");
            behaviorContext->EnumProperty<17>("Key_R");
            behaviorContext->EnumProperty<18>("Key_S");
            behaviorContext->EnumProperty<19>("Key_T");
            behaviorContext->EnumProperty<20>("Key_U");
            behaviorContext->EnumProperty<21>("Key_V");
            behaviorContext->EnumProperty<22>("Key_W");
            behaviorContext->EnumProperty<23>("Key_X");
            behaviorContext->EnumProperty<24>("Key_Y");
            behaviorContext->EnumProperty<25>("Key_Z");
            behaviorContext->EnumProperty<26>("Key_0");
            behaviorContext->EnumProperty<27>("Key_1");
            behaviorContext->EnumProperty<28>("Key_2");
            behaviorContext->EnumProperty<29>("Key_3");
            behaviorContext->EnumProperty<30>("Key_4");
            behaviorContext->EnumProperty<31>("Key_5");
            behaviorContext->EnumProperty<32>("Key_6");
            behaviorContext->EnumProperty<33>("Key_7");
            behaviorContext->EnumProperty<34>("Key_8");
            behaviorContext->EnumProperty<35>("Key_9");
            behaviorContext->EnumProperty<36>("Key_Space");
            behaviorContext->EnumProperty<37>("Key_Enter");
            behaviorContext->EnumProperty<38>("Key_Escape");
            behaviorContext->EnumProperty<39>("Key_Tab");
            behaviorContext->EnumProperty<40>("Key_Backspace");
            behaviorContext->EnumProperty<41>("Key_LShift");
            behaviorContext->EnumProperty<42>("Key_RShift");
            behaviorContext->EnumProperty<43>("Key_LCtrl");
            behaviorContext->EnumProperty<44>("Key_RCtrl");
            behaviorContext->EnumProperty<45>("Key_LAlt");
            behaviorContext->EnumProperty<46>("Key_RAlt");
            behaviorContext->EnumProperty<47>("Key_Up");
            behaviorContext->EnumProperty<48>("Key_Down");
            behaviorContext->EnumProperty<49>("Key_Left");
            behaviorContext->EnumProperty<50>("Key_Right");
            behaviorContext->EnumProperty<51>("Key_F1");
            behaviorContext->EnumProperty<52>("Key_F2");
            behaviorContext->EnumProperty<53>("Key_F3");
            behaviorContext->EnumProperty<54>("Key_F4");
            behaviorContext->EnumProperty<55>("Key_F5");
            behaviorContext->EnumProperty<56>("Key_F6");
            behaviorContext->EnumProperty<57>("Key_F7");
            behaviorContext->EnumProperty<58>("Key_F8");
            behaviorContext->EnumProperty<59>("Key_F9");
            behaviorContext->EnumProperty<60>("Key_F10");
            behaviorContext->EnumProperty<61>("Key_F11");
            behaviorContext->EnumProperty<62>("Key_F12");

            behaviorContext->EnumProperty<100>("Mouse_Left");
            behaviorContext->EnumProperty<101>("Mouse_Right");
            behaviorContext->EnumProperty<102>("Mouse_Middle");
            behaviorContext->EnumProperty<103>("Mouse_X");
            behaviorContext->EnumProperty<104>("Mouse_Y");
            behaviorContext->EnumProperty<105>("Mouse_Wheel");

            behaviorContext->EnumProperty<200>("Gamepad_A");
            behaviorContext->EnumProperty<201>("Gamepad_B");
            behaviorContext->EnumProperty<202>("Gamepad_X");
            behaviorContext->EnumProperty<203>("Gamepad_Y");
            behaviorContext->EnumProperty<204>("Gamepad_LB");
            behaviorContext->EnumProperty<205>("Gamepad_RB");
            behaviorContext->EnumProperty<206>("Gamepad_LT");
            behaviorContext->EnumProperty<207>("Gamepad_RT");
            behaviorContext->EnumProperty<208>("Gamepad_LS");
            behaviorContext->EnumProperty<209>("Gamepad_RS");
            behaviorContext->EnumProperty<210>("Gamepad_Start");
            behaviorContext->EnumProperty<211>("Gamepad_Select");
            behaviorContext->EnumProperty<212>("Gamepad_DPadUp");
            behaviorContext->EnumProperty<213>("Gamepad_DPadDown");
            behaviorContext->EnumProperty<214>("Gamepad_DPadLeft");
            behaviorContext->EnumProperty<215>("Gamepad_DPadRight");
            behaviorContext->EnumProperty<216>("Gamepad_LeftStickX");
            behaviorContext->EnumProperty<217>("Gamepad_LeftStickY");
            behaviorContext->EnumProperty<218>("Gamepad_RightStickX");
            behaviorContext->EnumProperty<219>("Gamepad_RightStickY");

            behaviorContext->Class<InputValue>("InputValue")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Constructor()
                ->Constructor<bool>()
                ->Constructor<float>()
                ->Method("IsZero", &InputValue::IsZero)
                ->Method("GetBool", &InputValue::GetBool)
                ->Method("GetAxis1D", &InputValue::GetAxis1D)
                ->Method("GetAxis2D", &InputValue::GetAxis2D)
                ->Method("GetAxis3D", &InputValue::GetAxis3D);

            behaviorContext->Class<InputActionInstance>("InputActionInstance")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Property("Value", [](const InputActionInstance* self) { return self->m_value; }, nullptr)
                ->Property("ElapsedTime", [](const InputActionInstance* self) { return self->m_elapsedTime; }, nullptr)
                ->Property("TriggeredTime", [](const InputActionInstance* self) { return self->m_triggeredTime; }, nullptr)
                ->Method("IsTriggered", &InputActionInstance::IsTriggered)
                ->Method("IsOngoing", &InputActionInstance::IsOngoing)
                ->Method("IsCompleted", &InputActionInstance::IsCompleted)
                ->Method("GetActionName", [](const InputActionInstance* self) -> AZStd::string {
                    return self->m_action ? self->m_action->GetName() : "";
                });

            behaviorContext->Class<InputMappingContext>("InputMappingContext")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Constructor<const AZStd::string&>()
                ->Method("GetName", &InputMappingContext::GetName)
                ->Method("ClearBindings", &InputMappingContext::ClearBindings);

            behaviorContext->Class<EnhancedInputLuaHelper>("EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Method("CreateContext", &EnhancedInputLuaHelper::CreateContext, { { { "ContextName", "" } } })
                ->Method("RegisterAction", &EnhancedInputLuaHelper::RegisterAction, { { { "ActionName", "" }, { "ValueType", "Boolean, Axis1D, Axis2D, Axis3D" } } })
                ->Method("UnregisterAction", &EnhancedInputLuaHelper::UnregisterAction, { { { "ActionName", "" } } })
                ->Method("BindKey", &EnhancedInputLuaHelper::BindKey, { { { "Context", "" }, { "ActionName", "" }, { "KeyName", "" } } })
                ->Method("BindKeyWithTrigger", &EnhancedInputLuaHelper::BindKeyWithTrigger, { { { "Context", "" }, { "ActionName", "" }, { "KeyName", "" }, { "TriggerType", "" } } })
                ->Method("BindAxis", &EnhancedInputLuaHelper::BindAxis, { { { "Context", "" }, { "ActionName", "" }, { "KeyName", "" }, { "ScaleX", "" }, { "ScaleY", "" }, { "ScaleZ", "" } } })
                ->Method("Bind", &EnhancedInputLuaHelper::Bind, { { { "Context", "" }, { "ActionName", "" }, { "KeyCode", "" }, { "TriggerType", "" } } })
                ->Method("AddContext", &EnhancedInputLuaHelper::AddContext, { { { "Context", "" }, { "Priority", "" } } })
                ->Method("RemoveContext", &EnhancedInputLuaHelper::RemoveContext, { { { "ContextName", "" } } })
                ->Method("ClearAllContexts", &EnhancedInputLuaHelper::ClearAllContexts)
                ->Method("GetActionValue", &EnhancedInputLuaHelper::GetActionValue, { { { "ActionName", "" } } })
                ->Method("GetActionValueX", &EnhancedInputLuaHelper::GetActionValueX, { { { "ActionName", "" } } })
                ->Method("GetActionValueY", &EnhancedInputLuaHelper::GetActionValueY, { { { "ActionName", "" } } })
                ->Method("GetActionValueZ", &EnhancedInputLuaHelper::GetActionValueZ, { { { "ActionName", "" } } })
                ->Method("IsActionTriggered", &EnhancedInputLuaHelper::IsActionTriggered, { { { "ActionName", "" } } })
                ->Method("AddModifierDeadZone", &EnhancedInputLuaHelper::AddModifierDeadZone, { { { "Context", "" }, { "ActionName", "" }, { "LowerThreshold", "" }, { "UpperThreshold", "" }, { "Type", "Axial or Radial" } } })
                ->Method("AddModifierNegate", &EnhancedInputLuaHelper::AddModifierNegate, { { { "Context", "" }, { "ActionName", "" }, { "NegateX", "" }, { "NegateY", "" }, { "NegateZ", "" } } })
                ->Method("AddModifierScale", &EnhancedInputLuaHelper::AddModifierScale, { { { "Context", "" }, { "ActionName", "" }, { "ScaleX", "" }, { "ScaleY", "" }, { "ScaleZ", "" } } })
                ->Method("AddModifierSwizzle", &EnhancedInputLuaHelper::AddModifierSwizzle, { { { "Context", "" }, { "ActionName", "" }, { "Order", "XYZ, XZY, YXZ, YZX, ZXY, ZYX" } } })
                ->Method("AddModifierClamp", &EnhancedInputLuaHelper::AddModifierClamp, { { { "Context", "" }, { "ActionName", "" }, { "MinValue", "" }, { "MaxValue", "" } } })
                ->Method("AddModifierNormalize", &EnhancedInputLuaHelper::AddModifierNormalize, { { { "Context", "" }, { "ActionName", "" } } });

            behaviorContext->EBus<EnhancedInputRequestBus>("EnhancedInputRequestBus")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Event("RegisterAction", &EnhancedInputRequests::RegisterAction)
                ->Event("UnregisterAction", &EnhancedInputRequests::UnregisterAction)
                ->Event("GetActionState", &EnhancedInputRequests::GetActionState);

            behaviorContext->EBus<EnhancedInputNotificationBus>("EnhancedInputNotificationBus")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Handler<EnhancedInputNotificationBusHandler>();
        }
    }

    void EnhancedInputSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("EnhancedInputService"));
    }

    void EnhancedInputSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("EnhancedInputService"));
    }

    void EnhancedInputSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void EnhancedInputSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    EnhancedInputSystemComponent::EnhancedInputSystemComponent()
    {
        if (EnhancedInputInterface::Get() == nullptr)
        {
            EnhancedInputInterface::Register(this);
        }
    }

    EnhancedInputSystemComponent::~EnhancedInputSystemComponent()
    {
        if (EnhancedInputInterface::Get() == this)
        {
            EnhancedInputInterface::Unregister(this);
        }
    }

    void EnhancedInputSystemComponent::Init()
    {
    }

    void EnhancedInputSystemComponent::Activate()
    {
        EnhancedInputRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
        AzFramework::InputChannelEventListener::Connect();
    }

    void EnhancedInputSystemComponent::Deactivate()
    {
        AzFramework::InputChannelEventListener::Disconnect();
        AZ::TickBus::Handler::BusDisconnect();
        EnhancedInputRequestBus::Handler::BusDisconnect();

        m_registeredActions.clear();
        m_activeContexts.clear();
        m_actionBindings.clear();
        m_actionStates.clear();
        m_pendingInputs.clear();
    }

    void EnhancedInputSystemComponent::RegisterAction(const AZStd::string& name, InputValueType valueType)
    {
        if (m_registeredActions.find(name) == m_registeredActions.end())
        {
            m_registeredActions[name] = InputAction(name, valueType);
            m_actionStates[name] = ActionRuntimeState();
            m_actionStates[name].m_instance.m_action = &m_registeredActions[name];
        }
    }

    void EnhancedInputSystemComponent::UnregisterAction(const AZStd::string& name)
    {
        m_registeredActions.erase(name);
        m_actionStates.erase(name);
        m_actionBindings.erase(name);
    }

    const InputAction* EnhancedInputSystemComponent::GetAction(const AZStd::string& name) const
    {
        auto it = m_registeredActions.find(name);
        return it != m_registeredActions.end() ? &it->second : nullptr;
    }

    void EnhancedInputSystemComponent::AddMappingContext(InputMappingContextPtr context, int priority)
    {
        if (context)
        {
            ActiveMappingContext active;
            active.m_context = context;
            active.m_priority = priority;
            m_activeContexts.insert(active);
        }
    }

    void EnhancedInputSystemComponent::RemoveMappingContext(const AZStd::string& contextName)
    {
        for (auto it = m_activeContexts.begin(); it != m_activeContexts.end(); ++it)
        {
            if (it->m_context && it->m_context->GetName() == contextName)
            {
                m_activeContexts.erase(it);
                break;
            }
        }
    }

    void EnhancedInputSystemComponent::ClearMappingContexts()
    {
        m_activeContexts.clear();
    }

    void EnhancedInputSystemComponent::BindAction(const AZStd::string& actionName, TriggerEvent events, InputActionCallback callback)
    {
        m_actionBindings[actionName] = ActionBindingData{ events, callback };
    }

    void EnhancedInputSystemComponent::UnbindAction(const AZStd::string& actionName)
    {
        m_actionBindings.erase(actionName);
    }

    const InputActionInstance* EnhancedInputSystemComponent::GetActionState(const AZStd::string& actionName) const
    {
        auto it = m_actionStates.find(actionName);
        return it != m_actionStates.end() ? &it->second.m_instance : nullptr;
    }

    bool EnhancedInputSystemComponent::OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel)
    {
        const AzFramework::InputChannelId& channelId = inputChannel.GetInputChannelId();
        AZ::Crc32 channelCrc = channelId.GetNameCrc32();
        float value = inputChannel.GetValue();

        if (inputChannel.IsStateEnded())
        {
            m_pendingInputs[channelCrc] = InputValue(0.0f);
        }
        else
        {
            m_pendingInputs[channelCrc] = InputValue(value);
        }

        return false;
    }

    void EnhancedInputSystemComponent::OnTick(float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
        for (auto& [actionName, state] : m_actionStates)
        {
            state.m_accumulatedValue = InputValue();
        }

        for (const auto& activeContext : m_activeContexts)
        {
            if (!activeContext.m_context)
            {
                continue;
            }

            for (const auto& binding : activeContext.m_context->GetBindings())
            {
                auto inputIt = m_pendingInputs.find(binding.m_inputChannelId.GetNameCrc32());
                if (inputIt == m_pendingInputs.end())
                {
                    continue;
                }

                InputValue modifiedValue = ApplyModifiers(inputIt->second, binding.m_modifiers);

                auto stateIt = m_actionStates.find(binding.m_actionName);
                if (stateIt != m_actionStates.end())
                {
                    AZ::Vector3 current = stateIt->second.m_accumulatedValue.GetAxis3D();
                    AZ::Vector3 incoming = modifiedValue.GetAxis3D();
                    stateIt->second.m_accumulatedValue = InputValue(current + incoming);

                    for (const auto& trigger : binding.m_triggers)
                    {
                        if (trigger)
                        {
                            stateIt->second.m_activeTriggers.push_back(trigger);
                        }
                    }
                }
            }
        }

        for (auto& [actionName, state] : m_actionStates)
        {
            state.m_instance.m_previousValue = state.m_instance.m_value;
            state.m_instance.m_value = state.m_accumulatedValue;

            TriggerState triggerState = TriggerState::None;

            if (!state.m_activeTriggers.empty())
            {
                triggerState = EvaluateTriggers(state.m_accumulatedValue, state.m_activeTriggers, deltaTime);
                state.m_activeTriggers.clear();
            }
            else
            {
                if (!state.m_accumulatedValue.IsZero())
                {
                    triggerState = TriggerState::Triggered;
                }
            }

            TriggerState previousState = state.m_instance.m_triggerState;
            state.m_instance.m_triggerState = triggerState;

            if (triggerState != TriggerState::None || previousState != TriggerState::None)
            {
                state.m_instance.m_elapsedTime += deltaTime;
                if (triggerState == TriggerState::Triggered)
                {
                    state.m_instance.m_triggeredTime = state.m_instance.m_elapsedTime;
                }

                NotifyActionState(actionName, state.m_instance);
            }

            if (triggerState == TriggerState::None || triggerState == TriggerState::Completed || triggerState == TriggerState::Canceled)
            {
                state.m_instance.m_elapsedTime = 0.0f;
            }
        }

        m_pendingInputs.clear();
    }

    void EnhancedInputSystemComponent::ProcessInputForAction(
        [[maybe_unused]] const AZStd::string& actionName,
        [[maybe_unused]] const InputValue& rawValue,
        [[maybe_unused]] float deltaTime)
    {
    }

    void EnhancedInputSystemComponent::NotifyActionState(const AZStd::string& actionName, const InputActionInstance& instance)
    {
        auto bindingIt = m_actionBindings.find(actionName);
        if (bindingIt != m_actionBindings.end())
        {
            const auto& binding = bindingIt->second;
            bool shouldCallback = false;

            switch (instance.m_triggerState)
            {
            case TriggerState::Started:
                shouldCallback = HasFlag(binding.m_events, TriggerEvent::Started);
                break;
            case TriggerState::Ongoing:
                shouldCallback = HasFlag(binding.m_events, TriggerEvent::Ongoing);
                break;
            case TriggerState::Triggered:
                shouldCallback = HasFlag(binding.m_events, TriggerEvent::Triggered);
                break;
            case TriggerState::Completed:
                shouldCallback = HasFlag(binding.m_events, TriggerEvent::Completed);
                break;
            case TriggerState::Canceled:
                shouldCallback = HasFlag(binding.m_events, TriggerEvent::Canceled);
                break;
            default:
                break;
            }

            if (shouldCallback && binding.m_callback)
            {
                binding.m_callback(instance);
            }
        }

        switch (instance.m_triggerState)
        {
        case TriggerState::Started:
            EnhancedInputNotificationBus::Event(actionName, &EnhancedInputNotifications::OnActionStarted, instance);
            break;
        case TriggerState::Ongoing:
            EnhancedInputNotificationBus::Event(actionName, &EnhancedInputNotifications::OnActionOngoing, instance);
            break;
        case TriggerState::Triggered:
            EnhancedInputNotificationBus::Event(actionName, &EnhancedInputNotifications::OnActionTriggered, instance);
            break;
        case TriggerState::Completed:
            EnhancedInputNotificationBus::Event(actionName, &EnhancedInputNotifications::OnActionCompleted, instance);
            break;
        case TriggerState::Canceled:
            EnhancedInputNotificationBus::Event(actionName, &EnhancedInputNotifications::OnActionCanceled, instance);
            break;
        default:
            break;
        }
    }

    InputValue EnhancedInputSystemComponent::ApplyModifiers(const InputValue& value, const AZStd::vector<InputModifierPtr>& modifiers) const
    {
        InputValue result = value;
        for (const auto& modifier : modifiers)
        {
            if (modifier)
            {
                result = modifier->ModifyValue(result);
            }
        }
        return result;
    }

    TriggerState EnhancedInputSystemComponent::EvaluateTriggers(
        const InputValue& value,
        AZStd::vector<InputTriggerPtr>& triggers,
        float deltaTime) const
    {
        if (triggers.empty())
        {
            return value.IsZero() ? TriggerState::None : TriggerState::Triggered;
        }

        TriggerState bestState = TriggerState::None;

        for (auto& trigger : triggers)
        {
            if (trigger)
            {
                TriggerState state = trigger->UpdateState(value, deltaTime);
                if (static_cast<int>(state) > static_cast<int>(bestState))
                {
                    bestState = state;
                }
            }
        }

        return bestState;
    }

} // namespace EnhancedInput
