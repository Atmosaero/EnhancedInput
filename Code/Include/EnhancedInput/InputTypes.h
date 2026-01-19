/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/RTTI/RTTI.h>
#include <AzCore/RTTI/ReflectContext.h>

namespace EnhancedInput
{
    enum class TriggerType : AZ::u8
    {
        Pressed = 0,
        Released = 1,
        Down = 2,
        Hold = 3,
        Tap = 4,
        Pulse = 5
    };

    enum class InputKey : AZ::u16
    {
        Key_A = 0,
        Key_B = 1,
        Key_C = 2,
        Key_D = 3,
        Key_E = 4,
        Key_F = 5,
        Key_G = 6,
        Key_H = 7,
        Key_I = 8,
        Key_J = 9,
        Key_K = 10,
        Key_L = 11,
        Key_M = 12,
        Key_N = 13,
        Key_O = 14,
        Key_P = 15,
        Key_Q = 16,
        Key_R = 17,
        Key_S = 18,
        Key_T = 19,
        Key_U = 20,
        Key_V = 21,
        Key_W = 22,
        Key_X = 23,
        Key_Y = 24,
        Key_Z = 25,

        Key_0 = 26,
        Key_1 = 27,
        Key_2 = 28,
        Key_3 = 29,
        Key_4 = 30,
        Key_5 = 31,
        Key_6 = 32,
        Key_7 = 33,
        Key_8 = 34,
        Key_9 = 35,

        Key_Space = 36,
        Key_Enter = 37,
        Key_Escape = 38,
        Key_Tab = 39,
        Key_Backspace = 40,

        Key_LShift = 41,
        Key_RShift = 42,
        Key_LCtrl = 43,
        Key_RCtrl = 44,
        Key_LAlt = 45,
        Key_RAlt = 46,

        Key_Up = 47,
        Key_Down = 48,
        Key_Left = 49,
        Key_Right = 50,

        Key_F1 = 51,
        Key_F2 = 52,
        Key_F3 = 53,
        Key_F4 = 54,
        Key_F5 = 55,
        Key_F6 = 56,
        Key_F7 = 57,
        Key_F8 = 58,
        Key_F9 = 59,
        Key_F10 = 60,
        Key_F11 = 61,
        Key_F12 = 62,

        Mouse_Left = 100,
        Mouse_Right = 101,
        Mouse_Middle = 102,
        Mouse_X = 103,
        Mouse_Y = 104,
        Mouse_Wheel = 105,

        Gamepad_A = 200,
        Gamepad_B = 201,
        Gamepad_X = 202,
        Gamepad_Y = 203,
        Gamepad_LB = 204,
        Gamepad_RB = 205,
        Gamepad_LT = 206,
        Gamepad_RT = 207,
        Gamepad_LS = 208,
        Gamepad_RS = 209,
        Gamepad_Start = 210,
        Gamepad_Select = 211,
        Gamepad_DPadUp = 212,
        Gamepad_DPadDown = 213,
        Gamepad_DPadLeft = 214,
        Gamepad_DPadRight = 215,
        Gamepad_LeftStickX = 216,
        Gamepad_LeftStickY = 217,
        Gamepad_RightStickX = 218,
        Gamepad_RightStickY = 219
    };

    void ReflectInputTypes(AZ::ReflectContext* context);

} // namespace EnhancedInput
