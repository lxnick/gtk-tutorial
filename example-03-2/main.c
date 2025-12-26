#include <gtk/gtk.h>

static void on_ok_clicked(GtkButton *btn, gpointer user_data) {
	g_print("Button clicked\n");
}

static void on_show_clicked(GtkButton* btn, gpointer entry_ptr){
	GtkEntry *entry = GTK_ENTRY(entry_ptr);
	const gchar* text = gtk_entry_get_text(entry);
	g_print("Type: %s\n", text);
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget * entry;
	GtkWidget * btn;

	builder = gtk_builder_new_from_file("ui/main.ui");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	entry = GTK_WIDGET(gtk_builder_get_object(builder,"txt_input"));
	btn = GTK_WIDGET(gtk_builder_get_object(builder, "btn_show"));
 
	g_signal_connect(btn, "clicked",G_CALLBACK(on_show_clicked), entry);

	gtk_window_set_application(GTK_WINDOW(window),app);
	gtk_widget_show_all(window);
}

int main(int argc, char** argv) {
	GtkApplication* app=gtk_application_new("org.example.builder", 0 );
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	
	return g_application_run(G_APPLICATION(app), argc, argv);
}



  	
