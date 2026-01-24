/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/InputTypes.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace EnhancedInput
{
    void ReflectInputTypes(AZ::ReflectContext* context)
    {
        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->EnumProperty<static_cast<int>(TriggerType::Pressed)>("TriggerType_Pressed");
            behaviorContext->EnumProperty<static_cast<int>(TriggerType::Down)>("TriggerType_Down");
            behaviorContext->EnumProperty<static_cast<int>(TriggerType::Released)>("TriggerType_Released");

            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_A)>("InputKey_A");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_B)>("InputKey_B");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_C)>("InputKey_C");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_D)>("InputKey_D");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_E)>("InputKey_E");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F)>("InputKey_F");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_G)>("InputKey_G");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_H)>("InputKey_H");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_I)>("InputKey_I");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_J)>("InputKey_J");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_K)>("InputKey_K");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_L)>("InputKey_L");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_M)>("InputKey_M");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_N)>("InputKey_N");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_O)>("InputKey_O");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_P)>("InputKey_P");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Q)>("InputKey_Q");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_R)>("InputKey_R");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_S)>("InputKey_S");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_T)>("InputKey_T");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_U)>("InputKey_U");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_V)>("InputKey_V");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_W)>("InputKey_W");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_X)>("InputKey_X");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Y)>("InputKey_Y");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Z)>("InputKey_Z");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_0)>("InputKey_0");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_1)>("InputKey_1");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_2)>("InputKey_2");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_3)>("InputKey_3");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_4)>("InputKey_4");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_5)>("InputKey_5");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_6)>("InputKey_6");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_7)>("InputKey_7");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_8)>("InputKey_8");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_9)>("InputKey_9");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Space)>("InputKey_Space");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Enter)>("InputKey_Enter");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Escape)>("InputKey_Escape");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Tab)>("InputKey_Tab");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Backspace)>("InputKey_Backspace");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_LShift)>("InputKey_LShift");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_RShift)>("InputKey_RShift");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_LCtrl)>("InputKey_LCtrl");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_RCtrl)>("InputKey_RCtrl");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_LAlt)>("InputKey_LAlt");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_RAlt)>("InputKey_RAlt");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Up)>("InputKey_Up");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Down)>("InputKey_Down");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Left)>("InputKey_Left");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_Right)>("InputKey_Right");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F1)>("InputKey_F1");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F2)>("InputKey_F2");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F3)>("InputKey_F3");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F4)>("InputKey_F4");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F5)>("InputKey_F5");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F6)>("InputKey_F6");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F7)>("InputKey_F7");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F8)>("InputKey_F8");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F9)>("InputKey_F9");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F10)>("InputKey_F10");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F11)>("InputKey_F11");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Key_F12)>("InputKey_F12");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Mouse_Left)>("InputKey_MouseLeft");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Mouse_Right)>("InputKey_MouseRight");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Mouse_Middle)>("InputKey_MouseMiddle");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Mouse_X)>("InputKey_MouseX");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Mouse_Y)>("InputKey_MouseY");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Mouse_Wheel)>("InputKey_MouseWheel");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_A)>("InputKey_GamepadA");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_B)>("InputKey_GamepadB");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_X)>("InputKey_GamepadX");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_Y)>("InputKey_GamepadY");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_LB)>("InputKey_GamepadLB");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_RB)>("InputKey_GamepadRB");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_LT)>("InputKey_GamepadLT");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_RT)>("InputKey_GamepadRT");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_LS)>("InputKey_GamepadLS");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_RS)>("InputKey_GamepadRS");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_Start)>("InputKey_GamepadStart");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_Select)>("InputKey_GamepadSelect");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_DPadUp)>("InputKey_GamepadDPadUp");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_DPadDown)>("InputKey_GamepadDPadDown");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_DPadLeft)>("InputKey_GamepadDPadLeft");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_DPadRight)>("InputKey_GamepadDPadRight");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_LeftStickX)>("InputKey_GamepadLeftStickX");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_LeftStickY)>("InputKey_GamepadLeftStickY");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_RightStickX)>("InputKey_GamepadRightStickX");
            behaviorContext->EnumProperty<static_cast<int>(InputKey::Gamepad_RightStickY)>("InputKey_GamepadRightStickY");
        }
    }

} // namespace EnhancedInput
