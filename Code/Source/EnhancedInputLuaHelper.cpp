/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/EnhancedInputLuaHelper.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzFramework/Input/Devices/Keyboard/InputDeviceKeyboard.h>
#include <AzFramework/Input/Devices/Mouse/InputDeviceMouse.h>
#include <AzFramework/Input/Devices/Gamepad/InputDeviceGamepad.h>

namespace EnhancedInput
{
    InputMappingContextPtr EnhancedInputLuaHelper::CreateContext(const AZStd::string& name)
    {
        return AZStd::make_shared<InputMappingContext>(name);
    }

    void EnhancedInputLuaHelper::RegisterAction(const AZStd::string& actionName, const AZStd::string& valueType)
    {
        InputValueType type = InputValueType::Boolean;
        if (valueType == "boolean" || valueType == "Boolean" || valueType == "bool")
        {
            type = InputValueType::Boolean;
        }
        else if (valueType == "axis1d" || valueType == "Axis1D" || valueType == "1d")
        {
            type = InputValueType::Axis1D;
        }
        else if (valueType == "axis2d" || valueType == "Axis2D" || valueType == "2d")
        {
            type = InputValueType::Axis2D;
        }
        else if (valueType == "axis3d" || valueType == "Axis3D" || valueType == "3d")
        {
            type = InputValueType::Axis3D;
        }
        EnhancedInputRequestBus::Broadcast(&EnhancedInputRequests::RegisterAction, actionName, type);
    }

    void EnhancedInputLuaHelper::UnregisterAction(const AZStd::string& actionName)
    {
        EnhancedInputRequestBus::Broadcast(&EnhancedInputRequests::UnregisterAction, actionName);
    }

