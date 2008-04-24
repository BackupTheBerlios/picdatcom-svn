
#include <windows.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <dll_decoder.h>

struct BDK_window{
	GtkWidget			*main_vbox;
	GtkWidget			*fenster;
	GtkWidget			*menubar;
	GtkWidget			*toolbar;
	GtkWidget			*hpaned;
	GtkWidget			*scrolled_window;
	GtkWidget			*image;
	GtkWidget			*fileopen;
	GdkPixbuf			*pixbuf;

	
	GtkWidget			*view;
	GtkTreeModel		*model;

	void				*decoder;
	char				*error_path;
	unsigned char		*buffer;
};

void create_Window();
static void create_menubar_menu();
static void create_toolbar_menu();
static void open_image(char* path);

static void create_view_and_model();
void age_cell_data_func(GtkTreeViewColumn *col,GtkCellRenderer *renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data);
void view_onRowActivated (GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata);
static void create_and_fill_model();

static gboolean open_event( GtkWidget *widget, gpointer data);