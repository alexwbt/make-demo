#include <net/server.h>

#include <string_message.pb.h>

class ServerCallback : public net::ServerCallback
{
    std::weak_ptr<net::Server> server_;

public:
    ServerCallback(std::weak_ptr<net::Server> server)
        : server_(server) {}

    void OnClientConnect(std::shared_ptr<net::Connection> c) override
    {
        std::cout << "New client(" << c->GetId() << ") connected." << std::endl;
    }

    void OnClientDisconnect(std::shared_ptr<net::Connection> c) override
    {
        std::cout << "Client(" << c->GetId() << ") disconnected." << std::endl;
    }

    void OnMessage(std::shared_ptr<const net::Packet> packet) override
    {
        if (packet->header.body_size == 0)
            return;

        auto message = std::make_shared<proto::StringMessage>();
        if (message->ParseFromArray(packet->body->data(), static_cast<int>(packet->body->size())))
        {
            if (auto server = server_.lock())
            {
                auto predicate = [packet](net::Connection &c)
                {
                    return c.GetId() != packet->connection_id;
                };
                server->SendToAllIf(predicate, 1, message);
            }
            std::cout << message->message() << std::endl;
        }
    }
};

int main()
{
    constexpr uint16_t kPort = 5625;
    auto server = std::make_shared<net::Server>(kPort);
    auto success = server->Start();
    if (!success)
    {
        std::cout << "Failed to start server." << std::endl;
        return -1;
    }
    std::cout << "Server started on port " << kPort << std::endl;

    ServerCallback callback(server);
    while (true)
    {
        server->Update(callback);
    }

    server->Stop();
}
