# Big Data and technologies

Deux technologies populaires relatives au Big Data

* **Avro** : Mal désigné
* **Thrift** : Meilleur langage/framework

``` 
	//Thrift
	struct MethodRequest {
		1: string foo,
		2: i64 bar,
	}
```

**Intérêt** : Il est possible d'évoluer ces objets petit à petit. 
On peut ajouter des nouveaux champs, et les programmes qui tournent 
avec l'ancienne structure continueront de fonctionner. 
Il est aussi possible de répliquer des serveurs car ils fonctionnent
*sans état*. Meilleure scabilité. 

**Automatiser les tâches** : Lancer 1000 instances de votre serveurs. 
Les problèmes arrivent. (Configuration/rolling updates). Il est nécessaire
d'avoir de l'automatisation de la configuration et des mises à jours. 
Être capable de remonter une infrastucture rapidement en cas de gros soucis
(datacenter qui brûle, Amazon Cloud qui ne peut plus supporter la charge, etc). 
Des outils existent : Puppet, Ansible.

**Chuby** : Développé par Google (repris par Yahoo! dans ZooKeeper).
Zookeeper fournit un système de fichier hautement disponible.
* File System : Znodes avec data et children 
* Znodes éphémères et persistentes. éphèmères n'ont pas d'enfants.
* ZooKeeper ajoute un préfixe incrémenté après chaque création de Znodes
* Znodes ont des `watches` (clients notifiés quand un evnt se passe sur une Znode)
	
**Garanties**:
* Sequentiel consistency
* Atomicity
* Single System Image
* Durability
* Timeless
 
## Storage - Comment stocker beaucoup de données ? 

**Logs** : Données massives utilisés uniquement par les machines
Nécessité d'archiver les métriques, en extrayant préalablement 
les données utiles. 

**Google File System** : système de fichiers distribué. 
Prendre beaucoup de HDD abordable, et distribuer l'espace mémoire.
Sémantique POSIX trop complexe pour les systèmes distribués. Google a 
simplifié. On ne stocke que de gros fichiers, et toujours à la fin. 

**Hadoop** : FS dans la lignée du GFS tiré d'un article scientifique Google. 
Tolérant aux pannes, support de très grand fichiers (1TB)
Les fichiers sont divisés en blocks, écris sur des parties contigus sur le disque. 
Les blocks sont répliqués sur différentes machines. Politique de placement 
des blocks intelligente( != machines, mais aussi sur != "rak") 
les datablocks sont référencé par un `NameNode`

**Écriture** : Le client veut écrire sur un block et demande à la 
`NameNode` pour savoir où sont ces écrits ces blocks. Le client écrit sur le 
premier cluster, et demande ensuite de répliquer sur les autres nodes. 

**Lecture** : La `NameNode` renvoie aussi l'addresse où lire la donnée.  

## Base de données

### 1. Réplication
Un maître écrit sur les autres esclaves. Marche bien si l'on a plus de 
lectures que d'écritures. Possibilité d'arriver rapidement à trop d'écritures
pour le maître. 

### 2. Sharding
Division des ressources. (Charge 1 : A-H // Charge 2 : I-Q // Charge 3 : 
R-Z)

### 3. Sharding+Replication
On divise les charges, et on a aussi un système de maître/esclave.
Marche bien sauf en cas de problèmes. Si la charge maître "tombe", comment
s'assurer que la donnée a été répliqué sur les autres ? 

**Base de donnée classique** : règles ACID

**Brewer's Theorem** : Dans un système distribué on peut choisir uniquement deux
caractéristiques parmi : 
* Cohérence
* Disponibilité
* Tolérence au partitionnement réseau

**Règles pour systèmes distribués** : 
* Basically Available
* Soft State (système en transition d'un état stable à un autre)
* Eventual Consistency (mise à jour d'un noeud, ces modifs se propagent
dans les autres noeuds potentiellement un peu plus tard)

=> Création de NoSQL

## NoSQL
### Introduction

A complèter....

## Analyzing Data
**Lisp** : Functionnal Programmation 

Google's Map Reduce est une généralisation de ce paradigme. 
On travaille sur un couple clé/valeur.
