#if !defined(Sender_hpp)
#define Sender_hpp

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "EventInfo.hpp"

class Sender {
 private:
  int _kq;

  // Constructor
 public:
  Sender(int kq) : _kq(kq) {}

  // Method
 private:
  void _registerEvent(int to_fd, int from_fd);
  void _deleteEvent(EventInfo& event_info);

  // Interface
 public:
  void sendClient(std::vector<EventInfo*>& event_list);
  void callCgi(EventInfo& event_info);
};

#endif  // Sender_hpp
