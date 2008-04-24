// UI_BDK_v1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//



#include "UI_BDK_v1.h"

static BDK_window bdk_window;

/* Our menu, an array of GtkItemFactoryEntry structures that defines each menu item */
static GtkItemFactoryEntry menu_items[] = {
  { "/_File",         NULL,         NULL,							0, "<Branch>" },
  //{ "/File/_New",     "<control>N", NULL,							0, "<StockItem>", GTK_STOCK_NEW },
  { "/File/_Open",    "<control>O", GTK_SIGNAL_FUNC(open_event),	0, "<StockItem>", GTK_STOCK_OPEN },
  //{ "/File/_Save",    "<control>S", NULL,							0, "<StockItem>", GTK_STOCK_SAVE },
  //{ "/File/Save _As", NULL,         NULL,							0, "<Item>" },
  { "/File/sep1",     NULL,         NULL,							0, "<Separator>" },
  { "/File/_Quit",    "<CTRL>Q",	gtk_main_quit,					0, "<StockItem>", GTK_STOCK_QUIT },
  { "/_Help",         NULL,         NULL,							0, "<LastBranch>" },
  { "/_Help/About",   NULL,         NULL,							0, "<Item>" },
};

static gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

enum
{
  COL_VARIABLE = 0,
  COL_VALUE,
  NUM_COLS
} ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{

	bdk_window.image		= NULL;
	bdk_window.decoder		= NULL;
	bdk_window.error_path	= "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Eigene Bilder\\error.txt";

	g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING,
					(GLogFunc) gtk_false, NULL);
	gtk_init (NULL, NULL);
	g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING,
	g_log_default_handler, NULL);

	create_Window();

	gtk_widget_show_all (bdk_window.fenster);

	gtk_main();
	return 0;
/*
	void* decoder;
	char* image_path	= "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Eigene Bilder\\image.jpc";
	char* error_path	= "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Eigene Bilder\\error.txt";
	decoder = create_Decoder_c(image_path, error_path);
	delete_Decoder(decoder);

	return 0;
*/
}

void create_Window()
{
	
	bdk_window.fenster = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect(GTK_OBJECT(bdk_window.fenster), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
	//g_signal_connect (G_OBJECT (fenster), "delete_event", G_CALLBACK (delete_event), NULL);
	gtk_window_set_title (GTK_WINDOW(bdk_window.fenster), "Bilddatenkompression(BDK) Tool");
	gtk_widget_set_size_request (GTK_WIDGET(bdk_window.fenster), 600, 600);

	/* Make a vbox to put the three menus in */
	bdk_window.main_vbox = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (bdk_window.main_vbox), 1);
	gtk_container_add (GTK_CONTAINER (bdk_window.fenster), bdk_window.main_vbox);

	create_menubar_menu();
	create_toolbar_menu();

	bdk_window.image			= gtk_image_new_from_file("C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Eigene Bilder\\Battlestar\\battlestargalpic_01.jpg");
	bdk_window.scrolled_window	= gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (bdk_window.scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bdk_window.scrolled_window), bdk_window.image);

	bdk_window.hpaned = gtk_hpaned_new();
	create_view_and_model();
	gtk_paned_add1(GTK_PANED(bdk_window.hpaned), bdk_window.view);
	gtk_paned_add2(GTK_PANED(bdk_window.hpaned), bdk_window.scrolled_window);
	gtk_box_pack_start (GTK_BOX (bdk_window.main_vbox), bdk_window.hpaned, TRUE, TRUE, 0);
}

/* Returns a menubar widget made from the above menu */
static void create_menubar_menu()
{
	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;

	/* Make an accelerator group (shortcut keys) */
	accel_group = gtk_accel_group_new ();

	/* Make an ItemFactory (that makes a menubar) */
	item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>",
									   accel_group);

	/* This function generates the menu items. Pass the item factory,
	 the number of items in the array, the array itself, and any
	 callback data for the the menu items. */
	gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);

	/* Attach the new accelerator group to the window. */
	gtk_window_add_accel_group (GTK_WINDOW (bdk_window.fenster), accel_group);

	/* Finally, return the actual menu bar created by the item factory. */
	bdk_window.menubar = gtk_item_factory_get_widget (item_factory, "<main>");

	gtk_box_pack_start (GTK_BOX (bdk_window.main_vbox), bdk_window.menubar, FALSE, TRUE, 0);
}

