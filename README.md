# Elewatory
Zadanie na przedmiot "Algorytmy i Struktury Danych"

do zadania został wykorzystany kopiec fibonacciego

Oryginalna treść zadania

Elewatory

W kilku elewatorach przechowywane jest ziarno. Należy napisać program, który obsługuje elewatory. Możliwe operacje to

    napełnianie i rozładunek zboża,
    wypisanie masy zboża w elewatorze.

Wejście
W pierwszej linii znajdują się dwie liczby n i m. Pierwsza z nich, to liczba elewatorów, a druga, to liczba operacji do wykonania.
W kolejnej linii znajduje się n liczb reprezentujące początkową masę zboża w każdym z elewatorów.
W następnych m liniach znajdują się operacje:

    napełnienie elewatora n nr_elewatora masa 
    napełnienie elewatora zawierającego najmniej zboża nm masa     
    napełnienie elewatora zawierającego najwięcej zboża nM masa     
    rozładunek elewatora r nr_elewatora masa     
    rozładunek elewatora zawierającego najmniej zboża rm masa     
    rozładunek elewatora zawierającego najwięcej zboża rM masa 
    wypisanie masy zboża w elewatorze w nr_elewatora     
    wypisanie masy zboża w elewatorze zawierającym najmniej zboża wm
    wypisanie masy zboża w elewatorze zawierającym najwięcej zboża wM
    

gdzie nr_elewatora to numer elewatora (liczba całkowita nieujemna, mniejsza od n), a masa to masa zboża (liczba całkowita nieujemna).

Całkowita masa zboża w każdym elewatorze nie przekracza 2000000000. Jeśli masa rozładunku zboża jest większa niż ilość masa zboża w elewatorze, to końcowa masa jest równa zero. Jeśli jest kilka elewatorów o najmniejszej/największej masie zboża, to wybieramy ten, o najmniejszym numerze. Elewator z najmniejszą ilością zboża to taki, który jest niepusty i zawiera najmniejszą masę ziarna. Jeśli wszystkie elewatory są puste, to pierwszy (indeks 0) elewator zawiera najmniejszą/największą masę zboża.
Wyjście
Przykład

Wejście
3 11 \n
2 0 4 \n
nm 5 \n
w 0 \n
wm \n
wM \n
r 2 10 \n
w 2 \n
wm \n
r 0 10 \n
w 0 \n
nm 10 \n
w 0 \n

Wyjście
7 \n
4 \n
7 \n
0 \n
7 \n
0 \n
10 \n

