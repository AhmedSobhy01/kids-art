#ifndef RECORDED_ACTION_LIST_H
#define RECORDED_ACTION_LIST_H

template  <class T>
class List
{
	T** items;
	int ItemsCount;
	int MaxSize;

public:
	List(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
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
		if (item && ItemsCount < MaxSize && index >= 0 && index <= ItemsCount && index < MaxSize)
		{
			if (index == MaxSize - 1 && items[index] != NULL) return;

			for (int i = ItemsCount; i > index; --i)
				items[i] = items[i - 1];

			items[index] = item;
			item->IncrementReference();

			ItemsCount++;
		}
	}

	void push_back(T* item)
	{
		push_back(item, ItemsCount);
	}

	T* pop_back()
	{
		if (!empty())
			return remove(ItemsCount - 1);

		return NULL;
	}

	T* remove(int index)
	{
		if (index < ItemsCount && index >= 0)
		{
			T* item = items[index];

			items[index] = NULL;
			item->DecrementReference();

			int i = index;
			while (i < ItemsCount - 1 && items[i + 1] != NULL)
			{
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
		if (item && !empty())
		{
			int index = -1;

			int i = 0;
			while (index == -1 && i < ItemsCount)
			{
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
