#pragma once
#include <algorithm>
#include <map>
#include <set>

template <class T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

template <class T, class Event>
class IObservable
{
public:
	virtual ~IObservable() = default;

	virtual void RegisterObserver(IObserver<T>& observer, unsigned priority) = 0;
	virtual void NotifyObservers(std::set<Event> const& changedEvents) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;

	virtual void SetEventSubscription(IObserver<T>& observer, Event event) = 0;
	virtual void DelEventSubscription(IObserver<T>& observer, Event event) = 0;
};

template <class T, class Event>
class CObservable : public IObservable<T, Event>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, unsigned priority) override
	{
		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers(std::set<Event> const& changedEvents) override
	{
		T data = GetChangedData();
		std::multimap<int, ObserverType*> observers = m_observers;

		for (auto iter = observers.rbegin(); iter != observers.rend(); ++iter)
		{
			/*iter->second->Update(data);*/
			if (IsSubscribe(iter->second, changedEvents))
			{
				iter->second->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto iter = m_observers.begin(); iter != m_observers.end(); ++iter)
		{
			if (iter->second == &observer)
			{
				m_observers.erase(iter);
				break;
			}
		}
		auto it = m_subscriptions.find(&observer);
		if (it != m_subscriptions.end())
		{
			m_subscriptions.erase(it);
		}
	}

	void SetEventSubscription(ObserverType& observer, Event event) override
	{
		if (m_subscriptions.find(&observer) == m_subscriptions.end())
		{
			m_subscriptions[&observer] = std::set<Event>{};
		}
		m_subscriptions[&observer].insert(event);
	}

	void DelEventSubscription(ObserverType& observer, Event event) override
	{
		if (m_subscriptions.find(&observer) == m_subscriptions.end())
		{
			return;
		}
		std::set<Event>& eventsSet = m_subscriptions[&observer];
		eventsSet.erase(eventsSet.find(event));
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	bool IsSubscribe(ObserverType* observer, std::set<Event> const& events)
	{
		std::set<Event> observerEvents = m_subscriptions[observer];
		return std::any_of(events.begin(), events.end(), [=](Event e) { return observerEvents.find(e) != observerEvents.end(); });
	}

	std::multimap<int, ObserverType*> m_observers;
	std::map<ObserverType*, std::set<Event>> m_subscriptions;
};
