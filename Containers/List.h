#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
	T **items;
	int ItemsCount;
	int MaxSize;

public:
	List(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
	{
		items = new T *[MaxSize];

		for (int i = 0; i < MaxSize; i++)
			items[i] = NULL;
	}

	T *operator[](int index) const
	{
		if (index < ItemsCount && index >= 0)
			return items[index];

		return NULL;
	}

	int Size() const
	{
		return ItemsCount;
	}

	void PushBack(T *item, int index)
	{
		if (item && ItemsCount < MaxSize && index >= 0 && index <= ItemsCount && index < MaxSize)
		{
			if (index == MaxSize - 1 && items[index] != NULL)
				return;

			for (int i = ItemsCount; i > index; --i)
				items[i] = items[i - 1];

			items[index] = item;
			item->IncrementReference();

			ItemsCount++;
		}
	}

	void PushBack(T *item)
	{
		PushBack(item, ItemsCount);
	}

	T *PopBack()
	{
		if (!Empty())
			return Remove(ItemsCount - 1);

		return NULL;
	}

	T *Remove(int index)
	{
		if (index < ItemsCount && index >= 0)
		{
			T *item = items[index];

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

	int Remove(T *item)
	{
		if (item && !Empty())
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
				Remove(index);
				return index;
			}
		}

		return -1;
	}

	bool Empty() const
	{
		return ItemsCount == 0;
	}

	void Clear()
	{
		for (int i = 0; i < ItemsCount; i++)
			items[i] = NULL;

		ItemsCount = 0;
	}

	~List()
	{
		Clear();

		delete items;
	}
};

#endif
