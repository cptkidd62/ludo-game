# Opis klas

## App

Główna klasa zarządzająca aplikacją - odpowiada za menu główne. Posiada listę użytkowników (obiekt klasy UsersList). Tworzy obiekty klas Match i Stats.

## Match

Klasa zarządzająca rozgrywką. Odpowiada za mechanikę i reprezentację graficzną gry. Przechowuje wskaźniki na obiekty graczy (Player*).

## Player

Klasa abstrakcyjna reprezentująca gracza.

### HumanPlayer

Podklasa Playera dla gracza kierowanego przez użytkownika. Przechowuje wskaźnik na dane użytkownika.

### AIPlayer

Abstrakcyjna podklasa Playera reprezentująca gracza kierowanego przez komputer.

### NormalAIPlayer, SimpleAIPlayer

Podklasy AIPlayera odpowiedzialne za różne strategie gracza komputerowego.

## Stats

Klasa odpowiadająca za wyświetlanie okna ze statystykami użytkownika. Przechowuje w tym celu obiekty klasy StatsView.

## StatsView

Klasa, która na podstawie obiektu klasy UserData tworzy dla niego reprezentację graficzną w SFML. Dziedziczy po sf::Drawable.

## UsersList

Klasa do zarządzania listą wszystkich użytkowników. Przechowuje id i imiona użytkowników w mapie. Umożliwia zapisywanie danych do pliku i wczytywanie ich z niego.

## UserData

Klasa do zarządzania informacjami na temat danego użytkownika oraz jego statystykami. Umożliwia zapisywanie danych do pliku i wczytywanie ich z niego.