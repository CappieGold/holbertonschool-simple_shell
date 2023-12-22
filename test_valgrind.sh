#!/bin/bash

# Nom du programme à tester
PROGRAM="./hsh"

# Options Valgrind
VALGRIND_OPTIONS="--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose"

# Commande à exécuter avec Valgrind
VALGRIND_COMMAND="valgrind $VALGRIND_OPTIONS $PROGRAM"

# Exécution du programme avec Valgrind
echo "Exécution de $PROGRAM avec Valgrind..."
$VALGRIND_COMMAND

# Analyser la sortie de Valgrind ici (optionnel)
# Vous pouvez ajouter des commandes pour analyser et rapporter les résultats
# Par exemple, vous pouvez chercher des chaînes comme "definitely lost"
# pour signaler une fuite de mémoire.
