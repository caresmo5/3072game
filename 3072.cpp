/****************************************************
Puesto que la asignatura fue cursada en valenciano,
las anotaciones y los nombres de las variables están
en ese idioma.
Coautores:
Andrés B.P.
Carlos E.M.
*****************************************************/

#include <iostream>
using namespace std;
#include <cstdlib>
#include <fstream>
#include <ctime>
const int I = 4;
const int J = 4;
typedef int Matriu [I][J];

struct Puntuacio
{
	string nom;
	int punts;
	int movim;
	Matriu mat;
};

const int N = 10;
typedef Puntuacio V_Punt[N];

struct Puntuacions
{
	int n;
	V_Punt punt;
};

void MatriuCuadro (const Matriu, int, int);
void MostrarOpcio (Matriu, Puntuacio &, Puntuacions &);
void MostrarMenu (char &, Matriu, Puntuacio &, Puntuacions &);
void llegirFitxerGuardat (ifstream &, Puntuacions &, Matriu,int & ,int &);
void MovimentDreta (Matriu);
void MatriuInici (Matriu);
void MovimentEsquerra (Matriu);
void MovimentDreta2 (Matriu);
void MovimentEsquerra2 (Matriu);
void MovimentAmunt (Matriu);
void MovimentAmunt2 (Matriu);
void MovimentAvall (Matriu);
void MovimentAvall2 (Matriu);
void NumAleatori (Matriu);
bool Noguanyat(Matriu);
void Portada ();
void Puntuar (Matriu, char &, Puntuacio &, Puntuacions &, int);
void escriureVector2Fitxer (ofstream &, Puntuacions, Matriu);
bool NoMov (Matriu);
Puntuacio introduirPuntuacio (string &, int, int);
bool insertarPuntuacio(Puntuacio, Puntuacions &, Matriu);
void Recompte (Matriu, int &);
void ContinuarPartida (ifstream &, Matriu, Puntuacions&, Puntuacio&,int & ,int &);

int main ()
{

    ifstream ranki;
	ofstream ranko;
	string tecla;
    char op;
    Matriu mat;
    Puntuacio punt;
    Puntuacions puntuacions;
    ranki.open("ranking.txt");
	if (!ranki)
	{
		Portada ();
		cout << "No existeix l.arixu 'ranking.txt'" << endl;
		cout << "Comencem un nou ranking" << endl;
		cout << "Pressione una tecla per a continuar..." << endl;
		getline(cin,tecla);
		system ("cls");
		MatriuInici (mat);
        MostrarMenu (op, mat, punt, puntuacions);
     }
    	else
	{
        
		MostrarMenu(op, mat, punt, puntuacions);
	}
	
	system ("pause");
	return 0;
}

/************************************************
void Portada ()
Entrades: Cap.
Eixides: Cap.
Objectiu: 
 Mostrar per pantalla la portada del joc. 
************************************************/
void Portada ()
{
cout << "--------------------------------------------------" << endl;
cout << "  3333333333  0000000000  7777777777  2222222222  " << endl;
cout << "  3333333333  0000000000  7777777777  2222222222  " << endl;
cout << "         333  000    000         777         222  " << endl;
cout << "  3333333333  000    000         777  2222222222  " << endl;
cout << "  3333333333  000    000         777  2222222222  " << endl;
cout << "         333  000    000         777  222         " << endl;
cout << "  3333333333  0000000000         777  2222222222  " << endl;
cout << "  3333333333  0000000000         777  2222222222  " << endl;
cout << "--------------------------------------------------" << endl;
cout << " Carlos Espanya Monedero & Andres Bertomeu Pedros " << endl;
cout << "--------------------------------------------------" << endl;
}


