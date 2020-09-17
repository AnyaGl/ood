#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <string>

struct SWindInfo
{
	double speed = 0;
	double direction = 0;

	bool operator==(SWindInfo const& windInfo) const
	{
		return speed == windInfo.speed && direction == windInfo.direction;
	}
	bool operator!=(SWindInfo const& windInfo) const
	{
		return !(*this == windInfo);
	}
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	SWindInfo wind;
};

enum class WeatherEvent
{
	Temperature,
	Humidity,
	Pressure,
	Wind
};

class CWeatherData : public CObservable<SWeatherInfo, WeatherEvent>
{
public:
	double GetTemperature() const
	{
		return m_temperature;
	}
	double GetHumidity() const
	{
		return m_humidity;
	}
	double GetPressure() const
	{
		return m_pressure;
	}
	SWindInfo GetWindInfo() const
	{
		return m_windInfo;
	}

	void MeasurementsChanged(std::set<WeatherEvent> const& changedEvents)
	{
		NotifyObservers(changedEvents);
	}

	void SetMeasurements(double temp, double humidity, double pressure, SWindInfo wind)
	{
		std::set<WeatherEvent> changedEvents = GetChangedEvents(temp, humidity, pressure, wind);

		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windInfo = wind;

		MeasurementsChanged(changedEvents);
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind = GetWindInfo();
		return info;
	}

	std::set<WeatherEvent> GetChangedEvents(double temp, double humidity, double pressure, SWindInfo wind) const
	{
		std::set<WeatherEvent> events;
		if (m_temperature != temp)
		{
			events.insert(WeatherEvent::Temperature);
		}
		if (m_humidity != humidity)
		{
			events.insert(WeatherEvent::Humidity);
		}
		if (m_pressure != pressure)
		{
			events.insert(WeatherEvent::Pressure);
		}
		if (m_windInfo != wind)
		{
			events.insert(WeatherEvent::Wind);
		}
		return events;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_windInfo;
};

class CStatistic
{
public:
	void Update(double value)
	{
		m_min = std::min(m_min, value);
		m_max = std::max(m_max, value);
		m_acc += value;
		++m_countAcc;
	}

	std::string ToString()
	{
		return "\tmin: " + std::to_string(m_min) + "\n\tmax: " + std::to_string(m_max) + "\n\taverage: " + std::to_string(m_acc / m_countAcc);
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

#define PI 3.14159265359

class CDirectionStatistic
{
public:
	void Update(double value)
	{
		m_sinSum += sin(ToRadians(value));
		m_cosSum += cos(ToRadians(value));
	}

	std::string ToString()
	{
		double x = ToDegrees(atan2(m_sinSum, m_cosSum)) + 360;
		double average = x - trunc(x / 360) * 360;
		return "\taverage direction: " + std::to_string(average);
	}

private:
	static double ToDegrees(double value)
	{
		return value * 180 / PI;
	}

	static double ToRadians(double value)
	{
		return value * PI / 180;
	}

	double m_sinSum = 0;
	double m_cosSum = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);
		m_windSpeedStats.Update(data.wind.speed);
		m_windDirectionStats.Update(data.wind.direction);

		std::cout << "Temperature\n"
				  << m_temperatureStats.ToString() << std::endl;
		std::cout << "Humidity\n"
				  << m_humidityStats.ToString() << std::endl;
		std::cout << "Pressure\n"
				  << m_pressureStats.ToString() << std::endl;
		std::cout << "Wind\n"
				  << m_windSpeedStats.ToString() << std::endl;
		std::cout << m_windDirectionStats.ToString() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CStatistic m_temperatureStats;
	CStatistic m_humidityStats;
	CStatistic m_pressureStats;
	CStatistic m_windSpeedStats;
	CDirectionStatistic m_windDirectionStats;
};
