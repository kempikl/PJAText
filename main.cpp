#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
/**
 * Struktura przechowuje informacje o funkcjach jakie ma wykonać program.
 */
struct Flags {
    bool is_newlines{};
    bool is_digits{};
    bool is_numbers{};
    bool is_chars{};
    bool is_sorted{};
    bool is_reverse{};
    bool is_output{};

    std::string output_patch;
};

/**
 * Funkcja obsługuje nieokreślenie flag przez użytkownika.
 */
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
    "-o [sciezka_do_pliku]    Zapisuje dane wyjściowe do pliku o podanej ścieżce\n" << '\n' <<
    "-i [sciezka_do_pliku]    Przyjmuje dane wejściowe z pliku o podanej ścieżce\n" <<
    "Ten parametr musi być jedynm określonym parametrem!\nParametry sterujące programem powinny znajdować się w pliku wejściowym";
}
/**
 * Funkcja waliduje dane wprowadzone przez użytkownika.
 * Obsługuje instancję struktury Flags.
 *
 * @param args vector zawierający dane użytkownika.
 * @param flags instancja struktury Flags.
 */
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

/**
 * Funkcja sprawdza możliwość otwarcia pliku i zapisuje go do bufora.
 *
 * @param file_path ścieżka dostępu do pliku.
 * @param stream bufor do którego jest zapisywana zawartość pliku.
 */
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

/**
 * Funkcja zlicza ilość lini w dostarczonym buforze.
 *
 * @param source bufor źródłowy.
 * @param output bufor przechowujący dane wyjściowe.
 */
void newlines(const std::stringstream& source, std::stringstream& output) {
    int counter = 0;
    std::string line;
    std::stringstream temp;
    temp << source.str();

    while (getline(temp, line)) counter++;

    output << "Liczba lini we wczytanym pliku: " <<counter << '\n' << '\n';
}

/**
 * Funkcja zlicza ilość liczb w buforze.
 *
 * @param source bufor źródłowy.
 * @param output bufor przechowujący dane wyjściowe.
 */
void digits(const std::stringstream& source, std::stringstream& output) {
    int counter = 0;
    std::stringstream temp;
    temp << source.str();
    std::string strtemp;

    while (temp>>strtemp){
        for(char i : strtemp)
        if(isdigit(i)) counter++;
    }

    output << "Liczba cyfr we wczytanym pliku to: " << counter << '\n' << '\n';
}

/**
 * Funkcja zlicza ilość cyfr w buforze.
 *
 * @param source bufor źródłowy.
 * @param output bufor przechowujący dane wyjściowe.
 */
void numbers(std::stringstream& source, std::stringstream& output) {
    int counter = 0;
    std::stringstream temp;
    temp << source.str();
    std::string strtemp;

    while (temp>>strtemp){
        std::vector<char> vtemp;
        int pos = 0;
        for(char i : strtemp) {
            pos++;
            if (isdigit(i) || i == '-') {
                break;
            }
        }
        if (pos != strtemp.length()) {
            counter++;
            for (char i : strtemp) {
                vtemp.push_back(i);
            }
            for (int i = pos; i < vtemp.size(); ++i) {
                if (!isdigit(vtemp[i])) counter--;
            }
        }
    }

    output << "Liczba liczb we wczytanym pliku to: " << counter << '\n' << '\n';
}

/**
 * Funkcja zlicza ilość znaków w buforze.
 *
 * @param source bufor źródłowy.
 * @param output bufor przechowujący dane wyjściowe.
 */
void chars(const std::stringstream& source, std::stringstream& output) {
    output << "Liczba znaków we wczytanym pliku to: " << source.str().length() << '\n' << '\n';
}

/**
 * Funkcja sortuje słowa z bufora w kolejności alfabetycznej.
 *
 * @param source bufor źródłowy.
 * @param output bufor przechowujący dane wyjściowe.
 */
void sorted(const std::stringstream& source, std::stringstream& output) {
    std::stringstream temp;
    temp << source.str();
    std::vector<std::string> vstr;
    std::string strtemp;

    while (temp>>strtemp) vstr.push_back(strtemp);
    std::sort(std::begin(vstr), std::end(vstr));

    output << "Słowa z pliku źródłowego posortowanie w kolejności alfabetycznej:" <<'\n';

    for (const std::string& str : vstr) {
        output << str << ' ';
    }

    output <<'\n' << '\n';
}

/**
 * Funkcja sortuje słowa z bufora w kolejności odwrotnej do alfabetycznej.
 *
 * @param source bufor źródłowy.
 * @param output bufor przechowujący dane wyjściowe.
 */
void reverse(const std::stringstream& source, std::stringstream& output) {
    std::stringstream temp;
    temp << source.str();
    std::vector<std::string> vstr;
    std::string strtemp;

    while (temp>>strtemp) vstr.push_back(strtemp);
    std::sort(std::begin(vstr), std::end(vstr), [](const std::string a, const std::string b) {return a > b; });

    output << "Słowa z pliku źródłowego posortowanie w kolejności odwrotnej do alfabetycznej:" <<'\n';

    for (const std::string& str : vstr) {
        output << str << ' ';
    }
}

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    Flags flags;
    std::stringstream source_stream;

/**
 * Obsługa wprowadzania parametrów z pliku.
 */
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

/**
 * Obsługa braku wprowadzonych flag.
 */
    if (args.empty() || args[0] == "--help") {
        if_empty();
    } else if (args[0] == "-f" || args[0] == "--file") {
        file_checker(args[1], source_stream);
    } else {
        std::cout << "Podane argumenty są nieprawidłowe!";
        exit(1);
    }

    flags_checker(args, flags);
    std::stringstream output_stream;

/**
 * Sprawdzanie aktywnych flag i wywoływanie odpowiednich funkcji.
 */
    if (flags.is_newlines) {
        newlines(source_stream, output_stream);
    }
    if (flags.is_digits) {
        digits(source_stream, output_stream);
    }
    if (flags.is_numbers) {
        numbers(source_stream, output_stream);
    }
    if (flags.is_chars) {
        chars(source_stream, output_stream);
    }
    if (flags.is_sorted) {
        sorted(source_stream, output_stream);
    }
    if (flags.is_reverse) {
        reverse(source_stream, output_stream);
    }

    /**
     * Obsługa zapisu danych wyjściowych do pliku.
     */
    if (flags.is_output) {
        std::ofstream output_file(flags.output_patch);
        if (output_file.is_open()) {
            output_file << output_stream.str();
        } else {
            std::cout << "Błąd zapisu pliku!";
            exit(3);
        }
        output_file.close();
    } else std::cout << output_stream.str();
}
