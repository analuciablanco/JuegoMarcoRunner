// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

#pragma region Declaración de variables.
GLFWwindow *window;

GLdouble xMarcos = -0.8f;
GLdouble yMarcos = -0.6f;
GLdouble velocidadMarcos = 1.0f;

GLdouble velocidad = 1.5f;
GLdouble velocidadEnemigo = 0.8f;
GLfloat velocidadActual = -0.6f;

GLdouble tiempoAnterior = 0.0;
GLdouble tiempoActual = 0.0;
GLdouble tiempoDiferencial = 0.0;

bool reinicio = false;
int contadorbrincos = 0;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionBolita = Direccion::Izquierda;
Direccion direccionBolita2 = Direccion::Arriba;
#pragma endregion

#pragma region Escenario.
void sueloVerde() {
	glBegin(GL_POLYGON);
	glColor3f(0.035, 0.57, 0.26);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void sueloDesierto() {
	glBegin(GL_POLYGON);

	glColor3f(0.82, 0.58, 0.17);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void sueloNevado() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void dibujarEscenarioDia() {
	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.05f, 0.88f, 0.92f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//sol
	glBegin(GL_POLYGON);
	glColor3f(1, .8, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) - 0.7, 0.3* sin((double)i*3.14159 / 180.0) + 0.6, 0.3);
	}
	glEnd();

	//Nubes
	glBegin(GL_POLYGON);
	glColor3f(.85, .82, .82);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.15, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.2, 0.1* sin((double)i*3.14159 / 180.0) + 0.5, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.2, 0.1* sin((double)i*3.14159 / 180.0) + 0.7, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.4, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	glEnd();

}

void dibujarEscenarioTarde() {
	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.92f, 0.49f, 0.11f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//sol
	glBegin(GL_POLYGON);
	glColor3f(1, .8, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) - 0.7, 0.3* sin((double)i*3.14159 / 180.0) + 0.6, 0.3);
	}
	glEnd();

}

void dibujarEscenarioNoche() {

	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.04f, 0.08f, 0.15f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//Luna
	glBegin(GL_POLYGON);
	glColor3f(0.89f, .90f, 0.92f);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.25*cos((double)i*3.14159 / 180.0) - 0.7, 0.3* sin((double)i*3.14159 / 180.0) + 0.6, 0.3);
	}
	glEnd();

	//Estrellas
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.3f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.68f, 0.0f);
	glVertex3f(-0.32f, 0.68f, 0.0f);
	glVertex3f(-0.32f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.7f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.2f, 0.75f, 0.0f);
	glVertex3f(0.2f, 0.73f, 0.0f);
	glVertex3f(0.22f, 0.73f, 0.0f);
	glVertex3f(0.22f, 0.75f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.8f, 0.75f, 1.0f);
	glVertex3f(0.8f, 0.73f, 1.0f);
	glVertex3f(0.78f, 0.73f, 1.0f);
	glVertex3f(0.78f, 0.75f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.3f, 1.0f);
	glVertex3f(0.0f, 0.28f, 1.0f);
	glVertex3f(0.02f, 0.28f, 1.0f);
	glVertex3f(0.02f, 0.3f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.3f, 1.0f);
	glVertex3f(0.5f, 0.28f, 1.0f);
	glVertex3f(0.48f, 0.28f, 1.0f);
	glVertex3f(0.48f, 0.3f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.8f, 0.0f, 1.0f);
	glVertex3f(-0.8f, -0.02f, 1.0f);
	glVertex3f(-0.78f, -0.02f, 1.0f);
	glVertex3f(-0.78f, 0.0f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.4f, -0.05f, 1.0f);
	glVertex3f(-0.4f, -0.03f, 1.0f);
	glVertex3f(-0.38f, -0.03f, 1.0f);
	glVertex3f(-0.38f, -0.05f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.2f, -0.07f, 1.0f);
	glVertex3f(0.2f, -0.09f, 1.0f);
	glVertex3f(0.22f, -0.09f, 1.0f);
	glVertex3f(0.22f, -0.07f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.7f, -0.05f, 1.0f);
	glVertex3f(0.7f, -0.07f, 1.0f);
	glVertex3f(0.72f, -0.07f, 1.0f);
	glVertex3f(0.72f, -0.05f, 1.0f);
	glEnd();
}
#pragma endregion

