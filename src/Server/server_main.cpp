#include <fcntl.h>

#include <iostream>
#include <sstream>

#include "EventInfo.hpp"
#include "Receiver.hpp"
#include "Sender.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "plz input only port!" << std::endl;
    return 1;
  }

  int                      kq        = kqueue();
  int                      listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  std::vector<EventInfo *> event_list;  // iter -> free
  Sender                   sender(kq);
  Receiver                 receiver(kq, listen_fd);

  fcntl(listen_fd, F_SETFL, O_NONBLOCK);
  EventInfo    *event_info = new EventInfo(-1, listen_fd);
  struct kevent ev;
  EV_SET(&ev, listen_fd, EVFILT_READ, EV_ADD, 0, 0, event_info);
  kevent(kq, &ev, 1, NULL, 0, NULL);  // ERROR CHECK

  sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(std::atoi(argv[1]));
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int ret;
  ret = bind(listen_fd, SOCKADDR(server_addr), sizeof(server_addr));
  ret = listen(listen_fd, BACKLOG);

  if (ret == -1) {
    std::cout << "Server: bind or listen error" << std::endl;
    return 1;
  }
  std::cout << "Server: listening.." << std::endl;

  while (1) {
    receiver.listen(event_list);
    sender.sendClient(event_list);
    event_list.clear();
  }
}
