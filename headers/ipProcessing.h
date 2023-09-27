typedef struct {
    int octets[4];
} ip_addr;

// Fonction qui convertit un octet en hexadécimal
void to_hex(unsigned char octet, char *output);

// Fonction qui convertit un octet en binaire
void to_binary(unsigned char octet, char *output);

// Fonction qui affiche toutes les adresses IP du fichier
void list_ips();

// Fonction qui vérifie si une adresse IP est valide
int is_valid_ip(ip_addr ip);

// Fonction qui ajoute l'adresse IP saisie par l'utilisateur dans un fichier
void add_ip(ip_addr ip);

// Fonction qui ajoute le masque de sous-réseau saisie par l'utilisateur à la suite de l'adresse IP dans le fichier
void add_mask(ip_addr mask);

// Fonction qui supprime une adresse IP du fichier
void delete_ip(int index);

