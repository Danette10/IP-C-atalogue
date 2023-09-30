#include <stdio.h>
#include "headers/ipProcessing.h"

int main() {
    char choice;

    while (1) {
        printf("\n\n");
        printf(" ::::::::                   ::: ::::::::::: :::     :::        ::::::::   ::::::::  :::    ::: ::::::::::\n");
        printf(":+:    :+:                :+: :+:   :+:   :+: :+:   :+:       :+:    :+: :+:    :+: :+:    :+: :+:    :+: \n");
        printf("+:+                      +:+   +:+  +:+  +:+   +:+  +:+       +:+    +:+ +:+        +:+    +:+ +:+\n");
        printf("+#+++   +#++:++#++:++ +#++:++#++: +#+ +#++:++#++: +#+       +#+    +:+ :#:        +#+    +:+ +#++:++#\n");
        printf("+#+                     +#+     +#+ +#+ +#+     +#+ +#+       +#+    +#+ +#+   +#+# +#+    +#+ +#+\n");
        printf("#+#    #+#              #+#     #+# #+# #+#     #+# #+#       #+#    #+# #+#    #+# #+#    #+# #+#\n");
        printf(" ########               ###     ### ### ###     ### ########## ########   ########   ########  ##########\n");
        printf("a - Add a new IP address\n");
        printf("l - List IP addresses\n");
        printf("s - Search similar by mask\n");
        printf("d - Delete an IP\n");
        printf("q - Quit\n");
        printf("Choice : \n");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a': {
                ip_addr ip;
                ip_addr mask;
                printf("Enter address : \n");
                scanf("%d.%d.%d.%d", &ip.octets[0], &ip.octets[1], &ip.octets[2], &ip.octets[3]);
                printf("Enter mask : \n");
                scanf("%d.%d.%d.%d", &mask.octets[0], &mask.octets[1], &mask.octets[2], &mask.octets[3]);
                add_ip(ip);
                add_mask(mask);
                break;
            }
            case 'd': {
                int index;
                list_ips(1);
                printf("0 - Cancel\n");
                printf("Enter index : \n");
                scanf("%d", &index);
                if (index == 0) {
                    break;
                }else{
                    delete_ip(index);
                }
                break;
            }
            case 'l': {
                list_ips(0);
                break;
            }
            case 's': {
                ip_addr ip;
                ip_addr mask;
                printf("Enter address : \n");
                scanf("%d.%d.%d.%d", &ip.octets[0], &ip.octets[1], &ip.octets[2], &ip.octets[3]);
                printf("Enter mask : \n");
                scanf("%d.%d.%d.%d", &mask.octets[0], &mask.octets[1], &mask.octets[2], &mask.octets[3]);
                search_similar(ip, mask, 0);
                break;
            }
            case 'q': {
                return 0;
            }
            default: {
                printf("Invalid choice\n");
                break;
            }
        }
    }
    return 0;
}
