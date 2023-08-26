#include "../includes/Server.hpp"

void	Server::cap( Client* it, std::string message )
{
	std::cout << YELLOW << "CAP" << END << std::endl;
	if (message.length() == 6 && message.compare("LS 302") == 0)
	{
		std::string response = "CAP * LS :multi-prefix sasl";
		response += "\r\n";
		std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		send(it->getFd(), response.c_str(), response.size(), 0);
	}
	if (message.length() == 17 && message.compare("REQ :multi-prefix") == 0)
	{
		std::string response = "CAP * ACK multi-prefix";
		response += "\r\n";
		std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		send(it->getFd(), response.c_str(), response.size(), 0);
	}
	if (message.length() == 3 && message.compare("END") == 0)
	{
		//it->setFirstContact();
		//std::string response = "001 " + it->getNickname() + " :Welcome to the HELL " + it->getNickname();
		//response += "\r\n";
		//std::string a = "x";
		//std::string response = RPL_WELCOME(it->getNickname());
		//std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		//send(it->getFd(), response.c_str(), response.size(), 0);
		std::cout << "BOŞ" << std::endl;
	}
}

void	Server::join( Client* it , std::string message )
{
	std::cout << YELLOW << "JOIN" << END << std::endl;
	if (it->getRegistered() == false)
	{
		std::cout << "BOŞ" << std::endl;
		//std::string response = ":" + it->getUsername() + " JOIN :" + "HELL" + "\r\n";
		//std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		//send(it->getFd(), response.c_str(), response.size(), 0);
	}
	else
	{
		std::string response = ":" + it->getUsername() + " JOIN :" + message + "\r\n";
		std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		send(it->getFd(), response.c_str(), response.size(), 0);
	}
	////size_t channelStart = message.find(":");
	////std::string channelName = message.substr(channelStart);
	////handleJoinMessage(it->getFd(), channelName);
	//std::string response = ":akaraca JOIN :" + message;
	//response += "\r\n";
	//send(it->getFd(), response.c_str(), response.size(), 0);
	////handleJoinMessage(it->getFd(), asdf);
}

void	Server::nick( Client* it, std::string message )
{
	std::cout << YELLOW << "NICK" << END << std::endl;
	if (it->getRegistered() == false)
	{
		it->setNickname(message);
		std::string response = RPL_WELCOME(it->getNickname());
		std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		send(it->getFd(), response.c_str(), response.size(), 0);
	}
	else
	{
		//std::string response = "You are now known as " + message + "\r\n";
		std::string response = ":" + it->getNickname() + " NICK " + message + "\r\n";
		it->setNickname(message);
		std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		send(it->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Server::privmsg( Client* it, std::string message )
{
	std::cout << YELLOW << "PRIVMSG" << END << std::endl;
	(void)it;
	std::cout << YELLOW "PRIVMSG: " + message << END << std::endl;
	//size_t pos = message.find(' ');
	//std::string target = message.substr(0, pos);
	//std::string text = message.substr(pos + 1);
	//// Örnek: ":John!john@example.com PRIVMSG #channel :Merhaba, nasılsınız?"
	//handlePrivateMessage(it->getFd(), target, text);
}

//"USER akaraca akaraca localhost :Ahmet Karaca" komutu aşağıdaki anlamı taşır:

//Kullanıcı Adı (Username): "akaraca"
//Ana Bilgisayar Adı (Hostname): "akaraca"
//Sunucu Adı (Servername): "localhost" (genellikle boş bırakılır)
//Gerçek İsim (Realname): "Ahmet Karaca"
void	Server::user( Client* it, std::string message )
{
	std::cout << YELLOW << "USER" << END << std::endl;
	if (it->getRegistered() == false)
	{
		size_t pos = 0;
		int i = 0;
		while ((pos = message.find(' ')) != std::string::npos)
		{
			if (i == 0)
			{
				it->setUsername(message.substr(0, pos));
				std::cout << "Username:>" << it->getUsername() << std::endl;
				message.erase(0, pos + 1);
			}
			if (i == 1)
			{
				it->setHostname(message.substr(0, pos));
				std::cout << "Hostname:>" << it->getHostname() << std::endl;
				message.erase(0, pos + 1);
			}
			if (i == 2)
			{
				it->setServername(message.substr(0, pos));
				std::cout << "Servername:>" << it->getServername() << std::endl;
				message.erase(0, pos + 1);
			}
			i++;
			if (i == 3)
			{
				it->setRealname(message.substr(1, message.length() - 1));
				std::cout << "Realname:>" << it->getRealname() << std::endl;
				break;
			}
		}
		std::string response = "Welcome to the server!";
		response += "\r\n";
		std::cout << YELLOW << "Response:>" + response << "<" << std::endl;
		send(it->getFd(), response.c_str(), response.size(), 0);
	}
}