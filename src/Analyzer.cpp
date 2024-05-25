#include "Analyzer.h"

Analyzer::Analyzer() { }

Analyzer::~Analyzer() { }

std::map<std::string, int>* Analyzer::getMap(std::string url) {
  return this->analizeHTML(this->getHTML(url));
}

std::map<std::string, int>* Analyzer::analizeHTML(std::string html) {
  std::regex regex_tag("<([^>]*)>");
  std::smatch matches;
  std::string::const_iterator begin = html.cbegin();
  std::string::const_iterator end = html.cend();
  std::map<std::string, int>* tags = new std::map<std::string, int>;
  while (std::regex_search(begin, end, matches, regex_tag)) {
    auto it = tags->find(matches[1].str());
    if (it == tags->end()) {
      tags->insert({ matches[1].str(), 1 });
    } else {
      it->second++;
    }
    begin = matches.suffix().first;
  }
  return tags;
}

std::string Analyzer::getHTML(std::string url) {
  Socket* socket = new Socket('s');
  socket->Connect(url.c_str(), "80");
  std::string request
      = "GET / HTTP/1.1\r\nHost: " + url + "\r\n" + "Connection: close\r\n\r\n";
  socket->Send(request.c_str(), request.length());
  char buffer[4096];
  size_t byteRecv = socket->Recv(buffer, sizeof(buffer));
  std::string response(buffer, byteRecv);
  delete socket;
  return response;
}

void Analyzer::sendMessage(std::map<std::string, int>* tags, Mailbox& mailbox) {
  Message_t* message = new Message_t;
  message->data = (void*)tags;
  message->sender_pid = getpid();
  mailbox.SendMsg(message);
}