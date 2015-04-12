#include <iostream>
#include <malamute.h>

zactor_t *server;

void startUp() {
  server=zactor_new(mlm_server, NULL);
  zstr_sendx (server, "BIND", "tcp://127.0.0.1:9999", NULL);
}

void shutDown() {
  zactor_destroy(&server);
}

int main(void ) {
  startUp();
  mlm_client_t *client=mlm_client_new();
  char *topic, *content;
  int rc=mlm_client_connect(client, "tcp://127.0.0.1:9999", 2000, "");
  assert ( rc == 0);
  std::cout << "client 1 sent; client 2 should now receive!" << std::endl;
  mlm_client_sendforx(client, "ManagerGive", "gotit", "", NULL);
  mlm_client_destroy(&client);

  client=mlm_client_new();
  rc=mlm_client_connect(client, "tcp://127.0.0.1:9999", 2000, "");
  assert ( rc == 0);
  std::cout
    << "client 2 connected, now telling broker want ManagerGive:got* msgs" << std::endl;
  mlm_client_set_worker(client, "ManagerGive", "got*");
  std::cout << "client 2 about to recvx..." << std::endl;
  mlm_client_recvx(client, &topic, &content, NULL);
  std::cout << "client 2 received" << std::endl;
  assert(!strcmp(content, "gotit"));
  mlm_client_destroy(&client);
  shutDown();
}
