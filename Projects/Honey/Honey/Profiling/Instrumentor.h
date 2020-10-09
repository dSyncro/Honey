#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>

#include <Honey/Core/Log.h>

#include "ProfileResult.h"

namespace Honey {

	struct InstrumentationSession
	{
		std::string Name;
	};

	/**
	 * @brief Instrumentor profiler.
	*/
	class Instrumentor
	{

	public:

		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		/**
		 * @brief Begin profiling session.
		 * @param name Session name.
		 * @param filepath Log file path.
		*/
		void beginSession(const std::string& name, const std::string& filepath = "results.json");

		/**
		 * @brief End profiling session.
		*/
		void endSession();

		/**
		 * @brief Write profile to output stream
		 * @param result Profiling result to write
		*/
		void writeProfile(const ProfileResult& result);

		/**
		 * @brief Get instrumentor instance.
		 * @return Instrumentor reference.
		*/
		static Instrumentor& get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:

		Instrumentor() : _currentSession(nullptr) { }

		~Instrumentor()
		{
			endSession();
		}

		void writeHeader();
		void writeFooter();

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void internalEndSession();

		std::mutex _mutex;
		InstrumentationSession* _currentSession;
		std::ofstream _outputStream;

	};

}
