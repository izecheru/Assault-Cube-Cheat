#pragma once
#include<GLFW/glfw3.h>

namespace GL
{
	void SetupOrtho()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		GLint viewport[4]; // x and y as well as width and height
		glGetIntegerv(GL_VIEWPORT, viewport);
		glViewport(0, 0, viewport[2], viewport[3]); //(top left x, top left y, width, height)
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST); // so what we draw is in front and not the back
	}

	void RestoreGL()
	{
		// reverse all thins done in setup
		glPopMatrix();
		glPopAttrib();
	}

	const GLubyte green[3] = { 0,255,0 };
	void DrawOutLine(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		glColor3ub(color[0], color[1], color[2]);
		glVertex2f(x - 0.5f, y - 0.5f);
		glVertex2f(x + width + 0.5f, y + height + 0.5f);
		glVertex2f(x + width + 0.5f, y + height + 0.5f);
		glVertex2f(x - 0.5f, y + height + 0.5f);
		glVertex2f(x - 0.5f, y + height - 0.5f);
		glEnd();
	}
}