# fsDB

This project is still a prototype under construction.

The idea is to develop a non-relational database, NoSQL, where it will be possible to access it using the websocket protocol.

A javascript library to assist in database handling, running queries, inserts etc, full CRUD will also be developed.

And the first version will be complete after the administrative panel is finalized, where it will be possible to generate authentication keys, creating users and access levels etc.

Not sure if FSDB will be the name of the final version, for now is this.

#Dependencies

##NoPoll Library:

 - See here how to install - http://www.aspl.es/nopoll/html/nopoll_core_library_manual.html
 
##After Installing nopoll library

##Ubuntu:
   - aptitude search libwebsocket
   - apt-get install libwebsockets.x86_64 libwebsockets-devel.x86_64 
   - ln -s /usr/local/lib/libnopoll.so.0 /usr/lib/libnopoll.so.0

##Fedora:
  - dnf search libwebsocket
  - dnf install libwebsockets.x86_64 libwebsockets-devel.x86_64
  - cp /usr/local/lib/libnopoll* /usr/lib64/
  - cp /usr/local/lib/pkgconfig/nopoll.pc /usr/lib64/pkgconfig/
