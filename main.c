#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // Assurez-vous que SDL_ttf est installé pour la gestion des polices
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("Menu Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        closeSDL();
        return 1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        closeSDL();
        return 1;
    }

    // Initialisation de SDL_ttf pour la gestion des polices
    if (TTF_Init() != 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        closeSDL();
        return 1;
    }
    // Chargement de la police
    font = TTF_OpenFont("C:/Users/diamx/OneDrive/Documents/GitHub/Jeu_de_plataforme_DM2/arial.ttf", 24); // Remplacez "arial.ttf" par le chemin de votre police
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        closeSDL();
        return 1;
    }

    // Couleur du texte
    SDL_Color textColor = {255, 255, 255}; // Blanc

    // Boucle principale du jeu
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Vérifier si le clic de souris est dans la zone du bouton
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 112 && mouseX <= 162 && mouseY >= 150 && mouseY <= 180) {
                    printf("Button clicked!\n");
                }
            }
        }

        // Effacer le rendu précédent
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur noire
        SDL_RenderClear(renderer);

        // Dessiner le bouton rectangulaire
        SDL_Rect buttonRect = {132, 150, 50, 30}; // Position et taille du bouton
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Couleur rouge
        SDL_RenderFillRect(renderer, &buttonRect);

        // Dessiner le texte "Start" au-dessus du bouton
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Start", textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {132, 150, 0, 0}; // Position du texte
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h); // Récupérer la taille du texte
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Libérer la surface et la texture du texte
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);
    }


    // Fermeture propre de SDL
    closeSDL();
    return 0;
}
