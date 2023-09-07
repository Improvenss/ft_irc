# include "../../includes/Server.hpp"

void	Server::cap( Client* it, std::vector<std::string> tokenArr ) // OK
{
	std::cout << YELLOW << "CAP" << END << std::endl;

	if (it->getIRCstatus() != CONNECTING)
	{
		it->sendMessageFd(RPL_NOTICE(it->getPrefix(), it->getNickname(), "Client's status is insufficient."));
		return ;
	}

	if (!tokenArr.at(0).compare("CAP")
			&& !tokenArr.at(1).compare("LS")
			&& !tokenArr.at(2).compare("302"))
		it->sendMessageFd("CAP * LS :multi-prefix sasl");

	if (!tokenArr.at(0).compare("CAP")
			&& !tokenArr.at(1).compare("REQ")
			&& !tokenArr.at(2).compare(":multi-prefix"))
		it->sendMessageFd("CAP * ACK multi-prefix");

	if (!tokenArr.at(0).compare("CAP")
			&& !tokenArr.at(1).compare("END"))
	{
		it->setIRCstatus(HANDSHAKE);
		it->sendMessageFd(RPL_NOTICE(it->getPrefix(), it->getNickname(), "Client status is now: HANDSHAKE."));
	}
}