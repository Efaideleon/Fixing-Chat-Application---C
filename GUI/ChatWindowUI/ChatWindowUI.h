#include <stdlib.h>
#include "gtk/gtk.h"

typedef struct
{
    GtkWidget *window;
    GtkWidget *scrolled_window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *label;
    GtkWidget *text_area;
    GtkEntryBuffer *buffer;
    GtkWidget *message_label;
} ChatWindowUI;