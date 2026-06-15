/**
 * Joukko-oppi
 * Anna lauseke muodossa: ((W∪X)∩(Z∪Y))
 * (W∪X)
 * (W∪∼X)
 * ((W∪X)∩(X∪Y))
 * ((W∩X)∪(X∩Y))
 * (W⊂X)
 * Muista! Lausekkeiden unicode merkit merkistö -sovelluksen avulla! Lisäksi muista syöttää sovellukseen
 * näin: 
 1. Valitse tehtäväpalkista -> Joukot
 2. Valitse Syötä joukot
 3. Anna joukkojen lukumäärä (esim. joukot W ja X niin annat joukon lukumääräksi 2)
 4. Syötä joukon nimet (esim. W ja X) ja niiden alle
 pilkuin eriteltyinä joukko (esim. 2,3 ja 1,3)
 5. Valitse tehtäväpalkista -> Lauseke
 6. Valitse Syötä lauseke ja anna lauseke:
 (W∪X)

 * */

#include <gtk/gtk.h>
#include <algorithm>
#include <vector>
#include <iostream>
//#include <io.h>
#include <fcntl.h>
#include <set>
#include <numeric>
#include <sstream>
#include <iterator>
#include <locale>
#include <codecvt>
#include <string>
#include <cstdlib>
//#include <windows.h>
#include <cwchar>
#include <cmath>
#include <fstream>
#include "joukko.h"
#include "infix_to_postfix.h"

#define MAXVAL	100
#define MAXOP	100
#define NUMBER	'0'
#define CHAR	'A'
#define BUFSIZE	100

using namespace std;
wchar_t s[MAXOP];
wchar_t osajoukko_m = u'\u2282';
int muuttujatlkm;
int* joukon_koko;
int* joukon_pilkuton_koko;
double mlkm2 = 0.0;
int sp = 0;
int spi = 0;
//int val[MAXVAL][MAXVAL];
int** val;
int* ival;
int* universumi;
int* perusjoukko;
int ukoko = 0;
int jkoko=0;
GtkBuilder  *builder;
GtkWidget   *isanta;
GtkWidget	*kaanteinen_joukko;
GtkWidget	*suorite;
GtkWidget	*binaari_tulos;
GtkWidget 	*win_joukon_nimi;
GtkWidget 	*win_joukon_koko;
GtkWidget	*win_muuttuja;
GtkWidget 	*win_lauseke;
GtkWidget	*win_joukko_lkm;
GtkWidget 	*text_view;
GtkWidget	*text_view2;
GtkWidget	*text_view3;
GtkWidget	*text_view4;
GtkWidget	*text_view5;
GtkWidget 	*window;
gchar *gnimi;
gchar *gkoko;
gchar *gmuuttujat;
gchar *glkm;
gchar *lauseke;
bool debug=FALSE;
string luku3;
string nluku3;
wstring wluku3;

typedef set<double, less<double> > set_type;
ostream& operator<<(ostream& out, const set_type& s) {
	copy(s.begin(), s.end(), std::ostream_iterator<set_type::value_type>(cout, " "));
	return out;
}
int ** lauseke_postfix(int muuttujatlkm);
int laske_joukon_koko(const char* teksti);
int* tayta_joukot(int joukon_koko, int joukko_nro, int pilkuton_koko, const char* teksti2);
int laske_joukon_pilkuton_koko(const char* teksti3);
int palauta_joukon_alkio(int kohta, const char* teksti2);
bool ei_joukossa(int joukko1, int kohta, int koko, int maara);
wstring muunna_postfix(wchar_t s[MAXOP]);
int* laske_lauseke(const wchar_t* toinen, int** tmp2);
set_type joukko1, joukko2, joukko3, joukko4, u;
set_type tulos1, tulos2, tulos3;
int** tmp;
int** joukot;
std::vector<std::string> joukon_nimet;

//int joukot[4][10];
//= new int[4][10];
std::vector<int> tulos(10);
// Create a vector to store entry widgets
std::vector<GtkWidget*> entries;
std::vector<GtkWidget*> entries2;

/**
 * lauseke_postfix !
 */

static void on_menu_item_suoritus(GtkWidget *wid, gpointer ptr){
	wcout << "on_menu_item_suoritus!" << endl;
	for (int c = 0; c < muuttujatlkm; c++) {
		for (int j = 0; j != joukon_pilkuton_koko[c]; j++) {
			//joukot[c][j] = koe[j];
			wcout << joukot[c][j] << endl;
			//cout << "joukot[" << c << "][" << j << "]:";
			//cout << koe[j] << endl;
		}
	} 
	gtk_widget_show_all(win_lauseke);
}

static void on_submit(GtkWidget *button, gpointer data){
	std::wcout << "Collected Values:" << std::endl;
	//std::vector<GtkWidget*> *entries = static_cast<std::vector<GtkWidget*>*>(data);
	int f=0;
	int e = 0, h=0;
	joukot = new int* [muuttujatlkm];
	joukon_pilkuton_koko = new int [muuttujatlkm];
	wcout << "entries size:" << entries.size() << endl;
	wcout << "entries size2:" << entries2.size() << endl;

	for(auto entry2 : entries2){
		const char *text2 = gtk_entry_get_text(GTK_ENTRY(entry2));
		wcout << text2 << endl;
		joukon_nimet.push_back(string(text2));
	}
	    
    for (auto entry : entries) {
        const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
        //std::wcout << text << std::endl;
		joukon_koko[f] = laske_joukon_koko(text);
		joukon_pilkuton_koko[f] = laske_joukon_pilkuton_koko(text);
		joukot[f] = tayta_joukot(joukon_koko[f], f, joukon_pilkuton_koko[f], text);
		
		f++;
		//wcout << "entry" << endl;
    }
	gtk_widget_hide(window);
	wcout << "\nTulostetaan joukot:\n" << endl;
	
	for (int c = 0; c < muuttujatlkm; c++) {
		for (int j = 0; j != joukon_pilkuton_koko[c]; j++) {
			//joukot[c][j] = koe[j];
			wcout << joukot[c][j] << endl;
			//cout << "joukot[" << c << "][" << j << "]:";
			//cout << koe[j] << endl;
		}
		for (int d = 0; d < joukon_pilkuton_koko[c]; d++) {
			wcout << "joukot[" << c << "][" << d << "]:" << joukot[c][d] << endl;

			if (ei_joukossa(joukot[c][d], c, joukon_pilkuton_koko[c], e)) {
				//cout << "ei joukossa:" << joukot[c][d] << endl;
				perusjoukko[e] = joukot[c][d];
				//universumi[e] = joukot[c][d];
				//cout << "universumi:" << universumi[e] << endl;
				//cout << "e:" << e << endl;
				e++;				
			}
		}
	}

	universumi = new int[e];
	wcout << "universumi:" << endl;

	for (int g = 0; g < e; g++) {
		universumi[g] = perusjoukko[g];
		//wcout << universumi[g] << ",";
	}

	std::vector<int> jarjestys(universumi, universumi + e);
	std::sort(jarjestys.begin(), jarjestys.begin() + e);

	for (std::vector<int>::iterator it2 = jarjestys.begin(); it2 != jarjestys.end(); ++it2) {
		universumi[h] = *it2;
		std::wcout << ' ' << universumi[h];
		h++;
	}
	wcout << endl;

	ukoko = e;
	for (int ddd = 0; ddd < 2; ddd++) {
		wcout << "joukot[" << 0 << "][" << ddd << "]:" << joukot[0][ddd] << endl;
	}
    //gtk_main_quit(); // Exit the GTK main loop
}

void joukko_nimi(GtkWidget *wid, gpointer ptr){
	wcout << "joukko_nimi!! Painoit painiketta!" << endl;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gnimi = gtk_text_buffer_get_text(buffer, &start, &end, debug);
        
	wcout << gnimi << endl;
	gtk_widget_hide(win_joukon_nimi);
	gtk_widget_show_all(win_joukon_koko);
	
}

