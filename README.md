

# Projekt: Symulator Wypożyczalni Aut w C++

- [Projekt: Symulator Wypożyczalni Aut w C++](#projekt-symulator-wypoyczalni-aut-w-c)
   * [Roadmap](#roadmap)
   * [Demo](#przykładowa-demonstracja-symulatora)
   * [Instrukcja obsługi](#instrukcja-obsługi)
   * [Cel Projektu](#cel-projektu)
   * [Główne Funkcjonalności](#główne-funkcjonalności)
   * [Diagram UML](#diagram-uml)

## Roadmap

- [ ] Praca nad interfejsem użytkownika - @mlewko #3
- [ ] Praca nad symulacją systemu, klasa ``Simulation`` - @jmuszyns #4
- [ ] Implementacja klas projektu
   - [x] Wstępny wybór i implementacja klas - @mlewko
   - [x] Refaktoryzacja i dalsza praca - @jmuszyns
   - [ ] Implementacja klas dziediczących ``User`` & ``Admin`` #1
   - [ ] Implementacja klas dziediczących ``Car`` & ``Truck`` #1
   - [ ] Modyfikacja klas ``Vehicle`` & ``Customer`` #1
- [ ] Implementacja testów jednostkowych
   - [x] Wstępne testy obecnie używanych klas - @all
- [ ] Obsługa wyjątków
   - [ ] W obrębie symulacji - @jmuszyns
   - [ ] W obrębie interfejsu użytkownika - @mlewko
- [ ] wydajne zarządzanie wskaźnikami (unique pointers) #2
- [ ] dokumentacja - @all
- [~] Implementacja interfejsu graficznego

## Przykładowa demonstracja symulatora

```
Wed Jun  5 20:09:47 2024

1. New customer registered: Freedman Issitt - fissitt18@mediafire.com
2. New rental opened: Freedman Issitt - fissitt18@mediafire.com rented
        Vehicle: Nissan License Plate: WI87174 Rental Rates: 10.98$
        Location ID: 29 Name: 7th
        Address: Trailsway Street Västerås
        Duration: 4 hours
3. Scheduled maintenance for Vehicle: BMW License Plate: WK28161 Rental Rates: 50.71$
        Location ID: 16 Name: Lakewood Gardens
        Address: Miller Street Boli
4. Finished maintenance for: Vehicle: MINI License Plate: WY05310 Rental Rates: 39.54$
        Location ID: 13 Name: Corben
        Address: Mccormick Street Pedro Carbo

Wed Jun  5 22:09:47 2024

1. New customer registered: Stearn Boyce - sboyce2q@google.co.uk
2. New rental opened: Stearn Boyce - sboyce2q@google.co.uk rented
        Vehicle: Mitsubishi License Plate: WR00649 Rental Rates: 51.24$
        Location ID: 56 Name: Mandrake
        Address: Eagan Street Mali
        Duration: 8 hours
3. Rental closed: Garreth Nielson - gnielson8@google.ca returned
        Vehicle: Mitsubishi License Plate: WT95467 Rental Rates: 29.92$
        Location ID: 27 Name: David
        Address: Corry Street Yanghe
        Total Cost: 119.68 $
4. Scheduled maintenance for Vehicle: Mitsubishi License Plate: WP43062 Rental Rates: 29.69$
        Location ID: 25 Name: Forest Run
        Address: Raven Street Gīvī

Customer Summary Report
-------------------------
Customer: Garreth Nielson - gnielson8@google.ca
Total Rentals: 2
Total Cost: 264.65$
Total Rental Duration: 11.00 hours
Average Rental Duration: 5.50 hours
-------------------------
Customer: Irene Guille - iguilleh@friendfeed.com
Total Rentals: 2
Total Cost: 514.00$
Total Rental Duration: 12.00 hours
Average Rental Duration: 6.00 hours
-------------------------
Customer: Rianon Daughton - rdaughton13@sphinn.com
Total Rentals: 1
Total Cost: 322.02$
Total Rental Duration: 6.00 hours
Average Rental Duration: 6.00 hours
-------------------------
Customer: Freedman Issitt - fissitt18@mediafire.com
Total Rentals: 1
Total Cost: 43.92$
Total Rental Duration: 4.00 hours
Average Rental Duration: 4.00 hours
-------------------------
Customer: Stearn Boyce - sboyce2q@google.co.uk
Total Rentals: 1
Total Cost: 409.92$
Total Rental Duration: 8.00 hours
Average Rental Duration: 8.00 hours
-------------------------

Vehicle Summary Report
--------------------
Vehicle: Buick License Plate: WA65431
Total Rentals: 0
Total Cost: 0.00$
Total Maintenance Count: 1
--------------------
Vehicle: Toyota License Plate: WY09795
Total Rentals: 1
Total Cost: 322.02$
Total Maintenance Count: 0
--------------------
```

## Instrukcja obsługi

```bash
cd build
cmake ..
make
./MyProject
```

## Cel Projektu
Celem projektu jest stworzenie aplikacji w języku C++, która symuluje działanie wypożyczalni samochodów. Aplikacja będzie umożliwiać zarządzanie flotą pojazdów, klientami oraz procesem wypożyczania i zwracania samochodów.

## Główne Funkcjonalności
1. **Zarządzanie Flotą Pojazdów**
   - Dodawanie nowych pojazdów do floty.
   - Usuwanie pojazdów z floty.
   - Aktualizacja danych pojazdu (np. stanu technicznego, dostępności).
   - Wyświetlanie listy dostępnych pojazdów.

2. **Zarządzanie Klientami**
   - Dodawanie nowych klientów do systemu.
   - Usuwanie klientów.
   - Aktualizacja danych klientów (np. danych kontaktowych, historii wypożyczeń).
   - Wyświetlanie listy klientów.

3. **Proces Wypożyczania i Zwrotu Pojazdów**
   - Wypożyczanie pojazdu przez klienta.
   - Rejestracja zwrotu pojazdu.
   - Obliczanie kosztów wypożyczenia na podstawie czasu wypożyczenia i cennika.
   - Wyświetlanie historii wypożyczeń dla poszczególnych klientów i pojazdów.

4. **Raportowanie i Statystyki**
   - Generowanie raportów o stanie floty (np. liczba dostępnych pojazdów, pojazdy w naprawie).
   - Generowanie statystyk dotyczących wypożyczeń (np. najczęściej wypożyczane pojazdy, najbardziej aktywni klienci).


## Diagram UML
<img src = "figures/diagram.png" width = "80%">




