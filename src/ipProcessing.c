#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/ipProcessing.h"


void to_hex(unsigned char octet, char *output) {
    sprintf(output, "%02X", octet);
}

void to_binary(unsigned char octet, char *output) {
    for (int i = 7; i >= 0; i--) {
        output[7-i] = (octet & (1 << i)) ? '1' : '0';
    }
    output[8] = '\0';
}

void list_ips() {
    FILE *file = fopen("../include/ips.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier.");
        return;
    }
    char line[40];
    char original_line[40]; // Nouvelle chaîne pour copier la ligne originale
    int i = 1;

    while (fgets(line, 40, file) != NULL) {
        strncpy(original_line, line, sizeof(original_line)); // Copiez la ligne originale

        char *token = strtok(line, "/");

        // Pour convertir en hexa et binaire
        char hex[12], bin[36];
        unsigned char octet;
        char temp[3], tempBin[9];

        hex[0] = '\0';
        bin[0] = '\0';

        for(int j = 0; j < 4; j++) {
            if(j > 0) {
                token = strtok(NULL, ".");
            }
            octet = atoi(token); // Convertit le token en int
            to_hex(octet, temp);
            strcat(hex, temp);
            if (j < 3) strcat(hex, ".");

            to_binary(octet, tempBin);
            strcat(bin, tempBin);
            if (j < 3) strcat(bin, ".");
        }

        printf("%d- \n%s \n%s \n%s\n", i, strtok(original_line, "/"), bin, hex);
        i++;
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
    char hex[12], bin[36];
    char temp[3], tempBin[9];

    hex[0] = '\0';
    bin[0] = '\0';

    for(int j = 0; j < 4; j++) {
        unsigned char octet = ip.octets[j];
        to_hex(octet, temp);
        strcat(hex, temp);
        if (j < 3) strcat(hex, ".");

        to_binary(octet, tempBin);
        strcat(bin, tempBin);
        if (j < 3) strcat(bin, ".");
    }

    if(is_valid_ip(ip)) {
        FILE *file = fopen("../include/ips.txt", "a");
        // Écrire l'adresse en format décimal
        fprintf(file, "%d.%d.%d.%d", ip.octets[0], ip.octets[1], ip.octets[2], ip.octets[3]);
        // Écrire l'adresse en format hexadécimal
        fprintf(file, " %s", hex);
        // Écrire l'adresse en format binaire
        fprintf(file, " %s\n", bin);
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
    char line[40];
    int i = 1;
    FILE *tempFile = fopen("../include/temp.txt", "w");
    while (fgets(line, 40, file) != NULL) {
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
