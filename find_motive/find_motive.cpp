#include <iostream>
#include <fstream>

using namespace std;

int main(string chemin, string motif)
{
    ifstream fichier(chemin, ios::in);
    int somme = 0;
    if (fichier)  
    {
        fichier.clear();
        fichier.seekg(0, ios::beg);
        string mot;
        while (fichier >> mot)
        {
            bool estCompte = 0;
            if (mot.size() >= motif.size())
            {
                for (int i = 0; i < mot.size(); i++)
                {
                    if (mot[i] == motif[0] && !estCompte)
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
                            estCompte = 1;
                        }
                    }
                }
            }
        }
        cout << "The file " << chemin << " contains " << somme << " words containing the motive " << motif << "\n" << endl;
        fichier.close();  
    }
    else  
        cout << "The file " << chemin << " could not be opened. \n" << endl;

    return 0;
}