void joukko_koko(GtkWidget *wid, gpointer ptr){
	wcout << "joukko_koko!! Painoit painiketta!" << endl;
	GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view2));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer2, &start);
    gtk_text_buffer_get_end_iter(buffer2, &end);
    gkoko = gtk_text_buffer_get_text(buffer2, &start, &end, debug);
    jkoko = atoi(gkoko);    
	wcout << gkoko << endl;
	gtk_widget_hide(win_joukon_koko);
	//gtk_widget_show_all(win_muuttuja);
}

void joukko_muuttujat(GtkWidget *wid, gpointer ptr){
	GtkTextBuffer *buffer3 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view3));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer3, &start);
    gtk_text_buffer_get_end_iter(buffer3, &end);
    gmuuttujat = gtk_text_buffer_get_text(buffer3, &start, &end, debug);    
    
	wcout << "joukko_muuttujat!! Painoit painiketta!" << endl;
	wcout << gmuuttujat << endl;
	gtk_widget_hide(win_muuttuja);
}

/*
* Tee nyt niin että keräät joukkojen lukumäärän ja keräät vastaavan määrän joukkoja!
* Allaolevalla funktiolla! 
*/

void joukko_lkm(GtkWidget *wid, gpointer ptr){
	GtkTextBuffer *buffer5 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view5));
	GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer5, &start);
    gtk_text_buffer_get_end_iter(buffer5, &end);
    glkm = gtk_text_buffer_get_text(buffer5, &start, &end, debug);
	wcout << "joukko_lkm:" << glkm << endl;
	tmp = lauseke_postfix(atoi(glkm));
	muuttujatlkm = atoi(glkm);
}

std::string wstring_to_utf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

gchar* wstring_to_gchar(const std::wstring& wstr) {
    try {
        // Use std::wstring_convert with UTF-8 codecvt facet
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(wstr);

        // Allocate memory for gchar* and copy the string
        gchar* gchar_str = g_strdup(utf8_str.c_str());
        return gchar_str;
    } catch (const std::exception& e) {
        std::cerr << "Error during conversion: " << e.what() << std::endl;
        return nullptr;
    }
}

/**
* Jatka tästä! muunna_postfix funktiosta!
**/

void suorita(GtkWidget *wid, gpointer ptr){
	wcout << "suorita!!" << endl;
	int* tulos3;
	GtkTextBuffer *buffer6 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view4));
	GtkTextBuffer* buffer7 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(kaanteinen_joukko));
	GtkTextIter start, end;
	gtk_text_buffer_get_bounds(buffer6, &start, &end);
	char *text = gtk_text_buffer_get_text(buffer6, &start, &end, FALSE);
	gsize len = g_utf8_strlen(text, -1);
	wcout << "len:" << len << endl;
	wchar_t *unitext = new wchar_t[len];
	size_t i = 0;
	//for(gsize i=0; i < len; ++i){
	while(text && *text != '\0'){
		//gunichar first_char = g_utf8_get_char(text);
		const wchar_t first_char = g_utf8_get_char(text);
		unitext[i] = first_char;
		wcout << L"Unicode char:" << unitext[i] << endl;
		text = g_utf8_next_char(text);
		i++;
	}
	wcout << L"lauseke:" << unitext << endl;
	wstring lauseke = muunna_postfix(unitext);
	std::string lauseke2 = wstring_to_utf8(lauseke);
	gtk_text_buffer_set_text(buffer7, lauseke2.c_str(), -1);
	tulos3 = laske_lauseke(lauseke.c_str(), tmp);
}

void on_menu_item_joukko_lkm(GtkMenuItem *menuitem, gpointer data){
	wcout << "Menu item pressed!\n" << endl;
	
    gtk_widget_show_all(win_joukko_lkm);
}


void on_menu_item_joukon_nimi(GtkMenuItem *menuitem, gpointer data) {
    /*GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    nimi = gtk_text_buffer_get_text(buffer, &start, &end, debug);
    
    //Siirrä allaoleva liitos myöhemmin text_view liitokseen!
    //gtk_text_buffer_set_text(buffer2, text, -1);
	wcout << nimi << endl;*/
	wcout << "Menu item joukon_nimi pressed!\n" << endl; 
    gtk_widget_show_all(win_joukon_nimi);
}

void on_menu_item_tyhjenna(GtkMenuItem *menuitem, gpointer data){
	wcout << "Menu item tyhjenna painettu" << endl;
	GtkTextBuffer* buffer8 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(kaanteinen_joukko));
	GtkTextBuffer* buffer9 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(suorite));
	GtkTextBuffer* buffer10 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(binaari_tulos));
	gchar *tyhjennys= g_strdup("");
	gtk_text_buffer_set_text(buffer8, tyhjennys, -1);
	gtk_text_buffer_set_text(buffer9, tyhjennys, -1);
	gtk_text_buffer_set_text(buffer10, tyhjennys, -1);
	wluku3.clear();
}

static void on_file_selected(GtkWidget *widget, gpointer data) {
	GtkFileChooser *chooser = GTK_FILE_CHOOSER(widget);
	GtkTextBuffer* buffer14 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(kaanteinen_joukko));
	GtkTextBuffer* buffer15 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(suorite));
	GtkTextBuffer* buffer16 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(binaari_tulos));
	gchar *otsikko1 = g_strdup("kaanteinen joukko");
	gchar *otsikko2 = g_strdup("suorite");
	gchar *otsikko3 = g_strdup("binaarinen tulos");
    char *filename = gtk_file_chooser_get_filename(chooser);
	if (filename) {
        wcout << "Selected file:" << filename << endl;
		wifstream ifs(filename);
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
		ifs.imbue(loc);
		std::wstring line;
		string content;
		bool joukko=false;
		bool suorite=false;
		bool tulos=false;
		bool seur=false;
		
		if (!ifs.is_open()) {
        	wcout << "Failed to open file." << endl;
        	return;
    	}

		while (std::getline(ifs, line)) {
			//const char* koe = line.c_str();
			//wcout << line << endl;  
			if(line == L"kaanteinen joukko"){
				seur = true;
				joukko = true;
			}else if(line == L"suorite"){
				seur = true;
				suorite = true;				
			}/*else if(line == L"binaarinen tulos"){
				seur = true;
				tulos = true;
			}*/else if(seur && suorite){
				string line2 = wstring_to_utf8(line);
				if(line2 != "binaarinen tulos"){
					wcout << line << endl;
					content += line2 + "\n";	
					gtk_text_buffer_set_text(buffer15, content.c_str(), -1);
					
				}else{
					seur = false;
					suorite = false;
					tulos = true;
				}
			}else if(seur && joukko){
				//g_print(koe);
				string line2 = wstring_to_utf8(line);
				wcout << line << endl;
				gtk_text_buffer_set_text(buffer14, line2.c_str(), -1);
				seur = false;
				joukko = false;
			}else if(tulos){
				string line2 = wstring_to_utf8(line);
				wcout << line << endl;
				gtk_text_buffer_set_text(buffer16, line2.c_str(), -1);
				tulos = false;
			}

		}
	}
}

void on_menu_item_lataa(GtkMenuItem *menu_item, gpointer data){
	wcout << "Menu item lataa painettu" << endl;
	GtkWidget *dialog;
    GtkWindow *parent = GTK_WINDOW(data);

    // Create a FileChooserDialog
    dialog = gtk_file_chooser_dialog_new("Open File",
                                         parent,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Open", GTK_RESPONSE_ACCEPT,
                                         NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        on_file_selected(dialog, NULL);
    }

    gtk_widget_destroy(dialog);
}

