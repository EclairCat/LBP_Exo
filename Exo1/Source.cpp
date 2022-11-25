//! [includes]
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <array>
using namespace cv;
using namespace std;


#include "./package_lbp/LBP.h"
#include "./package_lbp/olbp/OLBP.h"

/*
    Variable Changeable
*/

// Les types d'execution :
// 0 => Normal LBP
// 1 => Library LBP (Caroline)
const int exec_mode = 0;

// Choix du data :
// 0 => Parking
// 1 => CINIC 10
const int data_choice = 1;

// Traitement image :
// 0 => Gray Scale
// 1 => Color
const int color_choice = 1;


//Fonctionel!
int* lbp_Img_to_Vec(String path_img) {

    Mat img = imread(path_img);

    if (color_choice == 0) {
        img = imread(path_img, cv::ImreadModes::IMREAD_GRAYSCALE);
    }
  
    int pixelC;

    //Initialisation du Vecteur descripteur
    static int vec_desc[256];
    //static vector<int> vec_desc;

    for (int p = 0; p < 256; p++) {
        vec_desc[p] = 0;
        //vec_desc.push_back(0);
    }

    //Parcour de pixel sur Image
    for (int i = 1; i < img.rows - 1; i++) {
        for (int j = 1; j < img.cols - 1; j++) {

            pixelC = img.at<uchar>(i, j);

            //Parcours des pixel Voisins
            //Initiation du tableau de 8 bit
            vector<int> motifC;                

            //parcour en Rond D:
            if (img.at<uchar>(i - 1, j - 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i, j - 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i + 1, j - 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i + 1, j) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i + 1, j + 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i, j + 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i - 1, j + 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i - 1, j) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            //Convertissement du motif Binaire en Decimal
            int motifC_decimal = 0;

            for (int n = 0; n < 8; n++) {
                motifC_decimal = motifC_decimal * 2 + motifC.at(n);
            }

            //cout << "MotifC en Decimal " << motifC_decimal << endl;

            //Ajout au Compteur Descripteur.
            vec_desc[motifC_decimal]++;
        }
    }

    return vec_desc;
}

int* lbp_Img_to_Vec_from_img(Mat img) {    

    int pixelC;

    //Initialisation du Vecteur descripteur
    static int vec_desc[256];
    //static vector<int> vec_desc;

    for (int p = 0; p < 256; p++) {
        vec_desc[p] = 0;
        //vec_desc.push_back(0);
    }

    //Parcour de pixel sur Image
    for (int i = 1; i < img.rows - 1; i++) {
        for (int j = 1; j < img.cols - 1; j++) {

            pixelC = img.at<uchar>(i, j);

            //Parcours des pixel Voisins
            //Initiation du tableau de 8 bit
            vector<int> motifC;

            //parcour en Rond D:
            if (img.at<uchar>(i - 1, j - 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i, j - 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i + 1, j - 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i + 1, j) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i + 1, j + 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i, j + 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i - 1, j + 1) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            if (img.at<uchar>(i - 1, j) > pixelC) {
                motifC.push_back(1);
            }
            else {
                motifC.push_back(0);
            }

            //Convertissement du motif Binaire en Decimal
            int motifC_decimal = 0;

            for (int n = 0; n < 8; n++) {
                motifC_decimal = motifC_decimal * 2 + motifC.at(n);
            }

            //cout << "MotifC en Decimal " << motifC_decimal << endl;

            //Ajout au Compteur Descripteur.
            vec_desc[motifC_decimal]++;
        }
    }

    return vec_desc;
}

int* img_lbp_to_vec(Mat img) {
    //Mat img = imread(path_img, cv::ImreadModes::IMREAD_GRAYSCALE);    

    int pixelC;

    //Initialisation du Vecteur descripteur
    static int vec_desc[256];

    for (int p = 0; p < 256; p++) {
        vec_desc[p] = 0;
    }

    //Parcour de pixel sur Image
    for (int i = 1; i < img.rows - 1; i++) {
        for (int j = 1; j < img.cols - 1; j++) {

            pixelC = img.at<uchar>(i, j);
            //Ajout au Compteur Descripteur.
            vec_desc[pixelC]++;
        }
    }

    return vec_desc;
}

