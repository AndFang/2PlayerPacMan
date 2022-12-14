#ifndef Obverser_h
#define Obverser_h

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void Update() = 0;
};

class ObserverSubject
{
public:
	ObserverSubject() {}
	virtual ~ObserverSubject() {}
	void Attach(Observer* obs) { _observers.push_back(obs); }
	void Detach(Observer* obs) { _observers.erase(remove(_observers.begin(), _observers.end(), obs), _observers.end()); }
	void Notify()
	{
		for (auto i : _observers)
			i->Update();
	}

private:
	vector<Observer*> _observers;
};

#endif
