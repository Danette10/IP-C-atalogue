#define IP_STR_MAX 16
#define HEX_STR_MAX 12
#define BIN_STR_MAX 36
#define LINE_MAX 80

typedef struct {
    int octets[4];
} ip_addr;

typedef struct {
    ip_addr* ips;
    size_t size;
} IPArray;

// Fonction qui convertit un octet en hexadécimal
void to_hex(unsigned char octet, char *output);

// Fonction qui convertit un octet en binaire
void to_binary(unsigned char octet, char *output);

// Fonction qui affiche toutes les adresses IP du fichier
void list_ips(int env);

// Fonction qui vérifie si une adresse IP est valide
int is_valid_ip(ip_addr ip);

// Fonction qui ajoute l'adresse IP saisie par l'utilisateur dans un fichier
void add_ip(ip_addr ip);

// Fonction qui ajoute le masque de sous-réseau saisie par l'utilisateur à la suite de l'adresse IP dans le fichier
void add_mask(ip_addr mask);

// Fonction qui supprime une adresse IP du fichier
void delete_ip(int index);

// Fonction qui convertit une adresse IP saisie par l'utilisateur en une structure ip_addr
ip_addr str_to_ip_addr(const char* ip_str);

// Fonction qui initialise un tableau d'adresses IP
void init_ip_array(IPArray* arr);

// Fonction qui ajoute une adresse IP à un tableau d'adresses IP
void append_to_ip_array(IPArray* arr, ip_addr ip);

// Fonction qui applique un masque de sous-réseau à une adresse IP
ip_addr apply_mask(ip_addr ip, ip_addr mask);

// Fonction qui libère la mémoire allouée à un tableau d'adresses IP
void free_ip_array(IPArray* arr);

// Fonction qui recherche les adresses IP similaires à celle saisie par l'utilisateur
void search_similar(ip_addr ip, ip_addr mask, int env);