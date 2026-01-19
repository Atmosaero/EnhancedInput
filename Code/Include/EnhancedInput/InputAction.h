/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Asset/AssetCommon.h>
#include <AzCore/RTTI/RTTI.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/std/string/string.h>
#include <EnhancedInput/InputValue.h>
#include <EnhancedInput/TriggerState.h>

namespace EnhancedInput
{
    class InputAction
    {
    public:
        AZ_TYPE_INFO(InputAction, "{A1B2C3D4-E5F6-7890-1234-567890ABCDEF}");
        AZ_CLASS_ALLOCATOR(InputAction, AZ::SystemAllocator);

        InputAction() = default;
        explicit InputAction(const AZStd::string& name, InputValueType valueType = InputValueType::Boolean)
            : m_name(name)
            , m_valueType(valueType)
        {
        }

        const AZStd::string& GetName() const { return m_name; }
        void SetName(const AZStd::string& name) { m_name = name; }

        InputValueType GetValueType() const { return m_valueType; }
        void SetValueType(InputValueType type) { m_valueType = type; }

        bool GetConsumeInput() const { return m_consumeInput; }
        void SetConsumeInput(bool consume) { m_consumeInput = consume; }

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<InputAction>()
                    ->Version(1)
                    ->Field("Name", &InputAction::m_name)
                    ->Field("ValueType", &InputAction::m_valueType)
                    ->Field("ConsumeInput", &InputAction::m_consumeInput);
            }
        }

    private:
        AZStd::string m_name;
        InputValueType m_valueType = InputValueType::Boolean;
        bool m_consumeInput = true;
    };

    struct InputActionInstance
    {
        AZ_TYPE_INFO(InputActionInstance, "{B2C3D4E5-F6A7-8901-2345-6789ABCDEF01}");

        const InputAction* m_action = nullptr;
        InputValue m_value;
        InputValue m_previousValue;
        TriggerState m_triggerState = TriggerState::None;
        float m_elapsedTime = 0.0f;
        float m_triggeredTime = 0.0f;

        void Reset()
        {
            m_previousValue = m_value;
            m_value = InputValue();
            m_triggerState = TriggerState::None;
        }

        bool IsTriggered() const { return m_triggerState == TriggerState::Triggered; }
        bool IsOngoing() const { return m_triggerState == TriggerState::Ongoing; }
        bool IsCompleted() const { return m_triggerState == TriggerState::Completed; }
    };

} // namespace EnhancedInput
