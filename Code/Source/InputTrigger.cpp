/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/InputTrigger.h>
#include <AzCore/Serialization/EditContext.h>

namespace EnhancedInput
{
    void InputTrigger::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTrigger>()
                ->Version(1);
        }
    }

    TriggerState InputTriggerPressed::UpdateState(const InputValue& value, [[maybe_unused]] float deltaTime)
    {
        bool isPressed = !value.IsZero();

        if (isPressed && !m_wasPressed)
        {
            m_state = TriggerState::Triggered;
        }
        else
        {
            m_state = TriggerState::None;
        }

        m_wasPressed = isPressed;
        return m_state;
    }

    void InputTriggerPressed::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTriggerPressed, InputTrigger>()
                ->Version(1);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputTriggerPressed>("Pressed", "Triggers once when input is first pressed")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }
    }

    TriggerState InputTriggerReleased::UpdateState(const InputValue& value, [[maybe_unused]] float deltaTime)
    {
        bool isPressed = !value.IsZero();

        if (!isPressed && m_wasPressed)
        {
            m_state = TriggerState::Triggered;
        }
        else
        {
            m_state = TriggerState::None;
        }

        m_wasPressed = isPressed;
        return m_state;
    }

    void InputTriggerReleased::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTriggerReleased, InputTrigger>()
                ->Version(1);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputTriggerReleased>("Released", "Triggers once when input is released")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }
    }

    TriggerState InputTriggerDown::UpdateState(const InputValue& value, [[maybe_unused]] float deltaTime)
    {
        if (!value.IsZero())
        {
            m_state = TriggerState::Triggered;
        }
        else
        {
            m_state = TriggerState::None;
        }
        return m_state;
    }

    void InputTriggerDown::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTriggerDown, InputTrigger>()
                ->Version(1);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputTriggerDown>("Down", "Triggers every frame while input is held")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }
    }

    TriggerState InputTriggerHold::UpdateState(const InputValue& value, float deltaTime)
    {
        if (!value.IsZero())
        {
            m_elapsedTime += deltaTime;

            if (m_elapsedTime >= m_holdTime)
            {
                if (m_triggerOnce && m_hasTriggered)
                {
                    m_state = TriggerState::Ongoing;
                }
                else
                {
                    m_state = TriggerState::Triggered;
                    m_hasTriggered = true;
                }
            }
            else
            {
                m_state = TriggerState::Ongoing;
            }
        }
        else
        {
            if (m_state == TriggerState::Ongoing || m_state == TriggerState::Triggered)
            {
                m_state = TriggerState::Canceled;
            }
            else
            {
                m_state = TriggerState::None;
            }
            m_elapsedTime = 0.0f;
            m_hasTriggered = false;
        }

        return m_state;
    }

    void InputTriggerHold::Reset()
    {
        InputTrigger::Reset();
        m_elapsedTime = 0.0f;
        m_hasTriggered = false;
    }

    void InputTriggerHold::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTriggerHold, InputTrigger>()
                ->Version(1)
                ->Field("HoldTime", &InputTriggerHold::m_holdTime)
                ->Field("TriggerOnce", &InputTriggerHold::m_triggerOnce);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputTriggerHold>("Hold", "Triggers after input is held for specified duration")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputTriggerHold::m_holdTime, "Hold Time", "Time in seconds to hold before triggering")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputTriggerHold::m_triggerOnce, "Trigger Once", "If true, only triggers once per hold");
            }
        }
    }

    TriggerState InputTriggerTap::UpdateState(const InputValue& value, float deltaTime)
    {
        bool isPressed = !value.IsZero();

        if (isPressed)
        {
            if (!m_wasPressed)
            {
                m_elapsedTime = 0.0f;
            }
            else
            {
                m_elapsedTime += deltaTime;
            }
            m_state = TriggerState::Ongoing;
        }
        else
        {
            if (m_wasPressed && m_elapsedTime <= m_maxTapTime)
            {
                m_state = TriggerState::Triggered;
            }
            else
            {
                m_state = TriggerState::None;
            }
            m_elapsedTime = 0.0f;
        }

        m_wasPressed = isPressed;
        return m_state;
    }

    void InputTriggerTap::Reset()
    {
        InputTrigger::Reset();
        m_elapsedTime = 0.0f;
        m_wasPressed = false;
    }

    void InputTriggerTap::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTriggerTap, InputTrigger>()
                ->Version(1)
                ->Field("MaxTapTime", &InputTriggerTap::m_maxTapTime);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputTriggerTap>("Tap", "Triggers when input is pressed and released quickly")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputTriggerTap::m_maxTapTime, "Max Tap Time", "Maximum time for a tap to register");
            }
        }
    }

    TriggerState InputTriggerPulse::UpdateState(const InputValue& value, float deltaTime)
    {
        if (!value.IsZero())
        {
            m_timeSinceLastTrigger += deltaTime;

            if (m_isFirstTrigger && m_triggerOnStart)
            {
                m_state = TriggerState::Triggered;
                m_isFirstTrigger = false;
                m_timeSinceLastTrigger = 0.0f;
            }
            else if (m_timeSinceLastTrigger >= m_interval)
            {
                m_state = TriggerState::Triggered;
                m_timeSinceLastTrigger = 0.0f;
                m_isFirstTrigger = false;
            }
            else
            {
                m_state = TriggerState::Ongoing;
            }
        }
        else
        {
            m_state = TriggerState::None;
            m_timeSinceLastTrigger = 0.0f;
            m_isFirstTrigger = true;
        }

        return m_state;
    }

    void InputTriggerPulse::Reset()
    {
        InputTrigger::Reset();
        m_timeSinceLastTrigger = 0.0f;
        m_isFirstTrigger = true;
    }

    void InputTriggerPulse::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputTriggerPulse, InputTrigger>()
                ->Version(1)
                ->Field("Interval", &InputTriggerPulse::m_interval)
                ->Field("TriggerOnStart", &InputTriggerPulse::m_triggerOnStart);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputTriggerPulse>("Pulse", "Triggers repeatedly at specified interval while held")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputTriggerPulse::m_interval, "Interval", "Time between pulses in seconds")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputTriggerPulse::m_triggerOnStart, "Trigger On Start", "If true, triggers immediately when pressed");
            }
        }
    }

} // namespace EnhancedInput
