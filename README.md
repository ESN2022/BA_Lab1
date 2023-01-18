#BA_LAB1

Rapport LAB1


Le but de cette séance de LAB1 est de réaliser un chenillard (8 LEDS de la carte DE10-Lite) présentée ci-dessous.


![image](https://user-images.githubusercontent.com/102004780/213070735-ff4cc793-f635-442c-a331-32448dfb2e4a.png)

Les spécificités sont les suivantes :
  - Utiliser un Bouton poussoir sur la carte pour démmarer le chenillard
  - Utiliser 4 boutons switchs (interrupteurs), présents sur la carte pour faire varier la vitesse du chenillard
 
Du point de vue de la conception du système, les éléments qui suivent seront compris dans le design :
  - Une RAM : stockage des données (40 KB utilisées ici, car dimensionné assez large pour supporter le program exécuté et eviter les "Overflow")
  - Bouton Poussoir et Boutons Switchs
  - CPU : ici le NIOS II (compatible avec notre cible)
  - JTAG (UART) : pour télécharger le programme sur la cible
  - LEDS
  
Lors d'un appuie sur le bouton poussoir, une intérruption est déclenché sur le CPU qui, se charge ensuite de d'éxécuter le program permettant de dérouler le chenillard
Lors d'un appuie sur le bouton_switch_0 le chenillard déroule avec une vitesse v1 (la plus grande), puis un appuie sur bouton_switch_1 le déroule avec une vitesse v2 <  v1. Et ainsi que suite jusuq'au bouton_switch_3 avec des vitesses de déroulerement décroissante au fur et à mesure.
Ces vitesses de déroulement sont en fait cadencées tout simplement en augmentant les temporisations d'allumage entre les LEDS. Dans cette logique, les variations de déroulement qui s'opèrent sur les système sont les suivantes : 
  - bouton_switch_0 : temporisation de 100 ms
  - bouton_switch_1 : temporisation de 200 ms
  - bouton_switch_2 : temporisation de 300 ms
  - bouton_switch_3 : temporisation de 400 ms

![image](https://user-images.githubusercontent.com/102004780/213078801-9d5fcc5b-b05e-479a-9d12-2c8ff858aa63.png)


Le schéma synoptique en vue de la réalisation complète du système est le suivant : 

![image](https://user-images.githubusercontent.com/102004780/213077603-391cc489-4419-4e7d-8363-9f57b59ef5a1.png)


Pour ce faire, il faudra dans un premier temps concevoir l'architecture matérielle du système décris ci-dessus sous le logiciel "Platform Designer" fourni par "QUARTUS". Ainsi, l'architecture matérielle du système conçu à cet effet est présenté ci-dessous : 

![image](https://user-images.githubusercontent.com/102004780/213072245-30e03fe0-bbf2-4cb0-aa83-90a87495dc2f.png)


  - Le pio_0 représente les 8 LEDS utilisées pour le chenillard
  - Le pio_1 représente le Boutton poussoir utilisé pour déclencher le déroulement du chenillard
  - Le pio_2 représente les 4 Boutons switchs utilisés pour la variation de la vitesse du chenillard

Ci-dessous une configuration particulière pour bien spécifier que l'utilisation du bouton poussoir engendrera le déclenchement d'une intérruption. Il faudra en faire de même pour la configuration des 4 boutons switchs sur "Platform Designer".

![image](https://user-images.githubusercontent.com/102004780/213073039-15dad956-0d2e-459c-9fd2-6898b04eb6ea.png)

Ceci étant fait, la deuxième étape consiste à éditer le program VHDL qui s'éxécutera sur le FPGA, en s'assurant de faire les connections correctes des composants du système avec les broches à les signaux adéquats (sans oublier de faire l'assignation des broches dédiés : confère datasheet DE10-Lite). Puis, compiler Hardware sur QUARTUS et charger le "fichier.sof" 

La dernière étape consiste à éditer le code ".c" qui sera exécuter par le CPU.
Il est vous est fourni le fichier main.c sur ma branche GiT, à l'intérieur duquel il y a :
  - le fonctionnement du chenillard simple (sans boutons)
  - le fonctionnement du chenillard déclenché avec le boutons poussoir (sans l'activation des vitesses de déroulement)
  - le fonctionement du chenillard complet

Ci-dessous une vidéo qui présente la démonstration du fonctionneent du système : 



https://user-images.githubusercontent.com/102004780/213080453-015d6b75-99af-4100-8de0-c10916ec91ec.mp4


