#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Déclaration des prototypes
int main();
void menu();
void image();
void choix_niveau();
void numero(const char *text, int b);
void indication(int nombre1, int nombre2, int power[nombre1][nombre1], int nbtab1, int nbtab2);
void affichage_num();
void verification_cln(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau);
void verification_lgn(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau);
void change_color_true_lgn(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int ligne);
void change_color_false_lgn(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int ligne, int power[nombre1][nombre1]);
void change_color_true_cln(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int cln);
void change_color_false_cln(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int cln);

void numero_eiffel(const char *text, int b);
void affichage_num_eiffel();
void verification_cln_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau);
void verification_lgn_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau);
void change_color_true_lgn_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int ligne);
void change_color_false_lgn_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int ligne, int power[nombre1][nombre1]);
void change_color_true_cln_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int cln);
void change_color_false_cln_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int cln);

void numero_smile(const char *text, int b);
void affichage_num_smile();
void verification_cln_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau);
void verification_lgn_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau);
void change_color_true_lgn_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int ligne);
void change_color_false_lgn_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int ligne, int power[nombre1][nombre1]);
void change_color_true_cln_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int cln);
void change_color_false_cln_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int cln);

// Déclaration des variable globales SDL & TAB en global
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
SDL_Event event;
SDL_Surface *text = NULL;
SDL_Texture *text2 = NULL;
SDL_bool quit = SDL_FALSE;

Mix_Chunk *fond;
Mix_Chunk *clickmouse;
Mix_Chunk *notreprojet;

int nombre1 = 0;
int nombre2 = 0;

int tab2[5000] = {0};
int tab[5000] = {0};
char tmp[5000] = {0};

int a = 130;
int m = 150;

int x, y = 0;
int statut = EXIT_FAILURE;

// Initialisation de la SDL
void SDL_init()
{
	SDL_Surface *icone = SDL_LoadBMP("images/icone.bmp");							// Pour l'icone
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) // Initialisation de l'API Mixer
	{
		printf("%s", Mix_GetError());
	}
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
	}
	window = SDL_CreateWindow("Picross", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 1000, SDL_WINDOW_SHOWN); // Création de la fenetre en 1500x1000

	Mix_AllocateChannels(4);
	Mix_Volume(1, 50);
	Mix_Volume(2, 75);
	Mix_Volume(3, 30);
	fond = Mix_LoadWAV_RW(SDL_RWFromFile("sound/unamatinna.wav", "rb"), 2);
	clickmouse = Mix_LoadWAV_RW(SDL_RWFromFile("sound/click.wav", "rb"), 1);
	notreprojet = Mix_LoadWAV_RW(SDL_RWFromFile("sound/macronprojet.mp3", "rb"), 3);
	//Mix_PlayChannel(3, notreprojet, 0);
	Mix_PlayChannel(2, fond, -1);
	SDL_SetWindowIcon(window, icone);
}

// Generation de nombre aleatoire pour la Longueur et la Largeur
void generate_random_num()
{
	srand(time(NULL));
	nombre1 = (rand() % (5 - 4 + 1) + 4);
	// nombre2 = (rand() % (10 - 4 + 1) + 4);

	// nombre1 = 10;
	nombre2 = nombre1;
	printf("Cln : %d Lgn : %d\n\n", nombre1, nombre2);
}

void generate_random_num_dificile()
{
	srand(time(NULL));
	nombre1 = (rand() % (12 - 10 + 1) + 10);
	// nombre2 = (rand() % (10 - 4 + 1) + 4);

	// nombre1 = 10;
	nombre2 = nombre1;
	printf("Cln : %d Lgn : %d\n\n", nombre1, nombre2);
}

// Ouverture du fichier pour mode Tour Eiffel
void eiffel(int tabeiffel[nombre1][nombre2], int nombre1, int nombre2)
{

	FILE *fichier = NULL;
	int i = 0;
	int j = 0;
	fichier = fopen("Draw/eiffel.txt", "r"); // Ouverture du fichier

	for (i = 0; i < nombre1; i++)
	{
		for (j = 0; j < nombre2; j++)
		{
			tabeiffel[i][j] = 0;
			fscanf(fichier, "%d", &tabeiffel[i][j]); // Remplisage du tableau
		}
	}

	fclose(fichier);

	// afficher le tableau
	for (i = 0; i < nombre1; i++)
	{
		for (j = 0; j < nombre2; j++)
		{
			printf("%d ", tabeiffel[i][j]);
		}
		printf("\n");
	}
}

// Chargement de la matrice aleatoire pour le mode aleatoire
void matrice(int occupation[nombre1][nombre2], int power[nombre1][nombre2], int nbtab1, int nbtab2)
{
	for (int i = 0; i < nbtab2; i++)
	{
		for (int j = 0; j < nbtab1; j++)
		{
			power[i][j] = 0;
			occupation[i][j] = 0;
		}
	}

	for (int i = 0; i < nbtab2; i++)
	{
		for (int j = 0; j < nbtab1; j++)
		{
			power[i][j] = rand() % (1 - 0 + 1) + 0;
			printf("%d ", power[i][j]);
		}
		printf("\n");
	}
}

// Chargement de la matrice avec le fichier pour le mode smile
void matrice_smile(int occupation[nombre1][nombre2], int power[nombre1][nombre2], int nbtab1, int nbtab2)
{
	for (int i = 0; i < nbtab2; i++)
	{
		for (int j = 0; j < nbtab1; j++)
		{
			power[i][j] = 0;
			occupation[i][j] = 0;
		}
	}

	for (int i = 0; i < nbtab2; i++)
	{
		for (int j = 0; j < nbtab1; j++)
		{
			// power[i][j] = rand() % (1 - 0 + 1) + 0;
			printf("%d ", power[i][j]);
		}
		printf("\n");
	}
}

// Constrution du tableau pour le mode aleatoire
void construire_tab(int nombre1, int nombre2, SDL_Rect rect[nombre1][nombre2])
{
	int display_plateau1 = (nombre1 * 40) + 150;
	int display_plateau2 = (nombre2 * 40) + 150;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, display_plateau1, display_plateau2);
	if (NULL == texture)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 225, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// SDL_Rect rect[nombre1][nombre2];

	int largeur = nombre1;
	int longueur = nombre2;

	for (int i = 0; i < nombre1; i++)
	{
		for (int j = 0; j < nombre2; j++)
		{

			rect[i][j].x = 150 + i * 40;
			rect[i][j].y = 150 + j * 40;
			rect[i][j].w = 30;
			rect[i][j].h = 30;

			SDL_RenderFillRect(renderer, &rect[i][j]);
		}
	}

	SDL_SetRenderTarget(renderer, NULL);
}

