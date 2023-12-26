#include "UndoableActionStack.h"
#include "../Actions/UndoableFigureAction.h"

UndoableActionStack::UndoableActionStack(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
{
	items = new UndoableAction *[MaxSize]; // Create an array of pointers to the items of the stack

	for (int i = 0; i < MaxSize; i++) // Initialize all pointers to NULL
		items[i] = NULL;
}

int UndoableActionStack::Size() const
{
	return ItemsCount;
}

void UndoableActionStack::Push(UndoableAction *item)
{
	if (item)
	{
		if (ItemsCount >= MaxSize) // If the stack is full, remove the first item
		{
			items[0]->DecrementReference(); // Decrement the reference of the first item
			if (items[0]->CanBeDeleted())	// If the reference of the first item reaches 0, delete it
				delete items[0];
			items[0] = NULL;

			for (int i = 1; i < ItemsCount; i++) // Shift all items to the left
				items[i - 1] = items[i];

			ItemsCount--; // Decrement the number of items
		}

		items[ItemsCount++] = item; // Add the item to the end of the stack
		item->IncrementReference(); // Increment the reference of the item
	}
}

UndoableAction *UndoableActionStack::Pop()
{
	if (!Empty()) // If the stack is not empty, remove the last item
	{
		UndoableAction *item = items[ItemsCount - 1]; // Get the last item

		items[ItemsCount - 1] = NULL; // Remove the item from the stack
		item->DecrementReference();	  // Decrement the reference of the item

		ItemsCount--; // Decrement the number of items

		return item;
	}

	return NULL; // If the stack is empty, return NULL
}

UndoableAction *UndoableActionStack::Top() const
{
	if (!Empty())					  // If the stack is not empty, return the last item
		return items[ItemsCount - 1]; // Get the last item

	return NULL; // If the stack is empty, return NULL
}

bool UndoableActionStack::Empty() const
{
	return ItemsCount == 0; // Return true if the stack is empty
}

void UndoableActionStack::Clear()
{
	for (int i = 0; i < ItemsCount; i++) // Remove all items from the stack
		items[i] = NULL;

	ItemsCount = 0; // Reset the number of items
}

UndoableActionStack::~UndoableActionStack()
{
	Clear(); // Remove all items from the stack

	delete items; // Delete the array of pointers
}