void on_menu_item_tallennus(GtkMenuItem *menuitem, gpointer data){
	wcout << "Menu item tallennus painettu" << endl;
	GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	GtkTextBuffer* buffer11 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(kaanteinen_joukko));
	GtkTextBuffer* buffer12 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(suorite));
	GtkTextBuffer* buffer13 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(binaari_tulos));
	GtkTextIter start, end, s2, s3, s4, s5;
	size_t i = 0;
	size_t i2 = 0;
	
	gtk_text_buffer_get_start_iter(buffer11, &start);
    gtk_text_buffer_get_end_iter(buffer11, &end);
	gtk_text_buffer_get_start_iter(buffer12, &s2);
	gtk_text_buffer_get_end_iter(buffer12, &s3);
	gtk_text_buffer_get_start_iter(buffer13, &s4);
	gtk_text_buffer_get_end_iter(buffer13, &s5);
	char *text_kaanteinen_joukko = gtk_text_buffer_get_text(buffer11, &start, &end, FALSE);
	gchar *text1;
	//gchar *text_kaanteinen_joukko = gtk_text_buffer_get_text(buffer11, &start, &end, debug);
	//gchar *text_suorite = gtk_text_buffer_get_text(buffer12, &s2, &s3, debug);
	char *text_suorite = gtk_text_buffer_get_text(buffer12, &s2, &s3, debug);
	gchar *text_binaari_tulos = gtk_text_buffer_get_text(buffer13, &s4, &s5, debug);
	
	gsize len = g_utf8_strlen(text_kaanteinen_joukko, -1);
	gsize len2 = g_utf8_strlen(text_suorite, -1);

	wcout << "len:" << len << endl;
	wcout << "len2:" << len2 << endl;
	wchar_t *unitext = new wchar_t[len];
	wchar_t *unitext2 = new wchar_t[len2];

	while(*text_kaanteinen_joukko != '\0'){
		//gunichar first_char = g_utf8_get_char(text);
		const wchar_t first_char = g_utf8_get_char(text_kaanteinen_joukko);
		unitext[i] = first_char;
		wcout << L"Unicode char:" << unitext[i] << endl;
		text_kaanteinen_joukko = g_utf8_next_char(text_kaanteinen_joukko);
		i++;
	}
	wstring wjoukko;
	wjoukko.clear();
	wjoukko = unitext;

	while(*text_suorite != '\0'){
		const wchar_t first_char2 = g_utf8_get_char(text_suorite);
		unitext2[i2] = first_char2;
		wcout << L"Unicode char:" << unitext2[i2] << endl;
		text_suorite = g_utf8_next_char(text_suorite);
		i2++;
	}
	wstring wsuorite;
	wsuorite.clear();
	wsuorite = unitext2;
	
	//text1 =  wstring_to_gchar(wjoukko);
	//std::string str = wstring_to_utf8(wjoukko);
	//text1 = str.c_str();
	wcout << "wjoukko:" << wjoukko << endl;
	wcout << "wsuorite:" << wsuorite << endl;
	wcout << "binaarinen tulos:" << text_binaari_tulos << endl;

	dialog = gtk_file_chooser_dialog_new("Save File",
                                         NULL,
                                         action,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Save", GTK_RESPONSE_ACCEPT,
                                         NULL);
	chooser = GTK_FILE_CHOOSER(dialog);
	// Set a default filename
    gtk_file_chooser_set_current_name(chooser, "Untitled.jo");

    // Run the dialog and handle the response
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
		
		gchar *otsikko1 = g_strdup("kaanteinen joukko");
		gchar *otsikko2 = g_strdup("suorite");
		gchar *otsikko3 = g_strdup("binaarinen tulos");
		// Get the selected filename
        filename = gtk_file_chooser_get_filename(chooser);
		
		wofstream file(filename);
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
		file.imbue(loc);
		if (file.is_open()) {
			file << otsikko1 << std::endl;
			file << wjoukko << endl;
			file << otsikko2 << std::endl;
			file << wsuorite << endl;
			file << otsikko3 << std::endl;
			file << text_binaari_tulos << endl;
			file.close();
			std::cout << "Text written to file successfully!" << std::endl;
		} else {
        	std::cerr << "Failed to open file for writing!" << std::endl;
    	}
		
		wcout << "File saved as: \n" << filename;
		 // Free the filename string
    	g_free(filename);
	}
	
	// Destroy the dialog after use
    gtk_widget_destroy(dialog);
   
}

void on_menu_item_poistu(GtkMenuItem *menuitem, gpointer data){
	exit(0);
}

void on_menu_item_tietoa(GtkMenuItem *menuitem, gpointer data){
	wcout << "on_menu_item_tietoa" << endl;
	GtkWidget *dlg = gtk_dialog_new_with_buttons("Tietoa", GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, "OK", 0, NULL);	
	GtkWidget *lbl = gtk_label_new ("\n\n\nSovelluksen on kehittänyt: Markus Juhala \nmarkusju7@gmail.com\n15.10.2025");
	gtk_widget_set_size_request(dlg, 250, 200);
	//gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), lbl);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(box), FALSE); // Allow different heights
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), box);
	gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
	gtk_widget_show_all(dlg);
	g_signal_connect(dlg, "response", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_widget_show(dlg);
}

void push(int* f, int fkoko) {
	wcout << "push:" << endl;
	int koko = 0;

	if (fkoko == 0) {
		koko = sizeof(f) / sizeof(int);
		wcout << "sizeof(f):" << sizeof(sizeof(f)) << endl;
		wcout << "sizeof(int):" << sizeof(int) << endl;
	}else{
		koko = fkoko;
		wcout << "fkoko:" << koko << endl;
		wcout << "\ntulos.size:" << sizeof(f) / sizeof(int*) << endl;
	}	
	/*
	for (int aa = 0; aa < koko; aa++) {
		cout << f[aa] << endl;
	}*/

	//cout << f[1] << endl;
	//cout << f[2] << endl;
	//cout << "sp:" << sp << endl;
	if (sp < MAXVAL) {
		//cout << "sp < MAXVAL" << endl;
		val[sp++] = f;
		ival[spi++] = fkoko;
		//cout << "ohi" << endl;
		//cout << val[0][0] << endl;
		//cout << val[0][1] << endl;
	}
	else {
		wcout << "virhe: stack on t�ynn�, ei voi push \n" << f;
	}
}

int* pop(void) {
	int* tyhja = { 0 };
	if (sp > 0)
		return val[--sp];
	else {
		wcout << "virhe: stack on tyhj�" << endl;
		return tyhja;
	}
}

int size_pop(void) {
	int tyhja = 0;
	if (spi > 0)
		return ival[--spi];
	else {
		wcout << "virhe: stack on tyhj�" << endl;
		return tyhja;
	}
}

/**
 * Jatka tästä !!! int *tulos = new int[joukon_koko] on väärä!!!
 */

