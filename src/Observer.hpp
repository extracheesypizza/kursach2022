#ifndef OBSERVER_H
#define OBSERVER_H

#include <functional>
#include <vector>

namespace Project
{
// prototype class
template <typename T>
class Observable;

template <typename T>
class Observer
{
    friend Observable<T>;

   public:
    template <class Tt1, class Tt2, class Tt3>
    Observer(Tt1&& onSubscribe, Tt2&& onNotify, Tt3&& onUnsubscribe)
        : onSubscribe_(std::forward<Tt1>(onSubscribe)),  //
          onNotify_(std::forward<Tt2>(onNotify)),        //
          onUnsubscribe_(std::forward<Tt3>(onUnsubscribe)){};

    Observer(const Observer&) = delete;
    Observer& operator=(const Observer&) = delete;
    Observer(Observer&&) noexcept = delete;
    Observer& operator=(Observer&&) noexcept = delete;

    ~Observer() { unsubscribe(); }

    void unsubscribe()
    {
        if(!isSubscribed())
            return;
        Observable_->detach_(this);
        Observable_ = nullptr;
    }

    bool isSubscribed() const { return Observable_; }

   private:
    Observable<T>* Observable_ = nullptr;
    void setObservable_(Observable<T>* observable) { Observable_ = observable; }
    std::function<void(T)> onSubscribe_;
    std::function<void(T)> onNotify_;
    std::function<void(T)> onUnsubscribe_;
};

template <typename T>
class Observable
{
    friend Observer<T>;

   public:
    // move constructor
    template <class Tt>
    Observable(Tt&& data) : data_(std::forward<Tt>(data)){};

    Observable(const Observable&) = delete;
    Observable& operator=(const Observable&) = delete;
    Observable(Observable&&) noexcept = delete;
    Observable& operator=(Observable&&) noexcept = delete;

    ~Observable()
    {
        while(!Observers_.empty())
        {
            Observers_[Observers_.size() - 1]->unsubscribe();
            Observers_.pop_back();
        }
    }

    void subscribe(Observer<T>* obs)
    {
        if(obs->isSubscribed())
            obs->unsubscribe();
        Observers_.push_back(obs);
        obs->setObservable_(this);
        obs->onSubscribe_(data_());
    }

    void notify() const
    {
        for(auto obs : Observers_)  //
            obs->onNotify_(data_());
    }

   private:
    std::function<T()> data_;
    std::vector<Observer<T>*> Observers_;
    void detach_(Observer<T>* obs)
    {
        obs->onUnsubscribe_(data_());
        auto it = find(Observers_.begin(), Observers_.end(), obs);
        Observers_.erase(it);
    }
};
}  // namespace Project

#endif  // OBSERVER_HPP
