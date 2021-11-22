/*
  ==============================================================================

    HTTPServer.cpp
    Created: 19 Aug 2018 10:46:25pm
    Author:  Matthias Pueski

  ==============================================================================
*/

#include "HTTPServer.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "MessageBus/MessageBus.h"

juce::String makeResponse(juce::String message) {
    juce::String header = "";
    header += "HTTP/1.1 200 OK\r\n";
    header += "Content-Type:text/html\r\n";

    juce::String body = "";
    body += "<html><head><title>Jam App</title></head><body><h1>Jam App</h1><p>";
    body += message;
    body += "</p></body></html>\r\n";

    header += "Content-Length:"+juce::String(body.length())+"\r\n\r\n";

    return header + body;
}

HTTPServer::HTTPServer() : juce::Thread("Server") {

}

HTTPServer::HTTPServer(int port) : juce::Thread("Server") {
    this->port = port;
    socket = new juce::StreamingSocket();
    socket->bindToPort(port);
    socket->createListener(port);
    juce::Logger::getCurrentLogger()->writeToLog("Server startup");
    running = true;
}

HTTPServer::~HTTPServer() {
    stop();
    if (clientSocket != nullptr) {
        delete clientSocket;
    }
    delete socket;
}

void HTTPServer::run() {


    while(running) {

        if (clientSocket == nullptr) {
            clientSocket = socket->waitForNextConnection();
            sleep(10);
        }
        else {
            if (!clientSocket->isConnected()) {
                clientSocket->connect("127.0.0.1", port);
                juce::Logger::getCurrentLogger()->writeToLog("Client connected");
            }
            else {
                clientSocket->waitUntilReady(false, 10000);
                int bytes = clientSocket->read(buffer, 1024, false);

                juce::String request = juce::String(buffer,bytes);

                juce::StringArray tokens;
                tokens.addTokens (request, "\n","");

                for (int i=0; i<tokens.size(); i++)
                {
                    juce::Logger::getCurrentLogger()->writeToLog(tokens[i]);
                }

                printf("\n %d \n", tokens.size());

                if (tokens.size() == 0) {
                    juce::String response = makeResponse("Error. Empty Request");
                    clientSocket->write(response.toRawUTF8(),response.length());
                } else {
                    juce::String response = makeResponse("Server is running :)");
                    clientSocket->write(response.toRawUTF8(),response.length());
                }

                clientSocket->close();
                delete clientSocket;
                clientSocket = nullptr;
            }
        }

        sleep(10);

    }

}




void HTTPServer::stop() {
    running = false;
    if(clientSocket != nullptr) {
        if (clientSocket->isConnected()) {
            clientSocket->close();
        }
    }
    if (socket->isConnected()) {
        socket->close();
    }
}
