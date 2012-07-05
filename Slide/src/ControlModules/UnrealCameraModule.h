#pragma once
#ifndef __UnrealCameraModule_H__
#define __UnrealCameraModule_H__

class UnrealCameraModule : public ControlModule
{
public:
	UnrealCameraModule();
	virtual ~UnrealCameraModule();

	virtual bool ShouldMouseCursorVisible() { return false; }

	virtual void ProcessActivation(ControlModule * Previous);
	virtual void ProcessDeactivation(ControlModule * Next);

protected:
	virtual void ModuleProcessSlider(InputManager::VirtualInputId SliderId, double MovedAmount);

private:
	UnrealCameraModule(const UnrealCameraModule &);
	UnrealCameraModule & operator =(const UnrealCameraModule &);
};

#endif // __UnrealCameraModule_H__
