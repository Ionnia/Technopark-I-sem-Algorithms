// 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <algorithm>

template <class T>
int kStatDC(T *array, int size, int k, int choosePivot(int left, int right), bool comp(T& obj1, T& obj2));
template <class T>
int partition(T *array, int size, bool comp(T& obj1, T& obj2));

template <class T>
int kStatDC(T *array, int size, int k, int choosePivot(int left, int right), bool comp(T& obj1, T& obj2)){
    int left = 0;
    int right = size;
    int pivot = -1;
    while(pivot != k){
        pivot = choosePivot(left, right);
        std::swap(array[pivot], array[right-1]);
        pivot = partition(array + left, right - left, comp);
        pivot += left;  // Partition возващает индекс пивота в подмассиве
        if(pivot < k){
            left = pivot + 1;
        } else if(pivot > k){
            right = pivot;
        }
    }
    return array[pivot];
}

template <class T>
int partition(T *array, int size, bool comp(T& obj1, T& obj2)){
    int i = 0;
    int j = 0;
    while(j != size-1){
        if(comp(array[j], array[size-1])){
            std::swap(array[i], array[j]);
            ++i;
            ++j;
        } else {
            ++j;
        }
    }
    std::swap(array[i], array[size-1]);
    return i;
}

int main(){
    int n = 0;
    int k = 0;

    std::cin >> n >> k;
    int *array = new int [n];

    for(int i = 0; i < n; ++i){
        std::cin >> array[i];
    }

    srand(time(NULL));
    int kStat = kStatDC<int>(array, n, k,
                            [](int left, int right){
                                return left + ( rand() % (right - left) );
                                },
                            [](int& a, int& b){
                                return a <= b;
                                });
    std::cout << kStat << std::endl;

    delete[] array;
    return 0;
}