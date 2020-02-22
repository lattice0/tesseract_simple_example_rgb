#ifndef SIMPLEBUFFER_H
#define SIMPLEBUFFER_H
template<typename T>
class SimpleBuffer{
  public:
    SimpleBuffer() {

    }
    SimpleBuffer(size_t size): size_(size) {
        t = new T[size];
    }
    ~SimpleBuffer() {
        if (t) {
            //delete[] t;
        }
    }
    T* data() {
        return t;
    }
    size_t size() {
        return size_;
    }
  protected:
    T* t;
    size_t size_;
};

using SimpleRoseekBuffer = SimpleBuffer<unsigned char>;
#endif // SIMPLEBUFFER_H
