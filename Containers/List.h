#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
	T** items;
	int ItemsCount;
	int MaxSize;

public:
	List(int _MaxSize): ItemsCount(0), MaxSize(_MaxSize)
	{
		items = new T * [MaxSize];

		for (int i = 0; i < MaxSize; i++)
			items[i] = NULL;
	}

	T* operator[](int index) const
	{
		if (index < ItemsCount && index >= 0)
			return items[index];

		return NULL;
	}

	int size() const
	{
		return ItemsCount;
	}

	void push_back(T* item, int index)
	{
		if (item && ItemsCount < MaxSize && items[index] == NULL) {
			items[index] = item;
			ItemsCount++;
		}
	}

	void push_back(T* item)
	{
		push_back(item, ItemsCount);
	}

	T* pop_back()
	{
		if (!empty()) {
			T* item = items[ItemsCount - 1];

			items[--ItemsCount] = NULL;

			return item;
		}

		return NULL;
	}

	T* remove(int index)
	{
		if (index < ItemsCount && index >= 0) {
			T* item = items[index];

			items[index] = NULL;

			int i = index;
			while (items[i + 1] != NULL && i < ItemsCount) {
				items[i] = items[i + 1];
				items[i + 1] = NULL;
				i++;
			}

			ItemsCount--;

			return item;
		}

		return NULL;
	}

	int remove(T* item)
	{
		if (item && !empty()) {
			int index = -1;

			int i = 0;
			while (index == -1 && i < ItemsCount) {
				if (items[i] == item)
					index = i;
				i++;
			}

			if (index != -1)
			{
				remove(index);
				return index;
			}

		}

		return -1;
	}

	bool empty() const
	{
		return ItemsCount == 0;
	}

	void clear()
	{
		for (int i = 0; i < ItemsCount; i++)
			items[i] = NULL;

		ItemsCount = 0;
	}

	~List()
	{
		clear();

		delete items;
	}
};

#endif