static void create_toolbar_menu()
{
	GtkWidget *iconw;
	GtkWidget *close_button;

	bdk_window.toolbar = gtk_toolbar_new ();
	gtk_toolbar_set_orientation (GTK_TOOLBAR (bdk_window.toolbar), GTK_ORIENTATION_HORIZONTAL);
	gtk_toolbar_set_style (GTK_TOOLBAR (bdk_window.toolbar), GTK_TOOLBAR_BOTH);

	/* our first item is <close> button */
	iconw = gtk_image_new_from_stock (GTK_STOCK_OPEN, GTK_ICON_SIZE_SMALL_TOOLBAR)  ; // ("gtk.xpm"); /* icon widget */
	close_button = 
	gtk_toolbar_append_item (GTK_TOOLBAR (bdk_window.toolbar), /* our toolbar */
							 "Open",               /* button label */
							 "Open a file",     /* this button's tooltip */
							 "Private",             /* tooltip private info */
							 iconw,                 /* icon widget */
							 GTK_SIGNAL_FUNC (open_event), /* a signal */
							 NULL);
	gtk_toolbar_append_space (GTK_TOOLBAR (bdk_window.toolbar)); /* space after item */
	/* our first item is <close> button */
	iconw = gtk_image_new_from_stock (GTK_STOCK_QUIT, GTK_ICON_SIZE_SMALL_TOOLBAR)  ; // ("gtk.xpm"); /* icon widget */
	close_button = 
	gtk_toolbar_append_item(	GTK_TOOLBAR (bdk_window.toolbar), /* our toolbar */
								 "Close",               /* button label */
								 "Closes this app",     /* this button's tooltip */
								 "Private",             /* tooltip private info */
								 iconw,                 /* icon widget */
								 GTK_SIGNAL_FUNC (gtk_main_quit), /* a signal */
								 NULL);
	gtk_box_pack_start (GTK_BOX (bdk_window.main_vbox), bdk_window.toolbar, FALSE, TRUE, 0);
}


static gboolean open_event( GtkWidget *widget,
                              gpointer   data )
{

	GtkWidget		*dialog;
	GtkFileFilter	*filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filter, "*.jpc");

	dialog = gtk_file_chooser_dialog_new ("Open File",
							GTK_WINDOW(bdk_window.fenster),
							GTK_FILE_CHOOSER_ACTION_OPEN,
							GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
							NULL);

	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		open_image(filename);
	}

	gtk_widget_destroy (dialog);
    return FALSE;
}

static void open_image(char* path)
{
	unsigned int width, height;
	if(bdk_window.decoder != NULL){
		bdk_window.decoder = delete_Decoder(bdk_window.decoder);
	}
	bdk_window.decoder = create_Decoder_c(path, bdk_window.error_path);

	width	= get_SIZ_Xsiz(bdk_window.decoder) - get_SIZ_XOsiz(bdk_window.decoder);
	height	= get_SIZ_Ysiz(bdk_window.decoder) - get_SIZ_YOsiz(bdk_window.decoder);
	
	bdk_window.buffer	= new unsigned char[width * height * 3];
	bdk_window.pixbuf	= gdk_pixbuf_new_from_data( bdk_window.buffer,
													GDK_COLORSPACE_RGB,
													FALSE,
													8,
													width,
													height,
													width * 3,
													NULL,
													NULL);

	fill_buffer( bdk_window.decoder, 0, 0, bdk_window.buffer, width, height);

	gtk_image_clear(GTK_IMAGE(bdk_window.image));
	gtk_image_set_from_pixbuf(GTK_IMAGE(bdk_window.image), bdk_window.pixbuf);
	//gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bdk_window.scrolled_window), bdk_window.image);

	create_and_fill_model();

	gtk_tree_view_set_model(GTK_TREE_VIEW(bdk_window.view), bdk_window.model);
	g_object_unref(bdk_window.model);
}


static void create_view_and_model()
{
	GtkTreeViewColumn	*col;
	GtkCellRenderer		*renderer;

	bdk_window.view = gtk_tree_view_new();
	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(bdk_window.view), TRUE);

	col = gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col, "Variable");

	gtk_tree_view_append_column(GTK_TREE_VIEW(bdk_window.view), col);
	
	renderer = gtk_cell_renderer_text_new();

	gtk_tree_view_column_pack_start(col, renderer, TRUE);

	gtk_tree_view_column_add_attribute(col, renderer, "text", COL_VARIABLE);

	/* Columm #2 */

	col = gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col, "Value");

	gtk_tree_view_append_column(GTK_TREE_VIEW(bdk_window.view), col);

	renderer = gtk_cell_renderer_text_new();

	gtk_tree_view_column_pack_start(col, renderer, TRUE);

	gtk_tree_view_column_add_attribute(col, renderer, "text", COL_VALUE);

	gtk_tree_view_column_set_cell_data_func(col, renderer, age_cell_data_func, NULL, NULL);

	create_and_fill_model();

	gtk_tree_view_set_model(GTK_TREE_VIEW(bdk_window.view), bdk_window.model);

	g_object_unref(bdk_window.model);

	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(bdk_window.view)), GTK_SELECTION_NONE);

	g_signal_connect(bdk_window.view, "row-activated", (GCallback) view_onRowActivated, NULL);

}

