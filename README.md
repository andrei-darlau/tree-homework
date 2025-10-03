# Tema2 Structuri de Date si Algoritmi

## main.c

### citire argumente
Argumentele se paseaza in linia de comanda, deci trebuie sa ne folosim de argumentele functiei main, argc si *argv[] pentru a putea realiza tema. Cerinta este primul argument dupa ./tema2, un string de forma "-cX". De aici, putem spune ca cerinta este caracterul indexat la 2. Deoarece acesta este un char, il convertim la un integer scazand caracterul 0. Asemanator se citesc si urmatoarele argumente, dar daca cerinta este 2 avem un argument in plus si luam in calcul acest lucru.

### construire arbore
Dupa citirea tuturor argumentelor, initializam valorile initiale ale arborelui si punem prima frunza care va fi '$', apoi citim N si, cand este cazul, M. Citim cele N cuvinte si apelam functia de construire.

### output
Facem un switch, iar pentru fiecare caz apelam functiile necesare.

## functii.c

### addLeaf
Aceasta functie primeste ca argument o pozitie din arbore si un caracter, pentru a adauga in acel loc (daca nu exista deja) un caracter. Pentru a prelucra caracterele avem nevoie de ASCII (constanta 96 = 'a' - 1). De exemplu, daca caracterul este 'b', indexul va fi 'b' - 'a' + 1 == 2, de aceea avem un caz special pentru '$', deoarece acesta nu se afla inaintea lui 'a' pe tabelul ASCII. Daca frunza pe care vrem sa o initializam nu exista, facem alocarile necesare si adaugam caracterul pe pozitia string[0]. Am facut structura cu un string pentru a fi "future-proof", pentru taskul 4.

### buildTree
Aceasta functie "desface" cuvantul primit in toate sufixele posibile, dupa care apeleaza functia addLeaf, folosindu-se de auxiliarul curr pentru a tine cont de pozitia urmatorului caracter.

### printCerinta1
Acesta este mai mult un algoritm pentru grafuri, "Breadth First Search", care parcurge graful (arborele in cazul nostru) pe latime. Declaram o coada, iar apoi doua integer-uri pentru a sti cand coada s-a terminat. Cat timp coada nu s-a terminat, parcurgem toate nodurile de pe nivelul curent si adaugam in coada copiii elementului printat (daca acestia exista). Ne folosim de un boolean hasCharacter pentru a nu printa la inceputul fisierului un '\n'.

### freeArbore
Parcuge recursiv arborele de sus pana jos (un fel de RSD, dar cu mai multi copii pentru ca nu e binar) si elibereaza string si nodul in sine.

### nrLeaves
Acum ca ma gandesc, puteam sa numar cati '$' sunt, dar functia nrLeaves se foloseste de un contor primit ca argument sa numere numarul de frunze. Parcurge toti copiii nodului curent, iar daca acestia nu exista, boolean-ul leaf ramane true. Cand acesta este true, incrementam argumentul leaves.

### suffDimK
Pentru a determina un sufix de dimensiune k, inseamna ca pe nivelul k+1 se afla un dolar, indicand ca sufixul s-a terminat. Parcurgem tot arborele si incrementam nr daca conditia se indeplineste.

### nrDescendants
Numarul maxim de descendants il are clar nodul radacina, deoarece acesta are toate caracterele prezenta in sufixe. Dar am parcurs tot arborele sa ma asigur ca nu sunt depunctat. Ne folosim tot de un argument ca si contor, iar cand numarul curent de descendenti este mai mare, il inlocuim.

### checkSuffix
Parcurgem arborele caracter cu caracter, iar daca reusim sa epuizam caracterele sufixului si nu am intalnit NULL si am intalnit '$' dupa ultimul caracter, inseamna ca sufixul este prezent. In main avem un vector boolean suffixes (e declarat char pentru ca nu am mai schimbat, oricum e acelasi lucru) care tine contor daca sufixele au fost gasite sau nu. Puteam sa fac mai eficient daca faceam asta in switch (nu declaram un vector), dar am vrut ca switch-ul sa fie mai compact.

### printValues
La fel, am vrut ca switch-ul sa fie compact, deci am facut o functie pentru a printa elementele suffixes.

### compressTree
Aceasta functie face compresia arborelui. Daca nodul are doar un copil si nu are '$' dupa el, inseamna ca poate fi "concatenat" cu copilul sau. Declaram un Tree auxiliar, reallocam dimensiunea string-ului si le concatenam, dupa care dam free auxiliarului.

### printCerinta4
Este exact acelasi lucru ca printCerinta1, numai ca aici cand dam fprintf dam la tot string-ul, nu doar la indexul [0]. Aici crapa si valgrind-ul, "invalid read size 1" cand functia fprintf apeleaza strlen. Aceeasi problema e si la bucata comentata cu while, tot "invalid read size 1".

Rezultate pe rularea locala:

## Rezultate locale

Cerinta 1
Statistici_Test  0 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  1 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  2 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  3 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  4 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  5 ................................................. PASS
Cerinta 2
Statistici_Test  0 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  1 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  2 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  3 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  4 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  5 ................................................. PASS
Statistici_Test  6 ................................................. PASS
Statistici_Test  7 ................................................. PASS
Statistici_Test  8 ................................................. PASS
Statistici_Test  9 ................................................. PASS
Cerinta 3
Statistici_Test  0 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  1 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  2 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  3 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  4 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  5 ................................................. PASS
Statistici_Test  6 ................................................. PASS
Statistici_Test  7 ................................................. PASS
Statistici_Test  8 ................................................. PASS
Statistici_Test  9 ................................................. PASS
Cerinta 4
Statistici_Test  0 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  1 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  2 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  3 ................................................. PASS
VALGRIND ........................................................... PASS
Statistici_Test  4 ................................................. PASS
VALGRIND ........................................................... PASS
Cerinta 1 : 30
Cerinta 2 : 20
Cerinta 3 : 20
Cerinta 4 : 25
Total     : 95
Bonus     : 20.0
Felicitari! Ai punctajul maxim: 95p! :)
# tree-homework
