#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class ZeroEvenOdd {
private:
    int n;
    int num = 1;

    mutex mtx;
    condition_variable cv;

    bool zeroTurn = true;
    bool oddTurn = false;
    bool evenTurn = false;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    void zero(function<void(int)> printNumber) {

        for (int i = 0; i < n; i++) {

            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return zeroTurn;
            });

            printNumber(0);

            zeroTurn = false;

            if (num % 2 == 1)
                oddTurn = true;
            else
                evenTurn = true;

            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {

        for (int i = 0; i < n / 2; i++) {

            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return evenTurn;
            });

            printNumber(num);
            num++;

            evenTurn = false;
            zeroTurn = true;

            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {

        for (int i = 0; i < (n + 1) / 2; i++) {

            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return oddTurn;
            });

            printNumber(num);
            num++;

            oddTurn = false;
            zeroTurn = true;

            cv.notify_all();
        }
    }
};