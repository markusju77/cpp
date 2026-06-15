/**
*
Anna merkkijono k��nteinen Lukasievich -muodossa esim. A B + A C + *
Anna merkkijono (A'*C)+(A'*B)+(A*B'*C') muodossa
Ohjelma laskee merkkijonon loogisen arvon.
Muoto voi olla my�s lyhyempi, kuten AB*AC+*.
Huomaa unordered_map:in tuonti sovellukseen!!
F(A,B,C)=((A'*C)+(A'*B)+(A*B'*C')) OK OK <= T�M� LAUSEKE ON V��R�NLAINEN �L� K�YT� T�T�!
F(A,B,C)=((A'*C)+(A'*B)+((A*B')*C')) T�SS� TOINEN VERSIO LAUSEKKEESTA  J A T K A ! !
POS:
F(A,B,C)=((A'+C')*(A'+B')*((A+B)+C))
SOP:
F(A,B,C)=((A'*C)+(A'*B)+((A*B')*C'))

SOP:
F(A,B,C)=((A'*C)+(B')) OK OK
POS:
F(A,B,C)=((B'+C)*(A'+B')) OK

F(A,B,C)=((A*(B+C))') OK OK 

F(A,B,C)=((A*B)+(A*C)) OK OK 

F(A,B,C)=((A*(B+C))) OK	OK		Katso my�s max termit(c:\users\marku\ba.txt)
Joka on F(A,B,C)=(((A*(B+C)))=((A*B)+(A*C)))=((A'+C)+(B+A)) OK OK
F(A,B,C)=((A'+B')+(C'+C)+(B+A)) OK OK
F(B,C,D)=((B*C')+(B*D)) OK NOT WORKING
F(A)=((A'+A)) OK OK
												
Yll�oleva lauseke on oikein
Parittomien testaukseen:
F(A,B,C)=(((A'*B'*C')+(A*B'*C)+(A*B*C)))=((A*C)+(A'*B'*C'))  OK OK
F(A,B,C)=((A'*B'*C')+(A'*B*C)+(A*B'*C)) OK OK
Nelj�n muuttujan testaus:
F(A,B,C,D)=((A*B)+(C*D)) OK OK
F(B,C,D)=((B*C')+(B*D)) OK
F(D)=((D*D')) OK
Kolmen muuttujan testaus:
F(B,C)=((B*C)+(B'*C')) OK
F(C)=((C*C')) OK

Uusi p�ivitetty versio sy�tett�v�n lauseen sy�tt� formaatissa:
F(A,B,C)=((A'+A)) OK
F(A,B)=((A+(A*B))) OK OK
jotta saadaan kahdeksan bittinen tulos!
Uusin p�ivitetty versio ottaa vastaan yht� ja nollaa! Seuraavat lauseet toimivat:
F(A)=((A+0)) OK
F(A)=((A*0)) OK
F(A)=((A+1)) OK
F(A)=((A*1)) T�M� !!! MELKEIN KAIKKI OK
Nyt lis�t��n sovellukseen lausekkeen sy�tt� parametrin�!

SOP, jonka tulos on 1:
F(A,B,C)=((A'+B')+(C'+C)+(B+A)) OK
POS:
G(A,B,C)=((A'+B')+(C'+C)+(B+A))

SOP, jonka tulos on 0:
F(A,B,C)=((A*B)*(C*C')*(B'*A')) OK
F(A,B)=(((A*B)+A))
K��nn� sovellus
*/
// Gtk -luokkakirjasto lisätty
#include <gtk/gtk.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include "infix_to_postfix.h"
#include "quine_mccluskell.h"
#include "karnaugh.h"
#include "asm_ba.h"
using pari = pair<int, tietue>;
using namespace std;
int* stotuustaulu(bool tulostus);
void insert_text_at_position(GtkTextBuffer *buffer, const gchar *text, gint position);
int* muunnaString_int_array(string binaari, int koko2);

#define MAXVAL	100
#define MAXOP	100
#define NUMBER	'0'
#define CHAR	'A'
#define BUFSIZE	100

GtkWidget   *isanta;
GtkWidget   *Painike;
GtkWidget   *lapsi;
GtkBuilder  *builder;
GtkWidget *window;
GtkWidget *window2;
GtkWidget *text_view;
GtkWidget *text_view2;
GtkWidget *postfix;
GtkWidget *totuustaulu;
GtkWidget *sop;
GtkWidget *pos;
GtkWidget *selected_entry = nullptr;
gchar* gstr;
gchar *text;
gchar *text2;
gchar *tyhjennys;
string spostfix;
bool debug=FALSE;

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);

int sp = 0;
double val[MAXVAL];
int laskuri=0;
//int laskuri3 = 0;
int jakojaannos=0;