void dibujarMarco() {
	glPushMatrix();
	glTranslatef(xMarcos, yMarcos, 0.0f);
	glScalef(0.6f, 0.6f, 0.0f);
	glPointSize(10.5);
	glBegin(GL_POINTS);
	//Pierna izquierda
	glColor3f(1.0f, 0.8f, 0.6f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.02f, 0.0f);
	glVertex2f(0.02f, 0.0f);
	glVertex2f(0.02f, 0.02f);
	glVertex2f(0.04f, 0.02f);
	glVertex2f(0.04f, 0.00f);
	glVertex2f(0.00f, 0.02f);
	glVertex2f(0.00f, 0.04f);
	glVertex2f(0.02f, 0.04f);

	//Patineta
	glColor3f(0.0f, 0.53f, 1.0f);
	glVertex2f(-0.08f, 0.0f);
	glVertex2f(-0.06f, -0.02f);
	glVertex2f(-0.04f, -0.02f);
	glVertex2f(-0.02f, -0.02f);
	glVertex2f(0.0f, -0.02f);
	glVertex2f(0.02f, -0.02f);
	glVertex2f(0.04f, -0.02f);
	glVertex2f(0.06f, -0.02f);
	glVertex2f(0.08f, -0.02f);
	glVertex2f(0.1f, -0.02f);
	glVertex2f(0.12f, -0.02f);
	glVertex2f(0.14f, -0.02f);
	glVertex2f(0.16f, -0.02f);
	glVertex2f(0.18f, -0.02f);
	glVertex2f(0.2f, -0.02f);
	glVertex2f(0.22f, -0.02f);
	glVertex2f(0.24f, -0.02f);
	glVertex2f(0.26f, -0.02f);
	glVertex2f(0.28f, -0.02f);
	glVertex2f(0.3f, 0.0f);
	//Ruedas
	glColor3f(0.20f, 0.7f, 0.85f);
	glVertex2f(0.18f, -0.04f);
	glVertex2f(0.2f, -0.04f);
	glVertex2f(0.2f, -0.06f);
	glVertex2f(0.18f, -0.06f);

	glVertex2f(0.0f, -0.04f);
	glVertex2f(0.02f, -0.04f);
	glVertex2f(0.02f, -0.06f);
	glVertex2f(0.0f, -0.06f);

	//Pantalon
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.04f, 0.04f);
	glVertex2f(0.04f, 0.06f);
	glVertex2f(0.02f, 0.06f);
	glVertex2f(0.00f, 0.06f);
	glVertex2f(0.00f, 0.08f);
	glVertex2f(0.02f, 0.08f);
	glVertex2f(0.04f, 0.08f);
	glVertex2f(0.02f, 0.1f);
	glVertex2f(0.04f, 0.1f);

	glVertex2f(0.06f, 0.1f);
	glVertex2f(0.08f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, 0.08f);
	glVertex2f(0.12f, 0.08f);
	glVertex2f(0.14f, 0.08f);
	glVertex2f(0.16f, 0.1f);
	glVertex2f(0.18f, 0.12f);
	glVertex2f(0.2f, 0.12f);
	glVertex2f(0.22f, 0.1f);
	glVertex2f(0.24f, 0.08f);
	glVertex2f(0.22f, 0.12f);
	glVertex2f(0.22f, 0.14f);
	glVertex2f(0.2f, 0.14f);
	glVertex2f(0.18f, 0.14f);
	glVertex2f(0.16f, 0.14f);
	glVertex2f(0.16f, 0.12f);
	glVertex2f(0.14f, 0.1f);
	glVertex2f(0.12f, 0.1f);
	glVertex2f(0.14f, 0.12f);
	glVertex2f(0.12f, 0.12f);
	glVertex2f(0.1f, 0.12f);
	glVertex2f(0.08f, 0.12f);
	glVertex2f(0.06f, 0.12f);
	glVertex2f(0.04f, 0.12f);
	glVertex2f(0.02f, 0.12f);
	glVertex2f(0.02f, 0.14f);
	glVertex2f(0.04f, 0.14f);
	glVertex2f(0.06f, 0.14f);
	glVertex2f(0.08f, 0.14f);
	glVertex2f(0.1f, 0.14f);
	glVertex2f(0.12f, 0.14f);
	glVertex2f(0.14f, 0.14f);
	glVertex2f(0.1f, 0.16f);
	glVertex2f(0.08f, 0.16f);
	glVertex2f(0.06f, 0.16f);
	glVertex2f(0.04f, 0.16f);
	glVertex2f(0.22f, 0.08f);
	glVertex2f(0.2f, 0.08f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.18f, 0.1f);
	glVertex2f(0.18f, 0.1f);
	glVertex2f(0.18f, 0.08f);
	glVertex2f(0.16f, 0.08f);
	glVertex2f(0.16f, 0.06f);
	glVertex2f(0.18f, 0.06f);
	glVertex2f(0.2f, 0.06f);
	glVertex2f(0.22f, 0.06f);
	glVertex2f(0.22f, 0.04f);
	glVertex2f(0.2f, 0.04f);
	glVertex2f(0.18f, 0.04f);
	glVertex2f(0.16f, 0.04f);
	glVertex2f(0.16f, 0.02f);

	glColor3f(1.0f, 0.8f, 0.7f);
	glVertex2f(0.18f, 0.02f);
	glVertex2f(0.2f, 0.02f);
	glVertex2f(0.22f, 0.02f);
	glVertex2f(0.24f, 0.02f);
	glVertex2f(0.24f, 0.00f);
	glVertex2f(0.22f, 0.00f);
	glVertex2f(0.2f, 0.00f);
	glVertex2f(0.18f, 0.00f);
	glVertex2f(0.16f, 0.00f);

	glVertex2f(0.04f, 0.18f);
	glVertex2f(0.06f, 0.18f);
	glVertex2f(0.08f, 0.18f);
	glVertex2f(0.1f, 0.18f);
	glVertex2f(0.12f, 0.18f);
	glVertex2f(0.12f, 0.16f);
	glVertex2f(0.14f, 0.16f);
	glVertex2f(0.16f, 0.16f);
	glVertex2f(0.18f, 0.16f);
	glVertex2f(0.2f, 0.16f);
	glVertex2f(0.2f, 0.18f);
	glVertex2f(0.18f, 0.18f);
	glVertex2f(0.16f, 0.18f);
	glVertex2f(0.14f, 0.18f);
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.18f, 0.2f);
	glVertex2f(0.16f, 0.2f);
	glVertex2f(0.14f, 0.2f);
	glVertex2f(0.12f, 0.2f);
	glVertex2f(0.1f, 0.2f);
	glVertex2f(0.08f, 0.2f);
	glVertex2f(0.06f, 0.2f);
	glVertex2f(0.04f, 0.2f);
	glVertex2f(0.04f, 0.22f);
	glVertex2f(0.06f, 0.22f);
	glVertex2f(0.08f, 0.22f);
	glVertex2f(0.1f, 0.22f);
	glVertex2f(0.12f, 0.22f);
	glVertex2f(0.14f, 0.22f);
	glVertex2f(0.16f, 0.22f);
	glVertex2f(0.18f, 0.22f);
	glVertex2f(0.2f, 0.22f);
	glVertex2f(0.22f, 0.22f);
	glVertex2f(0.24f, 0.22f);
	glVertex2f(0.26f, 0.2f);
	glVertex2f(0.28f, 0.2f);
	glVertex2f(0.3f, 0.18f);
	glVertex2f(0.3f, 0.2f);
	glVertex2f(0.3f, 0.22f);
	glVertex2f(0.32f, 0.22f);
	glVertex2f(0.28f, 0.22f);
	glVertex2f(0.26f, 0.22f);
	glVertex2f(0.3f, 0.24f);
	glVertex2f(0.28f, 0.24f);
	glVertex2f(0.26f, 0.24f);
	glVertex2f(0.24f, 0.24f);
	glVertex2f(0.22f, 0.24f);
	glVertex2f(0.2f, 0.24f);
	glVertex2f(0.2f, 0.26f);
	glVertex2f(0.22f, 0.26f);
	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.26f, 0.26f);
	glVertex2f(0.32f, 0.2f);
	glVertex2f(0.32f, 0.22f);

	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.24f, 0.24f);
	glVertex2f(0.22f, 0.24f);
	glVertex2f(0.2f, 0.24f);
	glVertex2f(0.18f, 0.24f);
	glVertex2f(0.16f, 0.24f);
	glVertex2f(0.14f, 0.24f);
	glVertex2f(0.12f, 0.24f);
	glVertex2f(0.1f, 0.24f);
	glVertex2f(0.08f, 0.24f);
	glVertex2f(0.06f, 0.24f);
	glVertex2f(0.04f, 0.24f);
	glVertex2f(0.18f, 0.26f);
	glVertex2f(0.16f, 0.26f);
	glVertex2f(0.14f, 0.26f);
	glVertex2f(0.12f, 0.26f);
	glVertex2f(0.1f, 0.26f);
	glVertex2f(0.08f, 0.26f);
	glVertex2f(0.06f, 0.26f);
	glVertex2f(0.04f, 0.26f);

	glVertex2f(0.02f, 0.26f);
	glVertex2f(0.00f, 0.26f);
	glVertex2f(-0.02f, 0.24f);
	glVertex2f(-0.04f, 0.24f);
	glVertex2f(-0.04f, 0.22f);
	glVertex2f(-0.04f, 0.2f);
	glVertex2f(-0.06f, 0.2f);
	glVertex2f(-0.04f, 0.18f);
	glVertex2f(-0.06f, 0.18f);
	glVertex2f(-0.08f, 0.18f);
	glVertex2f(-0.08f, 0.2f);
	glVertex2f(-0.06f, 0.22f);
	glVertex2f(-0.06f, 0.24f);
	glVertex2f(-0.06f, 0.26f);
	glVertex2f(-0.04f, 0.26f);
	glVertex2f(-0.02f, 0.26f);
	glVertex2f(-0.04f, 0.28f);
	glVertex2f(-0.02f, 0.28f);
	glVertex2f(0.0f, 0.28f);
	glVertex2f(-0.02f, 0.2f);

	glVertex2f(0.02f, 0.28f);
	glVertex2f(0.04f, 0.28f);
	glVertex2f(0.06f, 0.28f);
	glVertex2f(0.08f, 0.28f);
	glVertex2f(0.1f, 0.28f);
	glVertex2f(0.12f, 0.28f);
	glVertex2f(0.14f, 0.28f);
	glVertex2f(0.16f, 0.28f);
	glVertex2f(0.18f, 0.28f);
	glVertex2f(0.2f, 0.28f);
	glVertex2f(0.22f, 0.28f);

	glVertex2f(0.16f, 0.3f);
	glVertex2f(0.14f, 0.3f);
	glVertex2f(0.12f, 0.3f);
	glVertex2f(0.1f, 0.3f);
	glVertex2f(0.08f, 0.3f);

	glVertex2f(0.06f, 0.32f);
	glVertex2f(0.04f, 0.34f);
	glVertex2f(0.02f, 0.36f);
	glVertex2f(0.02f, 0.38f);
	glVertex2f(0.02f, 0.4f);
	glVertex2f(0.02f, 0.42f);
	glVertex2f(0.04f, 0.44f);
	glVertex2f(0.06f, 0.46f);
	glVertex2f(0.08f, 0.48f);
	glVertex2f(0.1f, 0.48f);
	glVertex2f(0.12f, 0.48f);
	glVertex2f(0.14f, 0.48f);
	glVertex2f(0.16f, 0.48f);
	glVertex2f(0.18f, 0.46f);
	glVertex2f(0.2f, 0.44f);
	glVertex2f(0.22f, 0.42f);
	glVertex2f(0.22f, 0.4f);
	glVertex2f(0.22f, 0.38f);
	glVertex2f(0.22f, 0.36f);
	glVertex2f(0.2f, 0.34f);
	glVertex2f(0.18f, 0.32f);

	glVertex2f(0.16f, 0.32f);
	glVertex2f(0.14f, 0.32f);
	glVertex2f(0.12f, 0.32f);
	glVertex2f(0.1f, 0.32f);
	glVertex2f(0.08f, 0.32f);
	glVertex2f(0.06f, 0.34f);
	glVertex2f(0.08f, 0.34f);
	glVertex2f(0.1f, 0.34f);
	glVertex2f(0.12f, 0.34f);
	glVertex2f(0.14f, 0.34f);
	glVertex2f(0.16f, 0.34f);
	glVertex2f(0.18f, 0.34f);
	glVertex2f(0.04f, 0.36f);
	glVertex2f(0.06f, 0.36f);
	glVertex2f(0.08f, 0.36f);
	glVertex2f(0.1f, 0.36f);
	glVertex2f(0.12f, 0.36f);
	glVertex2f(0.14f, 0.36f);
	glVertex2f(0.16f, 0.36f);
	glVertex2f(0.18f, 0.36f);
	glVertex2f(0.2f, 0.36f);
	glVertex2f(0.04f, 0.38f);
	glVertex2f(0.06f, 0.38f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.1f, 0.38f);
	glVertex2f(0.12f, 0.38f);
	glVertex2f(0.14f, 0.38f);
	glVertex2f(0.16f, 0.38f);
	glVertex2f(0.18f, 0.38f);
	glVertex2f(0.2f, 0.38f);
	glVertex2f(0.04f, 0.4f);
	glVertex2f(0.06f, 0.4f);
	glVertex2f(0.08f, 0.4f);
	glVertex2f(0.1f, 0.4f);
	glVertex2f(0.12f, 0.4f);
	glVertex2f(0.14f, 0.4f);
	glVertex2f(0.16f, 0.4f);
	glVertex2f(0.18f, 0.4f);
	glVertex2f(0.2f, 0.4f);
	glVertex2f(0.04f, 0.42f);
	glVertex2f(0.06f, 0.42f);
	glVertex2f(0.08f, 0.42f);
	glVertex2f(0.1f, 0.42f);
	glVertex2f(0.12f, 0.42f);
	glVertex2f(0.14f, 0.42f);
	glVertex2f(0.16f, 0.42f);
	glVertex2f(0.18f, 0.42f);
	glVertex2f(0.2f, 0.42f);

	glVertex2f(0.06f, 0.44f);
	glVertex2f(0.08f, 0.44f);
	glVertex2f(0.1f, 0.44f);
	glVertex2f(0.12f, 0.44f);
	glVertex2f(0.14f, 0.44f);
	glVertex2f(0.16f, 0.44f);
	glVertex2f(0.18f, 0.44f);
	glVertex2f(0.16f, 0.46f);
	glVertex2f(0.14f, 0.46f);
	glVertex2f(0.12f, 0.46f);
	glVertex2f(0.1f, 0.46f);
	glVertex2f(0.08f, 0.46f);

	glEnd();

	glPopMatrix();
}

