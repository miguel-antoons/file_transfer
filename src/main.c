#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_transfer/sender.h"
#include "file_transfer/receiver.h"


typedef struct {
    bool sender;
    char dest_ip[15];
    char listen_ip[15];
    int port;
    char filename[256];
} options_t;


void print_help(char* program_name) {
    printf("Usage: %s [-s|-r] [-d DEST_IP] [-p PORT] [-f FILENAME]\n", program_name);
    printf("  -s, --send        : send file\n");
    printf("  -r, --receive     : receive file\n");
    printf("  -d, --destination : destination IP address to send the file to\n");
    printf("  -l, --listen      : listening IP address (only when receiving files, when specifying -r). Default is 0.0.0.0\n");
    printf("  -p, --port        : port on which to send/receive the files\n");
    printf("  -f, --filename    : filename of the file to send to remote host\n");
    printf("  -h, --help        : print this help message\n");
}


void set_options(options_t* options, int argc, char* argv[]) {
    if (argc < 2) {
        printf("[-]Error: no arguments provided\n");
        exit(1);
    }

    // set default values
    options->sender = false;
    sprintf(options->dest_ip, "%s", "\0");
    sprintf(options->listen_ip, "%s", "0.0.0.0\0");
    options->port = 49152;

    int current_arg = 1;
    while (current_arg < argc) {
        if (strcmp(argv[current_arg], "-s") == 0 || strcmp(argv[current_arg], "--send") == 0) {
            options->sender = true;
        } else if (strcmp(argv[current_arg], "-r") == 0 || strcmp(argv[current_arg], "--receive") == 0) {
            options->sender = false;
        } else if (strcmp(argv[current_arg], "-d") == 0 || strcmp(argv[current_arg], "--destination") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -d requires an argument\n");
                exit(1);
            }
            sprintf(options->dest_ip, "%s", argv[current_arg]);
        } else if (strcmp(argv[current_arg], "-p") == 0 || strcmp(argv[current_arg], "--port") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -p requires an argument\n");
                exit(1);
            }
            options->port = atoi(argv[current_arg]);
        } else if (strcmp(argv[current_arg], "-f") == 0 || strcmp(argv[current_arg], "--filename") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -f requires an argument\n");
                exit(1);
            }
            sprintf(options->filename, "%s", argv[current_arg]);
        } else if (strcmp(argv[current_arg], "-h") == 0 || strcmp(argv[current_arg], "--help") == 0) {
            print_help(argv[0]);
            exit(0);
        } else if (strcmp(argv[current_arg], "-l") == 0 || strcmp(argv[current_arg], "--listen") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -l requires an argument\n");
                exit(1);
            }
            sprintf(options->listen_ip, "%s", argv[current_arg]);
        } else {
            printf("[-]Error: unknown argument %s\n", argv[current_arg]);
            exit(1);
        }
        current_arg++;
    }
}


// verify that the options are consistent with each other
void verify_options(options_t* options) {
    if (options->sender && strcmp(options->dest_ip, "") == 0) {
        printf("[-]Error: destination IP (-d) is required when specifying -s (when sending)\n");
        exit(1);
    }
    if (options->sender && strcmp(options->filename, "") == 0) {
        printf("[-]Error: filename (-f) is required when specifying -s (when sending)\n");
        exit(1);
    }
}


int main(int argc, char *argv[]) {
    // get options and verify that they are consistent
    options_t options;
    set_options(&options, argc, argv);
    verify_options(&options);

    printf("sender: %d\n", options.sender);
    printf("port: %d\n", options.port);

    // start sender or receiver according to received options
    if (options.sender) {
        printf("dest_ip: %s\n", options.dest_ip);
        printf("filename: %s\n", options.filename);
        sender(options.dest_ip, options.port, options.filename);
    } else {
        printf("listen_ip: %s\n", options.listen_ip);
        receiver(options.listen_ip, options.port);
    }

    return 0;
}
