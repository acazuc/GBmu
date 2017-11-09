#ifndef DISPLAY_H
# define DISPLAY_H

# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <epoxy/gl.h>
# include <epoxy/glx.h>
//# include <GL/gl.h>
//# include <GL/glext.h>
# include <cstdint>

class MainDisplay
{

	private:
		GtkWidget *window;
		GtkWidget *gl;
		uint8_t *texDatas;
		GLuint texCoords;
		GLuint vertexes;

	public:
		MainDisplay();
		~MainDisplay();
		void iter();
		void putPixel(int32_t x, int32_t y, int32_t color);
		inline GLuint &getTexCoords() {return (this->texCoords);};
		inline GLuint &getVertexes() {return (this->vertexes);};

};

#endif
