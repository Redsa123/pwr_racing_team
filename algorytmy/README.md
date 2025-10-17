# Dokumentacja Projektu - Algorytmy geometryczne

## Spis treści
1. [Struktura projektu](#struktura-projektu)
2. [Szczegółowy opis plików](#szczegółowy-opis-plików)
3. [Algorytmy](#algorytmy)
4. [Struktury danych](#struktury-danych)
5. [Funkcje](#funkcje)
6. [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
7. [Przykład działania](#przykład-działania)

---

## Struktura projektu

```
projekt/
├── algorythm.h        # Plik nagłówkowy z deklaracjami
├── functions.cpp      # Implementacja algorytmów
├── main.cpp           # Program główny
└── punkty.txt         # Plik wejściowy z danymi
```

---

## Szczegółowy opis plików

### 1. `algorythm.h`

Plik nagłówkowy zawierający deklaracje wszystkich struktur i funkcji używanych w projekcie.

**Stałe:**
- `ZERO = 1e-9` - stała zmienna używana do porównań zmiennoprzecinkowych

**Struktury:**
- `Point` - reprezentacja punktu w przestrzeni 2D
- `Result` - przechowuje wynik wyszukiwania najbliższej pary punktów

**Deklaracje funkcji:**
- Funkcje pomocnicze geometryczne
- Algorytm budowy otoczki wypukłej (build_ring)
- Algorytm minimalnej szerokości (minimal_parallel_width)
- Algorytm najbliższej pary punktów (find_closest_pair)

### 2. `functions.cpp`

Plik z implementacją wszystkich algorytmów.

**Zawiera:**
- Funkcje geometryczne podstawowe
- Implementację algorytmu Grahama
- Implementację algorytmu znajdującego minimalną szerokość otoczki wypukłej
- Implementację algorytmu znajdującego najbliższą parę punktów

### 3. `main.cpp`

Program główny sterujący przepływem wykonania.

**Funkcjonalność:**
- Wczytywanie punktów z pliku
- Wywoływanie poszczególnych algorytmów
- Formatowanie i wyświetlanie wyników

### 4. `punkty.txt`

Plik danych wejściowych.

**Format:**
```
n                    # liczba punktów
x1 y1               # współrzędne pierwszego punktu
x2 y2               # współrzędne drugiego punktu
...
xn yn               # współrzędne n-tego punktu
```

---

## Algorytmy

### 1. Algorytm Grahama

**Cel:** Znalezienie otoczki wypukłej zbioru punktów.

**Złożoność:** O(n log n)

**Kroki algorytmu:**
1. Znajduje punkt o najmniejszej współrzędnej y (punkt bazowy P0)
2. Sortuje pozostałe punkty według kąta polarnego względem P0
3. Usuwa punkty współliniowe, zachowując najdalszy
4. Buduje otoczkę używając stosu:
   - Dodawaj kolejne punkty
   - Usuń punkty tworzące zakręt w prawo (wklęsły)
   - Zachowaj tylko punkty tworzące zakręt w lewo (wypukły)

**Funkcja:** `build_ring(vector<Point> &points)`

### 2. Algorytm znajdujący minimalną szerokość otoczki wypukłej

**Cel:** Znalezienie minimalnej szerokości otoczki wypukłej między równoległymi prostymi.

**Złożoność:** O(n)

**Zasada działania:**
1. Dla każdej krawędzi otoczki wypukłej znajduje punkt najbardziej odległy od prostej zawierającej tę krawędź
2. Oblicza odległość tego punktu od prostej
3. Minimalna z tych odległości to szukana szerokość

**Funkcja:** `minimal_parallel_width(const vector<Point> &ring)`

### 3. Algorytm znajdujący najbliższą parę punktów

**Cel:** Znalezienie najbliższej pary punktów w zbiorze.

**Złożoność:** O(n log n)

**Kroki algorytmu:**
1. Sortuje punkty według współrzędnej x i y
2. Dzieli zbiór na dwie równe części według mediany x
3. Rekurencyjnie znajduje najbliższą parę w lewej i prawej połowie
4. Znajduje najbliższą parę w pasie środkowym (punkty w odległości d od mediany)
5. Zwraca minimum z trzech wyników

**Optymalizacja pasa środkowego:**
- Rozpatruje tylko punkty w odległości d od linii podziału
- Dla każdego punktu sprawdza tylko punkty w oknie o wysokości d

**Funkcja:** `find_closest_pair(vector<Point> &points)`

---

## Struktury danych

### `Point`

Reprezentuje punkt w przestrzeni 2D.

```cpp
struct Point {
    double x;      // współrzędna x
    double y;      // współrzędna y
    int index;     // oryginalny indeks punktu
};
```

### `Result`

Przechowuje wynik wyszukiwania najbliższej pary punktów.

```cpp
struct Result {
    double distance;  // odległość między punktami
    Point p1;         // pierwszy punkt pary
    Point p2;         // drugi punkt pary
};
```

---

## Funkcje

### Funkcje geometryczne podstawowe

#### `vector_dir(Point p0, Point p1, Point p2)`
**Cel:** Oblicza iloczyn wektorowy (cross product) wektorów (p0→p1) i (p0→p2).

**Zwraca:**
- Wartość > 0: zakręt w lewo
- Wartość < 0: zakręt w prawo
- Wartość ≈ 0: punkty współliniowe

**Zastosowanie:** Określanie orientacji trzech punktów.

#### `distance(Point p1, Point p2)`
**Cel:** Oblicza odległość euklidesową między dwoma punktami.

**Wzór:** √[(x₂-x₁)² + (y₂-y₁)²]

#### `point_line_distance(Point P, Point P1, Point P2)`
**Cel:** Oblicza odległość punktu P od prostej przechodzącej przez P1 i P2.

**Wzór:** d = |Ax + By + C| / √(A² + B²)

### Funkcje porównujące

#### `compare_points(Point p1, Point p2)`
Porównuje punkty według kąta polarnego względem P0.

**Kryterium:**
1. Kąt polarny (mniejszy kąt = wcześniej)
2. W przypadku współliniowości - odległość od P0

#### `compare_x(const Point &a, const Point &b)`
Porównuje punkty według współrzędnej x.

#### `compare_y(const Point &a, const Point &b)`
Porównuje punkty według współrzędnej y.

### Funkcje algorytmiczne

#### `build_ring(vector<Point> &points)`
Implementacja algorytmu Grahama.

**Parametry:** Wektor punktów (modyfikowany w miejscu)

**Zwraca:** Wektor punktów tworzących otoczkę wypukłą w kolejności przeciwnej do ruchu wskazówek zegara.

**Przypadki szczególne:**
- Mniej niż 3 punkty: zwraca wszystkie punkty
- Wszystkie punkty współliniowe: zwraca punkty skrajne

#### `minimal_parallel_width(const vector<Point> &ring)`
Wyznacza minimalną szerokość otoczki wypukłej.

**Parametry:** Otoczka wypukła (wynik `build_ring`)

**Zwraca:** Minimalna odległość między równoległymi prostymi wspierającymi otoczkę.

#### `closest_pair_small(const vector<Point> &points, int start, int end)`
Wersja prostsza dla małych zbiorów (≤3 punkty).

#### `closest_pair_strip(const vector<Point> &strip, double d)`
Znajduje najbliższą parę w pasie środkowym.

#### `closest_pair(const vector<Point> &Px, const vector<Point> &Py)`
Znajduje parę punktów o najmniejszej odległości od siebie w zbiorze.

**Parametry:**
- `Px`: punkty posortowane według x
- `Py`: punkty posortowane według y

#### `find_closest_pair(vector<Point> &points)`
Funkcja inicjalizująca dla algorytmu najbliższej pary.

**Wykonuje:**
1. Sortowanie punktów według x i y
2. Wywołanie rekurencyjnej funkcji `closest_pair`

### Funkcje głównego programu

#### `load_points(const string &filename)`
Wczytuje punkty z pliku.

**Format pliku:**
- Pierwsza linia: liczba punktów n
- Kolejne n linii: współrzędne x y

**Zwraca:** Wektor punktów z przypisanymi indeksami.

#### `first_ring(vector<Point> points)`
Oblicza i wyświetla otoczkę wypukłą.

**Format wyjścia:** `Otoczka: (x1, y1), (x2, y2), ...`

#### `second_parallels(vector<Point> points)`
Oblicza i wyświetla minimalną szerokość otoczki.

**Format wyjścia:** `Proste: d=wartość` (4 miejsca po przecinku)

#### `third_pairs(vector<Point> points)`
Znajduje i wyświetla najbliższą parę punktów.

**Format wyjścia:** `Najblizsze Punkty: [(x1, y1), (x2, y2)] d=odległość` (3 miejsca po przecinku)

---

## Kompilacja i uruchomienie

### Kompilacja
```bash
g++ -std=c++11 -o program main.cpp functions.cpp
```

### Uruchomienie
```bash
./program        # Linux/Mac
program.exe      # Windows
```
---

## Przykład działania

### Dane wejściowe (`punkty.txt`)
```
10
-4 2
2.5 1.5
4 3
0 -2
-2 4
4 -1.5
2 2
-2 1
-1 2.5
1 0
```

### Przykładowe wyjście
```
Loaded 10 points from file punkty.txt
Otoczka: (-4.0, 2.0), (-2.0, 4.0), (4.0, 3.0), (4.0, -1.5), (0.0, -2.0)
Proste: d=5.1234
Najblizsze Punkty: [(2.500, 1.500), (2.000, 2.000)] d=0.707
```

### Interpretacja wyników

1. **Otoczka wypukła:** Lista punktów tworzących wielokąt wypukły okalający wszystkie punkty
2. **Minimalna szerokość:** Najmniejsza odległość między równoległymi prostymi zawierającymi otoczkę
3. **Najbliższa para:** Dwa punkty o najmniejszej wzajemnej odległości wraz z wartością tej odległości