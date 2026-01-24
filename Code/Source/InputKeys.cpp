#include <EnhancedInput/InputKeys.h>
#include <AzCore/RTTI/ReflectContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace EnhancedInput
{
    const AZStd::string InputKeys::A = "A";
    const AZStd::string InputKeys::B = "B";
    const AZStd::string InputKeys::C = "C";
    const AZStd::string InputKeys::D = "D";
    const AZStd::string InputKeys::E = "E";
    const AZStd::string InputKeys::F = "F";
    const AZStd::string InputKeys::G = "G";
    const AZStd::string InputKeys::H = "H";
    const AZStd::string InputKeys::I = "I";
    const AZStd::string InputKeys::J = "J";
    const AZStd::string InputKeys::K = "K";
    const AZStd::string InputKeys::L = "L";
    const AZStd::string InputKeys::M = "M";
    const AZStd::string InputKeys::N = "N";
    const AZStd::string InputKeys::O = "O";
    const AZStd::string InputKeys::P = "P";
    const AZStd::string InputKeys::Q = "Q";
    const AZStd::string InputKeys::R = "R";
    const AZStd::string InputKeys::S = "S";
    const AZStd::string InputKeys::T = "T";
    const AZStd::string InputKeys::U = "U";
    const AZStd::string InputKeys::V = "V";
    const AZStd::string InputKeys::W = "W";
    const AZStd::string InputKeys::X = "X";
    const AZStd::string InputKeys::Y = "Y";
    const AZStd::string InputKeys::Z = "Z";
    
    const AZStd::string InputKeys::_0 = "0";
    const AZStd::string InputKeys::_1 = "1";
    const AZStd::string InputKeys::_2 = "2";
    const AZStd::string InputKeys::_3 = "3";
    const AZStd::string InputKeys::_4 = "4";
    const AZStd::string InputKeys::_5 = "5";
    const AZStd::string InputKeys::_6 = "6";
    const AZStd::string InputKeys::_7 = "7";
    const AZStd::string InputKeys::_8 = "8";
    const AZStd::string InputKeys::_9 = "9";
    
    const AZStd::string InputKeys::Space = "Space";
    const AZStd::string InputKeys::Enter = "Enter";
    const AZStd::string InputKeys::Escape = "Escape";
    const AZStd::string InputKeys::Tab = "Tab";
    const AZStd::string InputKeys::Backspace = "Backspace";
    const AZStd::string InputKeys::LShift = "LShift";
    const AZStd::string InputKeys::RShift = "RShift";
    const AZStd::string InputKeys::LCtrl = "LCtrl";
    const AZStd::string InputKeys::RCtrl = "RCtrl";
    const AZStd::string InputKeys::LAlt = "LAlt";
    const AZStd::string InputKeys::RAlt = "RAlt";
    const AZStd::string InputKeys::Up = "Up";
    const AZStd::string InputKeys::Down = "Down";
    const AZStd::string InputKeys::Left = "Left";
    const AZStd::string InputKeys::Right = "Right";
    
    const AZStd::string InputKeys::F1 = "F1";
    const AZStd::string InputKeys::F2 = "F2";
    const AZStd::string InputKeys::F3 = "F3";
    const AZStd::string InputKeys::F4 = "F4";
    const AZStd::string InputKeys::F5 = "F5";
    const AZStd::string InputKeys::F6 = "F6";
    const AZStd::string InputKeys::F7 = "F7";
    const AZStd::string InputKeys::F8 = "F8";
    const AZStd::string InputKeys::F9 = "F9";
    const AZStd::string InputKeys::F10 = "F10";
    const AZStd::string InputKeys::F11 = "F11";
    const AZStd::string InputKeys::F12 = "F12";
    
    const AZStd::string InputKeys::MouseLeft = "Mouse_Left";
    const AZStd::string InputKeys::MouseRight = "Mouse_Right";
    const AZStd::string InputKeys::MouseMiddle = "Mouse_Middle";
    const AZStd::string InputKeys::MouseX = "Mouse_X";
    const AZStd::string InputKeys::MouseY = "Mouse_Y";
    const AZStd::string InputKeys::MouseWheel = "Mouse_Z";
    
    const AZStd::string InputKeys::GamepadA = "GamepadA";
    const AZStd::string InputKeys::GamepadB = "GamepadB";
    const AZStd::string InputKeys::GamepadX = "GamepadX";
    const AZStd::string InputKeys::GamepadY = "GamepadY";
    const AZStd::string InputKeys::GamepadL1 = "GamepadL1";
    const AZStd::string InputKeys::GamepadR1 = "GamepadR1";
    const AZStd::string InputKeys::GamepadL2 = "GamepadL2";
    const AZStd::string InputKeys::GamepadR2 = "GamepadR2";
    const AZStd::string InputKeys::GamepadL3 = "GamepadL3";
    const AZStd::string InputKeys::GamepadR3 = "GamepadR3";
    const AZStd::string InputKeys::GamepadStart = "GamepadStart";
    const AZStd::string InputKeys::GamepadSelect = "GamepadSelect";
    const AZStd::string InputKeys::GamepadDU = "GamepadDU";
    const AZStd::string InputKeys::GamepadDD = "GamepadDD";
    const AZStd::string InputKeys::GamepadDL = "GamepadDL";
    const AZStd::string InputKeys::GamepadDR = "GamepadDR";
    const AZStd::string InputKeys::LeftStickX = "LeftStickX";
    const AZStd::string InputKeys::LeftStickY = "LeftStickY";
    const AZStd::string InputKeys::RightStickX = "RightStickX";
    const AZStd::string InputKeys::RightStickY = "RightStickY";

    const AZStd::string InputTriggers::Pressed = "pressed";
    const AZStd::string InputTriggers::Down = "down";
    const AZStd::string InputTriggers::Released = "released";
    const AZStd::string InputTriggers::Hold = "hold";
    const AZStd::string InputTriggers::Tap = "tap";
    const AZStd::string InputTriggers::Pulse = "pulse";

    const AZStd::string InputModifiers::DeadZone = "deadzone";
    const AZStd::string InputModifiers::Scale = "scale";
    const AZStd::string InputModifiers::Negate = "negate";
    const AZStd::string InputModifiers::Invert = "invert";

    void InputKeys::Reflect(AZ::ReflectContext* context)
    {
        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<InputKeys>("KeyCode")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Constructor()
                ->Method("A", []() { return InputKeys::A; })
                ->Method("B", []() { return InputKeys::B; })
                ->Method("C", []() { return InputKeys::C; })
                ->Method("D", []() { return InputKeys::D; })
                ->Method("E", []() { return InputKeys::E; })
                ->Method("F", []() { return InputKeys::F; })
                ->Method("G", []() { return InputKeys::G; })
                ->Method("H", []() { return InputKeys::H; })
                ->Method("I", []() { return InputKeys::I; })
                ->Method("J", []() { return InputKeys::J; })
                ->Method("K", []() { return InputKeys::K; })
                ->Method("L", []() { return InputKeys::L; })
                ->Method("M", []() { return InputKeys::M; })
                ->Method("N", []() { return InputKeys::N; })
                ->Method("O", []() { return InputKeys::O; })
                ->Method("P", []() { return InputKeys::P; })
                ->Method("Q", []() { return InputKeys::Q; })
                ->Method("R", []() { return InputKeys::R; })
                ->Method("S", []() { return InputKeys::S; })
                ->Method("T", []() { return InputKeys::T; })
                ->Method("U", []() { return InputKeys::U; })
                ->Method("V", []() { return InputKeys::V; })
                ->Method("W", []() { return InputKeys::W; })
                ->Method("X", []() { return InputKeys::X; })
                ->Method("Y", []() { return InputKeys::Y; })
                ->Method("Z", []() { return InputKeys::Z; })
                ->Method("Num0", []() { return InputKeys::_0; })
                ->Method("Num1", []() { return InputKeys::_1; })
                ->Method("Num2", []() { return InputKeys::_2; })
                ->Method("Num3", []() { return InputKeys::_3; })
                ->Method("Num4", []() { return InputKeys::_4; })
                ->Method("Num5", []() { return InputKeys::_5; })
                ->Method("Num6", []() { return InputKeys::_6; })
                ->Method("Num7", []() { return InputKeys::_7; })
                ->Method("Num8", []() { return InputKeys::_8; })
                ->Method("Num9", []() { return InputKeys::_9; })
                ->Method("Space", []() { return InputKeys::Space; })
                ->Method("Enter", []() { return InputKeys::Enter; })
                ->Method("Escape", []() { return InputKeys::Escape; })
                ->Method("Tab", []() { return InputKeys::Tab; })
                ->Method("Backspace", []() { return InputKeys::Backspace; })
                ->Method("LShift", []() { return InputKeys::LShift; })
                ->Method("RShift", []() { return InputKeys::RShift; })
                ->Method("LCtrl", []() { return InputKeys::LCtrl; })
                ->Method("RCtrl", []() { return InputKeys::RCtrl; })
                ->Method("LAlt", []() { return InputKeys::LAlt; })
                ->Method("RAlt", []() { return InputKeys::RAlt; })
                ->Method("Up", []() { return InputKeys::Up; })
                ->Method("Down", []() { return InputKeys::Down; })
                ->Method("Left", []() { return InputKeys::Left; })
                ->Method("Right", []() { return InputKeys::Right; })
                ->Method("F1", []() { return InputKeys::F1; })
                ->Method("F2", []() { return InputKeys::F2; })
                ->Method("F3", []() { return InputKeys::F3; })
                ->Method("F4", []() { return InputKeys::F4; })
                ->Method("F5", []() { return InputKeys::F5; })
                ->Method("F6", []() { return InputKeys::F6; })
                ->Method("F7", []() { return InputKeys::F7; })
                ->Method("F8", []() { return InputKeys::F8; })
                ->Method("F9", []() { return InputKeys::F9; })
                ->Method("F10", []() { return InputKeys::F10; })
                ->Method("F11", []() { return InputKeys::F11; })
                ->Method("F12", []() { return InputKeys::F12; })
                ->Method("MouseLeft", []() { return InputKeys::MouseLeft; })
                ->Method("MouseRight", []() { return InputKeys::MouseRight; })
                ->Method("MouseMiddle", []() { return InputKeys::MouseMiddle; })
                ->Method("MouseX", []() { return InputKeys::MouseX; })
                ->Method("MouseY", []() { return InputKeys::MouseY; })
                ->Method("MouseWheel", []() { return InputKeys::MouseWheel; })
                ->Method("GamepadA", []() { return InputKeys::GamepadA; })
                ->Method("GamepadB", []() { return InputKeys::GamepadB; })
                ->Method("GamepadX", []() { return InputKeys::GamepadX; })
                ->Method("GamepadY", []() { return InputKeys::GamepadY; })
                ->Method("GamepadL1", []() { return InputKeys::GamepadL1; })
                ->Method("GamepadR1", []() { return InputKeys::GamepadR1; })
                ->Method("GamepadL2", []() { return InputKeys::GamepadL2; })
                ->Method("GamepadR2", []() { return InputKeys::GamepadR2; })
                ->Method("GamepadL3", []() { return InputKeys::GamepadL3; })
                ->Method("GamepadR3", []() { return InputKeys::GamepadR3; })
                ->Method("GamepadStart", []() { return InputKeys::GamepadStart; })
                ->Method("GamepadSelect", []() { return InputKeys::GamepadSelect; })
                ->Method("GamepadDU", []() { return InputKeys::GamepadDU; })
                ->Method("GamepadDD", []() { return InputKeys::GamepadDD; })
                ->Method("GamepadDL", []() { return InputKeys::GamepadDL; })
                ->Method("GamepadDR", []() { return InputKeys::GamepadDR; })
                ->Method("LeftStickX", []() { return InputKeys::LeftStickX; })
                ->Method("LeftStickY", []() { return InputKeys::LeftStickY; })
                ->Method("RightStickX", []() { return InputKeys::RightStickX; })
                ->Method("RightStickY", []() { return InputKeys::RightStickY; });
        }
    }

    void InputTriggers::Reflect(AZ::ReflectContext* context)
    {
        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<InputTriggers>("TriggerType")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Constructor()
                ->Method("Pressed", []() { return InputTriggers::Pressed; })
                ->Method("Down", []() { return InputTriggers::Down; })
                ->Method("Released", []() { return InputTriggers::Released; })
                ->Method("Hold", []() { return InputTriggers::Hold; })
                ->Method("Tap", []() { return InputTriggers::Tap; })
                ->Method("Pulse", []() { return InputTriggers::Pulse; });
        }
    }

    void InputModifiers::Reflect(AZ::ReflectContext* context)
    {
        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<InputModifiers>("ModifierType")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Constructor()
                ->Method("DeadZone", []() { return InputModifiers::DeadZone; })
                ->Method("Scale", []() { return InputModifiers::Scale; })
                ->Method("Negate", []() { return InputModifiers::Negate; })
                ->Method("Invert", []() { return InputModifiers::Invert; });
        }
    }
}