/************************************************
void MostrarMenu (char &op, Matriu mat, Puntuacio &, Puntuacions &)
Entrades:
 char &op: car?cter amb qu? s'elegeix una opci? del men?.
 Matriu mat: matriu inicial amb qu? es va a comen?ar a jugar.
 Puntuacio &: estructura de cont? els noms i les puntuacions dels jugadors.
 Puntuacions &: vector de registres que cont? els noms i les puntuacions dels jugadors.
Eixides:
 char &op: car?cter amb qu? s'elegeix una opci? del men?.
 Matriu mat: matriu inicial amb qu? es va a comen?ar a jugar.
 Puntuacio &: estructura de cont? els noms i les puntuacions dels jugadors.
 Puntuacions &: vector de registres que cont? els noms i les puntuacions dels jugadors.
Objectiu: 
 mostrar per pantalla la portada del joc. 
************************************************/
void MostrarMenu (char &op, Matriu mat, Puntuacio &, Puntuacions &)
{
	ifstream f;
	string aa;
	Puntuacio punt;
	int moviments = 0;
	int punts;
	int recompte;
	Puntuacions puntuacions;
	system ("cls");
	Portada ();
	do
	{
		cout << "p: Jugar una nueva partida" << endl;
		cout << "l: Continuar partida guardada" << endl;
		cout << "r: Mostrar ranking mejores puntuaciones" << endl;
		cout << "q: Salir del juego" << endl;
		cout << "Introduzca opcion: ";
		cin >> op;
		
		switch (op)
		{
			case 'p':
                  MatriuCuadro(mat, moviments, recompte);
                  MostrarOpcio(mat, punt, puntuacions);			
			break;
			case 'l':
				ContinuarPartida (f, mat, puntuacions, punt, punts, moviments);
				MatriuCuadro(mat, moviments, punts);
				MostrarOpcio(mat, punt, puntuacions);	
				
			break;
			case 'r':
				cout << "No sabem :(" << endl;
				cin.ignore();
				getline(cin,aa);
				MostrarMenu(op, mat, punt, puntuacions);
			break;		
		}	

	} while (op != 'q' && op != 'p' && op != 'l' && op != 'r');
	if (op == 'q')
		return;
}


/************************************************
void MatriuInici (Matriu mat)
Entrades:
 Matriu mat: matriu inicial amb qu? es va a comen?ar a jugar.
Eixides:
 Matriu mat: matriu inicial amb qu? es va a comen?ar a jugar.
Objectiu: 
 Generar la matriu inicial del joc.
************************************************/
void MatriuInici (Matriu mat)
{
	int i, j;
	for (i = 0; i < I; i++)
		for (j = 0; j < J; j++)
		    mat [i][j] = 0;	
	 mat[1][1] = 1;
	 mat[2][2] = 2;
}


/************************************************
void ContinuarPartida (ifstream &f, Matriu mat, Puntuacions&, Puntuacio&, int &punts, int &moviment)
Entrades:
 ifstream &g: fitxer de lectura on es guarden les dades d'un jugador.
 Matriu mat: matriu amb qu? es juga.
 Puntuacions &: vector de registres que cont? els noms i les puntuacions dels jugadors.
 Puntuacio&: registre on es guarden les dades del jugador.
 int &punts: enter que indica la puntuaci? del jugador.
 int &moviment: enter que indica el nombre de moviments del jugador.
Eixides:
 Matriu mat: matriu inicial amb qu? es va a comen?ar a jugar.
Objectiu: 
 Generar la matriu inicial del joc.
************************************************/
void ContinuarPartida (ifstream &f, Matriu mat, Puntuacions&, Puntuacio&, int &punts, int &moviment)
{
	Puntuacio punt;
	Puntuacions puntuacions;
	string partida;
	string pos;
	char c;
	cout << "Introdueix el nom de la partida:" << endl;
	cin >> partida;
	f.open(partida.c_str());
	if (!f)
	{
		cout << "Error al obrir l'arxiu.'";
		cin.ignore();
		getline(cin, pos);
		MatriuInici (mat);
		MostrarMenu(c, mat, punt, puntuacions);
	}
	else 
	{
		llegirFitxerGuardat (f, puntuacions, mat, punts, moviment);
		f.close();
		
	}
}       
    
	     
/************************************************
void MatriuCuadro (const Matriu mat, int moviments, int recompte)
Entrades:
 const Matriu mat: Matriu amb qu? es juga.
 int moviments: enter que representa el nombre de moviments que ha realitzat el jugador.
 int recompte: enter que representa la puntuaci? del jugador.
Eixides: Cap.
Objectiu: 
 Generar la matriu del joc.
************************************************/ 
void MatriuCuadro (const Matriu mat, int moviments, int recompte)
{
	int i, j;
	system("cls");
	cout << "Puntuacio: " << recompte << endl;
	cout << "Moviments: " << moviments << endl;
	cout << endl;
	for (i = 0; i < I; i++)
	{
      cout << "+-------+-------+-------+-------+" << endl;
		for (j = 0; j < J; j++)
		{		     
		    if ((mat[i][j])/10 == 0)
            cout << "|      " << mat[i][j];
        	else     if ((mat[i][j])/100 == 0)
            cout << "|     " << mat[i][j];
            else     if ((mat[i][j])/1000 == 0)
            cout << "|    " << mat[i][j];
            else     if ((mat[i][j])/10000 == 0)
            cout << "|   " << mat[i][j];
            }

		cout << '|' << endl;
	    }
		cout << "+-------+-------+-------+-------+" << endl;
  }