// Gestion des click pour le mode aleatoire
void click(int occupation[nombre1][nombre2], int power[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2])
{
	int display_plateau1 = (nombre1 * 40) + 220;
	int display_plateau2 = (nombre2 * 40) + 220;
	SDL_Rect gameplateau;
	gameplateau.x = (1500 / 2 - display_plateau1 / 2);
	gameplateau.y = (1000 / 2 - display_plateau2 / 2);

	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	SDL_RenderPresent(renderer);
	while (!quit)
	{

		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}

		Uint32 boutons;

		SDL_PumpEvents();

		boutons = SDL_GetMouseState(&x, &y);

		x = (x - (gameplateau.x + 150)) / 40;
		y = (y - (gameplateau.y + 150)) / 40;

		//printf(" DEHORS : %d et %d\n", x, y);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			// printf("\nDEDEANS : %d et %d\n", x, y);
			if ((x >= 17 && x <= 20) && (y >= 13 && y <= 15))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyRenderer(renderer);
				menu();
			}

			if (x < nombre1 && y < nombre2 && x >= 0 && y >= 0)
			{
				Mix_PlayChannel(1, clickmouse, 0);

				if (occupation[y][x] != 1)
				{
					SDL_SetRenderTarget(renderer, texture);
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect[x][y]);
					occupation[y][x] = 1;
				}
				else
				{

					SDL_SetRenderTarget(renderer, texture);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &rect[x][y]);
					occupation[y][x] = 0;
				}

				verification_cln(nombre1, nombre2, occupation, power, rect, gameplateau);
				verification_lgn(nombre1, nombre2, occupation, power, rect, gameplateau);
			}

			if ((x >= 17 && x <= 20) && (y >= 10 && y <= 15))
			{
				SDL_DestroyRenderer(renderer);
				menu();
			}
			SDL_SetRenderTarget(renderer, NULL);

			SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
			SDL_RenderCopy(renderer, texture, NULL, &gameplateau);

			SDL_RenderPresent(renderer);
			sleep(0.5);
			break;
		case SDL_QUIT:
			quit = SDL_TRUE;
			break;
		}
	}
	SDL_Delay(3000);
}

// Affiche des séquences pour le mode aleatoire
void numero(const char *tmp, int b)
{
	// SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, texture);
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/Minecrafter.Alt.ttf", 30);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {31, 116, 176, 0.9};

	text = TTF_RenderText_Blended(font, tmp, color);
	text2 = SDL_CreateTextureFromSurface(renderer, text);

	SDL_Rect texterect;
	texterect.x = a;
	texterect.y = m;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);
	SDL_RenderCopy(renderer, text2, NULL, &texterect);
	// SDL_RenderPresent(renderer);

	SDL_SetRenderTarget(renderer, NULL);
}

// Calcule pour send to affichage numero de la séquence aleatoire
void affichage_num()
{
	for (int i = 0; i < 5000; i++)
	{

		if (tab[i] == 99)
		{
			i++;
			m = m + 40;
			a = 130;
		}
		if (tab[i] == 99)
		{
			i++;
			m = m + 40;
			a = 130;
		}

		// sprintf(tmp, "%d", tab[i]);

		// if (strcmp(tmp, "99") == 0)
		// {
		// 	i++;
		// 	m = m + 40;
		// 	a = 130;
		// 	// printf("\n");
		// }
		sprintf(tmp, "%d", tab[i]);

		if (strcmp(tmp, "0") != 0)
		{
			// printf("%s ", tmp);
			numero(tmp, a);
			a = a - 30;
		}
	}
	// printf("=================================================================\n");
	m = 115;
	a = 155;
	for (int i = 0; i < 5000; i++)
	{
		// sprintf(tmp, "%d", tab2[i]);

		// if (strcmp(tmp, "99") == 0)
		// {
		// 	i++;
		// 	a = a + 40;
		// 	m = 115;
		// 	// printf("\n");
		// }

		if (tab2[i] == 99)
		{
			i++;
			a = a + 40;
			m = 115;
			// printf("\n");
		}
		if (tab2[i] == 99)
		{
			i++;
			a = a + 40;
			m = 115;
			// printf("\n");
		}
		sprintf(tmp, "%d", tab2[i]);

		if (strcmp(tmp, "0") != 0)
		{
			// printf("%s ", tmp);
			numero(tmp, m);
			m = m - 40;
		}
	}
}

// Verification de la colonne mode aleatoire
void verification_cln(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau)
{
	int total_power = 0;
	int count = 0;
	int i, y = 0;
	int total_power2 = 0;
	int total_occup = 0;
	SDL_Surface *text;
	SDL_Texture *texture2;
	SDL_Rect texterect;

	for (i = 0; i < nombre1; i++)
	{
		for (int j = 0; j < nombre1; j++)
		{
			if (power[i][j] == 1)
			{
				total_power2++;
			}
			if (occupation[i][j] == 1 && power[i][j] == 1)
			{
				total_occup++;
			}
		}
	}
	if (total_power2 == total_occup)
	{
		printf("OK");
		TTF_Init();
		TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
		if (!font)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
		}
		SDL_Color color = {0, 255, 0, 255};
		text = TTF_RenderText_Blended(font, "Bravo !", color);
		texture2 = SDL_CreateTextureFromSurface(renderer, text);
		SDL_Rect texterect;
		texterect.x = 580;
		texterect.y = 850;
		SDL_FreeSurface(text);
		TTF_CloseFont(font);

		TTF_Quit();
		SDL_SetRenderTarget(renderer, NULL);

		// SDL_RenderClear(renderer);

		SDL_QueryTexture(texture2, NULL, NULL, &texterect.w, &texterect.h);

		SDL_RenderCopy(renderer, texture2, NULL, &texterect);

		SDL_RenderPresent(renderer);
		sleep(4);
		SDL_DestroyTexture(texture2);
		SDL_DestroyRenderer(renderer);
		menu();
	}

	while (y < nombre1)
	{
		total_power = 0;
		count = 0;
		for (i = 0; i < nombre1; i++)
		{
			total_power += power[i][y];
		}

		for (int i = 0; i < nombre1; i++)
		{
			if ((power[i][y] == 1) && (occupation[i][y] == 1))
			{
				count++;
			}
			if ((power[i][y] == 0) && (occupation[i][y] == 1))
			{
				count--;
			}
		}

		if (count == total_power)
		{
			// printf("\ncln %d : Ok\n", y);
			change_color_true_cln(nombre1, nombre2, occupation, rect, gameplateau, power, y);
		}
		if (count != total_power)
		{
			change_color_false_cln(nombre1, nombre2, occupation, rect, gameplateau, y);
		}

		y++;
	}
}