int* tayta_joukot(int joukon_koko, int joukko_nro, int pilkuton_koko, const char* teksti2) {
	int muuttuja = 0;
	int pilkuton=0;
	int expilkku=0;
	int stulo_laskuri=0;
	int* tulos = new int[pilkuton_koko];
	char*ctulos = new char[pilkuton_koko];
	wstring stulos;
	wcout << "tayta_joukot!" << endl;
	wcout << "muuttujatlkm:" << muuttujatlkm << endl;
	wcout << "joukon_koko:" << joukon_koko << endl;
	wcout << "pilkuton_koko:" << pilkuton_koko << endl;
	wcout << "teksti2:" << teksti2 << endl;
	wcout << "joukko_nro:" << joukko_nro << endl;

	if (muuttujatlkm == 4 && joukko_nro == 0) {
		for (int a = 0; a < joukon_koko; a++) {
			//wcin >> muuttuja;
			if(teksti2[a] != ','){				
				stulos += teksti2[a];
				if(expilkku==pilkuton_koko-1 && stulo_laskuri == 1){
					wcout << "Joo" << endl;					
					tulos[pilkuton] = stoi(stulos);
					stulos.clear();
					wcout << "pilkuton:" << pilkuton << endl;					
				}		
				stulo_laskuri++;		
			}else{				
				tulos[pilkuton] = stoi(stulos);
				stulos.clear();
				wcout << "pilkuton:" << pilkuton << endl;				
				pilkuton++;
				expilkku++;
				stulo_laskuri=0;
			}			
			
			muuttuja = 0;
		}
		pilkuton =0 ;
	}
	else if (muuttujatlkm == 4 && joukko_nro == 1) {
		for (int b = 0; b < joukon_koko; b++) {			
			if(teksti2[b] != ','){
				stulos += teksti2[b];
				if(expilkku==pilkuton_koko-1 && stulo_laskuri == 1){
					wcout << "Joo" << endl;					
					tulos[pilkuton] = stoi(stulos);
					stulos.clear();
					wcout << "pilkuton:" << pilkuton << endl;					
				}		
				stulo_laskuri++;			
			}else{				
				tulos[pilkuton] = stoi(stulos);
				stulos.clear();
				wcout << "pilkuton:" << pilkuton << endl;				
				pilkuton++;
				expilkku++;
				stulo_laskuri=0;
			}			
			muuttuja = 0;
		}
		pilkuton = 0;
	}
	else if (muuttujatlkm == 4 && joukko_nro == 2) {
		for (int c = 0; c < joukon_koko; c++) {
			if(teksti2[c] != ','){
				stulos += teksti2[c];
				if(expilkku==pilkuton_koko-1 && stulo_laskuri == 1){
					wcout << "Joo" << endl;					
					tulos[pilkuton] = stoi(stulos);
					stulos.clear();
					wcout << "pilkuton:" << pilkuton << endl;					
				}		
				stulo_laskuri++;			
			}else{				
				tulos[pilkuton] = stoi(stulos);
				stulos.clear();
				wcout << "pilkuton:" << pilkuton << endl;				
				pilkuton++;
				expilkku++;
				stulo_laskuri=0;
			}
			muuttuja = 0;
		}
		pilkuton=0;
	}
	else if (muuttujatlkm == 4) {
		for (int d = 0; d < joukon_koko; d++) {			
			if(teksti2[d] != ','){
				stulos += teksti2[d];
				if(expilkku==pilkuton_koko-1 && stulo_laskuri == 1){
					wcout << "Joo" << endl;					
					tulos[pilkuton] = stoi(stulos);
					stulos.clear();
					wcout << "pilkuton:" << pilkuton << endl;					
				}		
				stulo_laskuri++;			
			}else{				
				tulos[pilkuton] = stoi(stulos);
				stulos.clear();
				wcout << "pilkuton:" << pilkuton << endl;				
				pilkuton++;
				expilkku++;
				stulo_laskuri=0;
			}			
			muuttuja = 0;
		}
		pilkuton = 0;
	}
	
	if (muuttujatlkm == 3 && joukko_nro == 0) {
		for (int a = 0; a < joukon_koko; a++) {
			//wcin >> muuttuja;
			if(teksti2[a] != ','){
				tulos[pilkuton] = palauta_joukon_alkio(a, teksti2);
				wcout << "teksti2:" << tulos[pilkuton] << endl;
				pilkuton++;			
			}
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
		pilkuton=0;
	}
	else if (muuttujatlkm == 3 && joukko_nro == 1) {
		for (int b = 0; b < joukon_koko; b++) {
			//wcin >> muuttuja;
			if(teksti2[b] != ','){
				tulos[pilkuton] = palauta_joukon_alkio(b, teksti2);
				wcout << "teksti2:" << tulos[pilkuton] << endl;
				pilkuton++;			
			}
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}
		pilkuton=0;
	}else if(muuttujatlkm == 3){
		for(int c=0; c < joukon_koko; c++){
			//wcin >> muuttuja;
			if(teksti2[c] != ','){
				tulos[pilkuton] = palauta_joukon_alkio(c, teksti2);
				wcout << "teksti2:" << tulos[pilkuton] << endl;
				pilkuton++;			
			}
			//joukko3.insert(muuttuja);
			muuttuja = 0;
		}	
		pilkuton=0;	
	}
	
	if (muuttujatlkm == 2 && joukko_nro == 0) {
		wcout << "Anna joukko1:" << endl;
		for (int a = 0; a < joukon_koko; a++) {
			//std::wcin >> muuttuja;
			//cin.get();
			if(teksti2[a] != ','){
				tulos[pilkuton] = palauta_joukon_alkio(a, teksti2);
				wcout << "teksti2:" << tulos[pilkuton] << endl;
				pilkuton++;
			}
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
		//joukon_pilkuton_koko = new int[pilkuton];	
		//joukon_pilkuton_koko[joukko_nro] = pilkuton;
		pilkuton=0;
	}else if(muuttujatlkm == 2){
		wcout << "Anna joukko2:" << endl;
		for(int b=0; b < joukon_koko; b++){
			//wcin >> muuttuja;
			if(teksti2[b] != ','){
				tulos[pilkuton] = palauta_joukon_alkio(b, teksti2);
				wcout << "teksti2:" << tulos[pilkuton] << endl;
				pilkuton++;
			}
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}
			
		//joukon_pilkuton_koko[joukko_nro] = pilkuton;
		pilkuton=0;				
	}
	//wcout << "joukon_pilkuton_koko:" << joukon_pilkuton_koko[joukko_nro] << endl;

	if (muuttujatlkm == 1 && joukko_nro == 0) {
		wcout << "Anna joukko1:" << endl;
		for (int d = 0; d < joukon_koko; d++) {
			//std::wcin >> muuttuja;
			//cin.get();
			if(teksti2[d] != ','){
				tulos[pilkuton] = palauta_joukon_alkio(d, teksti2);
				wcout << "teksti2:" << tulos[pilkuton] << endl;
				pilkuton++;			
			}
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
		pilkuton=0;
	}	
	
	return tulos;
}

int laske_joukon_koko(const char* teksti){
	int laskuri3=0;
	int muuttujien_lkm=0;

	for(int g=0; g < strlen(teksti); g++){
		//wcout << teksti[g] << endl;
		//if(teksti[g] != ','){
			laskuri3++;
		//}
	}
	muuttujien_lkm = laskuri3;
	wcout << "laske_joukon_koko:" << muuttujien_lkm << endl;
return muuttujien_lkm;
}

int laske_joukon_pilkuton_koko(const char* teksti3){
	int laskuri4=0;

	for(int h=0; h < strlen(teksti3); h++){
		if(teksti3[h] == ','){
			laskuri4++;
		}	
	}
return laskuri4+1;
}

int palauta_joukon_alkio(int kohta, const char* teksti2){
char paluu;

	paluu = teksti2[kohta];	
	wcout << "paluu:" << paluu << endl;
return atoi(&paluu);
}

bool ei_joukossa(int joukko1, int kohta, int koko, int maara) {
	int un = 0;
	//cout << endl;
	//cout << "maara:" << maara << endl;
	//cout << "kohta:" << kohta << endl;

	if (maara > 0) {
		for (int f = 0; f < maara; f++) {
		//	cout << "f:" << f << endl;
			//cout << "joukot[kohta][f]:" << joukot[kohta][f] << endl;
		//	cout << "perusjoukko[f]:" << perusjoukko[f] << endl;
		//	cout << "joukko1:" << joukko1 << endl;

			if (perusjoukko[f] != joukko1) {
		//		cout << "un:" << un << endl;
				un++;
			}

			/*
			if (joukot[kohta][f] != joukko1) {
				cout << "un:" << un << endl;
				un++;
			}*/
		}
		if (un == maara) {
			return true;
		}
		else {
		//	cout << "false" << endl;
			return false;
		}
	}
	else {
	//	cout << "true" << endl;
		return true;
	}
}

int** lauseke_postfix(int muuttujatlkm) {		
		
	//wcout << "Anna joukkojen lukumaara:" << endl;	
	//wcin >> muuttujatlkm;
	
	int e = 0, h=0;
	perusjoukko = new int[muuttujatlkm * 10];
	joukot = new int* [muuttujatlkm];
	joukon_koko = new int [muuttujatlkm];	
	gtk_widget_hide(win_joukko_lkm);

	 // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Syötä joukot:");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// Create a vertical box to hold widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

	for(int d=0; d < muuttujatlkm; d++){
		GtkWidget *entry2 = gtk_entry_new();
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), ("Joukon nimi: " + std::to_string(d + 1)).c_str());
        gtk_box_pack_start(GTK_BOX(vbox), entry2, FALSE, FALSE, 0);
        entries2.push_back(entry2);
	}

	for (int c = 0; c < muuttujatlkm; ++c) { // Adjust the number of inputs as needed
		wcout << c << endl;
        GtkWidget *entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry), ("Muuttujat: " + std::to_string(c + 1)).c_str());
        gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
        entries.push_back(entry);
    }

	wcout << "entries size:" << entries.size() << endl;
 
	// Add a submit button
    GtkWidget *button = gtk_button_new_with_label("OK");
    g_signal_connect(button, "clicked", G_CALLBACK(on_submit), &entries);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

	//for (int c = 0; c < muuttujatlkm; c++) {
		//wcout << "Joukon koko:" << endl;
		//wcin >> joukon_koko[c];
		
		//gtk_widget_show_all(win_joukon_koko);
		//wcout << "jkoko:" << jkoko << endl;
		//joukon_koko[c] = ;
	//}
	//exit(0);
	/*
		joukot[c] = tayta_joukot(joukon_koko[c], c);
		//int* koe = tayta_joukot(joukon_koko, c);
		for (int j = 0; j != joukon_koko[c]; j++) {
			//joukot[c][j] = koe[j];
			wcout << joukot[c][j] << endl;
			//cout << "joukot[" << c << "][" << j << "]:";
			//cout << koe[j] << endl;
		}
		//cout << "koe" << endl;		

		for (int d = 0; d < joukon_koko[c]; d++) {
			wcout << "joukot[" << c << "][" << d << "]:" << joukot[c][d] << endl;

			if (ei_joukossa(joukot[c][d], c, joukon_koko[c], e)) {
				//cout << "ei joukossa:" << joukot[c][d] << endl;
				perusjoukko[e] = joukot[c][d];
				//universumi[e] = joukot[c][d];
				//cout << "universumi:" << universumi[e] << endl;
				//cout << "e:" << e << endl;
				e++;				
			}
		}
		
	}
	
	universumi = new int[e];
	wcout << "universumi:" << endl;

	for (int g = 0; g < e; g++) {
		universumi[g] = perusjoukko[g];
		//cout << universumi[g] << ",";
	}

	std::vector<int> jarjestys(universumi, universumi + e);
	std::sort(jarjestys.begin(), jarjestys.begin() + e);

	for (std::vector<int>::iterator it2 = jarjestys.begin(); it2 != jarjestys.end(); ++it2) {
		universumi[h] = *it2;
		std::wcout << ' ' << universumi[h];
		h++;
	}
	ukoko = e;
	for (int ddd = 0; ddd < 2; ddd++) {
		wcout << "joukot[" << 0 << "][" << ddd << "]:" << joukot[0][ddd] << endl;
	}*/
	return joukot;
}

