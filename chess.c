/* simple chess board drawing in gtk */

#include <gtk/gtk.h>

gboolean quit_app(GtkWidget *w, gpointer data) {
    gtk_main_quit();
    return 0;
}

gboolean draw(GtkWidget *w, cairo_t *cr, gpointer data) {
    GtkStyleContext *context;
    GdkRGBA color;
    guint width, height;

    width = gtk_widget_get_allocated_width(w);
    height = gtk_widget_get_allocated_height(w);

    context = gtk_widget_get_style_context(w);
    gtk_render_background(context, cr, 0, 0, width, height);
    gtk_style_context_get_color(context, gtk_style_context_get_state(context), &color);
    gdk_cairo_set_source_rgba(cr, &color);
    
    for(int x = 0; x < 8; ++x) {
        for(int y = x % 2; y < 8; y += 2) {
            cairo_move_to(cr, x * width / 8, y * height / 8);
            cairo_line_to(cr, (x + 1) * width / 8, y * height / 8);
            cairo_line_to(cr, (x + 1) * width / 8, (y + 1) * height / 8);
            cairo_line_to(cr, x * width / 8, (y + 1) * height / 8);
            cairo_line_to(cr, x * width / 8, y * height / 8);
            cairo_fill(cr);
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    GtkWidget *window, *canvas;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    canvas = gtk_drawing_area_new();

    g_signal_connect(window, "delete-event", G_CALLBACK(quit_app), NULL);
    g_signal_connect(canvas, "draw", G_CALLBACK(draw), NULL);

    gtk_container_add(GTK_CONTAINER(window), canvas);

    gtk_widget_show(window);
    gtk_widget_show(canvas);

    gtk_main();

    return 0;
}