double mlkm2 = 0.0;
int ppause=0;
int bb=16;

int b = 0;

size_t koko = 16;
char s[MAXOP];

int A[4]={1, 3, 15, 255};
int B[4]={-1,5, 51, 3855};
int C[4]={-1,-1,85, 13107};
int D[4]={-1,-1,-1, 21845};

int nolla[4] = {0,0,0,0};
int yksi[4] = {3, 15, 255, 65535};

//char merkit[4] = {'A','B','C','D'};

int pot;
int muuttujatlkm;
string luku3;

string lauseke_postfix_gtk(gchar *ginfix, bool debug){
	std::stringstream ss;
	ss << ginfix;
	std::string infix = ss.str();
	//string infix(ginfix);
	cout << "infix: " << infix << endl;
	muuttujatlkm = collectMlkm(infix, debug);
	if(debug) cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	infix = concats(infix);
	if(debug) cout << "infix:" << infix << endl;
	mlkm2 = muuttujatlkm;
	return convert(infix, debug);		
}

string lauseke_muuttujatlkm(gchar *ginfix, bool debug){
	std::stringstream ss;
	ss << ginfix;
	std::string infix = ss.str();
	//string infix(ginfix);
	cout << "infix: " << infix << endl;
	muuttujatlkm = collectMlkm(infix, debug);
	if(debug) cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	mlkm2 = muuttujatlkm;
	infix = concats(infix);
	cout << "infix:" << infix << endl;
return infix;
}

void suorita(GtkWidget *wid, gpointer ptr){
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(postfix));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, debug);
    
    //Siirrä allaoleva liitos myöhemmin text_view liitokseen!
    //gtk_text_buffer_set_text(buffer2, text, -1);
	g_print(text);
	spostfix = lauseke_postfix_gtk(text, debug);
	const gchar* gstr = spostfix.c_str();
	gtk_text_buffer_set_text(buffer2, gstr, -1);
	gtk_widget_hide(window);
	int* tt = stotuustaulu(false);
	//GtkTextBuffer *buffer3 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sop));
	
	bool bs = lopputulos_SOP(tt, pot, muuttujatlkm);
	//cout << "\nrakennaTaulukko2:" << endl;
	rakennaTaulukko2();
	muuttujienAlustus();
	cout << "muuttujienParitus1:" << endl;
	muuttujienParitus1(muuttujatlkm);
	muuttujienParitus2(muuttujatlkm);
	vertaaTaulukkoja1(muuttujatlkm);
	vertaaTaulukkoja2(muuttujatlkm);
	poistaKaksoisarvot_ja_tulosta(muuttujatlkm);
	uusioKaytto(muuttujatlkm);
	poistaKaksoisarvot2(muuttujatlkm);
	tulostaTaulukot5ja6(muuttujatlkm);
	poistaParilliset_ja_tulosta();	
	poistaParilliset_ja_tulostaTaulukko2();
	asetaTaulukko_ja_tulosta2(muuttujatlkm);
	cout << "Matriisin taytto ja lasku" << endl;
	matriisinTaytto_ja_lasku(muuttujatlkm);
	// Allaoleva funktio ei ole pakollinen; kommentoi se jos videoi!
	//alusta_aseta_ja_tulosta_matriisi(muuttujatlkm);
	cout << "\nSiirraTaulukot_ja_laske matriisin tulos!" << endl;
	siirraTaulukot_ja_laskeMatriisin_tulos();
	cout << "TulostaSOP:" << endl;
	tulostaSOP(muuttujatlkm, pot, sop);
	cout << "\nTulosta POS:" << endl;
	//bool bs2 = tulostaPOS(tulos3, pot, muuttujatlkm);
	bool bs2 = tulostaPOS(tt, pot, muuttujatlkm);
	cout << "\nrakennaTaulukko2:" << endl;
	rakennaTaulukko2();
	muuttujienAlustus();
	cout << "muuttujienParitus1:" << endl;
	muuttujienParitus1(muuttujatlkm);
	muuttujienParitus2(muuttujatlkm);
	vertaaTaulukkoja1(muuttujatlkm);
	vertaaTaulukkoja2(muuttujatlkm);
	poistaKaksoisarvot_ja_tulosta(muuttujatlkm);
	uusioKaytto(muuttujatlkm);
	poistaKaksoisarvot2(muuttujatlkm);
	tulostaTaulukot5ja6(muuttujatlkm);
	poistaParilliset_ja_tulosta();
	cout << "\npoistaParilliset_ja_tulostaTaulukko2:" << endl;
	poistaParilliset_ja_tulostaTaulukko2();
	cout << "\nasetaTaulukko_ja_tulosta2:" << endl;
	asetaTaulukko_ja_tulosta2(muuttujatlkm);
	cout << "\nMatriisin taytto ja lasku:" << endl;
	matriisinTaytto_ja_lasku(muuttujatlkm);	
	cout << "\nSiirraTaulukot_ja_laske matriisin tulos!" << endl;
	siirraTaulukot_ja_laskeMatriisin_tulos();
	// TulostaPOS2 on kommentissa siihen saakka, ett� saadaan aikaan POS -tulos ja
	// tulostus on (-00)' = B+C ja (0--)' = A ja sit� rataa. Se t�ytyy korjata tulostaPOS2 funktioon!	
	tulostaPOS2(muuttujatlkm, pot, pos);	
}

