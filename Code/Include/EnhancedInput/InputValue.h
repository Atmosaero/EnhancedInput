/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Math/Vector2.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/RTTI/RTTI.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace EnhancedInput
{
    enum class InputValueType : AZ::u8
    {
        Boolean,
        Axis1D,
        Axis2D,
        Axis3D
    };

    struct InputValue
    {
        AZ_TYPE_INFO(InputValue, "{F3A1B2C4-D5E6-7890-ABCD-EF1234567890}");
        AZ_CLASS_ALLOCATOR(InputValue, AZ::SystemAllocator);

        InputValue() = default;
        explicit InputValue(bool value) : m_type(InputValueType::Boolean) { m_data.SetX(value ? 1.0f : 0.0f); }
        explicit InputValue(float value) : m_type(InputValueType::Axis1D) { m_data.SetX(value); }
        explicit InputValue(const AZ::Vector2& value) : m_type(InputValueType::Axis2D) { m_data.SetX(value.GetX()); m_data.SetY(value.GetY()); }
        explicit InputValue(const AZ::Vector3& value) : m_type(InputValueType::Axis3D) { m_data = value; }

        bool IsZero() const
        {
            return m_data.IsZero();
        }

        bool GetBool() const { return m_data.GetX() != 0.0f; }
        float GetAxis1D() const { return m_data.GetX(); }
        AZ::Vector2 GetAxis2D() const { return AZ::Vector2(m_data.GetX(), m_data.GetY()); }
        AZ::Vector3 GetAxis3D() const { return m_data; }

        InputValueType GetType() const { return m_type; }

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<InputValue>()
                    ->Version(1)
                    ->Field("Type", &InputValue::m_type)
                    ->Field("Data", &InputValue::m_data);
            }
        }

        InputValueType m_type = InputValueType::Boolean;
        AZ::Vector3 m_data = AZ::Vector3::CreateZero();
    };

} // namespace EnhancedInput
