# Projekt 2: Gra w oczko

## Opis Projektu

Celem projektu jest opracowanie i implementacja prostej gry karcianej, zwanej "grą w oczko". Gra odbywa się za pomocą standardowej talii kart, a zasady rozgrywki są dostosowane do potrzeb użytkownika.

## Zasady Gry

- W grze może uczestniczyć od 1 do 3 graczy "ludzkich" oraz od 1 do 3 graczy "komputerowych".
- Gra używa standardowej talii kart (52 karty, bez jokerów), która jest potasowana na początku.
- Każdy gracz zaczyna grę z dwiema kartami.
- Gracze mogą:
  - Dobrać jedną kartę.
  - Spasować - gracze, którzy spasowali, nie wykonują akcji w kolejnych turach.
  
**Uwaga:** Gracze, którzy mają 21 punktów lub więcej, automatycznie spasują.

### Punktacja Kart

| Figura | 2  | 3  | ... | 10 | Walet | Dama | Król | As  |
|--------|----|----|-----|----|-------|------|------|-----|
| Punkty | 2  | 3  | ... | 10 | 2     | 3    | 4    | 11  |

### Warunki Zwycięstwa

- Gracze, którzy zgromadzą 21 punktów, wygrywają.
- Jeśli żaden gracz nie ma 21 punktów, wygrywa ten, który ma najwięcej punktów, ale nie więcej niż 21.
- Jeśli wszyscy gracze mają ponad 21 punktów, wszyscy przegrywają.

## Etapy Projektu

### Etap 1: Wstępne Opracowanie

**Klasy: Karta, Kasyno i Gracz**

1. **Klasa Kasyno**
   - Inicjalizuje talię 52 kart.
   - Potrafi potasować talię.
   - Wydaje karty graczom, zapewniając, że każda karta może być wydana tylko raz.

2. **Klasa Gracz**
   - Posiada do 10 kart.
   - Śledzi ilość kart oraz ich łączną punktację.
   - Posiada metodę `wezKarte(Karta * _karta)` do przyjmowania kart.
   - Może wyświetlić posiadane karty.

3. **Relacja Kasyno-Gracz**
   - Kasyno składa się z dwóch obiektów klasy Gracz.
   - Metoda `graj` rozdaje karty graczom i wyświetla ich ręce.

### Etap 2: Interfejs Użytkownika

1. **Dwustronna Relacja Gracz-Kasyno**
   - Gracz ma świadomość o kasynie, które go stworzyło.
   - Gracz decyduje, czy dobiera kartę, czy pasuje.
   - Kasyno rozdaje karty tylko na początku gry, a następne karty w zależności od decyzji gracza.

2. **Określenie Zwycięzcy**
   - Kasyno określa, który gracz wygrał, gdy wszyscy gracze spasują.

### Etap 3: Strumienie – Zabezpieczenia i Pliki

1. **Zabezpieczenia Strumienia**
   - Wprowadzenie zabezpieczeń wejścia przy wprowadzaniu danych przez użytkownika.

2. **Atrybut Nazwa Gracza**
   - Klasa Gracz zawiera atrybut na nazwę gracza (maks. 20 znaków).

3. **Zapis Stanu Po Grze**
   - Klasa Kasyno zawiera metodę zapisującą stan gry do pliku tekstowego w formie tabeli.

4. **Operator `<<` dla Karty**
   - Dla ambitnych: utwórz przeciążony operator, który umożliwia wypisywanie obiektów klasy Karta w strumieniu.

### Etap 4: Gracze Komputerowi

1. **Klasa Gracz Komputerowy**
   - Klasa pochodna od Gracz, implementująca prostą sztuczną inteligencję.
   - Gracze komputerowi podejmują decyzje o dobieraniu kart w oparciu o zdefiniowany limit punktów (atrybut "odwaga").
   - Gracz komputerowy nie ma nazwy, a jedynie numer (np. "Bot1").
