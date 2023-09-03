# include "../../includes/Server.hpp"

/*

		311     RPL_WHOISUSER
						"<nick> <user> <host> * :<real name>"
		312     RPL_WHOISSERVER
						"<nick> <server> :<server info>"
		313     RPL_WHOISOPERATOR
						"<nick> :is an IRC operator"
		317     RPL_WHOISIDLE
						"<nick> <integer> :seconds idle"
		318     RPL_ENDOFWHOIS
						"<nick> :End of /WHOIS list"

	BUNLARIN HEPSİ BURADA GÖNDERİLMELİ
*/
void	Server::whois( Client* it, std::vector<std::string> tokenArr )
{
	std::cout << YELLOW << "WHOIS" << END << std::endl;
	int fd = Server::getClientFdByNickname(tokenArr[1]);
	if (fd != -1)
	{
		Client *dest = _clients.at(fd);
		it->sendMessageFd(RPL_WHOISUSER(it->getPrefix(), dest->getNickname(), dest->getUsername(), dest->getHostname(), dest->getRealname())); // Aranan kullanıcı hakkında bilgiyi yazdırır
		it->sendMessageFd(RPL_ENDOFWHOIS(it->getPrefix(), dest->getNickname())); // Arama işleminin bittiğini ifade eder.
	}
	else
		it->sendMessageFd(ERR_NOSUCHNICK(it->getPrefix(), tokenArr[1])); // bu hata mesajı sonrasında whowas döndürüyor //ekrana herhangi bir çıktı vermiyor, whowas döndürdüğünden dolayı sanırım
}