# Nom de l'exécutable
EXECUTABLE = HoeScape

# Liste des fichiers source
SOURCES = *.c

GNL_SOURCE = get_next_line/*.c

# Répertoire contenant les en-têtes
INCLUDE_DIR = Headers

# Flags de compilation
CFLAGS = -I$(INCLUDE_DIR) -lncurses -O2

# Commande de compilation
CC = gcc

# Génération des dépendances
DEPS = $(SOURCES:.c=.d)

# Règle pour construire l'exécutable
$(EXECUTABLE): $(SOURCES) $(GNL_SOURCE)
	$(CC) -o $@ $^ $(CFLAGS)

# Inclusion des fichiers de dépendances
-include $(DEPS)

# Nettoyage des fichiers générés
clean:
	rm -f $(EXECUTABLE) *.o *.d

# Règle pour démarrer le programme
run: clean $(EXECUTABLE)
	./$(EXECUTABLE)
