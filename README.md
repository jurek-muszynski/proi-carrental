

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
Sun Jun  2 21:28:05 2024

1. New customer registered: Artemis Eastabrook - aeastabrook27@addthis.com

Sun Jun  2 23:28:05 2024

1. New customer registered: Cirillo Walbrun - cwalbrun2c@myspace.com
2. New rental opened: Artemis Eastabrook - aeastabrook27@addthis.com rented
        Vehicle: GMC License Plate: MT80587 Rental Rates: 57.3
        Location ID: 9 Name: Sutherland
        Address: 6th Street Cashel
        Duration: 4 hours

Mon Jun  3 01:28:05 2024

1. New customer registered: Tedra Benezet - tbenezet2m@is.gd

Mon Jun  3 03:28:05 2024

1. New customer registered: Hillie Adolthine - hadolthine26@dropbox.com
2. Rental closed: Artemis Eastabrook - aeastabrook27@addthis.com returned
        Vehicle: GMC License Plate: MT80587 Rental Rates: 57.3
        Location ID: 9 Name: Sutherland
        Address: 6th Street Cashel
        Total Cost: 229.2 $
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