void suorita2(GtkWidget *wid, gpointer ptr){
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view2));
	GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(postfix));
	GtkTextBuffer *buffer6 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(totuustaulu));
	GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    text2 = gtk_text_buffer_get_text(buffer, &start, &end, debug);
	cout << "suorita2: " << endl;
	g_print(text2);
	string bin = lauseke_muuttujatlkm(text2, TRUE);
//	const gchar* gstr = bin.c_str();
	const gchar* gstr2 = "-";
//	gtk_text_buffer_set_text(buffer2, gstr, -1);
	gtk_text_buffer_set_text(buffer2, gstr2, -1);
	gtk_text_buffer_set_text(buffer6, gstr2, -1);
	gtk_widget_hide(window2);
	pot = pow(2, muuttujatlkm);
	// string binaari, int koko2
	int *tt2 = muunnaString_int_array(bin, bin.size());
	// Koeta tulostaa lauseke suorittamalla suorita funktio ja koeta minkäläinen tulos tulee!!
	bool bs = lopputulos_SOP(tt2, pot, muuttujatlkm);
	cout << "\nrakennaTaulukko2:" << endl;
	rakennaTaulukko2();
	muuttujienAlustus();
	cout << "muuttujienParitus1:" << endl;
	muuttujienParitus1(muuttujatlkm);
	muuttujienParitus2(muuttujatlkm);
	vertaaTaulukkoja1(muuttujatlkm);
	vertaaTaulukkoja2(muuttujatlkm);
	poistaKaksoisarvot_ja_tulosta(muuttujatlkm);
	uusioKaytto(muuttujatlkm);
	poistaKaksoisarvot2(muuttujatlkm);
	tulostaTaulukot5ja6(muuttujatlkm);
	poistaParilliset_ja_tulosta();
	poistaParilliset_ja_tulostaTaulukko2();
	asetaTaulukko_ja_tulosta2(muuttujatlkm);
	cout << "Matriisin taytto ja lasku" << endl;
	matriisinTaytto_ja_lasku(muuttujatlkm);
	// Allaoleva funktio ei ole pakollinen; kommentoi se jos videoi!
	//alusta_aseta_ja_tulosta_matriisi(muuttujatlkm);
	cout << "\nSiirraTaulukot_ja_laske matriisin tulos!" << endl;
	siirraTaulukot_ja_laskeMatriisin_tulos();
	cout << "TulostaSOP:" << endl;
	tulostaSOP(muuttujatlkm, pot, sop);
	cout << "\nTulosta POS:" << endl;
	//bool bs2 = tulostaPOS(tulos3, pot, muuttujatlkm);
	bool bs2 = tulostaPOS(tt2, pot, muuttujatlkm);
	cout << "\nrakennaTaulukko2:" << endl;
	rakennaTaulukko2();
	muuttujienAlustus();
	cout << "muuttujienParitus1:" << endl;
	muuttujienParitus1(muuttujatlkm);
	muuttujienParitus2(muuttujatlkm);
	vertaaTaulukkoja1(muuttujatlkm);
	vertaaTaulukkoja2(muuttujatlkm);
	poistaKaksoisarvot_ja_tulosta(muuttujatlkm);
	uusioKaytto(muuttujatlkm);
	poistaKaksoisarvot2(muuttujatlkm);
	tulostaTaulukot5ja6(muuttujatlkm);
	poistaParilliset_ja_tulosta();
	cout << "\npoistaParilliset_ja_tulostaTaulukko2:" << endl;
	poistaParilliset_ja_tulostaTaulukko2();
	cout << "\nasetaTaulukko_ja_tulosta2:" << endl;
	asetaTaulukko_ja_tulosta2(muuttujatlkm);
	cout << "\nMatriisin taytto ja lasku:" << endl;
	matriisinTaytto_ja_lasku(muuttujatlkm);
	cout << "\nSiirraTaulukot_ja_laske matriisin tulos!" << endl;
	siirraTaulukot_ja_laskeMatriisin_tulos();
	tulostaPOS2(muuttujatlkm, pot, pos);
}