bool osajoukko(int *joukko1, int *joukko2, int maara1, int maara2) {
	int tulos = 0;
	bool palautus = false;

	for (int eee = 0; eee < maara1; eee++) {
		for (int fff = 0; fff < maara2; fff++) {
			if (joukko1[eee] == joukko2[fff]) {
				wcout << joukko1[eee] << ", " << joukko2[fff] << endl;
				tulos++;
			}
		}
	}
	if (tulos == maara1) {
		palautus = true;
	}
	return palautus;
}

wstring muunna_postfix(wchar_t s[MAXOP]) {
	
	wcout << L"Anna lauseke:" << endl;
	
	//wcin >> s;
	wstring infix(s);
	
	/*
	
	std::wstring infix;
	std::wcin.sync();
	std::getline(std::wcin, infix); // Read a full line of input into a wstring
	std::getline(std::wcin, infix);
	std::wcout << L"You entered: " << infix << std::endl;
	*/
	
	//wcout << L"infix: " << infix << endl;
	//muuttujatlkm = collectMlkm(infix);
	wcout << "Muuttujien lkm:" << muuttujatlkm << endl;
	//infix = concats(infix);
	wcout << L"infix:" << infix << endl;
	
	mlkm2 = muuttujatlkm;
	wstring postfix = convert(infix);
	
	return postfix;
}

int* muunnaBinaari2(int bitti, int jakotulos, GtkTextBuffer *buffer, bool tulostus){
	int *tulos = new int[bitti];
	int laskuri2=0;
	int jakojaannos=0;
	const gchar* gstr;
	wcout << "muunnaBinaari2:" << endl;
	wcout << "bitti:" << bitti << endl;
	wcout << "jakotulos:" << jakotulos << endl;
	wcout << "tulostus:" << tulostus << endl;

	funktio:	
//laskuri++;

	//if(jakotulos > 2)
		jakojaannos = jakotulos;
		jakotulos = jakotulos/2;
		jakojaannos = jakojaannos%2;
	//else
	//	jakotulos = 2/jakotulos;
	tulos[laskuri2]=jakojaannos;
	
	//if(jakotulos>0)goto funktio;
	//else goto end;
	if(laskuri2 == bitti-1){
		goto end;
	}else{
		//taulukko[laskuri]=0;
		if(jakotulos==0){
			//cout << "-" << endl;
		}
		laskuri2++;
		goto funktio;
	}

end:	
	luku3.clear();

	if(tulostus){
		for(int a=bitti-1; a>=0; a--){
			wcout << tulos[a];
			luku3 += std::to_string(tulos[a]);			
		}
		luku3 += "\n";
		gstr = g_strdup(luku3.c_str());
		gtk_text_buffer_set_text(buffer, gstr, -1);
		//insert_text_at_position(buffer, gstr, luku3.length());
	}
	//luku3.erase();
	
return tulos;
}

int* muunnaBinaari(int* lopputulos, int koko) {
	int* tulos = new int[koko];
	int laskuri2 = 0;

	wcout << "muunnaBinaari:" << endl;

	for (int zz = koko-1; zz >= 0; zz--) {
		wcout << zz;
		wcout << " " << lopputulos[zz] << endl;
		/*if (lopputulos[zz] >= 0 && lopputulos[zz] < 32) {
			wcout << 1;
		}
		else {
			wcout << 0;
		}*/
	}

	return tulos;
}

std::string wcharToString(const wchar_t* wideStr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wideStr);
}

char* g_strdup_wide_string(const wchar_t* wide_str) {
    if (!wide_str) {
        return nullptr; // Handle null input gracefully
    }

    // Set the locale for proper wide-to-multibyte conversion
    std::setlocale(LC_ALL, "");

    // Get the required buffer size for the conversion
    size_t buffer_size = std::wcstombs(nullptr, wide_str, 0) + 1;
    if (buffer_size == 0) {
        return nullptr; // Conversion failed
    }

    // Allocate a buffer for the multibyte string
    char* narrow_str = new char[buffer_size];
    std::wcstombs(narrow_str, wide_str, buffer_size);

    // Duplicate the string using g_strdup
    char* duplicated_str = g_strdup(narrow_str);

    // Clean up the temporary buffer
    delete[] narrow_str;

    return duplicated_str;
}


/**
* Tutki laske_lausekkeen kaikki mahdolliset (unioni jne.) ja lisää binäärinen tulos textboxiin!
* Jatka tästä, lisää Suorite -tekstiboxiin kaikki
 */

