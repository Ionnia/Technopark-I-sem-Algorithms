// 3_1. Реализовать очередь с динамическим зацикленным буфером.

#include <iostream>

class QueueCycledBuf{
    public:
        QueueCycledBuf(int arraySize){
            this->arraySize = arraySize;
            array = new int[arraySize];
            headIndex = 0;
            tailIndex = 0;
        }

        QueueCycledBuf() : QueueCycledBuf(64) {};

        ~QueueCycledBuf(){
            delete[] array;
        }

        int pop(){
            if(numOfElements == 0){
                return -1;
            }
            int curHeadIndex = headIndex;
            headIndex = (headIndex+1)%arraySize;
            --numOfElements;
            return array[curHeadIndex];
        }

        void push(int num){
            if(arraySize == numOfElements){
                int *tmp = new int [arraySize*2];
                int index = 0;
                for(int i = 0; i < numOfElements; ++i){
                    index = (headIndex+i)%arraySize;
                    tmp[i] = array[index];
                }
                arraySize *= 2;
                headIndex = 0;
                tailIndex = numOfElements;
                delete[] array;
                array = tmp;
            }
            array[tailIndex++] = num;
            tailIndex %= arraySize;
            ++numOfElements;
        }

    private:
        int *array;
        int arraySize;
        int numOfElements;
        int headIndex;
        int tailIndex;
};

bool getExpectation(int command, int number, QueueCycledBuf& qcbuf){
    bool result = true;
    if(command == 2){
        result = (number == qcbuf.pop());
    } else {
        qcbuf.push(number);
    }
    return result;
}

int main(){
    int n = 0;

    std::cin >> n;

    QueueCycledBuf qcbuf;

    bool isOK = true;
    int command, number;
    for(int i = 0; i < n; ++i){
        std::cin >> command;
        std::cin >> number;
        isOK *= getExpectation(command, number, qcbuf);
    }

    std::cout << (isOK ? "YES" : "NO") << std::endl;

    return 0;
}