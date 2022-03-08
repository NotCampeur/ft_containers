#ifndef WEBSERV_LOGGER_HPP
# define WEBSERV_LOGGER_HPP

# include <fstream>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>

// This enum store the flags about the type of entry.
// Some entry like the errors need further specifications.
// Which are given by this enum.
typedef enum log_type
{
	basic_type,
	error_type
}	log_type;

// This enum store the flags about the importance restriction,
typedef enum log_importance_level
{
	none_lvl = 0x000,
	error_lvl = 0x001,
	major_lvl = 0x002,
	minor_lvl = 0x004,
	debug_lvl = 0x008,
	time_lvl = 0x010,
	all_lvl   = error_lvl | major_lvl | minor_lvl | debug_lvl | time_lvl
}	log_importance_level;

// Will force the unary expression to return a log_importance_level and not a int.
log_importance_level operator|(const log_importance_level & value_a,
								const log_importance_level & value_b);

// Will force the unary expression to return a log_importance_level and not a int.
log_importance_level operator^(const log_importance_level & value_a,
								const log_importance_level & value_b);

// Will force the unary expression to return a log_importance_level and not a int.
log_importance_level operator&(const log_importance_level & value_a,
								const log_importance_level & value_b);

// Will force the unary expression to return a log_importance_level and not a int.
log_importance_level operator~(const log_importance_level & value_a);

// A class to simplify logs creation.
// The common usage is
// Logger() << "This is a nice log entry" << 42 << '42';
// You can set which messages will be printed glade to :
// Logger::accept_importance(error_lvl | major_lvl | debug_lvl);
// You must call Logger::quit() before the exit to avoid leaks.
class Logger
{
	public:
		Logger(void);
		Logger(log_type type);
		Logger(log_importance_level importance);
		Logger(log_type type, log_importance_level importance);
		~Logger();

		// In case the type is not specified when you create a Logger. 
		// The type of the entry will be the default one.
		static void set_default_type(log_type type);

		// In case the importance is not specified when you create a Logger.
		// The importance of the entry will be the default one.
		static void set_default_importance(log_importance_level importance);

		// This function will set the accepted level.
		// If you try to write an entry below the accepted level
		// nothing will happen.
		// If you never set it yourself every messages are accepted.
		static void	accept_importance(log_importance_level accepted_importance);

		// This function will open the log file.
		// If the file is already opened nothing will happen.
		// If the file is not already opened it will be created.
		static void	open_log_file(std::string path); 

		// This function will close the log file.
		// If the file is already closed nothing will happen.
		static void	close_log_file();

		// This function will enable or disable the time display.
		// If you never set it yourself the time will be displayed.
		static void	enable_time(bool enable);

		// In cases you want to manually print the time. The use of enable_time is recommended.
		static void	put_timestamp(void);

		// This function need to be called right before the end of the program.
		// The ofstream map will be correctly deleted.
		static void	quit(void);

		// This tell you if the current instance will be allow to write entry.
		bool	is_important_enough(void) const;
		
		// The operator << will be used to write the entry on the previously opened log file.
		// The type T need his own operator <<.
		template< class T >
		Logger	&operator<<(const T & entry)
		{
			if (is_important_enough())
			{
				_file << entry;
				_file.flush();
			}
			return *this;
		}

		// A specialisation of the operator << for bool.
		template< bool >
		Logger	&operator<<(const bool & entry)
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
		
	private:
		static std::ofstream		_file;
		static log_importance_level	_accepted_importance;
		static pid_t				_process_id;
		static log_type				_type;
		static log_importance_level	_importance;
};

#endif
