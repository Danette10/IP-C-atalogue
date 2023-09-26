typedef struct {
    int octets[4];
} ip_addr;

// Fonction qui vérifie si une adresse IP est valide
int is_valid_ip(ip_addr ip);

// Fonction qui ajoute l'adresse IP saisie par l'utilisateur dans un fichier
void add_ip(ip_addr ip);

// Fonction qui ajoute le masque de sous-réseau saisie par l'utilisateur à la suite de l'adresse IP dans le fichier
void add_mask(ip_addr mask);