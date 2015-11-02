# Corba

Corba est un standard normalisant l'accés à des objets à distance. 
Évolution du modèle des RFC.

##Modèle objet de Corba

Client <-> Interface <-> Serveur

Le serveur stocke des objets (non défini dépend du langage).
Le client a une référence sur l'objet qu'il souhaite manipuler. 
	* Séparation de l'interface et de son implémentation
	* Requêtes / Méchanisme synchrone
	* Sémantique d'invocation

####Exemple : contrat d'assurance-vie
Contrat d'assurance qui doit rester disponible sur une longue durée.
Les programmes sont stockés sur des serveurs, il y a longtemps, avec 
des langages anciens (cobol), sous architecture (MVS/CICS). Peu de 
choses en commun entre les serveurs et les clients. Représentation 
abstraite des données différentes par exemple.  
Autre exemple : Applications codés par des physiciens en Fortran

=> Utilisation de **Corba** pour dialoguer entre ces **deux mondes**.

## Le langage de description d'interface - IDL

* Dans Corba tout est IDL
* Proche du C++
* Mapping

Mapping permet d'avoir une API portable

Opération = identificateur + paramètres + valeur de retour + 
sémantique d'invocation + exceptions + contexte

* Paramètres in/out/inout
* Sémantique d'invocation. Méthodes oneway => synchrone

### Syntaxe du langage
Voir PDF....

### Services du noyau de l'ORB
Voir PDF....

### Mapping vers Java
* Référence CORBA : `classe org.omg.CORBA.Object`
* Interface IDL : `interfaceHelper` et `interfaceHolder`

##### Types:
* Types simples (correspondances directes) (long -> int)
* Types complexes -> classes Java

##### Exceptions : 

##### Passages en arguments : 
* Paramètres IN : 
	`long write(in long p);` devient `int write(int p);`
* Paramètres OUT/INOUT : 
	Passage par valeur, sauf pour les objets => classe Holder
	`long ioctl(inout long param);` devient `int ioctl(IntHolder param);`