// Verification de ligne mode aleatoire
void verification_lgn(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau)
{
	int total_power = 0;
	int count = 0;
	int i, y = 0;
	while (y < nombre1)
	{
		total_power = 0;
		count = 0;
		for (i = 0; i < nombre1; i++)
		{
			total_power += power[y][i];
		}

		for (int i = 0; i < nombre1; i++)
		{
			if ((power[y][i] == 1) && (occupation[y][i] == 1))
			{
				count++;
			}
			if ((power[y][i] == 0) && (occupation[y][i] == 1))
			{
				count--;
			}
		}

		if (count == total_power)
		{
			// printf("\nLgn %d : Ok\n", y);
			change_color_true_lgn(nombre1, nombre2, occupation, rect, gameplateau, power, y);
		}
		if (count != total_power)
		{
			// change_color_false_lgn(nombre1, nombre2, occupation, rect, gameplateau, y, power);
		}

		y++;
	}
}

// Changement de couleur si ligne ok
void change_color_true_lgn(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int ligne)
{

	for (int i = 0; i < nombre1; i++)
	{
		if (power[ligne][i] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rect[i][ligne]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Changement de couleur si ligne pas ok
void change_color_false_lgn(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int ligne, int power[nombre1][nombre1])
{
	int count = 0;
	for (int i = 0; i < nombre1; i++)
	{
		if (occupation[ligne][i] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[i][ligne]);
		}
	}

	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);

	int total_power = 0;

	for (int i = 0; i < nombre1; i++)
	{
		total_power += power[i][ligne];
	}

	for (int i = 0; i < nombre1; i++)
	{
		if ((power[i][ligne] == 1) && (occupation[i][ligne] == 1))
		{
			count++;
		}
		if ((power[i][ligne] == 0) && (occupation[i][ligne] == 1))
		{
			count--;
		}
	}
	printf("La ligne : %d", ligne);
	for (int i = 0; i < nombre1; i++)
	{
		if (count == total_power)
		{
			if (power[i][ligne] == 1)
			{
				SDL_SetRenderTarget(renderer, texture);
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, &rect[ligne][i]);
			}
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	SDL_RenderPresent(renderer);
	// SDL_Delay(200);
}

// Calcul des sequences
void indication(int nombre1, int nombre2, int power[nombre1][nombre1], int nbtab1, int nbtab2)
{
	int i;
	int j;
	int k = 0;
	int count1 = 0;
	int z = 0;

	while (z < nbtab2)
	{

		for (i = 0; i < nbtab1; i++)
		{

			if (power[z][i] == 1)
			{
				count1 = count1 + 1;
			}

			if (power[z][i] == 0)
			{
				if (count1 > 0)
				{
					tab[k] = count1;
					k = k + 1;
					count1 = 0;
				}
			}
		}
		sleep(0.5);
		if (count1 > 0)
		{
			tab[k] = count1;
			k = k + 1;
			count1 = 0;
		}

		tab[k] = 99;
		k = k + 1;
		z = z + 1;
	}
	count1 = 0;
	k = 0;
	z = 0;
	while (z < nbtab1)
	{

		for (i = 0; i < nbtab2; i++)
		{

			if (power[i][z] == 1)
			{
				count1 = count1 + 1;
			}

			if (power[i][z] == 0)
			{
				if (count1 > 0)
				{
					tab2[k] = count1;
					k = k + 1;
					count1 = 0;
				}
			}
		}

		if (count1 > 0)
		{
			tab2[k] = count1;
			k = k + 1;

			count1 = 0;
		}
		tab2[k] = 99;
		k = k + 1;
		z = z + 1;
	}
}

// Changement couleur si colonne ok
void change_color_true_cln(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int cln)
{

	for (int i = 0; i < nombre1; i++)
	{
		if (power[i][cln] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rect[cln][i]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Affichage de la séquences mode eiffel
void numero_eiffel(const char *tmp, int b)
{
	// SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, texture);
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/Minecrafter.Alt.ttf", 25);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {31, 116, 176, 0.9};

	text = TTF_RenderText_Blended(font, tmp, color);
	text2 = SDL_CreateTextureFromSurface(renderer, text);

	SDL_Rect texterect;
	texterect.x = a;
	texterect.y = m;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);
	SDL_RenderCopy(renderer, text2, NULL, &texterect);
	// SDL_RenderPresent(renderer);

	SDL_SetRenderTarget(renderer, NULL);
}

// Changement couleur si colonne non ok
void change_color_false_cln(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int cln)
{
	for (int i = 0; i < nombre1; i++)
	{
		if (occupation[i][cln] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[cln][i]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Calcul coordonnée pour mode eiffel
void affichage_num_eiffel()
{
	for (int i = 0; i < 5000; i++)
	{

		sprintf(tmp, "%d", tab[i]);

		if (strcmp(tmp, "99") == 0)
		{
			i++;
			m = m + 35;
			a = 120;
			// printf("\n");
		}
		sprintf(tmp, "%d", tab[i]);

		if (strcmp(tmp, "0") != 0)
		{
			// printf("%s ", tmp);
			numero_eiffel(tmp, a);
			a = a - 35;
		}
	}
	// printf("=================================================================\n");
	m = 115;
	a = 155;
	for (int i = 0; i < 5000; i++)
	{
		sprintf(tmp, "%d", tab2[i]);

		if (strcmp(tmp, "99") == 0)
		{
			i++;
			a = a + 35;
			m = 115;
			// printf("\n");
		}
		sprintf(tmp, "%d", tab2[i]);

		if (strcmp(tmp, "0") != 0)
		{
			// printf("%s ", tmp);
			numero_eiffel(tmp, m);
			m = m - 35;
		}
	}
}

// Gestion des clicks pour le mode eiffel
void click_eiffel(int occupation[nombre1][nombre2], int power[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2])
{
	int display_plateau1 = (nombre1 * 35) + 220;
	int display_plateau2 = (nombre2 * 35) + 220;
	SDL_Rect gameplateau;
	gameplateau.x = (1500 / 2 - display_plateau1 / 2);
	gameplateau.y = (1000 / 2 - display_plateau2 / 2);

	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	SDL_RenderPresent(renderer);
	// sleep(1);
	while (!quit)
	{

		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}

		Uint32 boutons;

		SDL_PumpEvents();

		boutons = SDL_GetMouseState(&x, &y);

		x = (x - (gameplateau.x + 150)) / 35;
		y = (y - (gameplateau.y + 150)) / 35;

		// printf(" DEHORS : %d et %d\n", x, y);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			// printf("\nDEDEANS : %d et %d\n", x, y);
			if ((x >= 25 && x <= 29) && (y >= 20 && y <= 23))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyRenderer(renderer);
				image();
			}

			if (x < nombre1 && y < nombre2 && x >= 0 && y >= 0)
			{
				Mix_PlayChannel(1, clickmouse, 0);

				if (occupation[y][x] != 1)
				{
					SDL_SetRenderTarget(renderer, texture);
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect[x][y]);
					occupation[y][x] = 1;
				}
				else
				{

					SDL_SetRenderTarget(renderer, texture);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &rect[x][y]);
					occupation[y][x] = 0;
				}

				if ((x >= 20 && x <= 22) && (y >= 25 && y <= 29))
				{
					SDL_DestroyRenderer(renderer);
					menu();
				}
				verification_cln_eiffel(nombre1, nombre2, occupation, power, rect, gameplateau);
				verification_lgn_eiffel(nombre1, nombre2, occupation, power, rect, gameplateau);
			}

			SDL_SetRenderTarget(renderer, NULL);

			SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
			SDL_RenderCopy(renderer, texture, NULL, &gameplateau);

			SDL_RenderPresent(renderer);
			break;
		case SDL_QUIT:
			quit = SDL_TRUE;
			break;
		}
	}
	SDL_Delay(3000);
}

// Chargement de la matrice avec le fichier pour le mode eiffel
void matrice_eiffel(int occupation[nombre1][nombre2], int power[nombre1][nombre2], int nbtab1, int nbtab2)
{
	for (int i = 0; i < nbtab2; i++)
	{
		for (int j = 0; j < nbtab1; j++)
		{
			power[i][j] = 0;
			occupation[i][j] = 0;
		}
	}

}

// Mode aleatoir
void aleatoire()
{
	SDL_Rect dst = {0, 0, 0, 0};
	SDL_Surface *text = NULL;
	SDL_Texture *text2 = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y = 0;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// SDL_RenderClear(renderer);
	SDL_Surface *bg = SDL_LoadBMP("images/bg2.bmp");
	SDL_Texture *bg_aleatoire = SDL_CreateTextureFromSurface(renderer, bg);

	SDL_Texture *btn_retour = IMG_LoadTexture(renderer, "images/retour.png");
	SDL_Rect btn_return;
	btn_return.x = 1250;
	btn_return.y = 790;
	SDL_Color rouge = {0, 0, 0, 0}, bleu = {255, 255, 255, 255};

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(font, "Picross Game", color);
	text2 = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect texterect;
	texterect.x = 430;
	texterect.y = 0;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(bg_aleatoire, NULL, NULL, &dst.w, &dst.h);

	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);
	SDL_QueryTexture(btn_retour, NULL, NULL, &btn_return.w, &btn_return.h);
	SDL_RenderCopy(renderer, bg_aleatoire, NULL, &dst);

	SDL_RenderCopy(renderer, text2, NULL, &texterect);
	SDL_RenderCopy(renderer, btn_retour, NULL, &btn_return);
	SDL_RenderPresent(renderer);

	// generate_random_num();
	//  sleep(0.5);
	int occupation[nombre1][nombre2];
	int power[nombre1][nombre2];
	SDL_Rect rect[nombre1][nombre2];

	matrice(occupation, power, nombre1, nombre2); // Generation de la matrice avec les 1 et 0
	// sleep(0.5);
	indication(nombre1, nombre2, power, nombre1, nombre2); // Instrution pour le cln et lgn
	construire_tab(nombre1, nombre2, rect);				   // Construction du plateau de jeux
	// sleep(0.5);
	affichage_num(); // Affichage des des instructions de la grille
	// sleep(0.5);
	click(occupation, power, rect);
}

// Verification des collones pour le mode eiffel
void verification_cln_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau)
{
	int total_power = 0;
	int count = 0;
	int i, y = 0;
	int total_power2 = 0;
	int total_occup = 0;
	SDL_Surface *text;
	SDL_Texture *texture2;
	SDL_Rect texterect;

	for (i = 0; i < nombre1; i++)
	{
		for (int j = 0; j < nombre1; j++)
		{
			if (power[i][j] == 1)
			{
				total_power2++;
			}
			if (occupation[i][j] == 1 && power[i][j] == 1)
			{
				total_occup++;
			}
		}
	}
	if (total_power2 == total_occup)
	{
		printf("OK");
		TTF_Init();
		TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
		if (!font)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
		}
		SDL_Color color = {0, 255, 0, 255};
		text = TTF_RenderText_Blended(font, "Bravo !", color);
		texture2 = SDL_CreateTextureFromSurface(renderer, text);
		SDL_Rect texterect;
		texterect.x = 580;
		texterect.y = 890;
		SDL_FreeSurface(text);
		TTF_CloseFont(font);

		TTF_Quit();
		SDL_SetRenderTarget(renderer, NULL);

		// SDL_RenderClear(renderer);

		SDL_QueryTexture(texture2, NULL, NULL, &texterect.w, &texterect.h);

		SDL_RenderCopy(renderer, texture2, NULL, &texterect);

		SDL_RenderPresent(renderer);
		sleep(4);
		SDL_DestroyTexture(texture2);
		SDL_DestroyRenderer(renderer);
		menu();
	}
	while (y < nombre1)
	{
		total_power = 0;
		count = 0;
		for (i = 0; i < nombre1; i++)
		{
			total_power += power[i][y];
		}

		for (int i = 0; i < nombre1; i++)
		{
			if ((power[i][y] == 1) && (occupation[i][y] == 1))
			{
				count++;
			}
			if ((power[i][y] == 0) && (occupation[i][y] == 1))
			{
				count--;
			}
		}

		if (count == total_power)
		{
			// printf("\ncln %d : Ok\n", y);
			change_color_true_cln_eiffel(nombre1, nombre2, occupation, rect, gameplateau, power, y);
		}
		if (count != total_power)
		{
			change_color_false_cln_eiffel(nombre1, nombre2, occupation, rect, gameplateau, y);
		}

		y++;
	}
}

