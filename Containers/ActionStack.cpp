#include "ActionStack.h"

ActionStack::ActionStack(int _MaxSize): ItemsCount(0), MaxSize(_MaxSize - 1)
{
	items = new Action* [MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = nullptr;
}

int ActionStack::size() const
{
	return ItemsCount;
}

void ActionStack::push(Action* item)
{
	if (ItemsCount >= MaxSize) {
		for (int i = 1; i < ItemsCount - 1; i++)
			items[i - 1] = items[i];

		items[ItemsCount - 1] = nullptr;
		ItemsCount--;
	}
	
	items[ItemsCount++] = item;
}

Action* ActionStack::pop()
{
	if (!empty()) {
		Action* item = items[ItemsCount - 1];
		items[--ItemsCount] = nullptr;

		return item;
	}

	return nullptr;
}

Action* ActionStack::top() const
{
	if (!empty())
		return items[ItemsCount - 1];

	return nullptr;
}

bool ActionStack::empty() const
{
	return ItemsCount == 0;
}

void ActionStack::clear()
{
	for (int i = 0; i < ItemsCount; i++)
		items[i] = nullptr;

	ItemsCount = 0;
}

ActionStack::~ActionStack()
{
	clear();

	delete items;
}