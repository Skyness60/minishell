# Minishell

Minishell est un projet de l'école 42 qui consiste à recréer un shell minimaliste en C, inspiré de Bash --POSIX. Il permet d'exécuter des commandes simples avec gestion des redirections, des pipelines et des signaux, tout en respectant des normes strictes de codage de l'école 42.

## Comprendre le shell et son rôle
- Le shell est une interface utilisateur pour interagir avec le système d'exploitation.
- Il traduit les commandes textuelles de l'utilisateur en instructions compréhensibles pour le noyau.

### Fonctionnement du shell (simplifié)
- L'utilisateur entre une commande (par exemple : ls).-
- Le shell analyse la commande et communique avec le noyau.-
- Le noyau exécute la commande et renvoie le résultat au shell.-
- Le shell affiche le résultat à l'utilisateur.

![image](https://github.com/user-attachments/assets/ba4784c2-b326-4fd7-91fa-d6e570c51968)


## Qu'est-ce que le noyau ( Kernel ) ?

### Le noyau est le cœur du système d'exploitation. Il gère directement les ressources matérielles comme :

- Le processeur (exécution des instructions).
- La mémoire (allocation et gestion des espaces mémoire).
- Le stockage (lecture et écriture sur le disque).
- Les périphériques (clavier, écran, etc.).

### Le shell ne communique jamais directement avec le matériel : c'est toujours le noyau qui s'en charge.
## Interaction shell ↔ noyau
- Le shell utilise des appels système pour demander au noyau d'exécuter des tâches spécifiques (comme execve pour lancer un programme).

### Exemple d'appel système dans Minishell :

    execve("/bin/ls", args, env);


## Fonctionnalités

### Exécution de commandes : 
- Supporte les commandes système avec arguments. ( ls, cat, grep etc )

### Builtins : Implémentation des commandes suivantes :      
- echo : avec l'option -n.
- cd : avec un chemin relatif ou absolu.
- pwd : affiche le répertoire courant.
- export : gestion des variables d'environnement.
- unset : suppression des variables d'environnement.
- env : affiche les variables d'environnement.
- history : affiche l'historique des commandes et avec l'option -c de le supprimer.
- exit : termine le shell.

### Gestion des redirections :
- < : redirection d'entrée.
- > : redirection de sortie (écrasement).
- >> : redirection de sortie (ajout).

### heredoc :
- Support du heredoc avec limiter, la possibilité de pas faire plus de 17 heredoc

### Pipelines :
- Support des commandes enchaînées avec |.

### Gestion des variables d'environnement :
- Remplacement des variables avec $.
- Gestion de la variable spéciale $?.

### Gestion des signaux :
- Réagit correctement aux signaux Ctrl+C, Ctrl+D, et Ctrl+\ comme Bash.

### Erreurs gérées :
- Messages d'erreur cohérents pour les commandes ou redirections invalides.

### Garbage collector : 
- Utilisation d'un système de gestion de la mémoire personnalisé.

### Garbage Descriptor : 
- Utilisation d'un système de gestion des fds personnalisé.

## Installation et utilisation
### Prérequis
- GCC ou un compilateur C compatible.
- Une distribution Linux ou macOS.
- Make.

### Installation

### Clonez le projet et compilez avec make :

    git clone https://github.com/<ton-utilisateur>/minishell.git
    cd minishell
    make

### Utilisation

### Lancez le shell avec :

    ./minishell

### Exemples de commandes dans Minishell :

    echo "Hello, World!"
    export VAR=test
    echo $VAR
    ls -l | grep minishell > output.txt
    cat < output.txt
    exit

### Structure du projet

    src/ : Contient le code source principal.
    include/ : Contient les fichiers d'en-tête.
    Makefile : Fichier pour la compilation.
    README.md : Ce fichier.

# Contributeurs
- [jlebard07](https://github.com/jlebard07)
- [Skyness](https://github.com/Skyness60)