// Changement de couleur si ligne ok pour mode eiffel
void change_color_true_lgn_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int ligne)
{

	for (int i = 0; i < nombre1; i++)
	{
		if (power[ligne][i] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[i][ligne]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Changement de couleur si colonne non ok
void change_color_false_cln_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int cln)
{
	for (int i = 0; i < nombre1; i++)
	{
		if (occupation[i][cln] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[cln][i]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Verification ligne mode eiffel
void verification_lgn_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau)
{
	int total_power = 0;
	int count = 0;
	int i, y = 0;
	while (y < nombre1)
	{
		total_power = 0;
		count = 0;
		for (i = 0; i < nombre1; i++)
		{
			total_power += power[y][i];
		}

		for (int i = 0; i < nombre1; i++)
		{
			if ((power[y][i] == 1) && (occupation[y][i] == 1))
			{
				count++;
			}
			if ((power[y][i] == 0) && (occupation[y][i] == 1))
			{
				count--;
			}
		}

		if (count == total_power)
		{
			// printf("\nLgn %d : Ok\n", y);
			change_color_true_lgn_eiffel(nombre1, nombre2, occupation, rect, gameplateau, power, y);
		}
		if (count != total_power)
		{
			// change_color_false_lgn(nombre1, nombre2, occupation, rect, gameplateau, y, power);
		}

		y++;
	}
}

// Constrution plateau mode eiffel
void construire_tab_eiffel(int nombre1, int nombre2, SDL_Rect rect[nombre1][nombre2])
{
	int display_plateau1 = (nombre1 * 35) + 150;
	int display_plateau2 = (nombre2 * 35) + 150;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, display_plateau1, display_plateau2);
	if (NULL == texture)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 225, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// SDL_Rect rect[nombre1][nombre2];

	int largeur = nombre1;
	int longueur = nombre2;

	for (int i = 0; i < nombre1; i++)
	{
		for (int j = 0; j < nombre2; j++)
		{

			rect[i][j].x = 150 + i * 35;
			rect[i][j].y = 150 + j * 35;
			rect[i][j].w = 25;
			rect[i][j].h = 25;

			SDL_RenderFillRect(renderer, &rect[i][j]);
		}
	}

	SDL_SetRenderTarget(renderer, NULL);
}

// Changement de couleur si collone ok mode eiffel
void change_color_true_cln_eiffel(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int cln)
{

	for (int i = 0; i < nombre1; i++)
	{
		if (power[i][cln] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[cln][i]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Mode eiffel
void tour_eiffel()
{
	SDL_Rect dst = {0, 0, 0, 0};
	SDL_Surface *text = NULL;
	SDL_Texture *text2 = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y = 0;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// SDL_RenderClear(renderer);
	SDL_Surface *bg = SDL_LoadBMP("images/bg2.bmp");
	SDL_Texture *bg_aleatoire = SDL_CreateTextureFromSurface(renderer, bg);

	SDL_Texture *btn_retour = IMG_LoadTexture(renderer, "images/retour.png");
	SDL_Rect btn_return;
	btn_return.x = 1250;
	btn_return.y = 790;
	SDL_Color rouge = {0, 0, 0, 0}, bleu = {255, 255, 255, 255};

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(font, "Picross Game", color);
	text2 = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect texterect;
	texterect.x = 430;
	texterect.y = 0;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(bg_aleatoire, NULL, NULL, &dst.w, &dst.h);

	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);
	SDL_QueryTexture(btn_retour, NULL, NULL, &btn_return.w, &btn_return.h);
	SDL_RenderCopy(renderer, bg_aleatoire, NULL, &dst);

	SDL_RenderCopy(renderer, text2, NULL, &texterect);
	SDL_RenderCopy(renderer, btn_retour, NULL, &btn_return);
	SDL_RenderPresent(renderer);

	nombre1 = 21;
	nombre2 = 21;
	int occupation[nombre1][nombre2];

	SDL_Rect rect[nombre2][nombre1];
	int tabeiffel[nombre1][nombre2];

	matrice_eiffel(occupation, tabeiffel, nombre1, nombre2); // Generation de la matrice avec les 1 et 0
	eiffel(tabeiffel, nombre1, nombre2);

	indication(nombre1, nombre2, tabeiffel, nombre1, nombre2); // Instrution pour le cln et lgn
	construire_tab_eiffel(nombre1, nombre2, rect);			   // Construction du plateau de jeux
	affichage_num_eiffel();									   // Affichage des des instructions de la grille
	click_eiffel(occupation, tabeiffel, rect);
}

// Chargement fichier mode smile
void smile(int tabsmile[nombre1][nombre2], int nombre1, int nombre2)
{

	FILE *fichier = NULL;
	int i = 0;
	int j = 0;
	fichier = fopen("Draw/smile.txt", "r");

	for (i = 0; i < nombre1; i++)
	{
		for (j = 0; j < nombre2; j++)
		{
			tabsmile[i][j] = 0;
			fscanf(fichier, "%d", &tabsmile[i][j]);
		}
	}

	fclose(fichier);

}

// Changement couleur si colonne non ok mode smile
void change_color_false_cln_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int cln)
{
	for (int i = 0; i < nombre1; i++)
	{
		if (occupation[i][cln] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[cln][i]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Changement de couleur si colonne ok mode smile
void change_color_true_cln_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int cln)
{

	for (int i = 0; i < nombre1; i++)
	{
		if (power[i][cln] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[cln][i]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Changement de couleur si ligne ok mode smile
void change_color_true_lgn_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau, int power[nombre1][nombre1], int ligne)
{

	for (int i = 0; i < nombre1; i++)
	{
		if (power[ligne][i] == 1)
		{
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect[i][ligne]);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	// SDL_RenderPresent(renderer);
}

// Verification ligne mode smile
void verification_lgn_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau)
{
	int total_power = 0;
	int count = 0;
	int i, y = 0;
	while (y < nombre1)
	{
		total_power = 0;
		count = 0;
		for (i = 0; i < nombre1; i++)
		{
			total_power += power[y][i];
		}

		for (int i = 0; i < nombre1; i++)
		{
			if ((power[y][i] == 1) && (occupation[y][i] == 1))
			{
				count++;
			}
			if ((power[y][i] == 0) && (occupation[y][i] == 1))
			{
				count--;
			}
		}

		if (count == total_power)
		{
			// printf("\nLgn %d : Ok\n", y);
			change_color_true_lgn_smile(nombre1, nombre2, occupation, rect, gameplateau, power, y);
		}
		if (count != total_power)
		{
			// change_color_false_lgn(nombre1, nombre2, occupation, rect, gameplateau, y, power);
		}

		y++;
	}
}

// Vérification colonne mode smile
void verification_cln_smile(int nombre1, int nombre2, int occupation[nombre1][nombre2], int power[nombre1][nombre1], SDL_Rect rect[nombre1][nombre2], SDL_Rect gameplateau)
{
	int total_power = 0;
	int count = 0;
	int i, y = 0;
	int total_power2 = 0;
	int total_occup = 0;
	SDL_Surface *text;
	SDL_Texture *texture2;
	SDL_Rect texterect;

	for (i = 0; i < nombre1; i++)
	{
		for (int j = 0; j < nombre1; j++)
		{
			if (power[i][j] == 1)
			{
				total_power2++;
			}
			if (occupation[i][j] == 1 && power[i][j] == 1)
			{
				total_occup++;
			}
		}
	}
	if (total_power2 == total_occup)
	{
		printf("OK");
		TTF_Init();
		TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
		if (!font)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
		}
		SDL_Color color = {0, 255, 0, 255};
		text = TTF_RenderText_Blended(font, "Bravo !", color);
		texture2 = SDL_CreateTextureFromSurface(renderer, text);
		SDL_Rect texterect;
		texterect.x = 580;
		texterect.y = 900;
		SDL_FreeSurface(text);
		TTF_CloseFont(font);

		TTF_Quit();
		SDL_SetRenderTarget(renderer, NULL);

		// SDL_RenderClear(renderer);

		SDL_QueryTexture(texture2, NULL, NULL, &texterect.w, &texterect.h);

		SDL_RenderCopy(renderer, texture2, NULL, &texterect);

		SDL_RenderPresent(renderer);
		sleep(4);
		SDL_DestroyTexture(texture2);
		SDL_DestroyRenderer(renderer);
		menu();
	}
	while (y < nombre1)
	{
		total_power = 0;
		count = 0;
		for (i = 0; i < nombre1; i++)
		{
			total_power += power[i][y];
		}

		for (int i = 0; i < nombre1; i++)
		{
			if ((power[i][y] == 1) && (occupation[i][y] == 1))
			{
				count++;
			}
			if ((power[i][y] == 0) && (occupation[i][y] == 1))
			{
				count--;
			}
		}

		if (count == total_power)
		{
			// printf("\ncln %d : Ok\n", y);
			change_color_true_cln_smile(nombre1, nombre2, occupation, rect, gameplateau, power, y);
		}
		if (count != total_power)
		{
			change_color_false_cln_smile(nombre1, nombre2, occupation, rect, gameplateau, y);
		}

		y++;
	}
}

// Calcule coordonnée mode smile
void affichage_num_smile()
{
	for (int i = 0; i < 5000; i++)
	{

		sprintf(tmp, "%d", tab[i]);

		if (strcmp(tmp, "99") == 0)
		{
			i++;
			m = m + 35;
			a = 120;
			// printf("\n");
		}
		sprintf(tmp, "%d", tab[i]);

		if (strcmp(tmp, "0") != 0)
		{
			// printf("%s ", tmp);
			numero_smile(tmp, a);
			a = a - 35;
		}
	}
	// printf("=================================================================\n");
	m = 115;
	a = 155;
	for (int i = 0; i < 5000; i++)
	{
		sprintf(tmp, "%d", tab2[i]);

		if (strcmp(tmp, "99") == 0)
		{
			i++;
			a = a + 35;
			m = 115;
			// printf("\n");
		}
		sprintf(tmp, "%d", tab2[i]);

		if (strcmp(tmp, "0") != 0)
		{
			// printf("%s ", tmp);
			numero_smile(tmp, m);
			m = m - 35;
		}
	}
}

// Affichage numero mode smile
void numero_smile(const char *tmp, int b)
{
	// SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, texture);
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/Minecrafter.Alt.ttf", 25);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {31, 116, 176, 0.9};

	text = TTF_RenderText_Blended(font, tmp, color);
	text2 = SDL_CreateTextureFromSurface(renderer, text);

	SDL_Rect texterect;
	texterect.x = a;
	texterect.y = m;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);
	SDL_RenderCopy(renderer, text2, NULL, &texterect);
	// SDL_RenderPresent(renderer);

	SDL_SetRenderTarget(renderer, NULL);
}

// Gestion des cliks mode smile
void click_smile(int occupation[nombre1][nombre2], int power[nombre1][nombre2], SDL_Rect rect[nombre1][nombre2])
{
	int display_plateau1 = (nombre1 * 35) + 220;
	int display_plateau2 = (nombre2 * 35) + 130;
	SDL_Rect gameplateau;
	gameplateau.x = (1500 / 2 - display_plateau1 / 2);
	gameplateau.y = (1000 / 2 - display_plateau2 / 2);

	SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
	SDL_RenderCopy(renderer, texture, NULL, &gameplateau);
	SDL_RenderPresent(renderer);
	while (!quit)
	{

		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}

		Uint32 boutons;

		SDL_PumpEvents();

		boutons = SDL_GetMouseState(&x, &y);

		x = (x - (gameplateau.x + 150)) / 35;
		y = (y - (gameplateau.y + 150)) / 35;

		// printf(" DEHORS : %d et %d\n", x, y);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:

			// printf("\nDEDEANS : %d et %d\n", x, y);
			if ((x >= 24 && x <= 28) && (y >= 18 && y <= 20))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyRenderer(renderer);
				image();
			}

			if (x < nombre1 && y < nombre2 && x >= 0 && y >= 0)
			{
				Mix_PlayChannel(1, clickmouse, 0);
				if (occupation[y][x] != 1)
				{
					SDL_SetRenderTarget(renderer, texture);
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect[x][y]);
					occupation[y][x] = 1;
				}
				else
				{

					SDL_SetRenderTarget(renderer, texture);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &rect[x][y]);
					occupation[y][x] = 0;
				}

				verification_cln_smile(nombre1, nombre2, occupation, power, rect, gameplateau);
				verification_lgn_smile(nombre1, nombre2, occupation, power, rect, gameplateau);
			}

			SDL_SetRenderTarget(renderer, NULL);

			SDL_QueryTexture(texture, NULL, NULL, &gameplateau.w, &gameplateau.h);
			SDL_RenderCopy(renderer, texture, NULL, &gameplateau);

			SDL_RenderPresent(renderer);
			sleep(0.2);
			break;

		case SDL_QUIT:
			quit = SDL_TRUE;
			break;
		}
	}
	SDL_Delay(3000);
}

// Constrution du plateau mode smile
void construire_tab_smile(int nombre1, int nombre2, SDL_Rect rect[nombre1][nombre2])
{
	int display_plateau1 = (nombre1 * 35) + 150;
	int display_plateau2 = (nombre2 * 35) + 150;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, display_plateau1, display_plateau2);
	if (NULL == texture)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 225, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// SDL_RenderPresent(renderer);
	//  SDL_Rect rect[nombre1][nombre2];

	int largeur = nombre1;
	int longueur = nombre2;

	for (int i = 0; i < nombre1; i++)
	{
		for (int j = 0; j < nombre2; j++)
		{

			rect[i][j].x = 150 + i * 35;
			rect[i][j].y = 150 + j * 35;
			rect[i][j].w = 25;
			rect[i][j].h = 25;

			SDL_RenderFillRect(renderer, &rect[i][j]);
		}
	}

	SDL_SetRenderTarget(renderer, NULL);
}

