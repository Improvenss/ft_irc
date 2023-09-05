#include "Bot.hpp"

int	main( int argc, char **argv )
{
	try
	{
		Bot	ircBot(argc, argv);
		ircBot.start();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}