//Fonctionel!
void ecrire_dans_fichier(String nom_fichier, int* vec_desc, int mode) {
    fstream monFlux(nom_fichier);

    if (monFlux) {

        monFlux << mode << " ";
        for (int i = 0; i < 256; i++) {
            monFlux << vec_desc[i] << " ";
        }
        monFlux << endl;
    }
    else {
        cout << "ERREUR : Fichier immposible à ouvrir" << endl;
    }
}

//Fonctionel!
void reset_fichier(String fichier_txt) {
    fstream monFlux(fichier_txt, ofstream::out | ofstream::trunc);
}

//Fonctionel!
void init_model(String fichier_txt, String inputDirectory, int mode) {    

    fstream monFlux(fichier_txt, ofstream::out | ofstream::app);

    if (monFlux) {
        vector <string> filename;

        //Model Busy
        glob(inputDirectory, filename, false);

        for (int count = 0; count < filename.size(); count++) {
            Mat img = imread(filename[count]);
            if (img.empty())
            {
                cout << "image loading failed :  " << filename[count] << endl;
            }
            else {
                int* tab_vec_desc = lbp_Img_to_Vec(filename[count]);
                //vector<int> tab_vec_desc = lbp_Img_to_Vec(filename[count]);

                    monFlux << mode << " ";
                    for (int i = 0; i < 256; i++) {
                        monFlux << tab_vec_desc[i] << ' ';
                    }
                    monFlux << endl;            
            }
        }        
    }
    else {
        cout << "ERREUR : Fichier immposible à ouvrir" << endl;
    }
}

void init_model_with_lbp_lib(string fichier_txt, string inputDirectory, int mode) {
    lbplibrary::LBP* lbp;
    lbp = new lbplibrary::OLBP;

    Mat img_lbp;
    vector <string> filename;


    fstream monFlux(fichier_txt, ofstream::out | ofstream::app);

    if (monFlux) {
        vector <string> filename;

        //Model Busy
        glob(inputDirectory, filename, false);

        for (int count = 0; count < filename.size(); count++) {
            Mat img = imread(filename[count]);
            if (img.empty())
            {
                cout << "image loading failed :  " << filename[count] << endl;
            }
            else {
                lbp->run(img, img_lbp);
                int* tab_vec_desc = img_lbp_to_vec(img_lbp);

                monFlux << mode << " ";
                for (int i = 0; i < 256; i++) {
                    monFlux << tab_vec_desc[i] << ' ';
                }
                monFlux << endl;
            }
        }
    }
    else {
        cout << "ERREUR : Fichier immposible à ouvrir" << endl;
    }

}

//Fonctionel!
int* ligne_to_vec_desc(string ligne, int * vec_desc) {
    int counter = 0;
    string chiffre = "";
    for (int l = 0; l < ligne.size(); l++) {       
        if (ligne[l] != ' ') {
            chiffre += ligne[l];

            if (l == ligne.size() - 1) {
                vec_desc[counter] = stoi(chiffre);
                counter++;
                chiffre = "";
            }
        }
        else {
            if (chiffre != "") {
                vec_desc[counter] = stoi(chiffre);
                counter++;
                chiffre = "";
            }           
        }
    }

    return vec_desc;
}

//Distance : SAD  FONCTIONEL!
int compare_distance_SAD(int* vec1, int* vec2, int size) {
    int res = 0;

    for (int x = 0; x < size; x++) {
        res = res + abs(*(vec1 + x) - *(vec2 + x));
        //cout << "Iterration : " << x << " Donnee : " << *(vec1 + x) << " " << *(vec2 + x) << endl;
    }
    return res;
}

