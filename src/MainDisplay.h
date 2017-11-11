#ifndef DISPLAY_H
# define DISPLAY_H

# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <epoxy/gl.h>
# include <epoxy/glx.h>
# include <cstdint>

class MainDisplay
{

	private:
		GtkWidget *window;
		GtkWidget *gl;
		uint8_t *texDatas;
		GLuint texCoordsLocation;
		GLuint vertexesLocation;
		GLuint textureLocation;
		GLuint MVPLocation;
		GLuint texCoords;
		GLuint vertexes;
		GLuint texture;

	public:
		MainDisplay();
		~MainDisplay();
		void iter();
		void putPixel(int32_t x, int32_t y, int32_t color);
		inline GLuint &getTexCoordsLocation() {return (this->texCoordsLocation);};
		inline GLuint &getVertexesLocation() {return (this->vertexesLocation);};
		inline GLuint &getTextureLocation() {return (this->textureLocation);};
		inline GLuint &getMVPLocation() {return (this->MVPLocation);};
		inline GLuint &getTexCoords() {return (this->texCoords);};
		inline GLuint &getVertexes() {return (this->vertexes);};
		inline GLuint &getTexture() {return (this->texture);};

};

#endif