void dibujarElementos() {

	// Cuadro pilar
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-.05f, -.2f, 0);
	glVertex3f(-.25f, -.2f, 0);
	glVertex3f(-.25f, -.6f, 0);
	glVertex3f(-.05f, -.6f, 0);
	glEnd();
}

/* void checarColision() {

	if (xEnemigo < xMarcos + 0.4 &&
		xEnemigo > xMarcos - 0.16 &&
		yEnemigo < yMarcos + 0.6 &&
		yEnemigo > yMarcos - 0.2) {

		gEnemigo = 0.0;
		bEnemigo = 0.0;
	}

	else {
		gEnemigo = 1.0;
		bEnemigo = 1.0;
	}
} */

/* void moverObjetos() {
	if (xEnemigo > -1.2) {
		xEnemigo -= velocidadEnemigo * tiempoDiferencial;
	}




} */

void saltoMarcos() {
	int estadoTeclaArribaMarco = glfwGetKey(window, GLFW_KEY_UP);

	if ((estadoTeclaArribaMarco == GLFW_PRESS || estadoTeclaArribaMarco == GLFW_REPEAT) && contadorbrincos == 0 && (yMarcos >= -0.6f && yMarcos <= 0.0f))
	{
		if(yMarcos <= 0.0f)
		{
			yMarcos += (velocidadMarcos * tiempoDiferencial)*2;
		}
		if (yMarcos >= 0.0f)
		{
			yMarcos = 0.0f;
			contadorbrincos = 1;
		}			

	}
	else
		if (estadoTeclaArribaMarco == GLFW_RELEASE)
		{
			contadorbrincos = 1;
		}
		if (contadorbrincos == 1)
		{
			if (yMarcos >= -0.6f)
			{
				yMarcos -= velocidad * tiempoDiferencial;
			}
			if(yMarcos <= -0.6f)
			{
				yMarcos = -0.6f;
				contadorbrincos = 0;
			}
		}
	/*
	int estadoTeclaAbajoMarco = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoTeclaAbajoMarco == GLFW_PRESS)
	{
		yMarcos -= velocidadMarcos * tiempoDiferencial;
	}

	*/
}

/* void teclado_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		for (int i = 1; i <= 50; i++)
		{
			yMarcos += velocidad * tiempoDiferencial;
		}
	}
} */

void dibujar() {
	dibujarEscenarioDia();
	// dibujarEscenarioTarde();
	// dibujarEscenarioNoche();
	sueloVerde();
	// sueloDesierto();
	// sueloNevado();
	dibujarElementos();
	dibujarMarco();
}

void actualizar() {

	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;

	tiempoAnterior = tiempoActual;

	//moverObjetos();
	//checarColision();
	saltoMarcos();

	/* if (xEnemigo > 1.1f) {
		xEnemigo -= 2;
	}

	else if (xEnemigo < -1.1f) {
		xEnemigo += 2;
	} */
}

int main()
{

	//Si no se puede inicializar glfw
	//Iniciamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamosla ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	//Si nopodemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	//glfwSetKeyCallback(window, teclado_callback);
	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//ciclode dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(1, 1, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}