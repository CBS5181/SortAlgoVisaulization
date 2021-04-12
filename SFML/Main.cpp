#include <iostream>
#include "Bar.h"
#include <thread>
#include <chrono>


bool running = true;

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void shuffle(int* arr, int arrSize)
{
	srand(time(NULL));
	for (int i = arrSize - 1; i > 0; --i) { // round 1: 0~249 round2 : 0~248 .... 0~1
		int j = rand() % (i + 1);
		swap(arr, i, j);
	}
}

void renderBars(Bar* bars[], int barsCount, sf::RenderWindow& window)
{
	int pos_X = window.getSize().x / barsCount;
	int pos_Y = window.getSize().y;

	for (int i = 0; i < barsCount; ++i) {
		bars[i]->getRect()->setPosition(pos_X * i, pos_Y);
	}
	window.clear(sf::Color(120, 125, 135));
	for (int i = 0; i < barsCount; ++i) {
		window.draw(*(bars[i]->getRect()));
		//window.draw(sf::RectangleShape(*(bars[i]->getRect())));
	}
	window.display();
}

void updateBars(Bar* bars[], int* numbers, int numCount)
{
	for (int i = 0; i < numCount; ++i) {
		bars[i]->setNum(numbers[i]);
	}
}

void merge(int* arr, int begin, int mid, int end)
{
	int li, ri, k;
	int n1 = mid - begin + 1;
	int n2 = end - mid;
	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1; ++i) {
		L[i] = arr[begin + i];
	}
	for (int i = 0; i < n2; ++i) {
		R[i] = arr[mid + 1 + i];
	}

	li = 0;
	ri = 0;
	k = begin;
	while (li < n1 && ri < n2) {
		if (L[li] <= R[ri]) {
			arr[k++] = L[li++];
			std::this_thread::sleep_for(std::chrono::microseconds(10000));
		} else {
			arr[k++] = R[ri++];
			std::this_thread::sleep_for(std::chrono::microseconds(10000));
		}
	}
	while (li < n1) {
		arr[k++] = L[li++];
		std::this_thread::sleep_for(std::chrono::microseconds(10000));
	}
	while (ri < n2) {
		arr[k++] = R[ri++];
		std::this_thread::sleep_for(std::chrono::microseconds(10000));
	}
	
	delete[] L;
	delete[] R;
}

void mergeSort(int* arr, int begin, int end)
{
	if (!running) return;
	if (begin < end) {
		int mid = begin + (end - begin) / 2;
		mergeSort(arr, begin, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, begin, mid, end);
	}
}

int quickSortPartition(int* arr, int begin, int end)
{
	int pivot = arr[end];
	int i = begin - 1;
	for (int j = begin; j < end; ++j) {
		if (arr[j] < pivot) {
			++i;
			swap(arr, i, j);
			std::this_thread::sleep_for(std::chrono::microseconds(10000));
		}
	}
	++i;
	swap(arr, i, end);
	std::this_thread::sleep_for(std::chrono::microseconds(10000));
	return i;
}

void quickSort(int* numbers, int begin, int end)
{
	if (!running) return;
	if (begin < end) {
		int pivot = quickSortPartition(numbers, begin, end);
		quickSort(numbers, begin, pivot - 1);
		quickSort(numbers, pivot + 1, end);
	}
	// std::cout << "sort finish" << std::endl;
}

void selectionSort(int* arr, int numCount)
{
	for (int i = 0; i < numCount; ++i) {
		int min = i;
		for (int j = i + 1; j < numCount; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		if (min != i) {
			swap(arr, min, i);
			std::this_thread::sleep_for(std::chrono::microseconds(100000));
		}
	}
}

void insertionSort(int* arr, int numCount)
{
	for (int i = 1; i < numCount; ++i) {
		for (int j = i; j > 0 && (arr[j] < arr[j - 1]); --j) {
			if (!running) return;
			swap(arr, j, j - 1);
			std::this_thread::sleep_for(std::chrono::microseconds(10000));
			
		}
	}
	std::cout << "sort finish" << std::endl;
}

void bubbleSort(int* arr, int numCount)
{
	bool swapped;
	do {
		swapped = false;
		for (int i = 1; i < numCount; ++i) {
			if (!running) return;
			if (arr[i - 1] > arr[i]) {
				swap(arr, i - 1, i);
				swapped = true;
				std::this_thread::sleep_for(std::chrono::microseconds(10000));
			}
		}

	} while (swapped);
	std::cout << "sort finish" << std::endl;
}

int main()
{
	const int numCount = 140;

	Bar* bars[numCount];
	int numbers[numCount];

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithm Visualization", sf::Style::Close);
	int dx = ((window.getSize().x) / numCount);
	int dy = ((window.getSize().y) / numCount);
	//std::cout << "dx: " << dx << std::endl << "dy: " << dy << std::endl;
	for (int i = 0; i < numCount; ++i) {
		bars[i] = new Bar(dx, i, dy);
		numbers[i] = i;
	}

	// Make number order random
	shuffle(numbers, numCount);
	// Update new random order to bars
	updateBars(bars, numbers, numCount);

	// thread
	//std::thread sort(&bubbleSort, numbers, numCount);
	//std::thread sort(&insertionSort, numbers, numCount);
	//std::thread sort(&selectionSort, numbers, numCount);
	//std::thread sort(&quickSort, numbers, 0, numCount - 1);
	std::thread sort(&mergeSort, numbers, 0, numCount - 1);

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		// update
		updateBars(bars, numbers, numCount);
		// render
		renderBars(bars, numCount, window);
		
	}
	
	running = false;

	for (int i = 0; i < numCount; i++) {
		delete bars[i];
	}

	sort.join();
	return 0;
}


 
