1. Donnez la liste des //NOUVEAU, c'est-à-dire les modifications apportées au code de
votre Laboratoire #1.
	
	1.1  Fihcier : Vector.h ligne 35
		J'ai ajouté un contructeur qui prend en paramètre 3 scalaire(x,y et z).
	
	1.2  Fichier : Math3D.h ligne 249
		J'ai ajouter une fonction pour les matrices à coordonné homogène qui permet de facilement changer
		la collonne de translation.

	1.3 Fichier : Math3d.h ligne 263
		J'ai ajouter une fonction pour pouvoir facilement ajouter des points3d dans des matrices de points3d.


2. Répondez aux trois questions suivantes :
	Question 1. Quelle étape de l'algorithme ICP nécessite le plus de calcul ? Que pourrait-on
	faire pour améliorer cette étape ?

	Je pense que devoir calculer le centre géométrique du nuage de points à chaque itération nécessite plusieurs calculs.
	On pourrait garder les centres géométriques des deux nuages de points et appliquer la matrice de transformation 
	pour obtenir le centre de la prochaine itération.

	Question 2. Lorsqu'on utilise le modèle sphère, pourquoi n'obtient-on pratiquement jamais
	une erreur de 0 ?

	Les nuages de points arrive à un minimum local. Icp pense dont avoir trouvé la solution idéale mais ce n'est pas le cas.
	Lorsque le centre géométrique des deux nuages de points de la sphére s'aligne, il devient impossible pour icp de trouver 
	une rotation qui permetterait d'aligner tous les points.

	Question 3. Si dès le départ, on connaît la correspondance exacte entre les points des deux
	nuages, est-ce que le nombre d'itérations nécessaires à l'ICP est affecté ? En faudrait-il
	autant, plus ou moins? Justifiez.
	
	Si on connaît la correspondance exacte entre les points des deux nuages, le nombre d'itérations nécessaires à l'ICP devrait 
	réduire. Si on peut aligner la majorité des points avant de faire des itérations ICP, on peut s'assurer d'avoir un alignement
	très acceptable puiqu'on ne pourra pas tomber dans un minimum local.