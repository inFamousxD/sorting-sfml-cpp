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

void swap(int* a, int i, int j);
void shuffle(int* a, int arraySize);
void render(Bar* bars[], int barsCount, sf::RenderWindow& window);
void bubbleSort(int* arr, int numCount);
void update(Bar* bars[], int* numbers, int numCount);
void cpy_arr(Bar* src[], Bar* dest[], int start, int end);
void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int l, int r);
int quickSortPartition(int* a, int lowI, int highI);
void quickSort(int* numbers, int lowI, int highI);
void insertionSort(int* arr, int numCount);

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
	{
		window.draw(sf::RectangleShape(*(bars[i]->getRectangleShape())));
	}
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
		bars[i] = new Bar(dx, 2, dy);
		heights[i] = window.getSize().y - rand() % (window.getSize().y - window.getSize().y / 10);
	}

	shuffle(heights, BARS);
	update(bars, heights, BARS);

	for (int i = 0; i < BARS; ++i)
	{
		bars[i]->getRectangleShape()->setPosition(dx * (i), window.getSize().y);
	}

	// std::thread sort(&bubbleSort, heights, BARS);
	std::thread sort(&quickSort, heights, 0, BARS - 1);
	// std::thread sort(&mergeSort, heights, 0, BARS - 1);
	// std::thread sort(&insertionSort, heights, BARS);

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