// Mode smile
void mode_smile()
{
	SDL_Rect dst = {0, 0, 0, 0};
	SDL_Surface *text = NULL;
	SDL_Texture *text2 = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y = 0;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// SDL_RenderClear(renderer);
	SDL_Surface *bg = SDL_LoadBMP("images/bg2.bmp");
	SDL_Texture *bg_aleatoire = SDL_CreateTextureFromSurface(renderer, bg);

	SDL_Texture *btn_retour = IMG_LoadTexture(renderer, "images/retour.png");
	SDL_Rect btn_return;
	btn_return.x = 1250;
	btn_return.y = 790;
	SDL_Color rouge = {0, 0, 0, 0}, bleu = {255, 255, 255, 255};

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderClear(renderer);

	// SDL_RenderPresent(renderer);

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(font, "Picross Game", color);
	text2 = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect texterect;
	texterect.x = 430;
	texterect.y = 0;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_SetRenderTarget(renderer, NULL);
	SDL_QueryTexture(bg_aleatoire, NULL, NULL, &dst.w, &dst.h);

	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);
	SDL_QueryTexture(btn_retour, NULL, NULL, &btn_return.w, &btn_return.h);
	SDL_RenderCopy(renderer, bg_aleatoire, NULL, &dst);

	SDL_RenderCopy(renderer, text2, NULL, &texterect);
	SDL_RenderCopy(renderer, btn_retour, NULL, &btn_return);
	// SDL_RenderPresent(renderer);

	nombre1 = 19;
	nombre2 = 19;
	int occupation[nombre1][nombre2];

	SDL_Rect rect[nombre2][nombre1];
	int tabsmile[nombre1][nombre2];

	matrice_smile(occupation, tabsmile, nombre1, nombre2); // Generation de la matrice avec les 1 et 0
	smile(tabsmile, nombre1, nombre2);

	indication(nombre1, nombre2, tabsmile, nombre1, nombre2); // Instrution pour le cln et lgn
	construire_tab_smile(nombre1, nombre2, rect);			  // Construction du plateau de jeux
	affichage_num_smile();									  // Affichage des des instructions de la grille
	click_smile(occupation, tabsmile, rect);
}