/************************************************
void MostrarOpcio (Matriu mat, Puntuacio &, Puntuacions &)
Entrades:
 Matriu mat: Matriu amb qu? es juga.
 Puntuacio &: estructura de cont? els noms i les puntuacions dels jugadors.
 Puntuacions &: vector de registres que cont? els noms i les puntuacions dels jugadors.
Eixides:
 Matriu mat: Matriu amb qu? es juga.
 Puntuacio &: estructura de cont? els noms i les puntuacions dels jugadors.
 Puntuacions &: vector de registres que cont? els noms i les puntuacions dels jugadors.
Objectiu: 
 Mostrar els moviments de la matriu i modificar aquesta.
************************************************/ 
void MostrarOpcio (Matriu mat, Puntuacio &, Puntuacions &)
{
	Puntuacions puntuacions;
	Puntuacio punt;
	char op;
	int recompte = 0;
	int moviments = 0;

do
	{
		cout << "a: moure les caselles a l'esquerre" << endl;
		cout << "d: moure les caselles a la dreta" << endl;
		cout << "w: moure les caselles cap a dalt." << endl;
        cout << "s: moure les caselles cap a baix" << endl; 
        cout << "x: si no veus mes moviments" << endl; 
		cout << "q: Eixir del joc" << endl;
		cin >> op;
		
		switch (op)
		{
			case 'a':
				MovimentEsquerra (mat);
				MovimentEsquerra2 (mat);
				NumAleatori (mat);
				moviments ++;
				Recompte (mat, recompte);
				MatriuCuadro(mat, moviments, recompte);
							
			break;
			case 'd':
				
				MovimentDreta (mat);
				MovimentDreta2 (mat);
				NumAleatori (mat);
				moviments++;
				Recompte (mat, recompte);
				MatriuCuadro(mat, moviments, recompte);
			
			break;
			case 'w':
				MovimentAmunt (mat);
				MovimentAmunt2 (mat);
				NumAleatori (mat);
				moviments++;
				Recompte (mat, recompte);
				MatriuCuadro(mat, moviments, recompte);
			
			break;	
            case 's':
				MovimentAvall (mat);	
				MovimentAvall2 (mat);
				NumAleatori (mat);	
				moviments++;
				Recompte (mat, recompte);
				MatriuCuadro(mat, moviments, recompte);

			break;
			case 'x':
				Puntuar (mat, op, punt, puntuacions, moviments);	
			break;
			case 'q':
				Puntuar (mat, op, punt, puntuacions, moviments);	
		}	

	} while (op != 'q' && Noguanyat(mat) && NoMov (mat));
	

	if(op == 'q')
		MostrarOpcio (mat, punt, puntuacions);
	
	else if (!Noguanyat (mat))
	{
		cout << "\nENHORABONA. HAS GUANYAT" << endl;
		Puntuar (mat, op, punt, puntuacions, moviments);		
	}
	
	else if (!NoMov(mat))
	{
		cout << "\nGAME OVER" << endl;
		Puntuar (mat, op, punt, puntuacions, moviments);	
	}
		
	return;
}


