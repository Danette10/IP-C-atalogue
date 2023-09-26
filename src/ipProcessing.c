#include <stdio.h>
#include "../headers/ipProcessing.h"

void check_file(FILE *file) {
    if(file == NULL) {
        file = fopen("../include/ips.txt", "w");
        fclose(file);
    }
}

int is_valid_ip(ip_addr ip) {
    for(int i = 0; i < 4; i++) {
        if(ip.octets[i] < 0 || ip.octets[i] > 255) {
            return 0;
        }
    }
    return 1;
}

void add_ip(ip_addr ip) {
    if(is_valid_ip(ip)) {
        check_file(fopen("../include/ips.txt", "r"));
        FILE *file = fopen("../include/ips.txt", "a");
        fprintf(file, "%d.%d.%d.%d", ip.octets[0], ip.octets[1], ip.octets[2], ip.octets[3]);
        fclose(file);
    }else{
        printf("L'adresse IP saisie n'est pas valide.\n");
    }
}

void add_mask(ip_addr mask) {
    if(is_valid_ip(mask)) {
        FILE *file = fopen("../include/ips.txt", "a");
        fprintf(file, "/%d.%d.%d.%d\n", mask.octets[0], mask.octets[1], mask.octets[2], mask.octets[3]);
        fclose(file);
    }else{
        printf("Le masque de sous-réseau saisi n'est pas valide.\n");
    }
}