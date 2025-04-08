#!/bin/bash
# Ce script lance x fois la commande ./philo 5 800 200 200 7 
# et stocke chaque sortie dans le dossier "log" :
# - Un fichier logX pour chaque exécution
# - Un fichier "log" cumulant toutes les sorties
# 🚀💾

# Vérifier que l'utilisateur a fourni le nombre d'exécutions
if [ "$#" -ne 1 ]; then
    echo "Utilisation : $0 nombre_d_execution 🔢"
    exit 1
fi

nombre_exec=$1

# Création du dossier "log" s'il n'existe pas 🚧
if [ ! -d "log" ]; then
    mkdir log
fi

# Réinitialiser le fichier global et afficher un message de démarrage 🎬
echo "=== Début des exécutions === 🏁" > log/log

# Boucle de 1 à nombre_exec pour lancer les commandes
for (( i=1; i<=nombre_exec; i++ )); do
    echo "Exécution numéro $i 🚀" | tee -a log/log
    # Exécution de la commande et stockage dans "log/logX"
    ./philo 5 800 200 200 7 > "log/log$i"
    # Ajout de la sortie du fichier logX dans le log global
    cat "log/log$i" | tee -a log/log
    echo "-------------------------- 🔻" | tee -a log/log
done

echo "=== Exécutions terminées 🎉 ===" | tee -a log/log

