#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

struct Flags {
    bool is_newlines{};
    bool is_digits{};
    bool is_numbers{};
    bool is_chars{};
    bool is_anagrams{};
    bool is_palindroms{};
    bool is_sorted{};
    bool is_reverse{};
    bool is_output{};

    std::string output_patch;
};

void if_empty(){
    std::cout << "***********************************PJAText***********************************\n" << '\n' <<
    "Narzędzie służy do operacji na plikach tekstowych zapisanych w formacie ANSI.\n" <<
    "W celu sterowania działaniem programu należy uruchomić go z odpowiednim parametrem.\n" << '\n' <<
    "Dostępne są następujące opcje:\n" << '\n' <<
    "-f [sciezka_do_pliku]    Wczytuje plik źródłowy\n" <<
    "Ten parametr musi zostać określony jako pierwszy!\n" << '\n' <<
    "-n      Wyświetla liczbę lini pliku źródłowego\n" << '\n' <<
    "-d      Wyświetla liczbę wszystkich cyfr w pliku źródłowym\n" << '\n' <<
    "-dd     Wyświetla liczę cyfr oddzielonych znakami białymi\n" << '\n' <<
    "-c      Wyświetla liczbę znaków w pliku źródłowym\n" << '\n' <<
    "-s      Wyświetla wszystkie słowa z pliku w kolejności alfabetycznej\n" << '\n' <<
    "-rs     Wyświetla wszystkie słowa z pliku w kolejności odwrotnej do alfabetycznej\n" << '\n' <<
    "-a      Wyświetla anagramy słów podanych za parametrem\n" <<
    "Ten parametr musi zostać określony jako ostatni!\n" << '\n' <<
    "-p      Wyświetla palindromy słów podanych za parametrem\n" <<
    "Ten parametr musi zostać określony jako ostatni!\n" << '\n' <<
    "-o [sciezka_do_pliku]    Zapisuje dane wyjściowe do pliku o podanej ścieżce\n" << '\n' <<
    "-i [sciezka_do_pliku]    Przyjmuje dane wejściowe z pliku o podanej ścieżce\n" <<
    "Ten parametr musi być jedynm określonym parametrem!\nParametry sterujące programem powinny znajdować się w pliku wejściowym";
}

void flags_checker(std::vector<std::string>& args, Flags& flags) {
    for (int i = 2; i < args.size(); ++i) {
        if (args[i] == "--newlines" || args[i] == "-n") {
            flags.is_newlines = true;
        } else if (args[i] == "--digits" || args[i] == "-d") {
            flags.is_digits = true;
        } else if (args[i] == "--numbers" || args[i] == "-dd") {
            flags.is_numbers = true;
        } else if (args[i] == "--chars" || args[i] == "-c") {
            flags.is_chars = true;
        } else if (args[i] == "--anagrams" || args[i] == "-a") {
            flags.is_anagrams = true;
        } else if (args[i] == "--palindroms" || args[i] == "-p") {
            flags.is_palindroms = true;
        } else if (args[i] == "--sorted" || args[i] == "-s") {
            flags.is_sorted = true;
        } else if (args[i] == "--reverse-sorted" || args[i] == "-rs") {
            flags.is_reverse = true;
        } else if (args[i] == "--output" || args[i] == "-o") {
            flags.is_output = true;
            flags.output_patch = args[i+1];
            i++;
        } else {
            std::cout << "Podane argumenty są nieprawidłowe!";
            exit(1);
        }
    }
}

void file_checker(const std::string& file_path, std::stringstream& stream) {
    std::ifstream input_file(file_path);
    if (input_file.is_open()) {
        std::cout << "Plik " << file_path << " został wczytany poprawnie!\n" << '\n';
        stream << input_file.rdbuf();
        input_file.close();
    } else {
        std::cout << "Błąd wczytywania pliku" << "(" << file_path << ")!";
        exit(2);
    }
}

void newlines(const std::stringstream& source, std::stringstream& output) {

}

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::stringstream test;
    Flags flags;
    flags_checker(args, flags);
    std::stringstream source_stream;
    std::stringstream output_stream;

    if ((args[0] == "-i" || args[0] == "--input") && args.size() == 2) {
        std::stringstream input_stream;
        file_checker(args[1], input_stream);
        args.clear();

        for (std::string line; std::getline(input_stream, line);) {
            std::stringstream stream(line);
            for (std::string word; stream >> word;) {
                args.push_back(word);
            }
        }
    }

    if (args.empty() || args[0] == "--help") {
        if_empty();
    } else if (args[0] == "-f" || args[0] == "--file") {
        file_checker(args[1], source_stream);
    } else {
        std::cout << "Podane argumenty są nieprawidłowe!";
        exit(1);
    }

    if (flags.is_newlines) {
        newlines(source_stream, output_stream);
    }

    std::cout << output_stream.str();
}
