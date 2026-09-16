class Foo {
private:
    int count = 1;
    mutex mtx;
    condition_variable cv;

public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> lock(mtx);

        printFirst();
        count = 2;

        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this] {
            return count == 2;
        });

        printSecond();
        count = 3;

        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this] {
            return count == 3;
        });

        printThird();
    }
};