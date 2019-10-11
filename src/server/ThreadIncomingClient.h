//
// Created by facundotorraca on 10/10/19.
//

#ifndef MICROMACHINES_THREADINCOMINGCLIENT_H
#define MICROMACHINES_THREADINCOMINGCLIENT_H


class ThreadIncomingClient {
    ProtectedQueue& incoming_players;
    std::thread thread{};
    Socket socket;
    bool dead;

    public:
        ThreadIncomingClient(Socket&& socket, ProtectedQueue& incoming_players);

        void start();

        void join();

        bool answered();

        void wait_answer();
};


#endif //MICROMACHINES_THREADINCOMINGCLIENT_H