/************************************************
bool Noguanyat(Matriu mat)
Entrades:
 Matriu mat: Matriu amb qu? es juga.
Eixides:
 Matriu mat: Matriu amb qu? es juga.
 bool: boole? que indica si el jugador ha guanyat la partida o no.
Objectiu: 
 Indicar si el jugador ha guanyat la partida o no.
************************************************/ 
bool Noguanyat(Matriu mat)
{
	int i, j;
	bool noguanyat = true;
	for (i = 0; i < I; i++)
		for (j = 0; j < J; j++)
			if (mat[i][j] == 3072)
				noguanyat = false;
	
	return noguanyat;
}


/************************************************
bool NoMov (Matriu mat)
Entrades:
 Matriu mat: Matriu amb qu? es juga.
Eixides:
 bool: boole? que indica si hi ha moviments disponibles.
 Matriu mat: Matriu amb qu? es juga.
Objectiu: 
 Indicar si es pot realitzar moviments o no.
************************************************/
bool NoMov (Matriu mat)
{
	int i, j;
	bool nomov = true;
	for (i = 0; i < I; i++)
	{
		for (j = 0; j < J; j++)
		{
			if (((mat[i][j] != 2 && mat[i][j] != 1 && mat[i][j] != 0) && mat[i][j] != mat[i][j+1] && mat[i][j] != mat[i][j-1] && mat[i][j] != mat[i+1][j] && mat[i][j] != mat[i-1][j]))
				if ((mat[i][j] == 1 && mat[i][j+1] != 2 && mat[i][j-1] != 2 && mat[i+1][j] != 2 && mat[i-1][j] != 2) && (mat[i][j] == 2 && mat[i][j+1] != 1 && mat[i][j-1] != 1 && mat[i+1][j] != 1 && mat[i-1][j] != 1))
					nomov = false;
			if (nomov == true)
				return nomov;
		}
	}
	return nomov;
}


/************************************************
void llegirFitxerGuardat (ifstream &g, Puntuacions &puntu, Matriu mat,int &punts,int &moviment)
Entrades:
 ifstream &g: fitxer de lectura on es guarden les dades d'un jugador.
 Puntuacions &puntu: vector de registres que cont? els noms i les puntuacions dels jugadors.
 Matriu mat: matriu amb qu? es juga.
 int &punts: enter que indica la puntuaci? del jugador.
 int &moviment: enter que indica el nombre de moviments del jugador.
Eixides:
 ifstream &g: fitxer de lectura on es guarden les dades d'un jugador.
 Puntuacions &puntu: vector de registres que cont? els noms i les puntuacions dels jugadors.
 Matriu mat: matriu amb qu? es juga.
 int &punts: enter que indica la puntuaci? del jugador.
 int &moviment: enter que indica el nombre de moviments del jugador.
Objectiu: 
 Llegir un fitxer on es guarden les dades d'un jugador.
************************************************/
void llegirFitxerGuardat (ifstream &g, Puntuacions &puntu, Matriu mat,int &punts,int &moviment)
{
	int i, j;
	string nombre;
	while(getline(g, nombre))
	{
		g >> punts;
		g >> moviment;
		for (i = 0; i < I; i++)
         for (j = 0; j < J; j++)
             g >> mat[i][j];
		puntu.punt[puntu.n].nom = nombre;
		puntu.punt[puntu.n].punts = punts;
		puntu.punt[puntu.n].movim = moviment;
		puntu.n++;
		g.ignore();
	}
	return;
}


