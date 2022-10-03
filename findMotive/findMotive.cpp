#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "Veuillez ecrire le chemin de fichier : ";
    string doc;
    cin >> doc;
    cout << "Veuillez ecrire un motif : ";
    string motif;
    cin >> motif;
    ifstream fichier(doc, ios::in);
    int somme = 0;
    if (fichier)  
    {
        fichier.clear();
        fichier.seekg(0, ios::beg);
        string mot;
        while (fichier >> mot)
        {
            if (mot.size() >= motif.size())
            {
                for (int i = 0; i < mot.size(); i++)
                {
                    if (mot[i] == motif[0])
                    {
                        int j = 1;
                        for (int k = 1 ; k < motif.size(); k++)
                        {
                            if (mot[i + k] == motif[k])
                            {
                                j++;
                            }
                        }
                        if (j == motif.size())
                        {
                            somme++;
                        }
                    }
                }
            }
        }
        cout << "The file " << doc << " contains " << somme << " words containing the motive " << motif << "\n" << endl;
        fichier.close();  
    }
    else  
        cout << "The file " << doc << " could not be opened \n" << endl;

    return 0;
}