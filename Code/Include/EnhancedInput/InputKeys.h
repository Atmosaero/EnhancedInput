#pragma once

#include <AzCore/std/string/string.h>
#include <AzCore/RTTI/ReflectContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace EnhancedInput
{
    class InputKeys
    {
    public:
        AZ_TYPE_INFO(InputKeys, "{87654321-4321-4321-4321-210987654321}");
        static const AZStd::string A;
        static const AZStd::string B;
        static const AZStd::string C;
        static const AZStd::string D;
        static const AZStd::string E;
        static const AZStd::string F;
        static const AZStd::string G;
        static const AZStd::string H;
        static const AZStd::string I;
        static const AZStd::string J;
        static const AZStd::string K;
        static const AZStd::string L;
        static const AZStd::string M;
        static const AZStd::string N;
        static const AZStd::string O;
        static const AZStd::string P;
        static const AZStd::string Q;
        static const AZStd::string R;
        static const AZStd::string S;
        static const AZStd::string T;
        static const AZStd::string U;
        static const AZStd::string V;
        static const AZStd::string W;
        static const AZStd::string X;
        static const AZStd::string Y;
        static const AZStd::string Z;
        
        static const AZStd::string _0;
        static const AZStd::string _1;
        static const AZStd::string _2;
        static const AZStd::string _3;
        static const AZStd::string _4;
        static const AZStd::string _5;
        static const AZStd::string _6;
        static const AZStd::string _7;
        static const AZStd::string _8;
        static const AZStd::string _9;
        
        static const AZStd::string Space;
        static const AZStd::string Enter;
        static const AZStd::string Escape;
        static const AZStd::string Tab;
        static const AZStd::string Backspace;
        static const AZStd::string LShift;
        static const AZStd::string RShift;
        static const AZStd::string LCtrl;
        static const AZStd::string RCtrl;
        static const AZStd::string LAlt;
        static const AZStd::string RAlt;
        static const AZStd::string Up;
        static const AZStd::string Down;
        static const AZStd::string Left;
        static const AZStd::string Right;
        
        static const AZStd::string F1;
        static const AZStd::string F2;
        static const AZStd::string F3;
        static const AZStd::string F4;
        static const AZStd::string F5;
        static const AZStd::string F6;
        static const AZStd::string F7;
        static const AZStd::string F8;
        static const AZStd::string F9;
        static const AZStd::string F10;
        static const AZStd::string F11;
        static const AZStd::string F12;
        
        static const AZStd::string MouseLeft;
        static const AZStd::string MouseRight;
        static const AZStd::string MouseMiddle;
        static const AZStd::string MouseX;
        static const AZStd::string MouseY;
        static const AZStd::string MouseWheel;
        
        static const AZStd::string GamepadA;
        static const AZStd::string GamepadB;
        static const AZStd::string GamepadX;
        static const AZStd::string GamepadY;
        static const AZStd::string GamepadL1;
        static const AZStd::string GamepadR1;
        static const AZStd::string GamepadL2;
        static const AZStd::string GamepadR2;
        static const AZStd::string GamepadL3;
        static const AZStd::string GamepadR3;
        static const AZStd::string GamepadStart;
        static const AZStd::string GamepadSelect;
        static const AZStd::string GamepadDU;
        static const AZStd::string GamepadDD;
        static const AZStd::string GamepadDL;
        static const AZStd::string GamepadDR;
        static const AZStd::string LeftStickX;
        static const AZStd::string LeftStickY;
        static const AZStd::string RightStickX;
        static const AZStd::string RightStickY;

        static void Reflect(AZ::ReflectContext* context);
    };

    class InputTriggers
    {
    public:
        AZ_TYPE_INFO(InputTriggers, "{12345678-4321-4321-4321-123456789012}");
        static const AZStd::string Pressed;
        static const AZStd::string Down;
        static const AZStd::string Released;
        static const AZStd::string Hold;
        static const AZStd::string Tap;
        static const AZStd::string Pulse;

        static void Reflect(AZ::ReflectContext* context);
        
        static AZStd::string PulseWithInterval(float interval);
    };

    class InputModifiers
    {
    public:
        AZ_TYPE_INFO(InputModifiers, "{98765432-4321-4321-4321-123456789012}");
        static const AZStd::string DeadZone;
        static const AZStd::string Scale;
        static const AZStd::string Negate;
        static const AZStd::string Invert;

        static void Reflect(AZ::ReflectContext* context);
    };
}
