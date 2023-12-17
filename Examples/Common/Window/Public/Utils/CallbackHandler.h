#pragma once

template<typename TCallbackType>
class CallbackHandler {
public:
    using CallbackSignature = TCallbackType;

    void Set(CallbackSignature callback, void* userData) {
        _callback = callback;
        _userData = userData;
    }
    void Clear() {
        _callback = nullptr;
        _userData = nullptr;
    }
    template<typename... ARGS>
    void Invoke(ARGS&&... args) {
        if (_callback == nullptr) {
            return;
        }
        _callback(args..., _userData);
    }

private:
    CallbackSignature _callback{};
    void* _userData{};
};