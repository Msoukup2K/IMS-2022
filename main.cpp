/******************************************
* FILE: main.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#include <iostream>
#include <fstream>
#include <getopt.h>

#include "animation.h"
#include "ca.h"
#include "probability.h"
#include "error.h"

static CA *MODEL = nullptr;

void cleanup()
{
    delete MODEL;
}

int main(int argc, char *argv[])
{
    atexit(cleanup);
    probability_init();

    MODEL = new CA{180};

    int opt{};
    double animation_freq = 5;
    bool opt_p = false;
    int opt_p_val = -1;
    try
    {
        while ((opt = getopt(argc, argv, ":f:F:a:D:K:P:Q:I:p:E:h")) != -1)
        {
            switch (opt)
            {
            case 'h':
                std::cout << "VUT FIT IMS projekt 2022\n"
                    << "model a simulace růstu rakovinného nádoru, reakce imunitních buněk a zjednodušená chemoterapie\n\n"
                    << "použití: ./run [-h] [-E <time>] [-f <logfile>] [-F <refresh_frequency>] [-a <age_threshold>] [-D <age_threshold>]\n"
                    << "\t\t[-K <carrying_cap>] [-P <resistance>] [-Q <resistance>] [-I <resistance>] [-p <chemo_doses>]\n\n"
                    << "Pokud není nastaven žádný z přepínačů -E, -K, -p, program simuluje růst nádoru bez chemoterapie.\n"
                    << "Pokud některý z těchto přepínačů nastavený je, pak jsou simulovány efekty chemoterapie podle přepínače/ů.\n\n"
                    << "Ovládání klávesnicí:\n\n"
                    << "\tšipky nahoru/doprava\tF += 1 Hz\n"
                    << "\tšipky dolů/doleva\tF -= 1 Hz\n"
                    << "\tMezerník\t\tpause/unpause\n\n"
                    << "přepínače:\n\n"
                    << "\t-h\t\t\t"
                    << "Vypíše tuto nápovědu a ukončí program.\n\n"
                    << "\t-E <time>\t\t"
                    << "Zapne usmrcování buňek chemoterapií po uplynutí času time.\n"
                    << "\t\t\t\tJedná se pouze o triviální řešení, které pravděpodobně neodpovídá realitě.\n\n"
                    << "\t-f <logfile>\t\t"
                    << "Výpisy aplikace jsou zapisovány do souboru logfile. Pokud soubor se stejným názvem již existuje, je jeho obsah přepsán.\n"
                    << "\t\t\t\tPokud není přepínač zapnut, aplikace vypisuje na standardní výstup.\n\n"
                    << "\t-F <refresh_frequency>\t"
                    << "Nastaví obnovovací frekvenci animace v Hz. Bez použití přepínače je frekvence 5 Hz.\n\n"
                    << "\t-a <age_threshold>\t"
                    << "Nastaví věkovou hranici pro P buňky. Po dosažení daného věku (a dalších podmínek) se změní na Q buňky. default=10\n\n"
                    << "\t-D <age_threshold>\t"
                    << "Nastaví věkovou hranici pro buňky v nedefinovaném stavu. Po dosažení daného věku se změní na mrtvé buňky. default=5\n\n"
                    << "\t-K <carrying_cap>\t"
                    << "Upraví parametr pro kapacitu přenosu P buněk. Simuluje účinnost chemoterapie na velikost nádoru.\n"
                    << "\t\t\t\tPokud není nastaven, nebo je nastaven na 0, nádor dosahuje velikosti jako bez chemoterapie\n\n"
                    << "\t-P <resistance>\t\t"
                    << "Nastaví rezistenci P buněk proti chemoterapii. Bez přepínače -E nebo -p nemá žádný efekt.\n\n"
                    << "\t-Q <resistance>\t\t"
                    << "Nastaví reyistenci Q buněk proti chemoterapii. Bez přepínače -E nemá žádný efekt.\n\n"
                    << "\t-I <resistance>\t\t"
                    << "Nastaví reyistenci I buněk proti chemoterapii. Bez přepínače -E nemá žádný efekt.\n\n"
                    << "\t-p <chemo_doses>\t"
                    << "Upraví parametr pro provděpodobnost dělení P buněk. Simuluje účinnost chemoterapie na rychlost růstu nádoru.\n"
                    << "\t\t\t\tPokud není nastaven, nádor roste stejně rychle, jako bez chemoterapie.\n"
                    << "\t\t\t\tParametr chemo_doses odpovídá počtu dávek chemoterapie."
                    << std::endl;
                return EXIT_SUCCESS;
                break;

            case 'f':
                MODEL->setLog(optarg);
                break;

            case 'F':
                animation_freq = std::stod(optarg);
                if (animation_freq < 0.1 || animation_freq > 100)
                    error_exit("obnovovací frekvenca animace musí být v rozmezí 0.1 až 100 Hz");
                break;

            case 'a':
                if (!MODEL->setCellAgeThreshold(std::stoi(optarg)))
                    error_exit("věková hranice P buňky musí být větší než 0");
                break;

            case 'D':
                if (!MODEL->setNDead(std::stoi(optarg)))
                    error_exit("doba, po které nestabilní stav přejde na mrtvou buňku musí být větší než 0");
                break;

            case 'K':
                if (!MODEL->setTherapyTumorCarryingCapacity(std::stoi(optarg)))
                    error_exit("parametr pro změnu kapacity přenosu musí být v rozmezí 0 až %.2f", MODEL->upTTCC());
                break;

            case 'P':
                if (!MODEL->setTherapyResistanceIC(std::stod(optarg)))
                    error_exit("odolnost buňek typu P musí být v rozmezí 0 až 0.95");
                break;

            case 'Q':
                if (!MODEL->setTherapyResistanceIC(std::stod(optarg)))
                    error_exit("odolnost buňek typu Q musí být v rozmezí 0 až 0.4");
                break;

            case 'I':
                if (!MODEL->setTherapyResistanceIC(std::stod(optarg)))
                    error_exit("odolnost buňek typu I musí být v rozmezí 0 až 0.7");
                break;

            case 'p':
                opt_p_val = std::stoi(optarg);
                opt_p = true;
                break;

            case 'E':
                if (!MODEL->setTherapyCellDeath(std::stoi(optarg)))
                    error_exit("začátek úmrtí buněk musí být větší než 0");
                break;

            case ':':
                error_exit("přepínač %c vyžaduje argument", optopt);
                break;

            case '?':
                error_exit("neznámý přepínač %c", optopt);
                break;
            
            default:
                break;
            } // switch
        } // while
        // needs to be here, because it depends on the option -P
        // would use the default value in case of wrong order of options
        if (opt_p)
        {
            if (!MODEL->setTherapyDivisionProbability(opt_p_val))
                error_exit("počet dávek chemoterapie musí být větší než 0");
        }
    } // try
    catch(const std::exception& e)
    {
        error_exit("%s", e.what());
    }
    

    MODEL->init();
    Animation animation{argc, argv, "IMS 2022/23 -- simulace", MODEL};
    animation.setFreq(animation_freq);

    animation.run();

    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