void on_menu_item_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Menu item pressed!\n"); 
    gtk_widget_show_all(window);
}

void on_menu_item_tyhjenna(GtkMenuItem *menuitem, gpointer data){
	g_print("Menu item tyhjenna!");
	GtkTextBuffer *buffer4 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(postfix));
	GtkTextBuffer *buffer5 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(totuustaulu));
	GtkTextBuffer *buffer6 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sop));
	GtkTextBuffer *buffer7 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pos));
	tyhjennys = g_strdup("");
	gtk_text_buffer_set_text(buffer4, tyhjennys, -1);
	gtk_text_buffer_set_text(buffer5, tyhjennys, -1);
	gtk_text_buffer_set_text(buffer6, tyhjennys, -1);
	gtk_text_buffer_set_text(buffer7, tyhjennys, -1);
}

void on_menu_item_sulje(GtkMenuItem *menu_item, gpointer){
	g_print("Suljetaaan");
	gtk_main_quit();
}

void on_menu_item_syota(GtkMenuItem *menuitem, gpointer data){
	g_print("Syota!");
	gtk_widget_show_all(window2);
}

void copy_selected_fields(GtkWidget *widget, gpointer data) {
   	GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
   //const char* text_to_copy = "Selected: field1, field2"; // Modify this to collect actual values   	
   //text_to_copy = gtk_entry_get_text(GTK_ENTRY(selected_entry));
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(selected_entry));
   // Get the start and end iterators of the buffer
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    // Extract the text between the start and end iterators
    gchar *text_to_copy = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	if(selected_entry != NULL){        
    	gtk_clipboard_set_text(clipboard, text_to_copy, -1);
   	}else{
       	g_print("widget is null");
   	}   
}

void on_menu_item_copy(GtkMenuItem *menu_item, gpointer data){
	//g_print("Kopioi");
	//GtkWidget *selected_entry = static_cast<GtkWidget *>(data);

    if (selected_entry) {
        // Get the text from the selected entry
        //const gchar *text = gtk_entry_get_text(GTK_ENTRY(selected_entry));
		copy_selected_fields(selected_entry, NULL);
	//	g_print("menu copy");
		GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(selected_entry));

    // Get the start and end iterators of the buffer
    	GtkTextIter start, end;
    	gtk_text_buffer_get_start_iter(buffer, &start);
    	gtk_text_buffer_get_end_iter(buffer, &end);

    // Extract the text between the start and end iterators
    	gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    // Print or use the text
  //  	std::cout << "Text from GtkTextView: " << text << std::endl;
	}
}

void on_menu_item_paste(GtkMenuItem *menu_item, gpointer data){
//	g_print("paste");
	GtkTextBuffer *buffer8 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(selected_entry));
	GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer8, &start);
    gtk_text_buffer_get_end_iter(buffer8, &end);
    // Extract the text between the start and end iterators
    gchar *text1 = gtk_text_buffer_get_text(buffer8, &start, &end, FALSE);
   	gchar *text2 = gtk_clipboard_wait_for_text(clipboard);
	gchar* text = g_strconcat(text1, text2, nullptr);
//	std::cout << "Text from GtkTextView: " << text << std::endl;
   	gtk_text_buffer_set_text(buffer8, text, -1);
   	g_free(text);
}

static void on_file_selected(GtkWidget *widget, gpointer data) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(widget);
    char *filename = gtk_file_chooser_get_filename(chooser);
	GtkTextBuffer *buffer12 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(postfix));
	GtkTextBuffer *buffer13 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(totuustaulu));
	GtkTextBuffer *buffer14 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sop));
	GtkTextBuffer *buffer15 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pos));
	gchar *otsikko1 = g_strdup("postfix");
	gchar *otsikko2 = g_strdup("totuustaulu");
	gchar *otsikko3 = g_strdup("SOP");
	gchar *otsikko4 = g_strdup("POS");

    if (filename) {
        g_print("Selected file: %s\n", filename);
		std::ifstream ifs(filename);
		if (!ifs.is_open()) {
        	g_print("Failed to open file.");
        	return;
    	}
		std::string line;
    	std::string content;
		bool seur=false;
		bool pfx=false;
		bool totuus=false;
		bool SOP1=false;
		bool POS1=false;

		while (std::getline(ifs, line)) {
			const char* koe = line.c_str();    	
        	
			if(line == "postfix"){
				seur = true;
				pfx = true;
			}else if(line == "totuustaulu"){
				seur = true;
				totuus = true;
			}else if(line == "POS"){
				seur = true;
				POS1=true;
			}else if(seur && totuus){
				if(line != "SOP"){
					content += line + "\n";					
				//	g_print(koe);
					gtk_text_buffer_set_text(buffer13, content.c_str(), -1);
				}else{
					seur = false;
					totuus = false;
					SOP1 = true;
				}
			}else if(seur && pfx){
				//g_print(koe);
				gtk_text_buffer_set_text(buffer12, koe, -1);
				seur = false;
				pfx = false;
			}else if(seur && POS1){
				g_print(koe);
				gtk_text_buffer_set_text(buffer15, koe, -1);
			}else if(SOP1){
			//	g_print("SOP");
			//	g_print(koe);
				gtk_text_buffer_set_text(buffer14, koe, -1);
				SOP1 = false;
			}
    	}
    	ifs.close();
        g_free(filename);
    }
}

