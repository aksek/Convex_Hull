# Wyznaczenie powłoki wypukłej zbioru punktów w przestrzeni trójwymiarowej

### Autorzy:
Aniela Kosek, Maciej Kowalski

### Możliwe polecenia aktywacji programu
Komendę uruchamiającą program należy wykonać z głównego poziomu repozytorium (nie z poziomu katalogu bin).

````````
./nazwa_programu  (tryb)[1 , 2, 3] (algorytm)[n – naiwny, i – inkrementalny, g – gift wrapping, q - quickhull] (parametry specyficzne dla trybu) (dokładność)[1,2,3...n]
````````

Parametry specyficzne dla trybu:

Tryb 1:
``````
(ścieżka do pliku wejściowego)[/...] 
``````
Tryb 2:
``````
(sposób generacji danych)[n - rozkład normalny, c - sześcian, s - kula] (ilość 			punktów)[3,4...n] (zasięg)[1,2...n]
``````
Tryb 3:
``````
(liczba punktów na wykresie)[1,2...n] (liczba powtórzeń dla punktu na wykresie)[1,2...n] (minimalna liczba punktów)[3,4...n] (maksymalna liczba punktów)[3,4...n]
```````
Plik wyjściowy zapisywany jest w pliku output.txt w katalogu data.


### Konwencja danych wejściowych i wyjściowych
Dane wejściowe:
``````
X,	Y,	Z

x1,	y1,	y2

.

.

.

xn,	yn,	zn
`````````
Dane wyjściowe:
`````````
X,	Y,	Z,	I,	J,	K

X1,	y1,	z1,	i1,	j1,	k1

.

.

.

xn,	yn,	zn,	im,	jm,	km
`````````

n - liczba punktów

m - liczba trójkątów należących do powłoki

x, y, z - współrzędne punktów

i, j, k – indeksy punktów tworzących trójkąty należące do powłoki.


### Metody rozwiązania
Program rozwiązuje zadanie przy pomocy następujących algorytmów:
* algorytm naiwny - najprostszy algorytm, sprawdzający wszystkie możliwości
* algorytm giftwrapping - algorytm wykorzystujący wcześniej zidentyfikowane ściany otoczki do znajdowania kolejnych 
* algorytm przyrostowy - algorytm wykorzystujący strukturę grafową do reprezentacji otoczki wypukłej, dodający wierzchołki w losowej kolejności
* algorytm quickhull - algorytm podobny do przyrostowego, wybierający najbardziej korzystne punkty do dodania do otoczki wypukłej

### Przewodnik po plikach źródłowych
Wszystkie pliki nagłówkowe znajdują się w katalogu include, wszystkie pliki implementacyjne znajdują się w katalogu src.

Implementacje algorytmów:
* gift_wrapping
* incremental_solver
* naive_solver
* quickhull_solver

Struktury danych:
* Edge
* Face
* Plane
* Point
* Polyhedron
* Triangle
* Vector
* Vertex

Klasy pomocnicze:
* comparator
* data_converter
* data_generator
* preprocessing
* timer

Skrypty w Pythonie realizujące wizualizację wyników (src):
* visualize.py
* time.py