    void EnhancedInputLuaHelper::BindKey(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZStd::string& triggerType)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "BindKey: context is null");
            return;
        }

        InputActionBinding binding;
        binding.m_actionName = actionName;
        binding.m_inputChannelId = GetInputChannelIdFromName(keyName);

        auto trigger = CreateTriggerFromName(triggerType);
        if (trigger)
        {
            binding.m_triggers.push_back(trigger);
        }

        context->AddBinding(binding);
    }

    void EnhancedInputLuaHelper::BindAxis(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, float scaleX, float scaleY, float scaleZ)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "BindAxis: context is null");
            return;
        }

        InputActionBinding binding;
        binding.m_actionName = actionName;
        binding.m_inputChannelId = GetInputChannelIdFromName(keyName);

        auto trigger = AZStd::make_shared<InputTriggerDown>();
        binding.m_triggers.push_back(trigger);

        auto scaleModifier = AZStd::make_shared<InputModifierScale>(AZ::Vector3(scaleX, scaleY, scaleZ));
        binding.m_modifiers.push_back(scaleModifier);

        context->AddBinding(binding);
    }

    void EnhancedInputLuaHelper::BindAxis1D(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, float scale)
    {
        BindAxis(context, actionName, keyName, 0.0f, 0.0f, scale);
    }

    void EnhancedInputLuaHelper::BindAxis2D(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZ::Vector2& scale)
    {
        BindAxis(context, actionName, keyName, scale.GetX(), scale.GetY(), 0.0f);
    }

    void EnhancedInputLuaHelper::BindAxis3D(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZ::Vector3& scale)
    {
        BindAxis(context, actionName, keyName, scale.GetX(), scale.GetY(), scale.GetZ());
    }

    void EnhancedInputLuaHelper::AddContext(InputMappingContextPtr context, int priority)
    {
        EnhancedInputRequestBus::Broadcast(&EnhancedInputRequests::AddMappingContext, context, priority);
    }

    void EnhancedInputLuaHelper::RemoveContext(const AZStd::string& contextName)
    {
        EnhancedInputRequestBus::Broadcast(&EnhancedInputRequests::RemoveMappingContext, contextName);
    }

    void EnhancedInputLuaHelper::ClearAllContexts()
    {
        EnhancedInputRequestBus::Broadcast(&EnhancedInputRequests::ClearMappingContexts);
    }

    float EnhancedInputLuaHelper::GetActionValue(const AZStd::string& actionName)
    {
        const InputActionInstance* state = nullptr;
        EnhancedInputRequestBus::BroadcastResult(state, &EnhancedInputRequests::GetActionState, actionName);
        if (state)
        {
            return state->m_value.GetAxis1D();
        }
        return 0.0f;
    }

    float EnhancedInputLuaHelper::GetActionValueX(const AZStd::string& actionName)
    {
        const InputActionInstance* state = nullptr;
        EnhancedInputRequestBus::BroadcastResult(state, &EnhancedInputRequests::GetActionState, actionName);
        if (state)
        {
            return state->m_value.GetAxis3D().GetX();
        }
        return 0.0f;
    }

    float EnhancedInputLuaHelper::GetActionValueY(const AZStd::string& actionName)
    {
        const InputActionInstance* state = nullptr;
        EnhancedInputRequestBus::BroadcastResult(state, &EnhancedInputRequests::GetActionState, actionName);
        if (state)
        {
            return state->m_value.GetAxis3D().GetY();
        }
        return 0.0f;
    }

    float EnhancedInputLuaHelper::GetActionValueZ(const AZStd::string& actionName)
    {
        const InputActionInstance* state = nullptr;
        EnhancedInputRequestBus::BroadcastResult(state, &EnhancedInputRequests::GetActionState, actionName);
        if (state)
        {
            return state->m_value.GetAxis3D().GetZ();
        }
        return 0.0f;
    }

    bool EnhancedInputLuaHelper::IsActionTriggered(const AZStd::string& actionName)
    {
        const InputActionInstance* state = nullptr;
        EnhancedInputRequestBus::BroadcastResult(state, &EnhancedInputRequests::GetActionState, actionName);
        if (state)
        {
            return state->IsTriggered();
        }
        return false;
    }

    void EnhancedInputLuaHelper::AddModifierDeadZone(InputMappingContextPtr context, const AZStd::string& actionName, float lowerThreshold, float upperThreshold, const AZStd::string& type)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierDeadZone: context is null");
            return;
        }

        InputModifierDeadZone::DeadZoneType dzType = InputModifierDeadZone::DeadZoneType::Axial;
        if (type == "radial" || type == "Radial")
        {
            dzType = InputModifierDeadZone::DeadZoneType::Radial;
        }

        auto modifier = AZStd::make_shared<InputModifierDeadZone>(lowerThreshold, upperThreshold, dzType);

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    void EnhancedInputLuaHelper::AddModifierNegate(InputMappingContextPtr context, const AZStd::string& actionName, bool negateX, bool negateY, bool negateZ)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierNegate: context is null");
            return;
        }

        auto modifier = AZStd::make_shared<InputModifierNegate>(negateX, negateY, negateZ);

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    void EnhancedInputLuaHelper::AddModifierScaleVector(InputMappingContextPtr context, const AZStd::string& actionName, const AZ::Vector3& scale)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierScaleVector: context is null");
            return;
        }

        auto modifier = AZStd::make_shared<InputModifierScale>(scale);

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    void EnhancedInputLuaHelper::AddModifierDeadZoneVector(InputMappingContextPtr context, const AZStd::string& actionName, const AZ::Vector3& lowerThreshold, const AZ::Vector3& upperThreshold, const AZStd::string& type)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierDeadZoneVector: context is null");
            return;
        }

        InputModifierDeadZone::DeadZoneType dzType = InputModifierDeadZone::DeadZoneType::Axial;
        if (type == "radial" || type == "Radial")
        {
            dzType = InputModifierDeadZone::DeadZoneType::Radial;
        }

        // Create separate dead zone modifiers for each axis
        auto modifierX = AZStd::make_shared<InputModifierDeadZone>(lowerThreshold.GetX(), upperThreshold.GetX(), dzType);
        auto modifierY = AZStd::make_shared<InputModifierDeadZone>(lowerThreshold.GetY(), upperThreshold.GetY(), dzType);
        auto modifierZ = AZStd::make_shared<InputModifierDeadZone>(lowerThreshold.GetZ(), upperThreshold.GetZ(), dzType);

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifierX);
                binding.m_modifiers.push_back(modifierY);
                binding.m_modifiers.push_back(modifierZ);
            }
        }
    }

    
    AzFramework::InputChannelId EnhancedInputLuaHelper::GetInputChannelIdFromName(const AZStd::string& keyName)
    {
        using namespace AzFramework;

        if (keyName == "Mouse_Left" || keyName == "100") return InputDeviceMouse::Button::Left;
        if (keyName == "Mouse_Right" || keyName == "101") return InputDeviceMouse::Button::Right;
        if (keyName == "Mouse_Middle" || keyName == "102") return InputDeviceMouse::Button::Middle;
        if (keyName == "Mouse_X" || keyName == "103") return InputDeviceMouse::Movement::X;
        if (keyName == "Mouse_Y" || keyName == "104") return InputDeviceMouse::Movement::Y;
        if (keyName == "Mouse_Z" || keyName == "105") return InputDeviceMouse::Movement::Z;

        if (keyName == "Key_A" || keyName == "60") return InputDeviceKeyboard::Key::AlphanumericA;
        if (keyName == "Key_B" || keyName == "61") return InputDeviceKeyboard::Key::AlphanumericB;
        if (keyName == "Key_C" || keyName == "62") return InputDeviceKeyboard::Key::AlphanumericC;
        if (keyName == "Key_D" || keyName == "63") return InputDeviceKeyboard::Key::AlphanumericD;
        if (keyName == "Key_E" || keyName == "64") return InputDeviceKeyboard::Key::AlphanumericE;
        if (keyName == "Key_F" || keyName == "65") return InputDeviceKeyboard::Key::AlphanumericF;
        if (keyName == "Key_G" || keyName == "66") return InputDeviceKeyboard::Key::AlphanumericG;
        if (keyName == "Key_H" || keyName == "67") return InputDeviceKeyboard::Key::AlphanumericH;
        if (keyName == "Key_I" || keyName == "68") return InputDeviceKeyboard::Key::AlphanumericI;
        if (keyName == "Key_J" || keyName == "69") return InputDeviceKeyboard::Key::AlphanumericJ;
        if (keyName == "Key_K" || keyName == "70") return InputDeviceKeyboard::Key::AlphanumericK;
        if (keyName == "Key_L" || keyName == "71") return InputDeviceKeyboard::Key::AlphanumericL;
        if (keyName == "Key_M" || keyName == "72") return InputDeviceKeyboard::Key::AlphanumericM;
        if (keyName == "Key_N" || keyName == "73") return InputDeviceKeyboard::Key::AlphanumericN;
        if (keyName == "Key_O" || keyName == "74") return InputDeviceKeyboard::Key::AlphanumericO;
        if (keyName == "Key_P" || keyName == "75") return InputDeviceKeyboard::Key::AlphanumericP;
        if (keyName == "Key_Q" || keyName == "76") return InputDeviceKeyboard::Key::AlphanumericQ;
        if (keyName == "Key_R" || keyName == "77") return InputDeviceKeyboard::Key::AlphanumericR;
        if (keyName == "Key_S" || keyName == "78") return InputDeviceKeyboard::Key::AlphanumericS;
        if (keyName == "Key_T" || keyName == "79") return InputDeviceKeyboard::Key::AlphanumericT;
        if (keyName == "Key_U" || keyName == "80") return InputDeviceKeyboard::Key::AlphanumericU;
        if (keyName == "Key_V" || keyName == "81") return InputDeviceKeyboard::Key::AlphanumericV;
        if (keyName == "Key_W" || keyName == "82") return InputDeviceKeyboard::Key::AlphanumericW;
        if (keyName == "Key_X" || keyName == "83") return InputDeviceKeyboard::Key::AlphanumericX;
        if (keyName == "Key_Y" || keyName == "84") return InputDeviceKeyboard::Key::AlphanumericY;
        if (keyName == "Key_Z" || keyName == "85") return InputDeviceKeyboard::Key::AlphanumericZ;
        if (keyName == "Key_Space" || keyName == "86") return InputDeviceKeyboard::Key::EditSpace;
        if (keyName == "Key_Enter" || keyName == "87") return InputDeviceKeyboard::Key::EditEnter;
        if (keyName == "Key_Escape" || keyName == "88") return InputDeviceKeyboard::Key::Escape;

        if (keyName == "keyboard_key_alphanumeric_A" || keyName == "A") return InputDeviceKeyboard::Key::AlphanumericA;
        if (keyName == "keyboard_key_alphanumeric_B" || keyName == "B") return InputDeviceKeyboard::Key::AlphanumericB;
        if (keyName == "keyboard_key_alphanumeric_C" || keyName == "C") return InputDeviceKeyboard::Key::AlphanumericC;
        if (keyName == "keyboard_key_alphanumeric_D" || keyName == "D") return InputDeviceKeyboard::Key::AlphanumericD;
        if (keyName == "keyboard_key_alphanumeric_E" || keyName == "E") return InputDeviceKeyboard::Key::AlphanumericE;
        if (keyName == "keyboard_key_alphanumeric_F" || keyName == "F") return InputDeviceKeyboard::Key::AlphanumericF;
        if (keyName == "keyboard_key_alphanumeric_G" || keyName == "G") return InputDeviceKeyboard::Key::AlphanumericG;
        if (keyName == "keyboard_key_alphanumeric_H" || keyName == "H") return InputDeviceKeyboard::Key::AlphanumericH;
        if (keyName == "keyboard_key_alphanumeric_I" || keyName == "I") return InputDeviceKeyboard::Key::AlphanumericI;
        if (keyName == "keyboard_key_alphanumeric_J" || keyName == "J") return InputDeviceKeyboard::Key::AlphanumericJ;
        if (keyName == "keyboard_key_alphanumeric_K" || keyName == "K") return InputDeviceKeyboard::Key::AlphanumericK;
        if (keyName == "keyboard_key_alphanumeric_L" || keyName == "L") return InputDeviceKeyboard::Key::AlphanumericL;
        if (keyName == "keyboard_key_alphanumeric_M" || keyName == "M") return InputDeviceKeyboard::Key::AlphanumericM;
        if (keyName == "keyboard_key_alphanumeric_N" || keyName == "N") return InputDeviceKeyboard::Key::AlphanumericN;
        if (keyName == "keyboard_key_alphanumeric_O" || keyName == "O") return InputDeviceKeyboard::Key::AlphanumericO;
        if (keyName == "keyboard_key_alphanumeric_P" || keyName == "P") return InputDeviceKeyboard::Key::AlphanumericP;
        if (keyName == "keyboard_key_alphanumeric_Q" || keyName == "Q") return InputDeviceKeyboard::Key::AlphanumericQ;
        if (keyName == "keyboard_key_alphanumeric_R" || keyName == "R") return InputDeviceKeyboard::Key::AlphanumericR;
        if (keyName == "keyboard_key_alphanumeric_S" || keyName == "S") return InputDeviceKeyboard::Key::AlphanumericS;
        if (keyName == "keyboard_key_alphanumeric_T" || keyName == "T") return InputDeviceKeyboard::Key::AlphanumericT;
        if (keyName == "keyboard_key_alphanumeric_U" || keyName == "U") return InputDeviceKeyboard::Key::AlphanumericU;
        if (keyName == "keyboard_key_alphanumeric_V" || keyName == "V") return InputDeviceKeyboard::Key::AlphanumericV;
        if (keyName == "keyboard_key_alphanumeric_W" || keyName == "W") return InputDeviceKeyboard::Key::AlphanumericW;
        if (keyName == "keyboard_key_alphanumeric_X" || keyName == "X") return InputDeviceKeyboard::Key::AlphanumericX;
        if (keyName == "keyboard_key_alphanumeric_Y" || keyName == "Y") return InputDeviceKeyboard::Key::AlphanumericY;
        if (keyName == "keyboard_key_alphanumeric_Z" || keyName == "Z") return InputDeviceKeyboard::Key::AlphanumericZ;

        if (keyName == "keyboard_key_alphanumeric_0" || keyName == "0") return InputDeviceKeyboard::Key::Alphanumeric0;
        if (keyName == "keyboard_key_alphanumeric_1" || keyName == "1") return InputDeviceKeyboard::Key::Alphanumeric1;
        if (keyName == "keyboard_key_alphanumeric_2" || keyName == "2") return InputDeviceKeyboard::Key::Alphanumeric2;
        if (keyName == "keyboard_key_alphanumeric_3" || keyName == "3") return InputDeviceKeyboard::Key::Alphanumeric3;
        if (keyName == "keyboard_key_alphanumeric_4" || keyName == "4") return InputDeviceKeyboard::Key::Alphanumeric4;
        if (keyName == "keyboard_key_alphanumeric_5" || keyName == "5") return InputDeviceKeyboard::Key::Alphanumeric5;
        if (keyName == "keyboard_key_alphanumeric_6" || keyName == "6") return InputDeviceKeyboard::Key::Alphanumeric6;
        if (keyName == "keyboard_key_alphanumeric_7" || keyName == "7") return InputDeviceKeyboard::Key::Alphanumeric7;
        if (keyName == "keyboard_key_alphanumeric_8" || keyName == "8") return InputDeviceKeyboard::Key::Alphanumeric8;
        if (keyName == "keyboard_key_alphanumeric_9" || keyName == "9") return InputDeviceKeyboard::Key::Alphanumeric9;

        if (keyName == "keyboard_key_edit_space" || keyName == "Space") return InputDeviceKeyboard::Key::EditSpace;
        if (keyName == "keyboard_key_edit_enter" || keyName == "Enter") return InputDeviceKeyboard::Key::EditEnter;
        if (keyName == "keyboard_key_edit_backspace" || keyName == "Backspace") return InputDeviceKeyboard::Key::EditBackspace;
        if (keyName == "keyboard_key_edit_tab" || keyName == "Tab") return InputDeviceKeyboard::Key::EditTab;

        if (keyName == "keyboard_key_escape" || keyName == "Escape" || keyName == "Esc") return InputDeviceKeyboard::Key::Escape;

        if (keyName == "keyboard_key_modifier_shift_l" || keyName == "LeftShift" || keyName == "LShift") return InputDeviceKeyboard::Key::ModifierShiftL;
        if (keyName == "keyboard_key_modifier_shift_r" || keyName == "RightShift" || keyName == "RShift") return InputDeviceKeyboard::Key::ModifierShiftR;
        if (keyName == "keyboard_key_modifier_ctrl_l" || keyName == "LeftCtrl" || keyName == "LCtrl") return InputDeviceKeyboard::Key::ModifierCtrlL;
        if (keyName == "keyboard_key_modifier_ctrl_r" || keyName == "RightCtrl" || keyName == "RCtrl") return InputDeviceKeyboard::Key::ModifierCtrlR;
        if (keyName == "keyboard_key_modifier_alt_l" || keyName == "LeftAlt" || keyName == "LAlt") return InputDeviceKeyboard::Key::ModifierAltL;
        if (keyName == "keyboard_key_modifier_alt_r" || keyName == "RightAlt" || keyName == "RAlt") return InputDeviceKeyboard::Key::ModifierAltR;

        if (keyName == "keyboard_key_navigation_arrow_up" || keyName == "Up" || keyName == "ArrowUp") return InputDeviceKeyboard::Key::NavigationArrowUp;
        if (keyName == "keyboard_key_navigation_arrow_down" || keyName == "Down" || keyName == "ArrowDown") return InputDeviceKeyboard::Key::NavigationArrowDown;
        if (keyName == "keyboard_key_navigation_arrow_left" || keyName == "Left" || keyName == "ArrowLeft") return InputDeviceKeyboard::Key::NavigationArrowLeft;
        if (keyName == "keyboard_key_navigation_arrow_right" || keyName == "Right" || keyName == "ArrowRight") return InputDeviceKeyboard::Key::NavigationArrowRight;

        if (keyName == "keyboard_key_function_F1" || keyName == "F1") return InputDeviceKeyboard::Key::Function01;
        if (keyName == "keyboard_key_function_F2" || keyName == "F2") return InputDeviceKeyboard::Key::Function02;
        if (keyName == "keyboard_key_function_F3" || keyName == "F3") return InputDeviceKeyboard::Key::Function03;
        if (keyName == "keyboard_key_function_F4" || keyName == "F4") return InputDeviceKeyboard::Key::Function04;
        if (keyName == "keyboard_key_function_F5" || keyName == "F5") return InputDeviceKeyboard::Key::Function05;
        if (keyName == "keyboard_key_function_F6" || keyName == "F6") return InputDeviceKeyboard::Key::Function06;
        if (keyName == "keyboard_key_function_F7" || keyName == "F7") return InputDeviceKeyboard::Key::Function07;
        if (keyName == "keyboard_key_function_F8" || keyName == "F8") return InputDeviceKeyboard::Key::Function08;
        if (keyName == "keyboard_key_function_F9" || keyName == "F9") return InputDeviceKeyboard::Key::Function09;
        if (keyName == "keyboard_key_function_F10" || keyName == "F10") return InputDeviceKeyboard::Key::Function10;
        if (keyName == "keyboard_key_function_F11" || keyName == "F11") return InputDeviceKeyboard::Key::Function11;
        if (keyName == "keyboard_key_function_F12" || keyName == "F12") return InputDeviceKeyboard::Key::Function12;

        if (keyName == "mouse_button_left" || keyName == "MouseLeft" || keyName == "LMB") return InputDeviceMouse::Button::Left;
        if (keyName == "mouse_button_right" || keyName == "MouseRight" || keyName == "RMB") return InputDeviceMouse::Button::Right;
        if (keyName == "mouse_button_middle" || keyName == "MouseMiddle" || keyName == "MMB") return InputDeviceMouse::Button::Middle;

        if (keyName == "gamepad_button_a" || keyName == "GamepadA") return InputDeviceGamepad::Button::A;
        if (keyName == "gamepad_button_b" || keyName == "GamepadB") return InputDeviceGamepad::Button::B;
        if (keyName == "gamepad_button_x" || keyName == "GamepadX") return InputDeviceGamepad::Button::X;
        if (keyName == "gamepad_button_y" || keyName == "GamepadY") return InputDeviceGamepad::Button::Y;
        if (keyName == "gamepad_button_l1" || keyName == "GamepadL1" || keyName == "LB") return InputDeviceGamepad::Button::L1;
        if (keyName == "gamepad_button_r1" || keyName == "GamepadR1" || keyName == "RB") return InputDeviceGamepad::Button::R1;
        if (keyName == "gamepad_button_l3" || keyName == "GamepadL3" || keyName == "LS") return InputDeviceGamepad::Button::L3;
        if (keyName == "gamepad_button_r3" || keyName == "GamepadR3" || keyName == "RS") return InputDeviceGamepad::Button::R3;
        if (keyName == "gamepad_button_start" || keyName == "Start" || keyName == "GamepadStart") return InputDeviceGamepad::Button::Start;
        if (keyName == "gamepad_button_select" || keyName == "Select" || keyName == "Back" || keyName == "GamepadSelect") return InputDeviceGamepad::Button::Select;

        if (keyName == "gamepad_trigger_l2" || keyName == "GamepadL2" || keyName == "LT") return InputDeviceGamepad::Trigger::L2;
        if (keyName == "gamepad_trigger_r2" || keyName == "GamepadR2" || keyName == "RT") return InputDeviceGamepad::Trigger::R2;

        if (keyName == "gamepad_stick_l_x" || keyName == "LeftStickX") return InputDeviceGamepad::ThumbStickAxis1D::LX;
        if (keyName == "gamepad_stick_l_y" || keyName == "LeftStickY") return InputDeviceGamepad::ThumbStickAxis1D::LY;
        if (keyName == "gamepad_stick_r_x" || keyName == "RightStickX") return InputDeviceGamepad::ThumbStickAxis1D::RX;
        if (keyName == "gamepad_stick_r_y" || keyName == "RightStickY") return InputDeviceGamepad::ThumbStickAxis1D::RY;

        if (keyName == "gamepad_dpad_up" || keyName == "DPadUp" || keyName == "GamepadDU") return InputDeviceGamepad::Button::DU;
        if (keyName == "gamepad_dpad_down" || keyName == "DPadDown" || keyName == "GamepadDD") return InputDeviceGamepad::Button::DD;
        if (keyName == "gamepad_dpad_left" || keyName == "DPadLeft" || keyName == "GamepadDL") return InputDeviceGamepad::Button::DL;
        if (keyName == "gamepad_dpad_right" || keyName == "DPadRight" || keyName == "GamepadDR") return InputDeviceGamepad::Button::DR;

        if (keyName == "mouse_movement_x" || keyName == "MouseX" || keyName == "mouse_delta_x" || keyName == "MouseDeltaX") return InputDeviceMouse::Movement::X;
        if (keyName == "mouse_movement_y" || keyName == "MouseY" || keyName == "mouse_delta_y" || keyName == "MouseDeltaY") return InputDeviceMouse::Movement::Y;
        if (keyName == "mouse_movement_z" || keyName == "MouseZ" || keyName == "MouseWheel" || keyName == "mouse_delta_z") return InputDeviceMouse::Movement::Z;

        AZ_Warning("EnhancedInput", false, "Unknown key name: %s", keyName.c_str());
        return AzFramework::InputChannelId(keyName.c_str());
    }

    InputTriggerPtr EnhancedInputLuaHelper::CreateTriggerFromName(const AZStd::string& triggerType)
    {
        if (triggerType == "pressed" || triggerType == "Pressed")
        {
            return AZStd::make_shared<InputTriggerPressed>();
        }
        if (triggerType == "released" || triggerType == "Released")
        {
            return AZStd::make_shared<InputTriggerReleased>();
        }
        if (triggerType == "down" || triggerType == "Down")
        {
            return AZStd::make_shared<InputTriggerDown>();
        }
        if (triggerType == "hold" || triggerType == "Hold")
        {
            return AZStd::make_shared<InputTriggerHold>();
        }
        if (triggerType == "tap" || triggerType == "Tap")
        {
            return AZStd::make_shared<InputTriggerTap>();
        }
        if (triggerType == "pulse" || triggerType == "Pulse")
        {
            return AZStd::make_shared<InputTriggerPulse>();
        }
        
        // Parse pulse with interval: "pulse:0.5"
        if (triggerType.find("pulse:") == 0)
        {
            AZStd::string intervalStr = triggerType.substr(6); // Skip "pulse:"
            float interval = AZStd::stof(intervalStr);
            return AZStd::make_shared<InputTriggerPulse>(interval, true);
        }

        return AZStd::make_shared<InputTriggerPressed>();
    }

    void EnhancedInputLuaHelper::Reflect(AZ::ReflectContext* context)
    {
        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<EnhancedInputLuaHelper>("EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Method("CreateContext", &EnhancedInputLuaHelper::CreateContext)
                ->Method("RegisterAction", &EnhancedInputLuaHelper::RegisterAction)
                ->Method("UnregisterAction", &EnhancedInputLuaHelper::UnregisterAction)
                ->Method("AddContext", &EnhancedInputLuaHelper::AddContext)
                ->Method("RemoveContext", &EnhancedInputLuaHelper::RemoveContext)
                ->Method("ClearAllContexts", &EnhancedInputLuaHelper::ClearAllContexts)
                ->Method("GetActionValue", &EnhancedInputLuaHelper::GetActionValue)
                ->Method("IsActionTriggered", &EnhancedInputLuaHelper::IsActionTriggered);
        }
    }

} // namespace EnhancedInput
