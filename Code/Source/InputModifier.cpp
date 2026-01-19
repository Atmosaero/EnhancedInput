/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/InputModifier.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Math/MathUtils.h>

namespace EnhancedInput
{
    void InputModifier::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifier>()
                ->Version(1);
        }
    }

    InputValue InputModifierDeadZone::ModifyValue(const InputValue& value) const
    {
        AZ::Vector3 data = value.GetAxis3D();

        auto applyDeadZone = [this](float v) -> float
        {
            float absVal = AZ::GetAbs(v);
            if (absVal < m_lowerThreshold)
            {
                return 0.0f;
            }
            if (absVal > m_upperThreshold)
            {
                return v > 0.0f ? 1.0f : -1.0f;
            }
            float normalized = (absVal - m_lowerThreshold) / (m_upperThreshold - m_lowerThreshold);
            return v > 0.0f ? normalized : -normalized;
        };

        if (m_type == DeadZoneType::Axial)
        {
            data.SetX(applyDeadZone(data.GetX()));
            data.SetY(applyDeadZone(data.GetY()));
            data.SetZ(applyDeadZone(data.GetZ()));
        }
        else
        {
            float length = data.GetLength();
            if (length < m_lowerThreshold)
            {
                data = AZ::Vector3::CreateZero();
            }
            else if (length > m_upperThreshold)
            {
                data = data.GetNormalized();
            }
            else
            {
                float normalized = (length - m_lowerThreshold) / (m_upperThreshold - m_lowerThreshold);
                data = data.GetNormalized() * normalized;
            }
        }

        return InputValue(data);
    }

    void InputModifierDeadZone::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifierDeadZone, InputModifier>()
                ->Version(1)
                ->Field("LowerThreshold", &InputModifierDeadZone::m_lowerThreshold)
                ->Field("UpperThreshold", &InputModifierDeadZone::m_upperThreshold)
                ->Field("Type", &InputModifierDeadZone::m_type);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputModifierDeadZone>("Dead Zone", "Applies dead zone to input values")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Slider, &InputModifierDeadZone::m_lowerThreshold, "Lower Threshold", "Values below this are treated as zero")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                    ->DataElement(AZ::Edit::UIHandlers::Slider, &InputModifierDeadZone::m_upperThreshold, "Upper Threshold", "Values above this are treated as max")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                    ->DataElement(AZ::Edit::UIHandlers::ComboBox, &InputModifierDeadZone::m_type, "Type", "Dead zone calculation type");
            }
        }
    }

    InputValue InputModifierNegate::ModifyValue(const InputValue& value) const
    {
        AZ::Vector3 data = value.GetAxis3D();
        if (m_negateX) data.SetX(-data.GetX());
        if (m_negateY) data.SetY(-data.GetY());
        if (m_negateZ) data.SetZ(-data.GetZ());
        return InputValue(data);
    }

    void InputModifierNegate::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifierNegate, InputModifier>()
                ->Version(1)
                ->Field("NegateX", &InputModifierNegate::m_negateX)
                ->Field("NegateY", &InputModifierNegate::m_negateY)
                ->Field("NegateZ", &InputModifierNegate::m_negateZ);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputModifierNegate>("Negate", "Inverts input values")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputModifierNegate::m_negateX, "Negate X", "")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputModifierNegate::m_negateY, "Negate Y", "")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputModifierNegate::m_negateZ, "Negate Z", "");
            }
        }
    }

    InputValue InputModifierScale::ModifyValue(const InputValue& value) const
    {
        float inputMagnitude = value.GetAxis1D();
        AZ::Vector3 result = m_scale * inputMagnitude;
        return InputValue(result);
    }

    void InputModifierScale::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifierScale, InputModifier>()
                ->Version(1)
                ->Field("Scale", &InputModifierScale::m_scale);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputModifierScale>("Scale", "Multiplies input values by scale factor")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputModifierScale::m_scale, "Scale", "Scale multiplier for each axis");
            }
        }
    }

    InputValue InputModifierSwizzle::ModifyValue(const InputValue& value) const
    {
        AZ::Vector3 data = value.GetAxis3D();
        float x = data.GetX();
        float y = data.GetY();
        float z = data.GetZ();

        switch (m_order)
        {
        case SwizzleOrder::XYZ: break;
        case SwizzleOrder::XZY: data.Set(x, z, y); break;
        case SwizzleOrder::YXZ: data.Set(y, x, z); break;
        case SwizzleOrder::YZX: data.Set(y, z, x); break;
        case SwizzleOrder::ZXY: data.Set(z, x, y); break;
        case SwizzleOrder::ZYX: data.Set(z, y, x); break;
        }

        return InputValue(data);
    }

    void InputModifierSwizzle::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifierSwizzle, InputModifier>()
                ->Version(1)
                ->Field("Order", &InputModifierSwizzle::m_order);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputModifierSwizzle>("Swizzle", "Reorders input axes")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::ComboBox, &InputModifierSwizzle::m_order, "Order", "Axis reordering");
            }
        }
    }

    InputValue InputModifierClamp::ModifyValue(const InputValue& value) const
    {
        AZ::Vector3 data = value.GetAxis3D();
        data.SetX(AZ::GetClamp(data.GetX(), m_min, m_max));
        data.SetY(AZ::GetClamp(data.GetY(), m_min, m_max));
        data.SetZ(AZ::GetClamp(data.GetZ(), m_min, m_max));
        return InputValue(data);
    }

    void InputModifierClamp::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifierClamp, InputModifier>()
                ->Version(1)
                ->Field("Min", &InputModifierClamp::m_min)
                ->Field("Max", &InputModifierClamp::m_max);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputModifierClamp>("Clamp", "Clamps input values to range")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputModifierClamp::m_min, "Min", "Minimum value")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputModifierClamp::m_max, "Max", "Maximum value");
            }
        }
    }

    InputValue InputModifierNormalize::ModifyValue(const InputValue& value) const
    {
        AZ::Vector3 data = value.GetAxis3D();
        if (!data.IsZero())
        {
            data.Normalize();
        }
        return InputValue(data);
    }

    void InputModifierNormalize::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputModifierNormalize, InputModifier>()
                ->Version(1);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputModifierNormalize>("Normalize", "Normalizes input vector to unit length")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }
    }

} // namespace EnhancedInput
