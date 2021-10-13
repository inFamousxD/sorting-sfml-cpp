#include "Bar.h"
#include "Platform/Platform.hpp"
#include "chrono"
#include "iostream"
#include "math.h"
#include "stdlib.h"
#include "thread"
#include "unistd.h"

#define BARS 500
#define SLEEP 100
#define SLEEP_HIGH 1000

bool running = true;

int quickSortPartition(int* a, int lowI, int highI);
void swap(int* a, int i, int j);
void merge(int* arr, int l, int m, int r);
void shuffle(int* a, int arraySize);
void mergeSort(int* arr, int l, int r);
void quickSort(int* numbers, int lowI, int highI);
void bubbleSort(int* arr, int numCount);
void insertionSort(int* arr, int numCount);
void render(Bar* bars[], int barsCount, sf::RenderWindow& window);
void update(Bar* bars[], int* numbers, int numCount);
void cpy_arr(Bar* src[], Bar* dest[], int start, int end);
void cocktailSort(int* arr, int numCount);
void stoogeSort(int* arr, int l, int h);
void cycleSort(int* arr, int n);
void oddEvenSort(int* arr, int n);
void heapify(int* arr, int n, int i);
void heapSort(int* arr, int n);
int getMax(int* arr, int n);
void countSort(int* arr, int n, int exp);
void radixsort(int* arr, int n);
int shellSort(int* arr, int n);
bool isSorted(int* a, int n);
void shuffleBogoSort(int* a, int n);
void bogosort(int* a, int n);

void swap(int* a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void shuffle(int* a, int arraySize)
{
	srand(time(NULL));
	for (int i = arraySize - 1; i > 0; --i)
	{
		int j = rand() % i + 1;
		swap(a, i, j);
	}
}

void render(Bar* bars[], int barsCount, sf::RenderWindow& window)
{
	for (int i = 0; i < barsCount; ++i)
	{
		bars[i]->getRectangleShape()->setPosition(((window.getSize().x) / barsCount) * (i), window.getSize().y);
	}
	window.clear(sf::Color(50, 50, 50));
	for (int i = 0; i < barsCount; ++i)
		// {
		window.draw(sf::RectangleShape(*(bars[i]->getRectangleShape())));
	window.display();
}

void cpy_arr(Bar* src[], Bar* dest[], int start, int end)
{
	for (int i = start; i < end; ++i)
	{
		dest[i - start] = new Bar(src[i]->getHeight());
	}
}

void merge(int* arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int *L = new int[n1], *R = new int[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			usleep(SLEEP_HIGH);
			i++;
		}
		else
		{
			arr[k] = R[j];
			usleep(SLEEP_HIGH);
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		usleep(SLEEP_HIGH);
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		usleep(SLEEP_HIGH);
		j++;
		k++;
	}
}

void mergeSort(int* arr, int l, int r)
{
	if (!running)
		return;
	if (l < r)
	{
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

int quickSortPartition(int* a, int lowI, int highI)
{
	int pivot = a[highI];
	int i = lowI - 1;

	for (int j = lowI; j <= highI - 1; ++j)
	{
		if (a[j] <= pivot)
		{
			if (!running)
				return -1;
			i++;
			swap(a, i, j);
			usleep(SLEEP_HIGH * 3);
		}
	}
	swap(a, i + 1, highI);
	usleep(SLEEP_HIGH);
	return i + 1;
}

void quickSort(int* numbers, int lowI, int highI)
{
	if (!running)
		return;
	if (lowI < highI)
	{
		int pi = quickSortPartition(numbers, lowI, highI);

		quickSort(numbers, lowI, pi - 1);
		quickSort(numbers, pi + 1, highI);
	}
}

void insertionSort(int* arr, int numCount)
{

	for (int i = 0; i < numCount; ++i)
	{
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j)
		{
			if (!running)
				return;
			swap(arr, j, j - 1);
			usleep(SLEEP);
		}
	}
}

void bubbleSort(int* arr, int numCount)
{
	bool swapped;
	do
	{
		swapped = false;
		for (int i = 1; i < numCount; ++i)
		{
			if (!running)
				return;
			if (arr[i - 1] > arr[i])
			{
				swap(arr, i, i - 1);
				//swapped = true;
				usleep(SLEEP);
			}
		}

	} while (!swapped);
}

void cocktailSort(int* a, int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped)
	{
		swapped = false;

		for (int i = start; i < end; ++i)
		{
			if (a[i] > a[i + 1])
			{
				swap(a, i, i + 1);
				usleep(SLEEP);
				swapped = true;
			}
		}
		if (!swapped)
			break;
		swapped = false;
		--end;
		for (int i = end - 1; i >= start; --i)
		{
			if (a[i] > a[i + 1])
			{
				swap(a, i, i + 1);
				usleep(SLEEP);
				swapped = true;
			}
		}
		++start;
	}
}

void stoogeSort(int* arr, int l, int h)
{
	if (l >= h)
		return;

	if (arr[l] > arr[h])
	{
		swap(arr, l, h);
		usleep(SLEEP);
	}

	if (h - l + 1 > 2)
	{
		int t = (h - l + 1) / 3;

		stoogeSort(arr, l, h - t);
		stoogeSort(arr, l + t, h);
		stoogeSort(arr, l, h - t);
	}
}

void cycleSort(int* arr, int n)
{
	int writes = 0;

	for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
	{
		int item = arr[cycle_start];

		int pos = cycle_start;
		for (int i = cycle_start + 1; i < n; i++)
			if (arr[i] < item)
				pos++;

		if (pos == cycle_start)
			continue;

		while (item == arr[pos])
			pos += 1;

		if (pos != cycle_start)
		{
			int temp = item;
			item = arr[pos];
			arr[pos] = temp;
			usleep(SLEEP_HIGH * 10);
			writes++;
		}

		while (pos != cycle_start)
		{
			pos = cycle_start;

			for (int i = cycle_start + 1; i < n; i++)
				if (arr[i] < item)
					pos += 1;

			while (item == arr[pos])
				pos += 1;

			if (item != arr[pos])
			{
				int temp = item;
				item = arr[pos];
				arr[pos] = temp;
				usleep(SLEEP_HIGH * 10);
				writes++;
			}
		}
	}
}

void oddEvenSort(int* arr, int n)
{
	bool isSorted = false;

	while (!isSorted)
	{
		isSorted = true;

		for (int i = 1; i <= n - 2; i = i + 2)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr, i, i + 1);
				usleep(SLEEP);
				isSorted = false;
			}
		}

		for (int i = 0; i <= n - 2; i = i + 2)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr, i, i + 1);
				usleep(SLEEP);
				isSorted = false;
			}
		}
	}

	return;
}

