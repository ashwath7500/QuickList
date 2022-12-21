#include <bits/stdc++.h>
using namespace std;

template<typename T>
class fixed_alloc_helper{
public:
    fixed_alloc_helper() : size_(2) {
        blocks_.push_back(new T[1]);
        pool_.push(blocks_[0]);
    }
    ~fixed_alloc_helper() {
        for (auto it:blocks_) delete[] it;
    }
    T* allocate(size_t siz) {
        assert(siz == 1);
        if (pool_.empty()) {
            blocks_.push_back(new T[size_]);
            for (size_t i = 0;i<size_;i++) pool_.push(blocks_.back()+i);
            size_ *= 2;
        }
        T* ret = pool_.front();
        pool_.pop();
        return ret;
    }
    void deallocate(T* pointer, size_t siz) {
        assert(siz == 1);
        pool_.push(pointer);
    }
private:
    queue<T*> pool_;
    vector<T*> blocks_;
    size_t size_;
};

template<typename T>
class fixed_alloc{
public:
    using value_type = T;
    fixed_alloc() {
        helper_ = make_shared<fixed_alloc_helper<T> >();
    }
    template<class U>
    constexpr fixed_alloc (const fixed_alloc <U>&) {
        helper_ = make_shared<fixed_alloc_helper<T> >();
    }
    T* allocate(size_t siz) {
        return helper_->allocate(siz);
    }
    void deallocate(T* pointer, size_t siz) {
        helper_->deallocate(pointer,siz);
    }
private:
    shared_ptr<fixed_alloc_helper<T> > helper_;
};