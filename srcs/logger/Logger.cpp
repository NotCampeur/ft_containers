#include "Logger.hpp"
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

//Static initialisation.
std::ofstream			Logger::_file;
log_importance_level	Logger::_accepted_importance = log_importance_level(error_lvl | major_lvl | time_lvl);
pid_t					Logger::_process_id = getpid();
log_type				Logger::_type = basic_type;
log_importance_level	Logger::_importance = major_lvl;

Logger::Logger(void)
{
	if (is_important_enough() && (_accepted_importance & time_lvl) != 0)
		put_timestamp();
}

Logger::Logger(log_type type)
{
	_type = type;
	if (is_important_enough() && (_accepted_importance & time_lvl) != 0)
		put_timestamp();
}

Logger::Logger(log_importance_level importance)
{
	_importance = importance;
	if (is_important_enough() && (_accepted_importance & time_lvl) != 0)
		put_timestamp();
}

Logger::Logger(log_type type, log_importance_level importance)
{
	_type = type;
	_importance = importance;
	if (is_important_enough() && (_accepted_importance & time_lvl) != 0)
		put_timestamp();
}

Logger::~Logger()
{
	if (is_important_enough())
		_file << std::endl;
}

void
Logger::put_timestamp(void)
{
	std::string	msg;
	time_t		now(0);

	now = time(0);
	msg = ctime(&now);
	msg.erase(msg.end() - 1);
	msg = '[' + msg + "] ";
	if (getpid() != _process_id)
		msg += "{'SUBPROCESS'} ";
	if (_type == error_type)
		msg += "{ERROR} ";
	_file << msg;
}

void
Logger::set_default_type(log_type type)
{
	_type = type;
}

void
Logger::set_default_importance(log_importance_level importance)
{
	_importance = importance;
}

void
Logger::accept_importance(log_importance_level accepted_importance)
{
	_accepted_importance = accepted_importance;
}

void
Logger::open_log_file(std::string path)
{
	if (_file.is_open() == false)
		_file.open(path.c_str());
}

void
Logger::close_log_file(void)
{
	if (_file.is_open())
		_file.close();
}

void
Logger::enable_time(bool enable)
{
	if (enable == true && (_accepted_importance & time_lvl) == 0)
		_accepted_importance = _accepted_importance | time_lvl;
	else if (enable == false && (_accepted_importance & time_lvl) != 0)
		_accepted_importance = _accepted_importance & ~time_lvl;
}

void
Logger::quit(void)
{
	_file << "End of logs" << std::endl;
}

bool
Logger::is_important_enough(void) const
{
	if ((_accepted_importance & _importance) != 0)
		return true;
	return false;
}

log_importance_level
operator|(const log_importance_level & value_a, const log_importance_level & value_b)
{
	return ((log_importance_level)(static_cast<int>(value_a) | static_cast<int>(value_b)));
}

log_importance_level
operator^(const log_importance_level & value_a, const log_importance_level & value_b)
{
	return ((log_importance_level)(static_cast<int>(value_a) ^ static_cast<int>(value_b)));
}

log_importance_level
operator&(const log_importance_level & value_a, const log_importance_level & value_b)
{
	return ((log_importance_level)(static_cast<int>(value_a) & static_cast<int>(value_b)));
}

log_importance_level
operator~(const log_importance_level & value)
{
	return ((log_importance_level)(~static_cast<int>(value)));
}

Logger &
Logger::operator<<(const std::string & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const char * const & entry)
{
	if (is_important_enough() && entry != NULL)
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const char & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const int & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const ssize_t & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const size_t & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const bool & entry)
{
	if (is_important_enough())
	{
		if (entry == true)
			_file << "true";
		else
			_file << "false";
	}
	return *this;
}