void heapify(int* arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		swap(arr, i, largest);
		usleep(SLEEP_HIGH * 2);
		heapify(arr, n, largest);
	}
}

void heapSort(int* arr, int n)
{
	usleep(SLEEP_HIGH * 200);
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i > 0; i--)
	{
		swap(arr, 0, i);
		usleep(SLEEP_HIGH);

		heapify(arr, i, 0);
	}
}

int getMax(int* arr, int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void countSort(int* arr, int n, int exp)
{
	int* output = new int[n];
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
	{
		arr[i] = output[i];
		usleep(SLEEP_HIGH);
	}
}

void radixsort(int* arr, int n)
{
	int m = getMax(arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		countSort(arr, n, exp);
	}
}

int shellSort(int* arr, int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			arr[j] = temp;
			usleep(SLEEP_HIGH);
		}
	}
	return 0;
}

bool isSorted(int* a, int n)
{
	while (--n > 1)
		if (a[n] < a[n - 1])
			return false;
	return true;
}

void shuffleBogoSort(int* a, int n)
{
	for (int i = 0; i < n; i++)
		swap(a, i, rand() % n);
}

void bogosort(int* a, int n)
{
	while (!isSorted(a, n))
		shuffleBogoSort(a, n);
}

void update(Bar* bars[], int* numbers, int numCount)
{
	for (int i = 0; i < numCount; ++i)
	{
		bars[i]->setHeight(numbers[i]);
	}
}

int main()
{
#if defined(_DEBUG)
	std::cout << "Debug init success" << std::endl;
#endif

	Bar* bars[BARS];
	int heights[BARS];

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithms", sf::Style::Close);
	int dx = (window.getSize().x / BARS);
	int dy = (window.getSize().y / BARS);

	for (int i = 0; i < BARS; ++i)
	{
		bars[i] = new Bar(dx, 1, dy);
		heights[i] = window.getSize().y - rand() % (window.getSize().y - window.getSize().y / 10);
	}

	shuffle(heights, BARS);
	update(bars, heights, BARS);

	for (int i = 0; i < BARS; ++i)
	{
		bars[i]->getRectangleShape()->setPosition(dx * (i), window.getSize().y);
	}

	// std::thread sort(&bubbleSort, heights, BARS);
	// std::thread sort(&quickSort, heights, 0, BARS - 1);
	// std::thread sort(&mergeSort, heights, 0, BARS - 1);
	// std::thread sort(&insertionSort, heights, BARS);
	// std::thread sort(&cocktailSort, heights, BARS);
	// std::thread sort(&stoogeSort, heights, 0, BARS - 1);
	// std::thread sort(&cycleSort, heights, BARS);
	// std::thread sort(&oddEvenSort, heights, BARS);
	// std::thread sort(&heapSort, heights, BARS);
	// std::thread sort(&radixsort, heights, BARS);
	std::thread sort(&shellSort, heights, BARS);
	// std::thread sort(&bogosort, heights, BARS);

	sf::Event event;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		update(bars, heights, BARS);
		render(bars, BARS, window);
	}
	running = false;
	for (int i = 0; i < BARS; ++i)
	{
		delete bars[i];
	}
	sort.join();
	return 0;
}
