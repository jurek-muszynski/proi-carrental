

# Projekt: Symulator Wypożyczalni Aut w C++

   * [Roadmap](#roadmap)
   * [Demo](#przykładowa-demonstracja-symulatora)
   * [Instrukcja obsługi](#instrukcja-obsługi)
   * [Cel Projektu](#cel-projektu)
   * [Główne Funkcjonalności](#główne-funkcjonalności)
   * [Diagram UML](#diagram-uml)

## Roadmap

- [x] Praca nad interfejsem użytkownika - @mlewko #3
- [x] Praca nad symulacją systemu, klasa ``Simulation`` - @jmuszyns #4
- [ ] Implementacja klas projektu
   - [x] Wstępny wybór i implementacja klas - @mlewko
   - [x] Refaktoryzacja i dalsza praca - @jmuszyns
   - [x] Implementacja klas dziedziczących ``User`` & ``Admin`` #1 - @jmuszyns
   - [x] Implementacja klas dziedziczących ``Car`` & ``Truck`` #1 - @jmuszyns
   - [x] Modyfikacja klas ``Vehicle`` & ``Customer`` #1 - @all
   - [ ] Implementacja klasy ``userInteface`` #3 - @mlewko
- [ ] Implementacja testów jednostkowych
   - [x] Wstępne testy obecnie używanych klas - @jmuszyns
   - [ ] Dalsza praca nad weryfikacją różnych scenariuszy - @mlewko
- [ ] Obsługa wyjątków
   - [ ] W obrębie symulacji - @jmuszyns
   - [x] W obrębie interfejsu użytkownika - @mlewko
- [~] wydajne zarządzanie wskaźnikami (unique pointers) #2
- [ ] dokumentacja - @all
- [~] Implementacja interfejsu graficznego

## Przykładowa demonstracja symulatora

```
Thu Jun  6 15:34:03 2024

1. New customer registered: Armand Clitheroe - aclitheroe2f@newsvine.com
2. Rental closed: Roseanna Sachno - rsachno1s@bravesites.com returned
        Vehicle: Pontiac License Plate: WH49854 Rental Rates: 32.38$
        Location ID: 24 Name: Michigan
        Address: Northridge Street Ron Phibun
        Total Cost: 194.28 $
        Duration: 6 hours
        Distance: 154.59 km
3. Scheduled maintenance for Vehicle: Dodge License Plate: WQ99023 Rental Rates: 19.22$
        Location ID: 5 Name: Judy
        Address: Stuart Street Al Masallamiyya
        Maintained by Admin: Jobie Dictus ID: fae6ad1a-41c7-4984-a7e4-3934e24ae50c

Thu Jun  6 17:34:03 2024

1. New customer registered: Shea Cool - scool11@mozilla.com

Thu Jun  6 19:34:03 2024

1. New customer registered: Penny D'Alessandro - pdalessandro16@biblegateway.com
2. New customer registered: Hillie Adolthine - hadolthine26@dropbox.com
3. New customer registered: Dukey Abel - dabel1k@t-online.de
4. Rental closed: Janka Handmore - jhandmore1f@csmonitor.com returned
        Vehicle: Nissan License Plate: WX44781 Rental Rates: 46.38$
        Location ID: 52 Name: Northwestern
        Address: Northridge Street Ron Phibun
        Total Cost: 417.42 $
        Duration: 9 hours
        Distance: 193.38 km
5. Rental closed: Elena Donett - edonett12@wikispaces.com returned
        Vehicle: Chevrolet License Plate: WE12837 Rental Rates: 41.59$
        Location ID: 17 Name: Pleasure
        Address: Columbus Street Mulchén
        Total Cost: 332.72 $
        Duration: 8 hours
        Distance: 127.26 km
6. Scheduled maintenance for Vehicle: Suzuki License Plate: WI44581 Rental Rates: 43.76$
        Location ID: 64 Name: Moulton
        Address: Buhler Street Cafarnaum
        Maintained by Admin: Tedra Benezet ID: 42772b54-bf50-4479-a4ed-f320502ca9fa

Customer Summary Report
-------------------------
Customer: Gottfried Cheeld - gcheeldo@oaic.gov.au
Total Rentals: 2
Total Cost: 433.89$
Total Rental Duration: 15.00 hours
Average Rental Duration: 7.50 hours
-------------------------
Customer: Quintina Joannic - qjoannicp@amazon.com
Total Rentals: 1
Total Cost: 191.88$
Total Rental Duration: 6.00 hours
Average Rental Duration: 6.00 hours
-------------------------
Customer: Elena Donett - edonett12@wikispaces.com
Total Rentals: 1
Total Cost: 332.72$
Total Rental Duration: 8.00 hours
Average Rental Duration: 8.00 hours
-------------------------
Customer: Janka Handmore - jhandmore1f@csmonitor.com
Total Rentals: 1
Total Cost: 417.42$
Total Rental Duration: 9.00 hours
Average Rental Duration: 9.00 hours
-------------------------
Customer: Roseanna Sachno - rsachno1s@bravesites.com
Total Rentals: 1
Total Cost: 194.28$
Total Rental Duration: 6.00 hours
Average Rental Duration: 6.00 hours
-------------------------

Vehicle Summary Report
--------------------
Vehicle: Lincoln License Plate: WP43799
Total Rentals: 1
Total Maintenance Count: 0
Total Mileage: 84.9358 km
--------------------
Vehicle: Chevrolet License Plate: WE12837
Total Rentals: 1
Total Maintenance Count: 0
Total Mileage: 127.256 km
--------------------
Vehicle: Buick License Plate: WA65431
Total Rentals: 1
Total Maintenance Count: 0
Total Mileage: 67.6749 km
--------------------
```

## Instrukcja obsługi

Symulacja
```bash
cd build
cmake ..
make
./car_rental_simulation
```
Interfejsu użytkownika
```bash
cd build
cmake ..
make
./car_rental
```
testy
```bash
cd build
cmake ..
make
./car_rental_tests
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




