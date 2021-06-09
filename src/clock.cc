#include "../include/clock.h"

Clock::Clock (): m_dt      (std::chrono::duration<float>(0.0f)),
				 m_ellapsed(std::chrono::duration<float>(0.0f)) {
	Reset();
}

Clock::~Clock() {}

void Clock::Reset() {
	m_ellapsed += m_dt;
	m_start = std::chrono::system_clock::now();
}

void Clock::Tick () {
	m_dt = std::chrono::system_clock::now() - m_start;
}

float Clock::DeltaTime   () { return m_dt.count(); }
float Clock::EllapsedTime() { return m_ellapsed.count(); }