/************************************************
void Puntuar (Matriu mat, char &par, Puntuacio &, Puntuacions &, int moviment)
Entrades:
 ifstream &g: fitxer de lectura on es guarden les dades d'un jugador.
 Matriu mat: matriu amb qu? es juga. 
 char &par: car?cter que afirma o no una pregunta.
 Puntuacio &: registre que cont? el nom i la puntuacio d'un jugador.
 Puntuacions &: vector de registres que cont? els noms i les puntuacions dels jugadors.
 int &punts: enter que indica la puntuaci? del jugador.
 int &moviment: enter que indica el nombre de moviments del jugador.
Eixides:
 ifstream &g: fitxer de lectura on es guarden les dades d'un jugador.
 Puntuacions &puntu: vector de registres que cont? els noms i les puntuacions dels jugadors.
 Matriu mat: matriu amb qu? es juga.
 int &punts: enter que indica la puntuaci? del jugador.
 int &moviment: enter que indica el nombre de moviments del jugador.
Objectiu: 
 Llegir un fitxer on es guarden les dades d'un jugador.
************************************************/
void Puntuar (Matriu mat, char &par, Puntuacio &, Puntuacions &, int moviment)
{
	string nombre;
	string pos;
	int recompte;
	Puntuacio punt;
	ofstream f;
	Puntuacions puntuacions;
	char n;
	puntuacions.n= 0;
	//numero de la puntuacio
	cout << "Vols guardar la partida? (s/n)" << endl;
	cin >> par;
	if (par == 's')
	{
		Recompte (mat, recompte);
		cout << "Dime el nom." << endl;
		cin >> nombre;
		f.open(nombre.c_str());
		if (!f)
			cout << "Error obrint el fitxer" << endl;
		else
		{
			punt = introduirPuntuacio(nombre, recompte, moviment);
			if (insertarPuntuacio(punt, puntuacions, mat) == true)
			{
				escriureVector2Fitxer (f, puntuacions, mat);
				cout << "S'ha introduit la puntuacio.";
				cin.ignore();
				getline(cin,pos);
				MatriuInici (mat);
				MostrarMenu(par, mat, punt, puntuacions);
			}
			else
				cout << "No s'ha introduit correctament." << endl;
			
			f.close();
			MostrarMenu(par, mat, punt, puntuacions);
		}
	}
	else
		MatriuInici (mat);
		MostrarMenu(par, mat, punt, puntuacions);
		
}

/**************************************
bool insertarPuntuacio(Puntuacio p, Puntuacions &totspunts, Matriu mat)
Entrades:
 Puntuacio p: estructura on hem escrit el nom i la puntaci?.
 Puntuacions &totspunts: vector de registres que cont? les dades de tots els jugadors.
Eixides:
 Puntuacions &totspunts: vector de registres que cont? les dades de tots els jugadors.
Objectiu: 
 Indicar si s'ha pogut introduir la puntuaci? o no.
**************************************/
bool insertarPuntuacio(Puntuacio p, Puntuacions &totspunts, Matriu mat)
{
	int i, j;
		bool ok= false;
		
		if (totspunts.n < N)
		{   
		    totspunts.punt[totspunts.n] = p;
		    for (i=0; i<I; i++)
		    	for (j=0; j<J; j++)
		    		totspunts.punt[totspunts.n].mat[i][j] = mat[i][j];
		    totspunts.n++;
		    
		    ok= true;
      }
      return ok;	
}