// Mode image
void image()
{
	system("clear");
	a = 130;
	m = 150;
	for (int i = 0; i < 5000; i++)
	{
		tab[i] = 0;
		tab2[i] = 0;
		tmp[i] = 0;
	}

	SDL_Rect dst = {0, 0, 0, 0};
	SDL_Renderer *renderer2 = NULL;
	SDL_Surface *text = NULL;
	SDL_Texture *text2 = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y = 0;

	renderer2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer2);
	SDL_Surface *bg = SDL_LoadBMP("images/bg.bmp");
	SDL_Texture *bg_image = SDL_CreateTextureFromSurface(renderer2, bg);

	SDL_Texture *btn_retour = IMG_LoadTexture(renderer2, "images/retour.png");
	SDL_Rect btn_return;
	btn_return.x = 1250;
	btn_return.y = 790;

	SDL_Texture *btn_eiffel = IMG_LoadTexture(renderer2, "images/eiffeil_btn.png");
	SDL_Rect btn_eiffelc;
	btn_eiffelc.x = 500;
	btn_eiffelc.y = 130;

	SDL_Texture *btn_apple = IMG_LoadTexture(renderer2, "images/btn_apple.png");
	SDL_Rect btn_applec;
	btn_applec.x = 500;
	btn_applec.y = 340;

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(font, "Picross Game", color);
	text2 = SDL_CreateTextureFromSurface(renderer2, text);
	SDL_Rect texterect;
	texterect.x = 430;
	texterect.y = 0;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_SetRenderTarget(renderer2, NULL);
	SDL_QueryTexture(bg_image, NULL, NULL, &dst.w, &dst.h);
	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);

	SDL_QueryTexture(btn_retour, NULL, NULL, &btn_return.w, &btn_return.h);
	SDL_QueryTexture(btn_eiffel, NULL, NULL, &btn_eiffelc.w, &btn_eiffelc.h);
	SDL_QueryTexture(btn_apple, NULL, NULL, &btn_applec.w, &btn_applec.h);

	SDL_RenderCopy(renderer2, bg_image, NULL, &dst);
	SDL_RenderCopy(renderer2, text2, NULL, &texterect);
	SDL_RenderCopy(renderer2, btn_retour, NULL, &btn_return);
	SDL_RenderCopy(renderer2, btn_eiffel, NULL, &btn_eiffelc);
	SDL_RenderCopy(renderer2, btn_apple, NULL, &btn_applec);

	SDL_RenderPresent(renderer2);

	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}

		Uint32 boutons;
		// SDL_Delay(200);
		SDL_PumpEvents();
		boutons = SDL_GetMouseState(&x, &y);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN: // printf("Clic droit à la positions %d - %d\n", x, y);
			if ((x >= 605 && x <= 868) && (y >= 294 && y <= 401))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(text2);
				text2 = NULL;
				SDL_DestroyRenderer(renderer2);
				SDL_DestroyTexture(bg_image);
				SDL_DestroyTexture(btn_retour);
				SDL_DestroyTexture(btn_eiffel);
				SDL_DestroyTexture(btn_apple);
				SDL_DestroyTexture(text2);
				renderer2 = NULL;
				tour_eiffel();
			}

			if ((x >= 606 && x <= 869) && (y >= 505 && y <= 614))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(text2);
				text2 = NULL;
				SDL_DestroyTexture(bg_image);
				SDL_DestroyTexture(btn_retour);
				SDL_DestroyTexture(btn_eiffel);
				SDL_DestroyTexture(btn_apple);
				SDL_DestroyTexture(text2);
				SDL_DestroyRenderer(renderer2);
				renderer2 = NULL;
				mode_smile();
			}
			if ((x >= 1332 && x <= 1456) && (y >= 896 && y <= 949))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(text2);
				text2 = NULL;
				SDL_DestroyTexture(bg_image);
				SDL_DestroyTexture(btn_retour);
				SDL_DestroyTexture(btn_eiffel);
				SDL_DestroyTexture(btn_apple);
				SDL_DestroyTexture(text2);
				SDL_DestroyRenderer(renderer2);
				renderer2 = NULL;
				menu();
			}

			break;

		case SDL_QUIT:
			quit = SDL_TRUE;
			break;
		}
	}
}

