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

    void EnhancedInputLuaHelper::BindKey(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName)
    {
        BindKeyWithTrigger(context, actionName, keyName, "pressed");
    }

    void EnhancedInputLuaHelper::BindKeyWithTrigger(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZStd::string& triggerType)
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

    void EnhancedInputLuaHelper::Bind(InputMappingContextPtr context, const AZStd::string& actionName, int keyCode, int triggerType)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "Bind: context is null");
            return;
        }

        InputActionBinding binding;
        binding.m_actionName = actionName;
        binding.m_inputChannelId = GetInputChannelIdFromCode(keyCode);

        auto trigger = CreateTriggerFromCode(triggerType);
        if (trigger)
        {
            binding.m_triggers.push_back(trigger);
        }

        context->AddBinding(binding);
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

    void EnhancedInputLuaHelper::AddModifierScale(InputMappingContextPtr context, const AZStd::string& actionName, float scaleX, float scaleY, float scaleZ)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierScale: context is null");
            return;
        }

        auto modifier = AZStd::make_shared<InputModifierScale>(AZ::Vector3(scaleX, scaleY, scaleZ));

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    void EnhancedInputLuaHelper::AddModifierSwizzle(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& order)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierSwizzle: context is null");
            return;
        }

        InputModifierSwizzle::SwizzleOrder swizzleOrder = InputModifierSwizzle::SwizzleOrder::XYZ;
        if (order == "XZY" || order == "xzy") swizzleOrder = InputModifierSwizzle::SwizzleOrder::XZY;
        else if (order == "YXZ" || order == "yxz") swizzleOrder = InputModifierSwizzle::SwizzleOrder::YXZ;
        else if (order == "YZX" || order == "yzx") swizzleOrder = InputModifierSwizzle::SwizzleOrder::YZX;
        else if (order == "ZXY" || order == "zxy") swizzleOrder = InputModifierSwizzle::SwizzleOrder::ZXY;
        else if (order == "ZYX" || order == "zyx") swizzleOrder = InputModifierSwizzle::SwizzleOrder::ZYX;

        auto modifier = AZStd::make_shared<InputModifierSwizzle>(swizzleOrder);

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    void EnhancedInputLuaHelper::AddModifierClamp(InputMappingContextPtr context, const AZStd::string& actionName, float minValue, float maxValue)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierClamp: context is null");
            return;
        }

        auto modifier = AZStd::make_shared<InputModifierClamp>(minValue, maxValue);

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    void EnhancedInputLuaHelper::AddModifierNormalize(InputMappingContextPtr context, const AZStd::string& actionName)
    {
        if (!context)
        {
            AZ_Warning("EnhancedInput", false, "AddModifierNormalize: context is null");
            return;
        }

        auto modifier = AZStd::make_shared<InputModifierNormalize>();

        for (auto& binding : context->GetBindings())
        {
            if (binding.m_actionName == actionName)
            {
                binding.m_modifiers.push_back(modifier);
            }
        }
    }

    AzFramework::InputChannelId EnhancedInputLuaHelper::GetInputChannelIdFromName(const AZStd::string& keyName)
    {
        using namespace AzFramework;

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
        if (keyName == "gamepad_button_start" || keyName == "Start") return InputDeviceGamepad::Button::Start;
        if (keyName == "gamepad_button_select" || keyName == "Select" || keyName == "Back") return InputDeviceGamepad::Button::Select;

        if (keyName == "gamepad_trigger_l2" || keyName == "GamepadL2" || keyName == "LT") return InputDeviceGamepad::Trigger::L2;
        if (keyName == "gamepad_trigger_r2" || keyName == "GamepadR2" || keyName == "RT") return InputDeviceGamepad::Trigger::R2;

        if (keyName == "gamepad_stick_l_x" || keyName == "LeftStickX") return InputDeviceGamepad::ThumbStickAxis1D::LX;
        if (keyName == "gamepad_stick_l_y" || keyName == "LeftStickY") return InputDeviceGamepad::ThumbStickAxis1D::LY;
        if (keyName == "gamepad_stick_r_x" || keyName == "RightStickX") return InputDeviceGamepad::ThumbStickAxis1D::RX;
        if (keyName == "gamepad_stick_r_y" || keyName == "RightStickY") return InputDeviceGamepad::ThumbStickAxis1D::RY;

        if (keyName == "gamepad_dpad_up" || keyName == "DPadUp") return InputDeviceGamepad::Button::DU;
        if (keyName == "gamepad_dpad_down" || keyName == "DPadDown") return InputDeviceGamepad::Button::DD;
        if (keyName == "gamepad_dpad_left" || keyName == "DPadLeft") return InputDeviceGamepad::Button::DL;
        if (keyName == "gamepad_dpad_right" || keyName == "DPadRight") return InputDeviceGamepad::Button::DR;

        if (keyName == "mouse_movement_x" || keyName == "MouseX" || keyName == "mouse_delta_x" || keyName == "MouseDeltaX") return InputDeviceMouse::Movement::X;
        if (keyName == "mouse_movement_y" || keyName == "MouseY" || keyName == "mouse_delta_y" || keyName == "MouseDeltaY") return InputDeviceMouse::Movement::Y;
        if (keyName == "mouse_movement_z" || keyName == "MouseZ" || keyName == "MouseWheel" || keyName == "mouse_delta_z") return InputDeviceMouse::Movement::Z;

        AZ_Warning("EnhancedInput", false, "Unknown key name: %s", keyName.c_str());
        return AzFramework::InputChannelId(keyName.c_str());
    }

    AzFramework::InputChannelId EnhancedInputLuaHelper::GetInputChannelIdFromCode(int keyCode)
    {
        using namespace AzFramework;

        switch (keyCode)
        {
        case 0: return InputDeviceKeyboard::Key::AlphanumericA;
        case 1: return InputDeviceKeyboard::Key::AlphanumericB;
        case 2: return InputDeviceKeyboard::Key::AlphanumericC;
        case 3: return InputDeviceKeyboard::Key::AlphanumericD;
        case 4: return InputDeviceKeyboard::Key::AlphanumericE;
        case 5: return InputDeviceKeyboard::Key::AlphanumericF;
        case 6: return InputDeviceKeyboard::Key::AlphanumericG;
        case 7: return InputDeviceKeyboard::Key::AlphanumericH;
        case 8: return InputDeviceKeyboard::Key::AlphanumericI;
        case 9: return InputDeviceKeyboard::Key::AlphanumericJ;
        case 10: return InputDeviceKeyboard::Key::AlphanumericK;
        case 11: return InputDeviceKeyboard::Key::AlphanumericL;
        case 12: return InputDeviceKeyboard::Key::AlphanumericM;
        case 13: return InputDeviceKeyboard::Key::AlphanumericN;
        case 14: return InputDeviceKeyboard::Key::AlphanumericO;
        case 15: return InputDeviceKeyboard::Key::AlphanumericP;
        case 16: return InputDeviceKeyboard::Key::AlphanumericQ;
        case 17: return InputDeviceKeyboard::Key::AlphanumericR;
        case 18: return InputDeviceKeyboard::Key::AlphanumericS;
        case 19: return InputDeviceKeyboard::Key::AlphanumericT;
        case 20: return InputDeviceKeyboard::Key::AlphanumericU;
        case 21: return InputDeviceKeyboard::Key::AlphanumericV;
        case 22: return InputDeviceKeyboard::Key::AlphanumericW;
        case 23: return InputDeviceKeyboard::Key::AlphanumericX;
        case 24: return InputDeviceKeyboard::Key::AlphanumericY;
        case 25: return InputDeviceKeyboard::Key::AlphanumericZ;
        case 26: return InputDeviceKeyboard::Key::Alphanumeric0;
        case 27: return InputDeviceKeyboard::Key::Alphanumeric1;
        case 28: return InputDeviceKeyboard::Key::Alphanumeric2;
        case 29: return InputDeviceKeyboard::Key::Alphanumeric3;
        case 30: return InputDeviceKeyboard::Key::Alphanumeric4;
        case 31: return InputDeviceKeyboard::Key::Alphanumeric5;
        case 32: return InputDeviceKeyboard::Key::Alphanumeric6;
        case 33: return InputDeviceKeyboard::Key::Alphanumeric7;
        case 34: return InputDeviceKeyboard::Key::Alphanumeric8;
        case 35: return InputDeviceKeyboard::Key::Alphanumeric9;
        case 36: return InputDeviceKeyboard::Key::EditSpace;
        case 37: return InputDeviceKeyboard::Key::EditEnter;
        case 38: return InputDeviceKeyboard::Key::Escape;
        case 39: return InputDeviceKeyboard::Key::EditTab;
        case 40: return InputDeviceKeyboard::Key::EditBackspace;
        case 41: return InputDeviceKeyboard::Key::ModifierShiftL;
        case 42: return InputDeviceKeyboard::Key::ModifierShiftR;
        case 43: return InputDeviceKeyboard::Key::ModifierCtrlL;
        case 44: return InputDeviceKeyboard::Key::ModifierCtrlR;
        case 45: return InputDeviceKeyboard::Key::ModifierAltL;
        case 46: return InputDeviceKeyboard::Key::ModifierAltR;
        case 47: return InputDeviceKeyboard::Key::NavigationArrowUp;
        case 48: return InputDeviceKeyboard::Key::NavigationArrowDown;
        case 49: return InputDeviceKeyboard::Key::NavigationArrowLeft;
        case 50: return InputDeviceKeyboard::Key::NavigationArrowRight;
        case 51: return InputDeviceKeyboard::Key::Function01;
        case 52: return InputDeviceKeyboard::Key::Function02;
        case 53: return InputDeviceKeyboard::Key::Function03;
        case 54: return InputDeviceKeyboard::Key::Function04;
        case 55: return InputDeviceKeyboard::Key::Function05;
        case 56: return InputDeviceKeyboard::Key::Function06;
        case 57: return InputDeviceKeyboard::Key::Function07;
        case 58: return InputDeviceKeyboard::Key::Function08;
        case 59: return InputDeviceKeyboard::Key::Function09;
        case 60: return InputDeviceKeyboard::Key::Function10;
        case 61: return InputDeviceKeyboard::Key::Function11;
        case 62: return InputDeviceKeyboard::Key::Function12;
        case 100: return InputDeviceMouse::Button::Left;
        case 101: return InputDeviceMouse::Button::Right;
        case 102: return InputDeviceMouse::Button::Middle;
        case 103: return InputDeviceMouse::Movement::X;
        case 104: return InputDeviceMouse::Movement::Y;
        case 105: return InputDeviceMouse::Movement::Z;
        case 200: return InputDeviceGamepad::Button::A;
        case 201: return InputDeviceGamepad::Button::B;
        case 202: return InputDeviceGamepad::Button::X;
        case 203: return InputDeviceGamepad::Button::Y;
        case 204: return InputDeviceGamepad::Button::L1;
        case 205: return InputDeviceGamepad::Button::R1;
        case 206: return InputDeviceGamepad::Trigger::L2;
        case 207: return InputDeviceGamepad::Trigger::R2;
        case 208: return InputDeviceGamepad::Button::L3;
        case 209: return InputDeviceGamepad::Button::R3;
        case 210: return InputDeviceGamepad::Button::Start;
        case 211: return InputDeviceGamepad::Button::Select;
        case 212: return InputDeviceGamepad::Button::DU;
        case 213: return InputDeviceGamepad::Button::DD;
        case 214: return InputDeviceGamepad::Button::DL;
        case 215: return InputDeviceGamepad::Button::DR;
        case 216: return InputDeviceGamepad::ThumbStickAxis1D::LX;
        case 217: return InputDeviceGamepad::ThumbStickAxis1D::LY;
        case 218: return InputDeviceGamepad::ThumbStickAxis1D::RX;
        case 219: return InputDeviceGamepad::ThumbStickAxis1D::RY;
        default:
            AZ_Warning("EnhancedInput", false, "Unknown key code: %d", keyCode);
            return InputDeviceKeyboard::Key::AlphanumericA;
        }
    }

    InputTriggerPtr EnhancedInputLuaHelper::CreateTriggerFromCode(int triggerType)
    {
        switch (triggerType)
        {
        case 0: return AZStd::make_shared<InputTriggerPressed>();
        case 1: return AZStd::make_shared<InputTriggerReleased>();
        case 2: return AZStd::make_shared<InputTriggerDown>();
        case 3: return AZStd::make_shared<InputTriggerHold>();
        case 4: return AZStd::make_shared<InputTriggerTap>();
        case 5: return AZStd::make_shared<InputTriggerPulse>();
        default: return AZStd::make_shared<InputTriggerPressed>();
        }
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
                ->Method("BindKey", &EnhancedInputLuaHelper::BindKey)
                ->Method("BindKeyWithTrigger", &EnhancedInputLuaHelper::BindKeyWithTrigger)
                ->Method("AddContext", &EnhancedInputLuaHelper::AddContext)
                ->Method("RemoveContext", &EnhancedInputLuaHelper::RemoveContext)
                ->Method("ClearAllContexts", &EnhancedInputLuaHelper::ClearAllContexts)
                ->Method("GetActionValue", &EnhancedInputLuaHelper::GetActionValue)
                ->Method("IsActionTriggered", &EnhancedInputLuaHelper::IsActionTriggered);
        }
    }

} // namespace EnhancedInput