/**************************************
void escriureVector2Fitxer (ofstream & f, Puntuacions puntu, Matriu mat)
Entrades:
 ofstream & f: fitxer on es guarda el nom i la puntuaci? d'un jugador.
 Puntuacions puntu: estructura on es guarda el nom i la puntuaci? d'un jugador.
 Matriu mat: matriu on es juga.
Eixides:
 Cap.
Objectiu: 
 Escriure en un fitxer el nom, la puntuaci? d'un jugador.
**************************************/
void escriureVector2Fitxer (ofstream & f, Puntuacions puntu, Matriu mat)
{
	int i, j;
	for (i = 0; i < puntu.n; i++)
	{
		f << puntu.punt[i].nom << endl;
		f << puntu.punt[i].punts << endl;
		f << puntu.punt[i].movim << endl;
	}
	for (i=0; i < I; i++)
	{
		for (j=0; j < J; j++)
			f << mat[i][j] << endl;
	}
	return;
}


/**************************************
Puntuacio introduirPuntuacio (string &nombre, int recompte, int moviment)
Entrades:
 string &nombre: cadena que ?s el nom del jugador.
 int recompte: enter que indica la puntuaci? d'un jugador.
 int moviment: enter que indica el nombre de moviments d'un jugador.
Eixides:
 string &nombre: cadena que ?s el nom del jugador.
 Puntuacio: estructura on es guarda el nom i la puntuaci? d'un jugador.
Objectiu: 
 Introduir el nom i la puntuaci? d'un jugador.
**************************************/
Puntuacio introduirPuntuacio (string &nombre, int recompte, int moviment)
{
	Puntuacio punt;
 	punt.nom = nombre;
 	punt.punts = recompte;
 	punt.movim = moviment;
 	cout << endl;
 	
 	return punt;
}


/**************************************
void Recompte (Matriu mat, int &recompte)
Entrades:
 Matriu mat: matriu on es juga.
 int &recompte: enter que indica la puntuaci? d'un jugador.
Eixides:
 int &recompte: enter que indica la puntuaci? d'un jugador.
 Matriu mat: matriu on es juga.
Objectiu: 
 Comptar la puntuaci? d'un jugador.
**************************************/
void Recompte (Matriu mat, int &recompte)
{
	int i, j;
	recompte = mat[0][0];
	
	for (i=0; i < I; i++)
		for (j=0; j < J; j++)
		{
			if (mat[i][j] >= recompte)
				recompte = mat[i][j];
		}
	return;
}


/**************************************
void MovimentDreta (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga..
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Sumar els valors de la matriu cap a la esquerra.
**************************************/
void MovimentDreta (Matriu mat)
{
	int i, j;
	for (i =  0; i < I; i++)
	{
		for (j = J - 1; j >= 0; j--)
		{		
			if ((mat[i][j] == 1 && mat[i][j-1] == 2) || (mat[i][j] == 2 && mat[i][j-1]== 1))
			{
				mat[i][j-1] += mat[i][j];
				mat[i][j] = 0;			
			}
			else if ((mat[i][j] == mat[i][j-1]) && mat[i][j] != 0 && mat[i][j] != 1 && mat[i][j] != 2 )
			{
				mat[i][j-1] += mat[i][j];
				mat[i][j] = 0;
			}	
		}
	}
}


/**************************************
void MovimentDreta2 (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Moure els valors de la matriu cap a la dreta.
**************************************/
void MovimentDreta2 (Matriu mat)
{
	int i, j;
	for (i =  0; i < I; i++)
	{
			for (j = J-1; j > 0; j--)
		{
			if (mat[i][j] == 0 && mat[i][j-1] != 0)
			{
				mat[i][j] = mat[i][j-1];	
				mat[i][j-1] = 0;
			}
		}
	}
}


/**************************************
void MovimentEsquerra (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Sumar els valors de la matriu cap a la dreta.
**************************************/
void MovimentEsquerra (Matriu mat)
{
	int i, j;
	for (i =  0; i < I; i++)
	{
		for (j = 0; j < J - 1; j++)
		{	
		if ((mat[i][j+1] == 1 && mat[i][j] == 2) || (mat[i][j+1] == 2 && mat[i][j]== 1))
			{
				mat[i][j+1] += mat[i][j];
				mat[i][j] = 0;			
			}
			else if ((mat[i][j+1] == mat[i][j]) && mat[i][j] != 0 && mat[i][j] != 1 && mat[i][j] != 2 )
			{
				mat[i][j+1] += mat[i][j];
				mat[i][j] = 0;
			}	
		}
	}
}