int* laske_lauseke(const wchar_t* toinen, int** tmp2) {
	std::vector<int> v;
	std::vector<int> vluku2;
	std::vector<int> vluku1;
	std::vector<int>::iterator it;
	std::ostringstream oss;
	wchar_t tyyppi;
	gchar* gstr;
	char* dstr;
	//string muunnos;
	int* t3 = new int[0];
	bool oj = false;
	//int tyyppi=0, 
	int i = 0, j=0;
	int* luku1;
	int* luku2;
	int* tulos;
	int* tulos2;
	int* osajoukko2;
	int laskuri = 0;
	int lkoko3 = 0;
	int lkoko4 = 0;
	int lkoko5 = 0;
	int lkoko = 0;
	int lkoko2 = 0;
	int pot=0;
	int bin=0;

	wcout << "toinen:" << toinen << endl;
	val = new int* [palautaKoko()];
	ival = new int [palautaKoko()];
	wcout << "Lausekkeen koko:" << palautaKoko() << endl;
	GtkTextBuffer *buffer7 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(suorite));
	GtkTextBuffer *buffer8 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(binaari_tulos));
	laskuri = muuttujatlkm - 1;
	//laskuri = haeMlkm()-2;
	//cout << "haeMlkm:" << laskuri << endl;
	while ((tyyppi = toinen[i]) != '\0') {
		//while((type = getop(s)) != 10){
		wcout << "toinen[i]:" << toinen[i] << endl;
		switch (tyyppi) {
		case 0x2282:
			wcout << "Well congrats unicode!" << endl;
			luku2 = pop();
			luku1 = pop();
			lkoko = size_pop();
			lkoko2 = size_pop();
			oj = osajoukko(luku1, luku2, lkoko2, lkoko);
			std::wcout << std::boolalpha;
			wcout << L"\u2282:\n";
			
			osajoukko2 = new int[1];
			//wcout << "osajoukko2:" << endl;
						
			if (oj) {
				wcout << 1 << endl;
				osajoukko2[0] = 1;
				push(osajoukko2, 1);
			}
			else {
				wcout << 0 << endl;
				osajoukko2[0] = 0;
				push(osajoukko2, 1);
			}
			luku2 = new int[0];
			luku1 = new int[0];
			lkoko = 0;
			lkoko2 = 0;
			oj = false;
			break;
		case 0x0057:
			/*
			for (int dd = 0; dd < 2; dd++) {
				wcout << "tmp2[" << 0 << "][" << dd << "]:" << tmp2[0][dd] << endl;
			}
			*/
			// JATKA T�ST�, tarkkaile W:n arvoa !!!
			wcout << "W:";
			//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
			//wstring ws = L"W:";
			luku3 += "W: ";
			//string koe = wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(luku3);
			//string koe2 = wcharToString(koe);
			
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			
			// Lisää nyt luku3:een ja gstr:ään myös lukuarvo (esim. 3)
			for (int j = 0; j != joukon_pilkuton_koko[0]; j++) {
				//joukot[c][j] = koe[j];
				wcout << joukot[0][j] << endl;
				//oss << **(joukot + j);
				//string muunnos = oss.str();
				string muunnos = to_string(joukot[0][j]);
				wcout << "muunnos:" << wstring(muunnos.begin(), muunnos.end()) << endl;
				muunnos += " ";
				luku3 += muunnos;
				//cout << "joukot[" << c << "][" << j << "]:";
				//cout << koe[j] << endl;
			}
			luku3 += "\n";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			
			// joukot[0] viittaa annettuun joukkoon W!!
			//push(joukot[0], joukon_koko[0]);
			push(joukot[0], joukon_pilkuton_koko[0]);
			wcout << "joukot ohi" << endl;
			wcout << endl;
			
			//cout << "laskuri:" << laskuri << endl;
			break;
		case 0x0058:
			wcout << "X:";
			luku3 += "X: ";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			//cout << "laskuri:" << laskuri << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;
			for (int j = 0; j != joukon_pilkuton_koko[1]; j++) {
				//joukot[c][j] = koe[j];
				wcout << joukot[1][j] << endl;
				//oss << **(joukot + j);
				//string muunnos = oss.str();
				string muunnos = to_string(joukot[1][j]);
				wcout << "muunnos:" << wstring(muunnos.begin(), muunnos.end()) << endl;
				muunnos += " ";
				luku3 += muunnos;
				//cout << "joukot[" << c << "][" << j << "]:";
				//cout << koe[j] << endl;
			}
			luku3 += "\n";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			// joukot[1] viittaa annettuun joukkoon X!!
			//push(joukot[1], joukon_koko[1]);
			push(joukot[1], joukon_pilkuton_koko[1]);
			//cout << "B(" << laskuri << "):" << B[laskuri] << endl;
			//muunnaBinaari(pot, B[laskuri], true);
			wcout << endl;
			break;
		case 0x0059:
			cout << "Y:";
			luku3 += "Y: ";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			//cout << "laskuri:" << laskuri << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;
			for (int j = 0; j != joukon_pilkuton_koko[2]; j++) {
				//joukot[c][j] = koe[j];
				wcout << joukot[2][j] << endl;
				//oss << **(joukot + j);
				//string muunnos = oss.str();
				string muunnos = to_string(joukot[2][j]);
				wcout << "muunnos:" << wstring(muunnos.begin(), muunnos.end()) << endl;
				muunnos += " ";
				luku3 += muunnos;
				//cout << "joukot[" << c << "][" << j << "]:";
				//cout << koe[j] << endl;
			}
			luku3 += "\n";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			//pot = pow(2, muuttujatlkm);
			push(joukot[2], joukon_pilkuton_koko[2]);
			//muunnaBinaari(pot, C[laskuri], true);
			cout << endl;
			break;
		case 0x005A:
			cout << "Z:";
			luku3 += "Z: ";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			//cout << "laskuri:" << laskuri << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;
			for (int j = 0; j != joukon_pilkuton_koko[3]; j++) {
				//joukot[c][j] = koe[j];
				wcout << joukot[3][j] << endl;
				//oss << **(joukot + j);
				//string muunnos = oss.str();
				string muunnos = to_string(joukot[3][j]);
				wcout << "muunnos:" << wstring(muunnos.begin(), muunnos.end()) << endl;
				muunnos += " ";
				luku3 += muunnos;
				//cout << "joukot[" << c << "][" << j << "]:";
				//cout << koe[j] << endl;
			}
			luku3 += "\n";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer7, gstr, -1);
			//pot = pow(2, muuttujatlkm);
			push(joukot[3], joukon_pilkuton_koko[3]);
			//muunnaBinaari(pot, D[laskuri], true);
			cout << endl;
			break;
		case 0x0030:
			cout << "0:";
			//push(nolla[laskuri]);
			//muunnaBinaari(pot, nolla[laskuri], true);
			//cout << endl;
			break;
		case 0x0031:
			cout << "1:";
			//pot = pow(2, muuttujatlkm);
			//cout << "Numero:" << yksi[laskuri] << endl;
			//push(yksi[laskuri]);
			//muunnaBinaari(pot, yksi[laskuri], true);
			cout << endl;
			break;
		case 0x222A:
			// T�h�n laske pop() OR pop() ja push() pinoon
			// push(pop() + pop()
			j = 0;
			wluku3.clear();
			
			// Laske tässä kohdassa UNIONI
			luku2 = pop();
			luku1 = pop();
			lkoko3 = size_pop();
			lkoko4 = size_pop();
			//pot = pow(2, muuttujatlkm);
			//lkoko3 = sizeof(luku1) / sizeof(luku1[0]);
			//lkoko4 = sizeof(luku2) / sizeof(luku2[0]);
			
			wcout << "lkoko3:" << lkoko3 << endl;
			wcout << "lkoko4:" << lkoko4 << endl;

			for (int dd = 0; dd < lkoko3; dd++) {
				wcout << "luku2:" << luku2[dd] << endl;
				vluku2.push_back(luku2[dd]);
			}

			for (int ee = 0; ee < lkoko4; ee++) {
				wcout << "luku1:" << luku1[ee] << endl;
				vluku1.push_back(luku1[ee]);
			}

			wcout << "vluku1 size:" << vluku1.size() << endl;
			wcout << "vluku2 size:" << vluku2.size() << endl;
			
			std::set_union(vluku1.begin(), vluku1.end(), 
						   vluku2.begin(), vluku2.end(), 
						   std::back_inserter(v));
			//it = std::set_union(luku1, luku1 + lkoko4, luku2, luku2 + lkoko3,
			//	v.begin());
			//v.resize(it - v.begin());
			//tulos = laske(pot, luku1, luku2, 'A');
			
			//cout << "+:";
			wcout << L"\u222A:\n";
			//JATKA TÄTÄ
			wluku3 += L"\u222A: ";
			
			//string koe = wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(luku3);
			//string koe2 = wcharToString(koe);
						
			luku3 += wstring_to_utf8(wluku3);
			gtk_text_buffer_set_text(buffer7, luku3.c_str(), -1);

			wcout << endl;
			tulos2 = new int[v.size()];
			//wcout << "v.size():" << v.size() << endl;

			for (it = v.begin(); it != v.end(); ++it) {
				tulos2[j] = *it;
				std::wcout << ' ' << tulos2[j];
				t3[j] = *it;
				luku3 += to_string(tulos2[j]);
				luku3 += ' ';
				j++;
			}
			luku3 += "\n";
			gtk_text_buffer_set_text(buffer7, luku3.c_str(), -1);
			//cout << "j:" << j << endl;
			wcout << endl;
			push(tulos2, j);
			//t3 = muunnaBinaari(pot, tulos, true);
			/*for (auto it = v.begin(); it != v.end(); ++it) {
				it = v.erase(it);
			}*/
			v.clear();
			vluku1.clear();
			vluku2.clear();
			//memset(luku2, 0, lkoko3);
			//memset(luku1, 0, lkoko4);
			wcout << endl;
			break;
		case 0x2229:
			// T�h�n laske pop() AND pop() ja push() pinoon				
			//push(pop() * pop());
			//std::vector<int>::iterator it;
			// Laske tässä kohdassa LEIKKAUS
			//cout << "*" << endl;
			j = 0;
			wluku3.clear();
			luku2 = pop();
			luku1 = pop();
			lkoko = size_pop();
			lkoko2 = size_pop();			

			wcout << "lkoko:" << lkoko << endl;
			wcout << "lkoko2:" << lkoko2 << endl;

			for (int bb = 0; bb < lkoko; bb++) {
				wcout << "luku2:" << luku2[bb] << endl;
				vluku2.push_back (luku2[bb]);
			}

			for (int cc = 0; cc < lkoko2; cc++) {
				wcout << "luku1:" << luku1[cc] << endl;
				vluku1.push_back (luku1[cc]);
			}
			//pot = pow(2, muuttujatlkm);
			//lkoko = sizeof(luku1) / sizeof(luku1[0]);
			wcout << "\nluku2.size:" << sizeof(luku2) / sizeof(int*) << endl;

			//cout << "lkoko:" << lkoko << endl;
			//cout << "lkoko2:" << lkoko2 << endl;
			
			std::set_intersection(vluku2.begin(), vluku2.end(),	vluku1.begin(), vluku1.end(), std::back_inserter(v));

			//std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
			//	std::back_inserter(v_intersection));


			//it = set_intersection(luku2, luku2 + lkoko,
			//	luku1, luku1 + lkoko2, v.begin());

			wcout << "set_intersection ohi" << endl;
			//v.resize(it - v.begin());
			wcout << "v.size:" << v.size() << endl;

			tulos = new int[v.size()];
			wcout << "tulos.size:" << sizeof(tulos) / sizeof(int*) << endl;

			//cout << "*:";
			wcout << L"\u2229:\n";

			wluku3 += L"\u2229: ";
			
			//string koe = wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(luku3);
			//string koe2 = wcharToString(koe);
						
			luku3 += wstring_to_utf8(wluku3);
			gtk_text_buffer_set_text(buffer7, luku3.c_str(), -1);

			//gtk_text_buffer_set_text(buffer7, gstr, -1);

			//wcout << endl;
			for (it = v.begin(); it != v.end(); ++it) {
				tulos[j] = *it;
				std::wcout << ' ' << tulos[j];
				luku3 += to_string(tulos[j]);
				luku3 += ' ';
				t3[j] = *it;
				j++;
			}
			luku3 += "\n";
			gtk_text_buffer_set_text(buffer7, luku3.c_str(), -1);
			wcout << endl;
			//tulos = laske(pot, luku1, luku2, 'K');
			//cout << "j:" << j << endl;
			//cout << "\ntulos.size:" << sizeof(tulos) / sizeof(int*) << endl;
			push(tulos, j);	
			//cout << "push ohi" << endl;
			//t3 = muunnaBinaari(pot, tulos, true);
			
			/*for (auto it = v.begin(); it != v.end(); ++it) {
				it = v.erase(it);				 
			}*/
			
			v.clear();
			vluku1.clear();
			vluku2.clear();
			//memset(luku2, 0, lkoko2);
			//memset(luku1, 0, lkoko);

			break;
		case 0x0027:
			// T�M� ON NOT
			luku1 = pop();
			// Hei, katso allaolevaa riviä vielä
			lkoko5 = sizeof(luku1) / sizeof(luku1[0]);
			wcout << "luku1:" << luku1[0] << "," << luku1[1] << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "Not:" << luku1;
			//cout << "Luku2:" << luku2 << endl;
			//cout << "2 potenssi muuttujien lkm:" << pot << endl;
			it = set_difference(universumi, universumi + ukoko,
				luku1, luku1 + lkoko5, v.begin());
			v.resize(it - v.begin());
			wcout << "\nv.size():" << v.size() << endl;

			tulos = new int[v.size()];

			wcout << "':";
			wcout << endl;
			for (it = v.begin(); it != v.end(); ++it) {
				tulos[j] = *it;
				std::wcout << ' ' << tulos[j];
				//t3[j] = *it;
				j++;
			}
			//tulos2 = not(bb, luku1);
			wcout << "\nj:n arvo on:" << j << endl;
			wcout << "\ntulos.size:" << sizeof(tulos) / sizeof(int*) << endl;
			push(tulos, j);
			/*
			for (auto it = v.begin(); it != v.end(); ++it) {
				it = v.erase(it);
			}
			*/
			v.clear();
			//memset(luku2, 0, lkoko2);
			memset(luku1, 0, lkoko);
			//cout << "':";
			//t3 = muunnaBinaari(pot, tulos2, true);
			wcout << endl;
			break;
		case 0x22BB:
			// T�h�n laske pop() XOR pop() ja push() pinoon
			// push(pop() + pop()
			luku2 = pop();
			luku1 = pop();
			//pot = pow(2, muuttujatlkm);
			//tulos = laske(pot, luku1, luku2, 'E');
			//tulos2 = not(bb, tulos);
			//push(tulos2);
			wcout << "=:";
			//t3 = muunnaBinaari(pot, tulos2, true);
			wcout << endl;
			break;
		case '\n':
			//cout << "Loppu:" << pop() << endl;
			break;
		default:
			wcout << "Virhe: Tuntematon komento" << s << endl;
			break;
		}
		i++;
	}

	luku2 = pop();
	luku1 = pop();
	lkoko = size_pop();
	lkoko2 = size_pop();

	wcout << "lkoko:" << lkoko << endl;
	wcout << "lkoko2:" << lkoko2 << endl;

	for (int bb = 0; bb < lkoko; bb++) {
		wcout << "luku2:" << luku2[bb] << endl;
		bin += pow(2, bb); 
	}

	for (int cc = 0; cc < lkoko2; cc++) {
		wcout << "luku1:" << luku1[cc] << endl;
	}
	if(lkoko > 1){
		pot = pow(2, muuttujatlkm);	
	}else{
		pot = pow(2, muuttujatlkm);	
	}
	wcout << "pow:" << pow(2, muuttujatlkm) << endl;
	wcout << "bin:" << bin << endl;
	//int * mb = muunnaBinaari(luku2, pow(2, muuttujatlkm));
	//int * mb = muunnaBinaari(luku2, lkoko);
	//int bitti, int jakotulos, GtkTextBuffer *buffer, bool tulostus

	int * mb = muunnaBinaari2(pot, bin, buffer8, true);
	return 0;
}
/*
void SetFontExample(HDC hdc) {
	HFONT hFont = CreateFont(
		24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial")
	);

	SelectObject(hdc, hFont);
	TextOut(hdc, 10, 10, TEXT("Hello, World!"), 13);

	DeleteObject(hFont);
}
	*/
