[_KopiecFibonacciego_][1]
=

    Struktura danych realizująca operacje kolejki priorytetowej,
    składająca się z kolekcji drzew z porządkiem kopcowym.
    Kopce te mają lepszy czas zamortyzowany, niż wiele innych implementacji kolejek priorytetowych,
    w tym kopce binarne i dwumianowe.

_Dlaczego Fibonacciego?_:
    
    TODO
   _Zlozonosc_:
   
      Dla kopców Fibonacciego operacja znalezienia minimum zajmuje czas stały (O(1)) w sensie zamortyzowanym. Podobnie jak operacje wstawiania oraz zmniejszania klucza. 
      Usuwanie elementu (najczęściej jest używany w specjalnym przypadku usuwania minimalnego elementu) działa w czasie zamortyzowanym O(log n), gdzie n to rozmiar stosu.
      

_Operacje do zaimplementowania_:
- **push()** -> wstawia element do kopcawstawia element do kopca
- **pop()** -> usuwa i zwraca wartość najmniejszego elementu
- **top()** -> zwraca wartość najmniejszego elementu
- **size()** -> zwraca liczbę elementów na stosie
- **decrease-key()** -> zmniejsza wartość elementu
- **remove()** -> usuwa element

_Pytanie dodatkowe_:

>Proszę przedstawić proces dodawania elementów 1, 2, …, 10 a następnie operacji remove (delete-min).

[1]: https://www.wikiwand.com/pl/Kopiec_Fibonacciego
