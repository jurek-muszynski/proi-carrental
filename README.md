

# Projekt: Symulator Wypożyczalni Aut w C++

- [Projekt: Symulator Wypożyczalni Aut w C++](#projekt-symulator-wypoyczalni-aut-w-c)
   * [Instrukcja obsługi](#instrukcja-obsługi)
   * [Cel Projektu](#cel-projektu)
   * [Główne Funkcjonalności](#główne-funkcjonalności)
   * [Diagram UML](#diagram-uml)



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