// Menu pricipal
void menu()
{
	system("clear");
	for (int i = 0; i < 5000; i++)
	{
		tab[i] = 0;
		tab2[i] = 0;
		tmp[i] = 0;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	a = 130;
	m = 150;
	// printf("Menu\n");
	SDL_Texture *texture = NULL;
	SDL_Texture *texture2 = NULL;

	SDL_Surface *tmp = NULL;
	SDL_Surface *text = NULL;

	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y = 0;

	tmp = SDL_LoadBMP("images/bg.bmp");
	SDL_Rect dst = {0, 0, 0, 0};

	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	SDL_Texture *btn1 = IMG_LoadTexture(renderer, "images/btn1.png");

	SDL_Rect btn_one;
	btn_one.x = 500;
	btn_one.y = 130;

	SDL_Texture *btn2 = IMG_LoadTexture(renderer, "images/btn2.png");
	SDL_Rect btn_two;
	btn_two.x = 500;
	btn_two.y = 340;

	SDL_Texture *btn3 = IMG_LoadTexture(renderer, "images/exit.png");
	SDL_Rect btn_exit;
	btn_exit.x = 1250;
	btn_exit.y = 790;

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(font, "Picross Game", color);
	texture2 = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect texterect;
	texterect.x = 430;
	texterect.y = 0;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_SetRenderTarget(renderer, texture);

	SDL_RenderClear(renderer);

	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_QueryTexture(texture2, NULL, NULL, &texterect.w, &texterect.h);

	SDL_QueryTexture(btn1, NULL, NULL, &btn_one.w, &btn_one.h);
	SDL_QueryTexture(btn2, NULL, NULL, &btn_two.w, &btn_two.h);
	SDL_QueryTexture(btn3, NULL, NULL, &btn_exit.w, &btn_exit.h);

	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_RenderCopy(renderer, texture2, NULL, &texterect);
	SDL_RenderCopy(renderer, btn1, NULL, &btn_one);
	SDL_RenderCopy(renderer, btn2, NULL, &btn_two);
	SDL_RenderCopy(renderer, btn3, NULL, &btn_exit);

	SDL_RenderPresent(renderer);

	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}

		Uint32 boutons;
		// SDL_Delay(100);

		SDL_PumpEvents();
		boutons = SDL_GetMouseState(&x, &y);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if ((x >= 605 && x <= 868) && (y >= 294 && y <= 401))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(texture2);
				texture2 = NULL;
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				SDL_DestroyTexture(texture);
				texture = NULL;
				SDL_DestroyTexture(btn1);
				btn1 = NULL;
				SDL_DestroyTexture(btn2);
				btn2 = NULL;
				SDL_DestroyTexture(btn3);
				btn3 = NULL;

				image();
			}

			if ((x >= 606 && x <= 869) && (y >= 505 && y <= 614))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(texture2);
				texture2 = NULL;
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				SDL_DestroyTexture(texture);
				texture = NULL;
				SDL_DestroyTexture(btn1);
				btn1 = NULL;
				SDL_DestroyTexture(btn2);
				btn2 = NULL;
				SDL_DestroyTexture(btn3);
				btn3 = NULL;

				//aleatoire();
				choix_niveau();
			}

			if ((x >= 1332 && x <= 1456) && (y >= 896 && y <= 949))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(texture);
				texture = NULL;
				SDL_DestroyTexture(texture2);
				texture2 = NULL;
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				SDL_DestroyWindow(window);
				window = NULL;
				exit(0);
			}
			break;

		case SDL_QUIT:
			quit = SDL_TRUE;
			break;

		default:
			break;
		}
	}
}

