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


/**
 * @brief Create a chat window ui object using malloc()
 * 
 * @return ChatWindowUI* 
 */
ChatWindowUI *create_chat_window_ui();

/**
 * @brief Destroys the ChatWindowUI->window by calling `gtk_widget_destroy()`
 * frees the memory allocated to chat_window_ui 
 * 
 * @param chat_window_ui 
 */
void destroy_chat_window_ui(ChatWindowUI *chat_window_ui);