void age_cell_data_func(	GtkTreeViewColumn	*col,
							GtkCellRenderer		*renderer,
							GtkTreeModel		*model,
							GtkTreeIter			*iter,
							gpointer			user_data)
{
	guint value;
	gchar buf[64];
	
	gtk_tree_model_get(model, iter, COL_VALUE, &value, -1);

	if(value != 0xFFFFFFFF){
		g_snprintf(buf, sizeof(buf)," %u ", value);
		g_object_set(renderer,"foreground-set", FALSE, NULL);
	}else{
		g_snprintf(buf, sizeof(buf), "");
		//g_object_set(renderer, "foreground", "Red", "foreground-set", TRUE, NULL);
	}
	g_object_set(renderer, "text", buf, NULL);
}

static void create_and_fill_model()
{
	GtkTreeStore	*treestore;
	GtkTreeIter		toplevel, child, child1;
	unsigned int iHelp1, iHelp2;
	gchar buf[64];

	treestore = gtk_tree_store_new( NUM_COLS,
									G_TYPE_STRING,
									G_TYPE_UINT);

	if(bdk_window.decoder != NULL){
		gtk_tree_store_append(treestore, &toplevel, NULL);
		gtk_tree_store_set(	treestore, &toplevel,
							COL_VARIABLE, "SIZ",
							COL_VALUE, (guint) 0xFFFFFFFF,
							-1);


		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "Lsiz",
						COL_VALUE, (guint) get_SIZ_Lsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "Rsiz",
						COL_VALUE, (guint) get_SIZ_Rsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "Xsiz",
						COL_VALUE, (guint) get_SIZ_Xsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "Ysiz",
						COL_VALUE, (guint) get_SIZ_Ysiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "XOsiz",
						COL_VALUE, (guint) get_SIZ_XOsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "YOsiz",
						COL_VALUE, (guint) get_SIZ_YOsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "XTsiz",
						COL_VALUE, (guint) get_SIZ_XTsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "YTsiz",
						COL_VALUE, (guint) get_SIZ_YTsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "XTOsiz",
						COL_VALUE, (guint) get_SIZ_XTOsiz(bdk_window.decoder),
						 -1);

		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "YTOsiz",
						COL_VALUE, (guint) get_SIZ_YTOsiz(bdk_window.decoder),
						 -1);


		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,
						COL_VARIABLE, "Csiz",
						COL_VALUE, (guint) get_SIZ_Csiz(bdk_window.decoder),
						 -1);

		iHelp2 = get_SIZ_Csiz(bdk_window.decoder);
		for(iHelp1 = 0; iHelp1 < iHelp2; iHelp1++){

			g_snprintf(buf, sizeof(buf),"Componente %u ", iHelp1);
			gtk_tree_store_append(treestore, &child, &toplevel);
			gtk_tree_store_set(	treestore, &child,
								COL_VARIABLE, buf,
								COL_VALUE, (guint) 0xFFFFFFFF,
								-1);
			gtk_tree_store_append(treestore, &child1, &child);
			gtk_tree_store_set(	treestore, &child1,
								COL_VARIABLE, "Ssiz",
								COL_VALUE, (guint) (guint) get_SIZ_Ssiz(bdk_window.decoder, (int) iHelp1),
								-1);
			gtk_tree_store_append(treestore, &child1, &child);
			gtk_tree_store_set(	treestore, &child1,
								COL_VARIABLE, "XRsiz",
								COL_VALUE, (guint) (guint) get_SIZ_XRsiz(bdk_window.decoder, (int) iHelp1),
								-1);
			gtk_tree_store_append(treestore, &child1, &child);
			gtk_tree_store_set(	treestore, &child1,
								COL_VARIABLE, "YRsiz",
								COL_VALUE, (guint) (guint) get_SIZ_YRsiz(bdk_window.decoder, (int) iHelp1),
								-1);
		}

	}
	bdk_window.model = GTK_TREE_MODEL(treestore);
}

void
view_onRowActivated (	GtkTreeView        *treeview,
						GtkTreePath        *path,
						GtkTreeViewColumn  *col,
						gpointer            userdata)
{
/*
	GtkTreeModel *model;
	GtkTreeIter   iter;

	g_print ("A row has been double-clicked!\n");

	model = gtk_tree_view_get_model(treeview);

	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gchar *name;
		setImage();
		gtk_tree_model_get(model, &iter, COL_LAST_NAME, &name, -1);
		//name = gtk_tree_path_to_string(path);
		g_print ("Double-clicked row contains name %s\n", name);

		g_free(name);
	}
*/
}