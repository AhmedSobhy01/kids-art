#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
	T **items;		// Array of pointers to the items of the list (each item is a pointer to an object of type T)
	int ItemsCount; // Number of items in the list (number of pointers in the array)
	int MaxSize;	// Maximum number of items in the list (maximum number of pointers in the array)

public:
	List(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize) // Constructor
	{
		items = new T *[MaxSize]; // Create an array of pointers to the items of the list

		for (int i = 0; i < MaxSize; i++) // Initialize all pointers to NULL
			items[i] = NULL;
	}

	T *operator[](int index) const // Overloading the [] operator to access the list items using the [] operator (if the index is out of range, NULL will be returned)
	{
		if (index < ItemsCount && index >= 0) // If the index is in range, return the item at this index
			return items[index];

		return NULL; // If the index is out of range, return NULL
	}

	int Size() const // Get the number of items in the list (number of pointers in the array)
	{
		return ItemsCount;
	}

	void PushBack(T *item, int index) // Add an item to the list at a specific index (if the index is out of range or the list is full, nothing will happen)
	{
		if (item && ItemsCount < MaxSize && index >= 0 && index <= ItemsCount && index < MaxSize) // If the item is not NULL and the list is not full and the index is in range, add the item to the list
		{
			if (index == MaxSize - 1 && items[index] != NULL) // If the list is full, return
				return;

			for (int i = ItemsCount; i > index; --i) // Shift all items to the right
				items[i] = items[i - 1];

			items[index] = item;		// Add the item to the list
			item->IncrementReference(); // Increment the reference of the item

			ItemsCount++; // Increment the number of items
		}
	}

	void PushBack(T *item) // Add an item to the end of the list
	{
		PushBack(item, ItemsCount);
	}

	T *PopBack() // Remove the last item in the list and return it (if the list is empty, NULL will be returned)
	{
		if (!Empty()) // If the list is not empty, remove the last item
			return Remove(ItemsCount - 1);

		return NULL; // If the list is empty, return NULL
	}

	T *Remove(int index) // Remove an item from the list at a specific index and return it (if the index is out of range, NULL will be returned)
	{
		if (index < ItemsCount && index >= 0)
		{
			T *item = items[index]; // Get the item at the index

			items[index] = NULL;		// Remove the item from the list
			item->DecrementReference(); // Decrement the reference of the item

			int i = index;
			while (i < ItemsCount - 1 && items[i + 1] != NULL) // Shift all items to the left
			{
				items[i] = items[i + 1];
				items[i + 1] = NULL;
				i++;
			}

			ItemsCount--; // Decrement the number of items

			return item; // Return the item
		}

		return NULL;
	}

	int Remove(T *item) // Remove an item from the list and return its index (if the item is not found, -1 will be returned)
	{
		if (item && !Empty()) // If the item is not NULL and the list is not empty, search for the item
		{
			int index = -1;

			int i = 0;
			while (index == -1 && i < ItemsCount) // Search for the item
			{
				if (items[i] == item) // If the item is found, save its index
					index = i;
				i++;
			}

			if (index != -1) // If the item is found, remove it and return its index
			{
				Remove(index);
				return index;
			}
		}

		return -1; // If the item is not found, return -1
	}

	bool Empty() const // Check if the list is empty or not (if the list is empty, true will be returned)
	{
		return ItemsCount == 0; // Return true if the list is empty
	}

	void Clear() // Clear the list (remove all items from the list)
	{
		for (int i = 0; i < ItemsCount; i++) // Remove all items from the list
			items[i] = NULL;

		ItemsCount = 0; // Reset the number of items
	}

	~List()
	{
		Clear(); // Clear the list before deleting it

		delete items; // Delete the array of pointers to the items
	}
};

#endif
