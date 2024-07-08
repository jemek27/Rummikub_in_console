//
// Created by jemek on 28.04.2023.
//
#include <list>
#include <vector>
#include "Zeton.h"
#include "CiagZetonow.h"
#include "TabliczkaGracza.h"
#include "Menu.h"
#include <sstream>

#ifndef RUMMIKUB_PLANSZA_H
#define RUMMIKUB_PLANSZA_H


class Plansza {
    std::vector<CiagZetonow*> wszystkieCiagi;
    std::vector<TabliczkaGracza*> wszystkieTabGr;
    std::vector<Zeton*> resztaZetonowWWorku;
    std::vector<int> tabelaZwyciezcow;
    Plansza* kopiaZaposwaPlanszy;
    bool pierwszeWykonanieKomendy;
    bool poprawnePierwszewylozenie;

public:
    Plansza(WorekNaZetony &worek, std::vector<std::string> nazwyGraczy);
    Plansza(const Plansza &inna);
    Plansza(TabliczkaGracza *tabGr);
    ~Plansza();

    Plansza& operator=(const Plansza& inna);

    bool czySkonczyl(int idGr, const int nrRundy);
    void czyWygranaWlakowerem(int idGr, const int nrRundy);
    int iluSkonczylo();
    std::vector<int> dajTabZwy();

    void pokazPlansze();
    void kolejGracza(int id, const int nrRundy);
    std::vector<std::string> podzielKomendy(std::string komenda);

    bool koncoweSprawdzanieRuchu (const int &id);
    //todo po f gdy jest nie poprawny ciąg, dać drugą szanse
    void pierwszeRuchGracza(const int &id, const int nrRundy);
    void ruchGracza(const int &idGr, const int &nrCiagu, std::list<Zeton *>::iterator iterZeton);

    void sprOgolnejPoprawnosciKomendy (const int &id, const std::string &komenda, bool &koniecTury, const int nrRundy);
    void KomendaDziel (const std::string &komenda);
    void KomendaLacz (const std::string &komenda);
    void KomendaNowy (std::string &komenda, int id);
    void KomendaWez (const std::string &komenda, int id);
    void KomendaRuch (const std::string &komenda, int id);

    std::pair<int, int> sprKomendyPodzielCiag (const std::string &komenda);
    CiagZetonow* podzielCiagi (CiagZetonow *pierwszyCiag, int poKtorym);
    void polaczCiagi(int idPierwszego, int idDrugiego);

    bool bylZTabGr (Zeton * z, const int &idGr);
    void dodatkoweZetony ();

    void testkopi();
    void testKolejGracza(int id, std::vector<std::string> komendy);
    void testWieleKomend ();
//    void ciagniecieZWorka(int id)

};






#endif //RUMMIKUB_PLANSZA_H