void on_menu_item_lataa(GtkMenuItem *menu_item, gpointer data){
	g_print("lataa");
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

void on_menu_item_tallenna(GtkMenuItem *menu_item, gpointer data){
	g_print("tallenna");
	GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;

	GtkTextBuffer *buffer8 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(postfix));
	GtkTextBuffer *buffer9 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(totuustaulu));
	GtkTextBuffer *buffer10 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sop));
	GtkTextBuffer *buffer11 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pos));

	GtkTextIter start, end, s2, s3, s4, s5, s6, s7;
	gtk_text_buffer_get_start_iter(buffer8, &start);
    gtk_text_buffer_get_end_iter(buffer8, &end);
	gtk_text_buffer_get_start_iter(buffer9, &s2);
	gtk_text_buffer_get_end_iter(buffer9, &s3);
	gtk_text_buffer_get_start_iter(buffer10, &s4);
	gtk_text_buffer_get_end_iter(buffer10, &s5);
	gtk_text_buffer_get_start_iter(buffer11, &s6);
	gtk_text_buffer_get_end_iter(buffer11, &s7);
	
    gchar *text_postfix = gtk_text_buffer_get_text(buffer8, &start, &end, debug);
	gchar *text_totuus = gtk_text_buffer_get_text(buffer9, &s2, &s3, debug);
	gchar *text_SOP = gtk_text_buffer_get_text(buffer10, &s4, &s5, debug);
	gchar *text_POS = gtk_text_buffer_get_text(buffer11, &s6, &s7, debug);
	//g_print(text_totuus);

    // Create the file chooser dialog
    dialog = gtk_file_chooser_dialog_new("Save File",
                                         NULL,
                                         action,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Save", GTK_RESPONSE_ACCEPT,
                                         NULL);

    chooser = GTK_FILE_CHOOSER(dialog);
	
    // Set a default filename
    gtk_file_chooser_set_current_name(chooser, "Untitled.ba2");

    // Run the dialog and handle the response
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
		gchar *otsikko1 = g_strdup("postfix");
		gchar *otsikko2 = g_strdup("totuustaulu");
		gchar *otsikko3 = g_strdup("SOP");
		gchar *otsikko4 = g_strdup("POS");
        // Get the selected filename
        filename = gtk_file_chooser_get_filename(chooser);

		std::ofstream file(filename);
    	if (file.is_open()) {
			file << otsikko1 << std::endl;
        	file << text_postfix << std::endl;
			file << otsikko2 << std::endl;
			file << text_totuus;
			file << otsikko3 << std::endl;
			file << text_SOP << std::endl;
			file << otsikko4 << std::endl;
			file << text_POS << std::endl;
        	file.close();
        	std::cout << "Text written to file successfully!" << std::endl;
    	} else {
        	std::cerr << "Failed to open file for writing!" << std::endl;
    	}

        g_print("File saved as: %s\n", filename);

        // Free the filename string
        g_free(filename);
    }

    // Destroy the dialog after use
    gtk_widget_destroy(dialog);
}

void on_menu_item_tietoa(GtkMenuItem *menu_item, gpointer data){
	g_print("tietoa");
	GtkWidget *dlg = gtk_dialog_new_with_buttons("Tietoa", GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, "OK", 0, NULL);
	
	GtkWidget *lbl = gtk_label_new ("\n\n\nSovelluksen on kehittänyt: Markus Juhala \nmarkusju7@gmail.com\n18.6.2025");
	gtk_widget_set_size_request(dlg, 250, 200);
	//gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), lbl);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(box), FALSE); // Allow different heights
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), box);
	gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
	gtk_widget_show_all(dlg);
	g_signal_connect(dlg, "response", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_widget_show(dlg);
	//gtk_widget_show(lbl);
	//int result = gtk_dialog_run(GTK_DIALOG(dlg));
	//gtk_widget_destroy(dlg);
}

