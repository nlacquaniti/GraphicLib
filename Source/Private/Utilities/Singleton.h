#pragma once

template<typename SingletonClass>
class Singleton {
public:
    static SingletonClass& Get() {
        if (_instance == nullptr) {
            _instance = new SingletonClass{};
        }
        return *_instance;
    }
    static const SingletonClass& ConstGet() { return Get(); }

private:
    static SingletonClass* _instance = {};
};
