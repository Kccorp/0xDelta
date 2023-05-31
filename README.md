##0xDelta
Ce challenge est orienté crypto. Il consiste à trouver le flag en analysant le code d'un chiffrement fait en Python pour retrouver la clé utilisée pour le chiffrement AES.

##Scénario
J'ai intercepté une étrange chaîne de caractères. Voilà ce que j'ai pu récupérer :

Download: main.py / Output.txt

##Write-up
La première étape est d'analyser le code Python donné. On peut s'apercevoir que le code utilise l'algorithme AES CBC 128 bits pour chiffrer le flag.

Le deuxième fichier est une sortie valide de ce code (probablement le flag chiffré).

Dans le code Python, la variable "plaintext" a été effacée et la clé de déchiffrement est exprimée en fonction du temps lors du lancement du programme.

Nous comprenons que le format de temps est "%y-%m-%d%H:%M:%S" et par chance nous avons la date de l'écriture du programme en haut du fichier, soit le 31-05-2023.

Il ne nous manque plus que l'heure exacte à laquelle le programme a été exécuté. Dans le fichier Output.txt, nous avons ce qui ressemble à un log de retour avec donc l'heure et les minutes indiquées.

Il ne nous manque plus que les secondes et pour cela nous allons bruteforcer sur les 60 possibilités pour déchiffrer notre message.

Après formatage, nous avons la date suivante : 23-05-3115:44:??

Nous essayons donc toutes les secondes de 00 à 59 et après quelques secondes, nous obtenons un résultat à la 30e seconde.

Nous obtenons donc à 23-05-3115:44:30 pour la chaîne 32332d30352d333131353a34343a333067cc5db0367794df11c080b01aec64ca380a6f75dba147e7b670a67385643dfb

Le flag suivant est : {«D¯Ó±qPÆqA40xD{D3l7a_Crypt} Soit une fois nettoyé 0xD{D3l7a_Crypt}.
