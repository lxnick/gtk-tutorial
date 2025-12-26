#include <gtk/gtk.h>

static void on_ok_clicked(GtkButton *btn, gpointer user_data) {
	g_print("Button clicked\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *button;

	builder = gtk_builder_new_from_file("ui/main.ui");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));

	g_signal_connect(button,"clicked", G_CALLBACK(on_ok_clicked), NULL);

	gtk_window_set_application(GTK_WINDOW(window),app);
	gtk_widget_show_all(window);
}

int main(int argc, char** argv) {
	GtkApplication* app=gtk_application_new("org.example.builder", 0 );
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	
	return g_application_run(G_APPLICATION(app), argc, argv);
}



  	
