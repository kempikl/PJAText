#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void empty() {
    std::cout << "***********************************PJAText***********************************\n" << '\n' <<
    "Narzędzie służy do operacji na plikach tekstowych zapisanych w formacie ANSI.\n" <<
    "W celu sterowania działaniem programu należy uruchomić go z odpowiednim parametrem.\n" << '\n' <<
    "Dostępne są następujące opcje:\n" << '\n' <<
    "-f [sciezka_do_pliku]    Wczytuje plik źródłowy\n" <<
    "(Ten parametr musi zostać określony jako pierwszy)\n" << '\n' <<
    "-n      Wyświetla liczbę lini pliku źródłowego\n" << '\n' <<
    "-d      Wyświetla liczbę wszystkich cyfr w pliku źródłowym\n" << '\n' <<
    "-dd     Wyświetla liczę cyfr oddzielonych znakami białymi\n" << '\n' <<
    "-c      Wyświetla liczbę znaków w pliku źródłowym\n" << '\n' <<
    "-s      Wyświetla wszystkie słowa z pliku w kolejności alfabetycznej\n" << '\n' <<
    "-rs     Wyświetla wszystkie słowa z pliku w kolejności odwrotnej do alfabetycznej\n" << '\n' <<
    "-a      Wyświetla anagramy słów podanych za parametrem\n" <<
    "(Ten parametr musi zostać określony jako ostatni)\n" << '\n' <<
    "-p      Wyświetla palindromy słów podanych za parametrem\n" <<
    "(Ten parametr musi zostać określony jako ostatni)\n" << '\n' <<
    "-o [sciezka_do_pliku]    Zapisuje dane wyjściowe do pliku o podanej ścieżce\n" << '\n' <<
    "-i [sciezka_do_pliku]    Przyjmuje dane wejściowe z pliku o podanej ścieżce";
}

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::stringstream output;

    if (args.empty()) {
        empty();
    } else {
        for (const auto& x : args) {
            std::cout << '[' << x << "]\n";
        }
    }
    std::cout << output.str();
}
