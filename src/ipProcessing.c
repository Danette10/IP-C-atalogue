#include <stdio.h>
#include <string.h>
#include "../headers/ipProcessing.h"

void list_ips() {
    FILE *file = fopen("../include/ips.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier.");
        return;
    }
    char line[40];
    int i = 1;
    while (fgets(line, 40, file) != NULL) {
        char *token = strtok(line, "/");
        printf("%d- %s\n", i, token);
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
    if(is_valid_ip(ip)) {
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