void on_entry_selected(GtkWidget *entry, gpointer user_data) {
    //GtkWidget **selected_entry = static_cast<GtkWidget **>(user_data);
    g_print("selected:");
    
    if(entry != NULL){
        g_print("entry is not null");
        selected_entry = GTK_WIDGET(entry);
   	}else{
        g_print("selected_entry is null");
   	}
}

void push(double f){
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		cout << "virhe: stack on t�ynn�, ei voi push \n" << f;
}

double pop(void){
	if(sp > 0)
		return val[--sp];
	else {
		cout << "virhe: stack on tyhj�" << endl;
		return 0.0;
	}
}

int getop(char s[]){
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	i=0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		cout << "ungetch: liikaa merkkej�\n" << endl;
	else
		buf[bufp++] = c;
}

int laske(int bitti, int numero1, int numero2, char konnektiivi){
	int tulos=0;

	if(konnektiivi == 'K'){
		tulos = numero1 & numero2;	
	}else if(konnektiivi == 'A'){
		tulos = numero1 | numero2;
	}else if(konnektiivi == 'E'){
		tulos = numero1 ^ numero2;
	}
return tulos;
}

int cnot(int bitti, int numero1){
	int nr=0;
	//if(bitti == 4){
		//nr = ~numero1;
	
		//cout << "pow:" << bitti << endl;
		nr = pow(2, bitti)-1;
		nr = nr - numero1;
		//cout << "nr:" << nr << endl;
		//cout << "bitti == 4";
	//}
return nr;
}

// Huomaa stringstream clear() !
int* muunnaString_int_array(string binaari, int koko2){
	cout << "MuunnaString_int_array" << endl;
	cout << "koko2:" << koko2 << endl;
	stringstream st;
	int abc=0;
	int np = koko2-1;
	int* tulos4 = new int[koko2];
	for(int h=0; h < koko2; h++){
		//int abc = static_cast<int>(binaari[h]);		
		st << binaari[np];
		st >> tulos4[h];
		//tulos4[h] = binaari[h];
		//cout << binaari[h] << endl;
		cout << tulos4[h] << endl;
		st.clear();
		np--;
	}
return tulos4;
}

