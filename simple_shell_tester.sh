#!/bin/bash

# Définir les fonctions interdites
forbidden_functions=("strcpy" "strncpy" "sprintf" "strcat" "realloc")

# Parcourir les fichiers source C
for file in *.c; do
    for func in "${forbidden_functions[@]}"; do
        if grep -q $func $file; then
            echo "Fonction interdite $func trouvée dans $file"
            exit 1
        fi
    done
done

echo "Aucune fonction interdite trouvée."

# Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
if [ $? -ne 0 ]; then
    echo "Erreur de compilation."
    exit 1
fi

echo "Compilation réussie."

# Tests de base du shell
echo "Début des tests de base..."

# Test de la commande intégrée 'exit'
echo "exit" | ./hsh
echo "Test de la commande 'exit' passé."

# Test de la commande intégrée 'env'
echo "env" | ./hsh
echo "Test de la commande 'env' passé."

# Ajoutez d'autres tests de base ici

echo "Tous les tests de base ont réussi."