//Distance SSD Somme des différence au carré
int distance_SSD(int* vec1, int* vec2, int size) {
    int res = 0;

    for (int x = 0; x < size; x++) {
        res = res + pow(vec1[x] - vec2[x], 2);
        //cout << "Iterration : " << x << " Donnee : " << *(vec1 + x) << " " << *(vec2 + x) << endl;
    }

    return res;
}

//Distance Battacharya https://fr.wikipedia.org/wiki/Distance_de_Bhattacharyya
int distance_bhattacharya(int* vec1, int* vec2, int size) {
    int res = 0;

    for (int x = 0; x < size; x++) {
        res = res + sqrt(vec1[x] * vec2[x]);
        //cout << "Iterration : " << x << " Donnee : " << *(vec1 + x) << " " << *(vec2 + x) << endl;
    }

    return res;
}

//Distance ChiSquare https://www.geeksforgeeks.org/chi-square-distance-in-python/
int distance_ChiSquare(int* vec1, int* vec2, int size) {
    int res = 0;

    for (int x = 0; x < size; x++) {

        int diviser = vec1[x] + vec2[x];
        if (diviser == 0) {
            diviser = 1;
        }

        res = res + (pow(vec1[x] - vec2[x],2) / diviser);
        //cout << "Iterration : " << x << " Donnee : " << *(vec1 + x) << " " << *(vec2 + x) << endl;
    }

    res = res / 2;

    return res;
}

float compare_model_and_test(int method_compare, string name) { 

    cout << endl;

    cout << "Traitrement comparaison " + name << "..." << endl;

    ifstream modelFlux("model.txt");
    ifstream testFlux("test.txt");

    if (modelFlux && testFlux) { 

        String ligneModel;
        String ligneTest;

        vector<string> lignes_Model;
        vector<string> lignes_Test;


        //Pourcentage de réussite
        float pourcentage = 0;

        //Stock des lignes sur des vecteur String
        while (getline(testFlux, ligneTest)) {
            lignes_Test.push_back(ligneTest);
        }

        while (getline(modelFlux, ligneModel)) {
            lignes_Model.push_back(ligneModel);
        }

        int labelModel;
        int labelTest;

        int vec_desc_test[256];
        int vec_desc_model[256];

        int res;

        for (int cTest = 0; cTest < lignes_Test.size(); cTest++) {
            ligneTest = lignes_Test[cTest];

            int best_res = INT_MAX;
            int best_label;

            //Transformation de la ligne Test en Vecteur Descripteur
            labelTest = ligneTest[0] - '0'; //Classe pour savoir si c'est Busy or Free 
            
            ligne_to_vec_desc(ligneTest.substr(1), vec_desc_test);

            //Parcour du Model
            for (int cModel = 0; cModel < lignes_Model.size(); cModel++) {
                ligneModel = lignes_Model[cModel];               

                labelModel = ligneModel[0] - '0'; //Classe pour savoir si c'est Busy or Free

                //Tranformation des lignes en Vecteur Descripteur                
                ligne_to_vec_desc(ligneModel.substr(1), vec_desc_model);


                //Compare la distance des 2 vecteur descripteur.
                switch (method_compare) {
                    case 0:
                        res = compare_distance_SAD(vec_desc_test, vec_desc_model, 256);
                        break;
                    case 1:
                        res = distance_SSD(vec_desc_test, vec_desc_model, 256);
                        break;
                    case 2:
                        res = distance_bhattacharya(vec_desc_test, vec_desc_model, 256);
                        break;
                    case 3:
                        res = distance_ChiSquare(vec_desc_test, vec_desc_model, 256);
                        break;                    
                }
                
               
                //cout << res << endl;
                
                //Enregistrement du résultat
                if (best_res > res) {
                    best_label = labelModel;
                    best_res = res;
                    //cout << "Iteration : " << t << endl;
                    //cout << "New Res! " << best_res << " Label : " << best_label << endl;
                    //cout << "Tableau Info  " << tab_res[t][1] << " Label : " << tab_res[t][0] << endl;
                }
            }

            //cout << "Img Test : " << cTest+1 << "  Best Res : " << best_res << " Label Img Test  : " << labelTest << "  Label Img Model " << best_label << endl;
            

            if (labelTest == best_label) {
                //cout << "Test Reussit!" << endl << endl;
                pourcentage++;
            }            
        }

        cout << "Image traiter Reussi : " << pourcentage << "/" << lignes_Test.size() << endl;

        pourcentage = (pourcentage * 100) / lignes_Test.size();

        cout << pourcentage << "% de reussite!" << endl;

        return pourcentage;
        
    }
    else {
        cout << "ERREUR : Fichier immposible à ouvrir" << endl;
        return -1;
    }

}

