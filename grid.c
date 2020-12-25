/* just a simple grid using gtk and cairo */

#include <stdio.h>

#include <gtk/gtk.h>
#include <cairo.h>

gpointer end_application() {
    gtk_main_quit();

    return NULL;
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    guint width, height;
    GtkStyleContext *context;
    GdkRGBA color;

    /* get dimensions */
    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    context = gtk_widget_get_style_context(widget);
    gtk_render_background (context, cr, 0, 0, width, height);

    gtk_style_context_get_color (context,
                               gtk_style_context_get_state (context),
                               &color);
    gdk_cairo_set_source_rgba (cr, &color);

    for(int i = 1; i < 11; ++i) {
        cairo_move_to(cr, i * width / 11, 0);
        cairo_line_to(cr, i * width / 11, height);
        cairo_stroke(cr);
    }
    for(int i = 1; i < 11; ++i) {
        cairo_move_to(cr, 0, i * height / 11);
        cairo_line_to(cr, width, i * height / 11);
        cairo_stroke(cr);
    }

    return 0;
}

int main(int argc, char **argv) {
    GtkWidget *window, *drawing_area;

    gtk_init(&argc, &argv);

    /* create window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow *) window, "Grid");
    g_signal_connect(window, "delete-event", G_CALLBACK(end_application), NULL);

    /* create drawing area */
    drawing_area = gtk_drawing_area_new();
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback), NULL);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    /* present everything */
    gtk_widget_show(window);
    gtk_widget_show(drawing_area);

    gtk_main();

    return 0;
}
