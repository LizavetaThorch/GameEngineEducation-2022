//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#pragma once

class GameTimer
{
public:
	GameTimer();

	float TotalTime()const; // in seconds
	float DeltaTime()const; // in seconds

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};


/*
* Код определяет следующие члены класса:

* Публичные методы:
  - TotalTime(): возвращает общее время, прошедшее с момента сброса таймера (в секундах).
  - DeltaTime(): возвращает время, прошедшее между текущим и предыдущим кадром (в секундах).
  - Reset(): вызывается перед циклом обработки сообщений, сбрасывает таймер.
  - Start(): вызывается для возобновления таймера после паузы.
  - Stop(): вызывается для приостановки таймера.
  - Tick(): вызывается на каждой итерации игрового цикла для обновления состояния таймера.

* Приватные члены:
  - mSecondsPerCount: число секунд в одном такте (рассчитывается при создании объекта GameTimer).
  - mDeltaTime: время, прошедшее между текущим и предыдущим кадром.
  - mBaseTime: время запуска таймера.
  - mPausedTime: общая продолжительность паузы.
  - mStopTime: время остановки таймера.
  - mPrevTime: время завершения предыдущего кадра.
  - mCurrTime: время завершения текущего кадра.
  - mStopped: флаг, указывающий на то, остановлен ли таймер.

* Таким образом, данный заголовочный файл предоставляет интерфейс для класса GameTimer, 
* который используется для измерения и работы с временем в игровом приложении.
*/