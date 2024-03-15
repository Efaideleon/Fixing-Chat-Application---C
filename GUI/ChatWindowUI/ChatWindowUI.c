#include "ChatWindowUI.h"

ChatWindowUI *create_chat_window_ui()
{
    return (ChatWindowUI*)malloc(sizeof(ChatWindowUI));
}

void destroy_chat_window_ui(ChatWindowUI *chat_window_ui)
{
    free(chat_window_ui);
}