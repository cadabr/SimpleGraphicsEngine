#pragma once

template <typename SingletonClass>
class ExplicitSingleton {
public:
    ExplicitSingleton() {
        if (s_instance) {
            throw std::runtime_error("ExplicitSingleton already constructed!");
        }
        s_instance = static_cast<SingletonClass*>(this);
    }

    ~ExplicitSingleton() {
        s_instance = nullptr;
    }

    static SingletonClass& instance() {
        if (!s_instance) {
            throw std::runtime_error("ExplicitSingleton used before construction!");
        }
        return *s_instance;
    }

private:
    static SingletonClass* s_instance;
};