int main(){    

    const int nb_method = 4;
    const int total_class = 10;


    //Show Donnée 
    switch (exec_mode) {
    case 0:
        cout << "Execution mode : Normal LBP" << endl;
        break;
    case 1:
        cout << "Execution mode : Lib LBP" << endl;
        break;
    }

    switch (color_choice) {
    case 0:
        cout << "Traitement d'image : GrayScale" << endl;
        break;
    case 1:
        cout << "Traitement d'image : Couleur RGB" << endl;
        break;
    }

    switch (data_choice) {
    case 0:
        cout << "Data choice : Parking slot" << endl;        
        break;
    case 1:
        cout << "Data choice : CINIC-10 Image Classification" << endl;        
        break;
    }
    
    cout << endl;

    //Convertissement librairie d'images
    
    cout << "Initiation du fichier Model..." << endl;
    reset_fichier("model.txt");

    cout << "Initiation du fichier Test..." << endl;
    reset_fichier("test.txt");

    string path_train = "";
    string path_test = "";
    string tab_classes[total_class]{ "airplane", "automobile", "bird", "cat","deer","dog","frog","horse","ship","truck" };
    string tab_classes_parking[total_class]{ "free", "busy" };
    string* p_tab = tab_classes;

    switch (data_choice) {
        case 0:            
            p_tab = tab_classes_parking;
            path_train = "./Images/parking_base";
            path_test = "./Images/parking_query";
            break;
        case 1:            
            p_tab = tab_classes;
            path_train = "./Images/cinic_train_2000";
            path_test = "./Images/cinic_test_1000";
            break;
    }    
    
    int count_class = 0;
    for (count_class; count_class < total_class; count_class++) {
        switch (exec_mode) {
            case 0:                
                //Normale
                init_model("model.txt", path_train + "/" + p_tab[count_class], count_class);
                init_model("test.txt", path_test + "/" + p_tab[count_class], count_class);
                break;
            case 1:                
                //Using Lib LBP
                init_model_with_lbp_lib("model.txt", path_train + "/" + p_tab[count_class], count_class);
                init_model_with_lbp_lib("test.txt", path_test + "/" + p_tab[count_class], count_class);
                break;
        }       
    }

    //Cacul des comparaisons
    cout << "Lancement de la comparaison..." << endl;    
    float tab_res[nb_method];
    string tab_label[4]{ "SAD", "SSD", "Battacharya", "ChiSquare" };

    /* Numerotation Mesure de Distance :    
    0- SAD  
    1- SDD  
    2- Bhatarrya  
    3- ChiSquare  
    4- Intersection  (Non fait)
    5- Corrélation    
    */    
    
    float res = compare_model_and_test(0, "SAD");
    tab_res[0] = res;

    res = compare_model_and_test(1, "SSD");
    tab_res[1] = res;

    res = compare_model_and_test(2, "Battacharya");
    tab_res[2] = res;

    res = compare_model_and_test(3, "ChiSquare");
    tab_res[3] = res;


    //Résumé des resultats
    int i = 0;
    cout << endl;
    cout << "Resume Resultat : " << endl;
    for (i; i < 4; i++) {
        std::cout << tab_label[i] << ": " << tab_res[i] << "%" << endl;
    } 

    return 0;
}

