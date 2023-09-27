#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/ipProcessing.h"

#define IP_STR_MAX 16
#define HEX_STR_MAX 12
#define BIN_STR_MAX 36
#define LINE_MAX 80

void to_hex(unsigned char octet, char *output) {
    sprintf(output, "%02X", octet);
}

void to_binary(unsigned char octet, char *output) {
    for (int i = 7; i >= 0; i--) {
        output[7-i] = (octet & (1 << i)) ? '1' : '0';
    }
    output[8] = '\0';
}

void list_ips(int env) {
    FILE *file = fopen("../include/ips.txt", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier.");
        return;
    }

    char line[LINE_MAX];
    char original_ip[IP_STR_MAX];
    char hex_ip[HEX_STR_MAX];
    char bin_ip[BIN_STR_MAX];
    int i = 1;

    while (fgets(line, sizeof(line), file)) {
        if (3 == sscanf(line, "%15[^/]/%11[^/]/%35[^/]", original_ip, hex_ip, bin_ip)) {
            if(env == 1){
                printf("%d - %s\n", i, original_ip);
            }else{
                printf("%d- %s \n%s \n%s\n", i, original_ip, bin_ip, hex_ip);
            }
            i++;
        } else {
            fprintf(stderr, "Erreur de format pour la ligne: %s\n", line);
        }
    }
    fclose(file);
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
    char hex[HEX_STR_MAX];
    char bin[BIN_STR_MAX];
    char temp[3];
    char tempBin[9];

    hex[0] = '\0';
    bin[0] = '\0';

    for(int j = 0; j < 4; j++) {
        unsigned char octet = ip.octets[j];
        to_hex(octet, temp);
        strcat(hex, temp);
        if (j < 3) strcat(hex, ".");

        to_binary(octet, tempBin);
        strcat(bin, tempBin);
    }

    if(is_valid_ip(ip)) {
        FILE *file = fopen("../include/ips.txt", "a");
        // Écrire l'adresse en format décimal
        fprintf(file, "%d.%d.%d.%d", ip.octets[0], ip.octets[1], ip.octets[2], ip.octets[3]);
        // Écrire l'adresse en format hexadécimal
        fprintf(file, "/%s", hex);
        // Écrire l'adresse en format binaire
        fprintf(file, "/%s", bin);
        fclose(file);
    } else {
        printf("L'adresse IP saisie n'est pas valide.\n");
    }
}

void add_mask(ip_addr mask) {
    if(is_valid_ip(mask)) {
        FILE *file = fopen("../include/ips.txt", "a");
        fprintf(file, "/%d.%d.%d.%d\n", mask.octets[0], mask.octets[1], mask.octets[2], mask.octets[3]);
        fclose(file);
    } else {
        printf("Le masque de sous-reseau saisi n'est pas valide.\n");
    }
}

void delete_ip(int index) {
    FILE *file = fopen("../include/ips.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier.");
        return;
    }
    char line[LINE_MAX];
    int i = 1;
    FILE *tempFile = fopen("../include/temp.txt", "w");
    while (fgets(line, sizeof(line), file)) {
        if (i != index) {
            fputs(line, tempFile);
        }
        i++;
    }
    fclose(file);
    fclose(tempFile);
    remove("../include/ips.txt");
    rename("../include/temp.txt", "../include/ips.txt");
    printf("Adresse IP supprimee.\n");
}