/**************************************
void MovimentEsquerra2 (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Moure els valors de la matriu cap a la esquerra.
**************************************/
void MovimentEsquerra2 (Matriu mat)
{
	int i, j;
	for (i =  0; i < I; i++)
	{
			for (j = 0; j < J -1; j++)
		{
			if (mat[i][j] == 0 && mat[i][j+1] != 0)
			{
				mat[i][j] = mat[i][j+1];	
				mat[i][j+1] = 0;
			}
		}
	}
}


/**************************************
void MovimentAmunt (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Sumar els valors de la matriu cap avall.
**************************************/
void MovimentAmunt (Matriu mat)
{
	int i, j;
	for (i = 0; i < I; i++)
	{
		for (j = 0; j < J; j++)
		{
			if ((mat[i][j] == 1 && mat[i+1][j] == 2) || (mat[i][j] == 2 && mat[i+1][j] == 1))
			{
				mat[i+1][j] += mat[i][j];
				mat[i][j] = 0;
			}
			else if (mat[i][j] == mat[i+1][j] && mat[i][j] != 0 && mat[i][j] != 1 && mat[i][j] != 2)
			{
				mat[i+1][j] += mat[i][j];
				mat[i][j] = 0;
			}
		}
	}
}


/**************************************
void MovimentAmunt2 (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Moure els valors de la matriu cap amunt.
**************************************/
void MovimentAmunt2 (Matriu mat)
{
	int i, j;
	for (i = 0; i < I-1; i++)
	{
			for (j = 0; j < J; j++)
			{
				if(mat[i][j] == 0 && mat[i+1][j] != 0)
				{
					mat[i][j] = mat[i+1][j];
					mat[i+1][j] = 0;
				}
			}	
	}
}


/**************************************
void MovimentAvall (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Sumar els valors de la matriu cap amunt.
**************************************/
void MovimentAvall (Matriu mat)
{
	int i, j;
	for (i = I; i >=0; i--)
	{
		for (j = 0; j < J; j++)
		{
			if ((mat[i][j] == 1 && mat[i-1][j] == 2) || (mat[i][j] == 2 && mat[i-1][j] == 1))
			{
				mat[i-1][j] += mat[i][j];
				mat[i][j] = 0;
			}
			else if (mat[i][j] == mat[i-1][j] && mat[i][j] != 0 && mat[i][j] != 1 && mat[i][j] != 2)
			{
				mat[i-1][j] += mat[i][j];
				mat[i][j] = 0;
			}
		}
	}
}


/**************************************
void MovimentAvall2 (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Moure els valors de la matriu cap avall.
**************************************/
void MovimentAvall2 (Matriu mat)
{
	int i, j;
	for (i = I-1; i > 0; i--)
	{
			for (j = 0; j < J; j++)
			{
				if(mat[i][j] == 0 && mat[i-1][j] != 0)
				{
					mat[i][j] = mat[i-1][j];
					mat[i-1][j] = 0;
				}
			}
	}	
}


/**************************************
void NumAleatori (Matriu mat)
Entrades:
 Matriu mat: matriu on es juga.
Eixides:
 Matriu mat: matriu on es juga.
Objectiu: 
 Generar un nombre aleatori del 1 al 3 en una posici? aleat?ria de la matriu.
**************************************/
void NumAleatori (Matriu mat)
{
	int i, j, x;
	bool zero = false;
	srand (time (NULL));
	
	for (i = 0; i < I; i++)
		for (j = 0; j < J; j++)
			if (mat[i][j] == 0)
				zero = true;
	if (zero)
	{
		do
		{
			i = rand ()%4;
			j = rand ()%4;
			x = 1 + rand()%3;
		}while (mat[i][j] != 0);
		
		mat[i][j] = x;			
	}			
}
