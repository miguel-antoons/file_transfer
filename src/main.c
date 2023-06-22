#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_transfer/sender.h"
#include "file_transfer/receiver.h"


typedef struct {
    bool sender;
    char dest_ip[15];
    int port;
    char filename[256];
} options_t;


void set_options(options_t* options, int argc, char* argv[]) {
    if (argc < 2) {
        printf("[-]Error: no arguments provided\n");
        exit(1);
    }

    options->sender = false;
    sprintf(options->dest_ip, "%s", "");
    options->port = 49152;
    int current_arg = 1;

    while (current_arg < argc) {
        if (strcmp(argv[current_arg], "-s") == 0) {
            options->sender = true;
        } else if (strcmp(argv[current_arg], "-r") == 0) {
            options->sender = false;
        } else if (strcmp(argv[current_arg], "-d") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -d requires an argument\n");
                exit(1);
            }
            sprintf(options->dest_ip, "%s", argv[current_arg]);
        } else if (strcmp(argv[current_arg], "-p") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -p requires an argument\n");
                exit(1);
            }
            options->port = atoi(argv[current_arg]);
        } else if (strcmp(argv[current_arg], "-f") == 0) {
            current_arg++;
            if (current_arg >= argc) {
                printf("[-]Error: -f requires an argument\n");
                exit(1);
            }
            sprintf(options->filename, "%s", argv[current_arg]);
        } else if (strcmp(argv[current_arg], "-h") == 0) {
            printf("Usage: %s [-s|-r] [-d DEST_IP] [-p PORT] [-f FILENAME]\n", argv[0]);
            exit(0);
        } else {
            printf("[-]Error: unknown argument %s\n", argv[current_arg]);
            exit(1);
        }
        current_arg++;
    }
}


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
    options_t options;
    set_options(&options, argc, argv);
    verify_options(&options);

    printf("sender: %d\n", options.sender);
    printf("dest_ip: %s\n", options.dest_ip);
    printf("port: %d\n", options.port);
    printf("filename: %s\n", options.filename);

    if (options.sender) {
        sender();
    } else {
        receiver();
    }

    return 0;
}