int* muunnaBinaari(int bitti, int jakotulos, GtkTextBuffer *buffer, bool tulostus){
	int *tulos = new int[koko];
	int laskuri2=0;
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

	if(tulostus){
		for(int a=bitti-1; a>=0; a--){
			cout << tulos[a];
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

std::string convert_int_to_string(int arr[], int size) {
	std::ostringstream os;
	int ii = size-1;
//	cout << "convert_int_to_string:" << endl;
//	cout << size << endl;

	for (int i = 0; i < size; i++) {
		os << arr[ii];
//		cout << arr[ii];
		ii--;
	}
//	cout << endl;
	std::string str(os.str());
	return str;
}



string lauseke_postfix() {	
	cout << "Anna lauseke:" << endl;
	cin.getline(s, 100);
	string infix(s);
	cout << "infix: " << infix << endl;
	muuttujatlkm = collectMlkm(infix, debug);
	cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	infix = concats(infix);
	cout << "infix:" << infix << endl;
	mlkm2 = muuttujatlkm;
	return convert(infix, debug);
}

string pura_parametrit(int argc, char* argv[]) {
	//string infix2;
	int count = 0;

	cout << "\nKomentorivin argumentit:\n";
	for (count = 0; count < argc; count++) {
		cout << "  argv[" << count << "]   "
			<< argv[count] << "\n";

	}
	string infix2(argv[1]);
	cout << "infix2:" << infix2 << endl;
	muuttujatlkm = collectMlkm(infix2, debug);
	cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	infix2 = concats(infix2);
	cout << "infix2:" << infix2 << endl;
	mlkm2 = muuttujatlkm;
	return convert(infix2, debug);
}

void insert_text_at_position(GtkTextBuffer *buffer, const gchar *text, gint position) {
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, position);
    gtk_text_buffer_insert(buffer, &iter, text, -1);
}

int* laske_lauseke(const char* toinen, bool tulostus) {
	int* t3;
	int type, i = 0;
	int luku1, luku2;
	int tulos, tulos2;
	if (tulostus) cout << "toinen koko:" << strlen(toinen) << endl;
	std::string str(toinen, 5);
		
	GtkTextBuffer *buffer3 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(totuustaulu));
   //text = gtk_text_buffer_get_text(buffer, &start, &end, debug);
   //	const gchar* gstr;
		
	//gtk_text_buffer_set_text(buffer3, gstr, -1);
	
	laskuri = muuttujatlkm-1;
	std::string str2 = "A:";
	std::string a;
	//laskuri = haeMlkm()-2;
	//cout << "haeMlkm:" << laskuri << endl;
	while ((type = toinen[i]) != '\0') {
		//while((type = getop(s)) != 10){
		switch (type) {
		case 65:
			// JATKA T�ST�, tarkkaile A:n arvoa !!!
			//luku3.erase();
			//gstr= g_strdup("");
			if (tulostus)	cout << "A:";
			luku3 += "A:";
			//gstr = luku3.c_str();
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			//insert_text_at_position(buffer3, gstr, luku3.length());
			//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
			//cout << "A:";
			pot = pow(2, muuttujatlkm);
			// T�h�n push()
			//cout << "pot:" << pot << endl;
			push(A[laskuri]);
			muunnaBinaari(pot, A[laskuri], buffer3, true);
			cout << endl;
			//cout << "laskuri:" << laskuri << endl;
			break;
		case 66:
			if (tulostus)	cout << "B:";
			luku3 += "B:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			//cout << "laskuri:" << laskuri << endl;
			pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;
			push(B[laskuri]);
			//cout << "B(" << laskuri << "):" << B[laskuri] << endl;
			
			muunnaBinaari(pot, B[laskuri], buffer3, true);
			cout << endl;
			break;
		case 67:
			if (tulostus)cout << "C:";
			luku3 += "C:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			pot = pow(2, muuttujatlkm);
			push(C[laskuri]);
			muunnaBinaari(pot, C[laskuri], buffer3, true);
			cout << endl;
			break;
		case 68:
			if (tulostus)	cout << "D:";
			luku3 += "D:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			pot = pow(2, muuttujatlkm);
			push(D[laskuri]);
			muunnaBinaari(pot, D[laskuri], buffer3, true);
			cout << endl;
			break;
		case 48:
			if (tulostus)	cout << "0:";
			luku3 += "0:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			push(nolla[laskuri]);
			muunnaBinaari(pot, nolla[laskuri], buffer3, true);
			cout << endl;
			break;
		case 49:
			if (tulostus)	cout << "1:";
			luku3 += "1:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			pot = pow(2, muuttujatlkm);
			//cout << "Numero:" << yksi[laskuri] << endl;
			push(yksi[laskuri]);
			muunnaBinaari(pot, yksi[laskuri], buffer3, true);
			cout << endl;
			break;
		case 43:
			// T�h�n laske pop() OR pop() ja push() pinoon
			// push(pop() + pop()
			luku3 += "+:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			luku2 = pop();
			luku1 = pop();
			pot = pow(2, muuttujatlkm);

			tulos = laske(pot, luku1, luku2, 'A');
			push(tulos);
			if (tulostus)	cout << "+:";
			t3 = muunnaBinaari(pot, tulos, buffer3, true);
			cout << endl;
			break;
		case 42:
			// T�h�n laske pop() AND pop() ja push() pinoon				
			//push(pop() * pop());
			luku3 += "*:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			luku2 = pop();
			luku1 = pop();
			pot = pow(2, muuttujatlkm);

			tulos = laske(pot, luku1, luku2, 'K');
			push(tulos);
			if (tulostus)	cout << "*:";
			t3 = muunnaBinaari(pot, tulos, buffer3, true);
			cout << endl;
			break;
		case 39:
			// T�M� ON NOT
			luku1 = pop();
			pot = pow(2, muuttujatlkm);
			//cout << "Not:" << luku1;
			//cout << "Luku2:" << luku2 << endl;
			//cout << "2 potenssi muuttujien lkm:" << pot << endl;

			tulos2 = cnot(bb, luku1);
			push(tulos2);
			if (tulostus)	cout << "':";
			luku3 += "':";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			t3 = muunnaBinaari(pot, tulos2, buffer3, true);
			cout << endl;
			break;
		case 61:
			// T�h�n laske pop() XOR pop() ja push() pinoon
			// push(pop() + pop()
			luku2 = pop();
			luku1 = pop();
			pot = pow(2, muuttujatlkm);
			tulos = laske(pot, luku1, luku2, 'E');
			tulos2 = cnot(bb, tulos);
			push(tulos2);
			if (tulostus)	cout << "=:";
			luku3 += "=:";
			gstr = g_strdup(luku3.c_str());
			gtk_text_buffer_set_text(buffer3, gstr, -1);
			t3 = muunnaBinaari(pot, tulos2, buffer3, true);
			cout << endl;
		case '\n':
			//cout << "Loppu:" << pop() << endl;
			break;
		default:
			cout << "Virhe: Tuntematon komento" << s << endl;
			break;
		}
		i++;
	}
	return t3;
}

int* stotuustaulu(bool tulostus){
	int* tulos3;
	tulos3 = laske_lauseke(spostfix.c_str(), tulostus);
return tulos3;
}

int main(int argc, char* argv[]){
	gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "menu_auttavasti.glade", NULL);
    isanta = (GtkWidget *)gtk_builder_get_object(builder, "isanta");
    g_signal_connect(isanta, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    postfix = (GtkWidget *)gtk_builder_get_object(builder, "postfix");
	totuustaulu = (GtkWidget *)gtk_builder_get_object(builder, "totuustaulu");
	sop = (GtkWidget *)gtk_builder_get_object(builder, "sop");
	pos = (GtkWidget *)gtk_builder_get_object(builder, "pos");
	//gtk_entry_set_placeholder_text(GTK_ENTRY(sop), "Field 1");

    //lapsi = (GtkWidget *)gtk_builder_get_object(builder, "lapsi");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //gtk_window_set_default_size(GTK_WINDOW(lapsi), 400, 300);
    GtkMenuItem *menu_item = GTK_MENU_ITEM(gtk_builder_get_object(builder, "syota"));
	GtkMenuItem *menu_item2 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tyhjenna"));
	GtkMenuItem *menu_item3 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "sulje"));
	GtkMenuItem *menu_item4 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tulos"));
	GtkMenuItem *menu_item5 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "kopioi"));
	GtkMenuItem *menu_item6 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "liitä"));
	GtkMenuItem *menu_item7 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "lataa"));
	GtkMenuItem *menu_item8 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tallenna"));
	GtkMenuItem *menu_item9 = GTK_MENU_ITEM(gtk_builder_get_object(builder, "tietoa"));

    text_view = gtk_text_view_new();
    GtkWidget *btn = gtk_button_new_with_label("Suorita");
    g_signal_connect (btn, "clicked", G_CALLBACK(suorita), NULL);

	text_view2 = gtk_text_view_new();
	GtkWidget *btn2 = gtk_button_new_with_label("Suorita");
	g_signal_connect(btn2, "clicked", G_CALLBACK(suorita2), NULL);
    
    // Set the size request for the GtkTextView
    gtk_widget_set_size_request(text_view, 300, 200);
    GtkWidget *box = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), text_view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

	gtk_widget_set_size_request(text_view2, 300, 200);
	GtkWidget *box2 = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box2), text_view2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box2), btn2, TRUE, TRUE, 0);

    // Add the GtkTextView to the window
    //gtk_container_add(GTK_CONTAINER(window), text_view);
    gtk_container_add(GTK_CONTAINER(window), box); 
	gtk_container_add(GTK_CONTAINER(window2), box2);     

    //GtkWidget *tv = (GtkWidget *)gtk_builder_get_object(builder, "tw");
    
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	gtk_window_set_default_size(GTK_WINDOW(window2), 400, 300);
	
    // Create a GtkTextView widget
    g_signal_connect(text_view, "focus-in-event", G_CALLBACK(on_entry_selected), &selected_entry);
	g_signal_connect(text_view2, "focus-in-event", G_CALLBACK(on_entry_selected), &selected_entry);
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_activate), NULL);
	g_signal_connect(menu_item2, "activate", G_CALLBACK(on_menu_item_tyhjenna), NULL);
	g_signal_connect(menu_item3, "activate", G_CALLBACK(on_menu_item_sulje), NULL);
	g_signal_connect(menu_item4, "activate", G_CALLBACK(on_menu_item_syota), NULL);
	g_signal_connect(menu_item5, "activate", G_CALLBACK(on_menu_item_copy), &selected_entry);
	g_signal_connect(menu_item6, "activate", G_CALLBACK(on_menu_item_paste), &selected_entry);
	g_signal_connect(menu_item7, "activate", G_CALLBACK(on_menu_item_lataa), NULL);
	g_signal_connect(menu_item8, "activate", G_CALLBACK(on_menu_item_tallenna), NULL);
	g_signal_connect(menu_item9, "activate", G_CALLBACK(on_menu_item_tietoa), NULL);

    //gtk_container_add(GTK_CONTAINER(scrolled_window), tv);
	gtk_widget_set_size_request(totuustaulu, 200, 500);
    gtk_widget_hide(window);
	gtk_widget_hide(window2);
    //gtk_widget_show_all(window);
    gtk_widget_show(isanta);
    	
	string postfix;
	/*
	if (argc > 1)
		postfix = pura_parametrit(argc, argv);
	else
		postfix = lauseke_postfix();
	JATKA*/
	
	//const char* toinen = postfix.c_str();
	//cout << "tulos3:" << tulos3 << endl;
	/*
	cout << "Lopputulos taulukosta tulos3 SOP:" << endl;
			
	JATKA TÄSTÄ!	
	*/	
	//asetaTaulukko_ja_tulostaTaulukko(muuttujatlkm);	
	gtk_main();
						
return 0;
}
