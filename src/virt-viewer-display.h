/*
 * Virt Viewer: A virtual machine console viewer
 *
 * Copyright (C) 2007-2009 Red Hat,
 * Copyright (C) 2009 Daniel P. Berrange
 * Copyright (C) 2010 Marc-André Lureau
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Daniel P. Berrange <berrange@redhat.com>
 */
#ifndef _VIRT_VIEWER_DISPLAY_H
#define _VIRT_VIEWER_DISPLAY_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define VIRT_VIEWER_TYPE_DISPLAY virt_viewer_display_get_type()

#define VIRT_VIEWER_DISPLAY(obj)					\
	(G_TYPE_CHECK_INSTANCE_CAST ((obj), VIRT_VIEWER_TYPE_DISPLAY, VirtViewerDisplay))

#define VIRT_VIEWER_DISPLAY_CLASS(klass)				\
	(G_TYPE_CHECK_CLASS_CAST ((klass), VIRT_VIEWER_TYPE_DISPLAY, VirtViewerDisplayClass))

#define VIRT_VIEWER_IS_DISPLAY(obj)                                     \
	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), VIRT_VIEWER_TYPE_DISPLAY))

#define VIRT_VIEWER_IS_DISPLAY_CLASS(klass)                             \
	(G_TYPE_CHECK_CLASS_TYPE ((klass), VIRT_VIEWER_TYPE_DISPLAY))

#define VIRT_VIEWER_DISPLAY_GET_CLASS(obj)				\
	(G_TYPE_INSTANCE_GET_CLASS ((obj), VIRT_VIEWER_TYPE_DISPLAY, VirtViewerDisplayClass))

typedef struct _VirtViewerDisplay       VirtViewerDisplay;
typedef struct _VirtViewerDisplayClass  VirtViewerDisplayClass;
typedef struct _VirtViewerDisplayPrivate VirtViewerDisplayPrivate;

typedef struct _VirtViewerDisplayChannel VirtViewerDisplayChannel;


/* perhaps this become an interface, and be pushed in gtkvnc and spice? */
struct _VirtViewerDisplay {
	GtkBin parent;

	VirtViewerDisplayPrivate *priv;
};

struct _VirtViewerDisplayClass {
	GtkBinClass parent_class;

	/* virtual methods */
	void (* close) (VirtViewerDisplay* display);
	void (* send_keys) (VirtViewerDisplay* display,
			    const guint *keyvals, int nkeyvals);
	GdkPixbuf* (* get_pixbuf) (VirtViewerDisplay* display);
	gboolean (* open_fd) (VirtViewerDisplay* display, int fd);
	gboolean (* open_host) (VirtViewerDisplay* display, char *host, char *port);
	gboolean (* channel_open_fd) (VirtViewerDisplay* display, VirtViewerDisplayChannel *channel, int fd);

	/* signals */
	void (*display_connected)(VirtViewerDisplay *display);
	void (*display_initialized)(VirtViewerDisplay *display);
	void (*display_disconnected)(VirtViewerDisplay *display);
	void (*display_auth_refused)(VirtViewerDisplay *display, const char *msg);
	void (*display_auth_failed)(VirtViewerDisplay *display, const char *msg);

	void (*display_channel_open)(VirtViewerDisplay *display, VirtViewerDisplayChannel *channel);

	void (*display_pointer_grab)(VirtViewerDisplay *display);
	void (*display_pointer_ungrab)(VirtViewerDisplay *display);
	void (*display_keyboard_grab)(VirtViewerDisplay *display);
	void (*display_keyboard_ungrab)(VirtViewerDisplay *display);

	void (*display_desktop_resize)(VirtViewerDisplay *display);

	void (*display_cut_text)(VirtViewerDisplay *display, const char *str);
	void (*display_bell)(VirtViewerDisplay *display);
};

GType virt_viewer_display_get_type(void);

GtkWidget *virt_viewer_display_new(void);

void virt_viewer_display_set_desktop_size(VirtViewerDisplay *display,
					  guint width,
					  guint height);

void virt_viewer_display_get_desktop_size(VirtViewerDisplay *display,
					  guint *width,
					  guint *height);

void virt_viewer_display_set_zoom_level(VirtViewerDisplay *display,
					guint zoom);
void virt_viewer_display_set_zoom(VirtViewerDisplay *display,
				  gboolean zoom);


void virt_viewer_display_close(VirtViewerDisplay* display);
void virt_viewer_display_send_keys(VirtViewerDisplay* display,
				   const guint *keyvals, int nkeyvals);
GdkPixbuf* virt_viewer_display_get_pixbuf(VirtViewerDisplay* display);
gboolean virt_viewer_display_open_fd(VirtViewerDisplay* display, int fd);
gboolean virt_viewer_display_open_host(VirtViewerDisplay* display, char *host, char *port);
GObject* virt_viewer_display_get(VirtViewerDisplay* display);
gboolean virt_viewer_display_channel_open_fd(VirtViewerDisplay* display,
					     VirtViewerDisplayChannel* channel, int fd);

G_END_DECLS

#endif /* _VIRT_VIEWER_DISPLAY_H */
/*
 * Local variables:
 *  c-indent-level: 8
 *  c-basic-offset: 8
 *  tab-width: 8
 * End:
 */
