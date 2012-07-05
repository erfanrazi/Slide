#include "../Globals.h"

ControlModule::ControlModule(uint32 Buttons, uint32 Sliders, uint32 Axes)
	: InputListener(),
	  m_Buttons(Buttons),
	  m_Sliders(Sliders),
	  m_Axes(Axes),
	  m_ButtonsPressed(Buttons, false),							// Initialize the m_ButtonsPressed array to falses
	  m_AxisStates(Axes, InputManager::AxisState(0, 0))			// Initialize the m_AxisStates array to zeros
{
}

ControlModule::~ControlModule()
{
}

void ControlModule::VerifyMapping(uint32 Buttons, uint32 Sliders, uint32 Axes)
{
	if (m_Buttons != Buttons || m_Sliders != Sliders || m_Axes != Axes)
		throw 0;
}

// By default, a module should become active iff any of its buttons are pressed
bool ControlModule::ShouldActivate() const
{
	for (uint32 Button = 0; Button < m_Buttons; ++Button)
	{
		if (IsButtonPressed(Button))
		{
			return true;
		}
	}

	return false;
}

// By default, a module is should deactivate when it should no longer activate
bool ControlModule::ShouldDeactivate() const
{
	return !ShouldActivate();
}

bool ControlModule::IsButtonPressed(uint32 Button) const
{
	if (Button >= m_Buttons) {
		std::cerr << "Exception: ControlModule::IsButtonPressed() only accepts " << m_Buttons << " buttons, but got Button == " << Button << "." << std::endl;
		throw 0;
	}

	return m_ButtonsPressed[Button];
}

InputManager::AxisState ControlModule::GetAxisState(uint32 Axis) const
{
	if (Axis >= m_Axes) {
		std::cerr << "Exception: ControlModule::GetAxisPosition() only accepts " << m_Axes << " axes, but got Axis == " << Axis << "." << std::endl;
		throw 0;
	}

	return m_AxisStates[Axis];
}

void ControlModule::ProcessButton(InputManager::VirtualInputId ButtonId, bool Pressed)
{
	if (ButtonId >= m_Buttons) {
		std::cerr << "Exception: ControlModule only accepts " << m_Buttons << " buttons, but got Button == " << ButtonId << "." << std::endl;
		throw 0;
	}

	m_ButtonsPressed[ButtonId] = Pressed;			// This is updated first

	if (IsActiveExternally())
		ModuleProcessButton(ButtonId, Pressed);			// This is called second
}

void ControlModule::ProcessSlider(InputManager::VirtualInputId SliderId, double MovedAmount)
{
	if (SliderId >= m_Sliders) {
		std::cerr << "Exception: ControlModule only accepts " << m_Sliders << " sliders, but got Slider == " << SliderId << "." << std::endl;
		throw 0;
	}

	if (IsActiveExternally())
		ModuleProcessSlider(SliderId, MovedAmount);
}

void ControlModule::ProcessAxis(InputManager::VirtualInputId AxisId, InputManager::AxisState AxisState)
{
	if (AxisId >= m_Axes) {
		std::cerr << "Exception: ControlModule only accepts " << m_Axes << " axes, but got Axis == " << AxisId << "." << std::endl;
		throw 0;
	}

	m_AxisStates[AxisId] = AxisState;			// This is updated first

	if (IsActiveExternally())
		ModuleProcessAxis(AxisId, AxisState);			// This is called second
}

void ControlModule::Process2Axes(InputManager::VirtualInputId FirstAxisId, InputManager::AxisState AxisState[2])
{
	if (FirstAxisId + 1u >= m_Axes) {
		std::cerr << "Exception: ControlModule only accepts " << m_Axes << " axes, but got 2 axes with FirstAxis == " << FirstAxisId << "." << std::endl;
		throw 0;
	}

	m_AxisStates[FirstAxisId + 0] = AxisState[0];				// This is updated first
	m_AxisStates[FirstAxisId + 1] = AxisState[1];

	if (IsActiveExternally())
		ModuleProcess2Axes(FirstAxisId, AxisState);		// This is called second
}

void ControlModule::ProcessCharacter(int Character, bool Pressed)
{
	if (IsActiveExternally())
		ModuleProcessCharacter(Character, Pressed);
}

void ControlModule::ProcessTimePassed(double TimePassed)
{
	if (IsActiveExternally())
		ModuleProcessTimePassed(TimePassed);
}