void choix_niveau()
{
	system("clear");
	a = 130;
	m = 150;
	for (int i = 0; i < 5000; i++)
	{
		tab[i] = 0;
		tab2[i] = 0;
		tmp[i] = 0;
	}

	SDL_Rect dst = {0, 0, 0, 0};
	SDL_Renderer *renderer2 = NULL;
	SDL_Surface *text = NULL;
	SDL_Texture *text2 = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y = 0;

	renderer2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer2);
	SDL_Surface *bg = SDL_LoadBMP("images/bg.bmp");
	SDL_Texture *bg_image = SDL_CreateTextureFromSurface(renderer2, bg);

	SDL_Texture *btn_retour = IMG_LoadTexture(renderer2, "images/retour.png");
	SDL_Rect btn_return;
	btn_return.x = 1250;
	btn_return.y = 790;

	SDL_Texture *btn_eiffel = IMG_LoadTexture(renderer2, "images/btnfacile.png");
	SDL_Rect btn_eiffelc;
	btn_eiffelc.x = 500;
	btn_eiffelc.y = 130;

	SDL_Texture *btn_apple = IMG_LoadTexture(renderer2, "images/btndificille.png");
	SDL_Rect btn_applec;
	btn_applec.x = 500;
	btn_applec.y = 340;

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/hammerscoutexpand.ttf", 80);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[!] Unable to open font: %s\n", TTF_GetError());
	}
	SDL_Color color = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(font, "Picross Game", color);
	text2 = SDL_CreateTextureFromSurface(renderer2, text);
	SDL_Rect texterect;
	texterect.x = 430;
	texterect.y = 0;
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_SetRenderTarget(renderer2, NULL);
	SDL_QueryTexture(bg_image, NULL, NULL, &dst.w, &dst.h);
	SDL_QueryTexture(text2, NULL, NULL, &texterect.w, &texterect.h);

	SDL_QueryTexture(btn_retour, NULL, NULL, &btn_return.w, &btn_return.h);
	SDL_QueryTexture(btn_eiffel, NULL, NULL, &btn_eiffelc.w, &btn_eiffelc.h);
	SDL_QueryTexture(btn_apple, NULL, NULL, &btn_applec.w, &btn_applec.h);

	SDL_RenderCopy(renderer2, bg_image, NULL, &dst);
	SDL_RenderCopy(renderer2, text2, NULL, &texterect);
	SDL_RenderCopy(renderer2, btn_retour, NULL, &btn_return);
	SDL_RenderCopy(renderer2, btn_eiffel, NULL, &btn_eiffelc);
	SDL_RenderCopy(renderer2, btn_apple, NULL, &btn_applec);

	SDL_RenderPresent(renderer2);

	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}

		Uint32 boutons;
		// SDL_Delay(200);
		SDL_PumpEvents();
		boutons = SDL_GetMouseState(&x, &y);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN: // printf("Clic droit à la positions %d - %d\n", x, y);
			if ((x >= 605 && x <= 868) && (y >= 294 && y <= 401))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(text2);
				text2 = NULL;
				SDL_DestroyRenderer(renderer2);
				SDL_DestroyTexture(bg_image);
				SDL_DestroyTexture(btn_retour);
				SDL_DestroyTexture(btn_eiffel);
				SDL_DestroyTexture(btn_apple);
				SDL_DestroyTexture(text2);
				renderer2 = NULL;
				generate_random_num();

				aleatoire();
			}

			if ((x >= 606 && x <= 869) && (y >= 505 && y <= 614))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(text2);
				text2 = NULL;
				SDL_DestroyTexture(bg_image);
				SDL_DestroyTexture(btn_retour);
				SDL_DestroyTexture(btn_eiffel);
				SDL_DestroyTexture(btn_apple);
				SDL_DestroyTexture(text2);
				SDL_DestroyRenderer(renderer2);
				renderer2 = NULL;
				generate_random_num_dificile();

				aleatoire();
			}
			if ((x >= 1332 && x <= 1456) && (y >= 896 && y <= 949))
			{
				Mix_PlayChannel(1, clickmouse, 0);
				SDL_DestroyTexture(text2);
				text2 = NULL;
				SDL_DestroyTexture(bg_image);
				SDL_DestroyTexture(btn_retour);
				SDL_DestroyTexture(btn_eiffel);
				SDL_DestroyTexture(btn_apple);
				SDL_DestroyTexture(text2);
				SDL_DestroyRenderer(renderer2);
				renderer2 = NULL;
				menu();
			}

			break;

		case SDL_QUIT:
			quit = SDL_TRUE;
			break;
		}
	}
}
// Main
int main(int argc, char *argv[])
{
	SDL_init();
	menu();
}
