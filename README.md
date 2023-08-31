# File Transfer

Program allows 2 users to transfer files fast over LAN as fast as possible.

## Installation

### Linux

### Windows

Not available yet, coming soon...

## Usage

The program can be used in two modes: server mode and client mode.
In server mode, the client can only receive files from other clients while in client mode, the program can only send files to a server.  

To transfer a file from one host to another using this program, the host sending the file must use the program in client mode while the host sending the file must be activated in server mode.  

The general usage of this program is specified below.

```bash
./transfer [-s|-r] [-d DEST_IP] [-f FILENAME]
```

### Server mode

In server mode, the program awaits a client to open a connection and receive a file from that client.
At this moment, the program can only receive files from client in server mode. Thus, it cannot send files.

### Client mode

## Sources

The code in this repository is mainly based on the following source : <https://idiotdeveloper.com/file-transfer-using-tcp-socket-in-c/>
