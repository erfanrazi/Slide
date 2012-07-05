#pragma once
#ifndef __PlayerInputListener_H__
#define __PlayerInputListener_H__

class SystemInputListener
	: public InputListener
{
public:
	SystemInputListener();
	virtual ~SystemInputListener();

	void ProcessButton(InputManager::InputId ButtonId, bool Pressed);

private:
	SystemInputListener(const SystemInputListener &);
	SystemInputListener & operator =(const SystemInputListener &);
};

#endif // __PlayerInputListener_H__
