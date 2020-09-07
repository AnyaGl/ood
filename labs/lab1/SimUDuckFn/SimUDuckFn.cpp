#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

using Strategy = function<void()>;

function<void()> FlyWithWings()
{
	size_t flightCounter = 0;
	return [flightCounter]() mutable {
		++flightCounter;
		cout << "I'm flying with wings for the " << flightCounter << " time(s)" << endl;
	};
};
void FlyNoWay(){};

void QuackBehavior()
{
	cout << "Quack Quack!!!" << endl;
};
void SqueakBehavior()
{
	cout << "Squeek!!!" << endl;
};
void MuteQuackBehavior(){};

void DanceTheWaltz()
{
	cout << "I'm dancing waltz!!" << endl;
};
void DanceTheMinuet()
{
	cout << "I'm dancing minuet!!" << endl;
};
void DanceNoWay(){};

class Duck
{
public:
	Duck(Strategy&& flyBehavior,
		Strategy&& quackBehavior,
		Strategy&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
	{
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim() const
	{
		cout << "I'm swimming" << endl;
	}
	void Fly() const
	{
		m_flyBehavior();
	}
	void Dance() const
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(Strategy&& flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	Strategy m_flyBehavior;
	Strategy m_quackBehavior;
	Strategy m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackBehavior, DanceTheWaltz)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), QuackBehavior, DanceTheMinuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}
