#!/bin/bash

# Parcourir chaque fichier .c et .h dans le dossier courant
find . -name "*.c" -o -name "*.h" | while read file; do
    echo "Vérification de $file"
    betty "$file"
done