/*
int* muunnaBinaari(int* lopputulos, int koko) {
	int* tulos = new int[koko];
	int laskuri2 = 0;

	wcout << "muunnaBinaari:" << endl;

	for (int zz = 0; zz < koko; zz++) {
		if (lopputulos[zz] > -1) {
			wcout << 1;
		}
		else {
			wcout << 0;
		}		 
	}

	return tulos;
}
*/

/*
* Huomaa että setmode -funktio tarvitsee stdin sekä stdout -määreet jotta sisäänpäin kulkeva tieto on
* unicode muodossa!
*/

//int wmain(void) {
int main(int argc, char* argv[]){
	int* tulos3;
	//_setmode(_fileno(stdin), _O_U16TEXT);
	//_setmode(_fileno(stdout), _O_U16TEXT);

	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	//gtk_builder_add_from_file (builder, "joukot.glade", NULL);
	GError *error = NULL;
	if (!gtk_builder_add_from_file(builder, "../joukot.glade", &error)) {
    		g_error("VIRHE: Glade-tiedoston lataus epäonnistui! Syy: %s", error->message);
	}
	isanta = (GtkWidget *)gtk_builder_get_object(builder, "ikkuna");
	
	if (isanta == NULL) {
    		g_error("Hups! Ikkunaa 'ikkuna' ei löytynyt Glade-tiedostosta!");
	}
	// Pakotetaan ikkuna muuttamaan kokonsa 800x600 pikseliin
	gtk_window_resize(GTK_WINDOW(isanta), 800, 600);
	g_signal_connect(isanta, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	kaanteinen_joukko = (GtkWidget *)gtk_builder_get_object(builder, "kaanteinen_joukko");
	suorite = (GtkWidget *)gtk_builder_get_object(builder, "suorite");
	binaari_tulos = (GtkWidget *)gtk_builder_get_object(builder, "binaari_tulos");

	win_joukon_nimi = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	win_joukon_koko = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	win_muuttuja = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	win_lauseke = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	win_joukko_lkm = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	GtkMenuItem *menu_item = GTK_MENU_ITEM(gtk_builder_get_object(builder, "lataa"));
	GtkMenuItem *menu_item2 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tallenna"));
	GtkMenuItem *menu_item3 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "poistu"));
	GtkMenuItem *menu_item4 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "sulje"));
	GtkMenuItem *menu_item5 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "syota"));
	GtkMenuItem *menu_item6 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tyhjenna"));
	GtkMenuItem *menu_item7 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "syota_joukko"));
	GtkMenuItem *menu_item8 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tieto"));

	text_view = gtk_text_view_new();
    GtkWidget *btn = gtk_button_new_with_label("Lisää nimi");
    g_signal_connect (btn, "clicked", G_CALLBACK(joukko_nimi), NULL);

	text_view2 = gtk_text_view_new();
	GtkWidget *btn2 = gtk_button_new_with_label("Lisää koko");
	g_signal_connect(btn2, "clicked", G_CALLBACK(joukko_koko), NULL);

	text_view3 = gtk_text_view_new();
	GtkWidget *btn3 = gtk_button_new_with_label("Lisää muuttuja");
	g_signal_connect(btn3, "clicked", G_CALLBACK(joukko_muuttujat), NULL);

	text_view4 = gtk_text_view_new();
	GtkWidget *btn4 = gtk_button_new_with_label("Suorita");
	g_signal_connect(btn4, "clicked", G_CALLBACK(suorita), NULL);

	text_view5 = gtk_text_view_new();
	GtkWidget *btn5 = gtk_button_new_with_label("Lisää joukkojen lkm");
	//g_signal_connect(btn5, "clicked", G_CALLBACK(), NULL);
	g_signal_connect(btn5, "clicked", G_CALLBACK(joukko_lkm), NULL);


	gtk_widget_set_size_request(text_view, 300, 200);
    GtkWidget *box = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), text_view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

	gtk_widget_set_size_request(text_view2, 300, 200);
	GtkWidget *box2 = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box2), text_view2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box2), btn2, TRUE, TRUE, 0);

	gtk_widget_set_size_request(text_view3, 300, 200);
	GtkWidget *box3 = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box3), text_view3, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box3), btn3, TRUE, TRUE, 0);

	gtk_widget_set_size_request(text_view4, 300, 200);
	GtkWidget *box4 = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box4), text_view4, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box4), btn4, TRUE, TRUE, 0);

	gtk_widget_set_size_request(text_view5, 300, 200);
	GtkWidget *box5 = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box5), text_view5, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box5), btn5, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(win_joukon_nimi), box);
	gtk_container_add(GTK_CONTAINER(win_joukon_koko), box2);
	gtk_container_add(GTK_CONTAINER(win_muuttuja), box3);
	gtk_container_add(GTK_CONTAINER(win_lauseke), box4);
	gtk_container_add(GTK_CONTAINER(win_joukko_lkm), box5);

	gtk_window_set_default_size(GTK_WINDOW(win_joukon_nimi), 400, 300);
	gtk_window_set_default_size(GTK_WINDOW(win_joukon_koko), 400, 300);
	gtk_window_set_default_size(GTK_WINDOW(win_muuttuja), 400, 300);
	gtk_window_set_default_size(GTK_WINDOW(win_lauseke), 400, 300);
	gtk_window_set_default_size(GTK_WINDOW(win_joukko_lkm), 400, 300);
	
	g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_lataa), NULL);
	g_signal_connect(menu_item2, "activate", G_CALLBACK(on_menu_item_tallennus), NULL);
	g_signal_connect(menu_item3, "activate", G_CALLBACK(on_menu_item_poistu), NULL);
	g_signal_connect(menu_item4, "activate", G_CALLBACK(on_menu_item_poistu), NULL);
	g_signal_connect(menu_item6, "activate", G_CALLBACK(on_menu_item_tyhjenna), NULL);
	g_signal_connect(menu_item7, "activate", G_CALLBACK(on_menu_item_joukko_lkm), NULL);
	g_signal_connect(menu_item5, "activate", G_CALLBACK(on_menu_item_suoritus), NULL);
	g_signal_connect(menu_item8, "activate", G_CALLBACK(on_menu_item_tietoa), NULL);

	gtk_widget_show(isanta);
	gtk_main();
	/*
	const wchar_t teksti = L'\u2229';
	//std::wcout << L"Hello, ⊃ or \u2282!\n";
	if (teksti == L'\u2229') {
		std::wcout << teksti << endl;
	}
	else {
		std::cout << "Ei ole!" << endl;
	}
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);
	
	//std::wcin.imbue(std::locale("en_US.UTF-8")); // Set UTF-8 locale for input
	//std::wcout.imbue(std::locale("en_US.UTF-8")); // Set UTF-8 locale for output
	
	//std::locale::global(std::locale(""));

	wchar_t input;
	std::wcout << L"Enter a Unicode character: ";
	std::wcin >> input;
	if (!std::wcin.good()) return -1;
	
	std::wcout << L"You entered: " << input << std::endl;
	
	exit(0);	
	*/
	exit(0);
	
	/*
	int** tmp = lauseke_postfix();	
	wstring lauseke = muunna_postfix();
	wcout << "lauseke:" << lauseke << endl;	

	tulos3 = laske_lauseke(lauseke.c_str(), tmp);
	*/

	int t1[] = {0,1};
	int t2[] = {1,2,3};
	int m1 = 2;
	int m2 = 3;
	std::cout << std::boolalpha;
	cout << "osajoukko:" << osajoukko(t1, t2, m1, m2) << endl;
/*
	set_type joukko1, joukko2, joukko3, joukko4, joukko5, u;
	joukko1.insert(2);
	joukko1.insert(3);
	cout << joukko1 << endl;
	joukko2.insert(1);
	joukko2.insert(3);
	cout << joukko2 << endl;
	u.insert(0);
	u.insert(1);
	u.insert(2);
	u.insert(3);

	set_union(joukko1.begin(), joukko1.end(), joukko2.begin(), joukko2.end(),
		inserter(joukko3, joukko3.begin()));

	cout << "Yhdiste on:" << joukko3 << endl;

	set_intersection(joukko1.begin(), joukko1.end(),
		joukko2.begin(), joukko2.end(), inserter(joukko4, joukko4.begin()));

	cout << "Leikkaus on:" << joukko4 << endl;

	set_difference(u.begin(), u.end(),
		joukko1.begin(), joukko1.end(), inserter(joukko5, joukko5.begin()));

	cout << "Komplementti on:" << joukko5 << endl;*/
	//cin.get();

	return 0;
}

